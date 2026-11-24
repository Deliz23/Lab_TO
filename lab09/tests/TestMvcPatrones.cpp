#include <QtTest/QtTest>
#include <QSignalSpy>
#include <QTemporaryFile>
#include <QTextStream>

#include "model/RepositorioActividades.h"
#include "patterns/ActividadFactory.h"
#include "patterns/CsvRepositorioAdapter.h"
#include "controller/ActividadController.h"

class TestMvcPatrones : public QObject {
    Q_OBJECT

private slots:
    void testFactoryMethodValidoEInvalido() {
        auto fabExamen = ActividadFactory::obtenerFabrica("Examen");
        DatosActividad ok{"Examen", "Parcial 3", QDate(2026, 12, 5), "25.0"};
        auto examen = fabExamen->crear(ok);

        QCOMPARE(examen->tipo(), QString("Examen"));
        QCOMPARE(examen->resumenDetalle(), QString("Peso: 25.0%"));

        DatosActividad invalido{"Examen", "Parcial 3", QDate(2026, 12, 5), "-10"};
        QVERIFY_EXCEPTION_THROWN(fabExamen->crear(invalido), std::invalid_argument);
    }

    void testAdapterImportaCsvLegacy() {
        QTemporaryFile csvTemp;
        QVERIFY(csvTemp.open());
        QTextStream out(&csvTemp);
        out << "COD_TIPO;NOMBRE_ACT;FECHA_LIM;DETALLE_EXTRA\n";
        out << "TAR;Practica 9;2026-11-28;TO\n";
        out << "PRO;App Qt;2026-12-10;Grupo 1\n";
        out.flush();

        RepositorioActividades repo;
        CsvRepositorioAdapter adapter(repo);
        adapter.importarDesdeCsv(csvTemp.fileName());

        QCOMPARE(repo.listar().size(), 2u);
        QCOMPARE(repo.listar()[0]->tipo(), QString("Tarea"));
        QCOMPARE(repo.listar()[1]->tipo(), QString("Proyecto"));
    }

    void testControllerEmiteSenalesSinGui() {
        RepositorioActividades repo;
        CsvRepositorioAdapter adapter(repo);
        ActividadController controller(adapter);

        QSignalSpy spyOk(&controller, &ActividadController::listaActualizada);
        QSignalSpy spyErr(&controller, &ActividadController::operacionFallida);

        controller.registrarActividad("Tarea", "Guia Lab 09", QDate(2026, 11, 25), "EPIS");
        QCOMPARE(spyOk.count(), 1);
        QCOMPARE(spyErr.count(), 0);
        QCOMPARE(controller.obtenerLista().size(), 1u);

        // Título vacío debe disparar operacionFallida
        controller.registrarActividad("Tarea", "   ", QDate(2026, 11, 25), "EPIS");
        QCOMPARE(spyErr.count(), 1);
    }
};

QTEST_MAIN(TestMvcPatrones)
#include "TestMvcPatrones.moc"
