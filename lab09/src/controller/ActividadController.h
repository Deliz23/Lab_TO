#pragma once

#include "model/Actividad.h"
#include "patterns/CsvRepositorioAdapter.h"
#include <QObject>
#include <QString>
#include <vector>

struct ActividadDTO {
    QString tipo;
    QString titulo;
    QString fecha;
    QString detalle;
};

class ActividadController : public QObject {
    Q_OBJECT
public:
    explicit ActividadController(CsvRepositorioAdapter& repositorioAdapter, QObject* parent = nullptr);

    std::vector<ActividadDTO> obtenerLista() const;

public slots:
    void registrarActividad(const QString& tipo, const QString& titulo, const QDate& fecha, const QString& extra);
    void cargarCsvLegacy(const QString& rutaArchivo);

signals:
    void listaActualizada();
    void operacionFallida(const QString& mensajeError);

private:
    CsvRepositorioAdapter& m_repositorio;
};
