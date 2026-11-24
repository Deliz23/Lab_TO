#include "ActividadController.h"
#include "patterns/ActividadFactory.h"
#include <exception>

ActividadController::ActividadController(CsvRepositorioAdapter& repositorioAdapter, QObject* parent)
    : QObject(parent), m_repositorio(repositorioAdapter) {}

void ActividadController::registrarActividad(const QString& tipo, const QString& titulo,
                                             const QDate& fecha, const QString& extra) {
    try {
        DatosActividad datos{tipo, titulo, fecha, extra};
        auto fabrica = ActividadFactory::obtenerFabrica(tipo);
        m_repositorio.agregar(fabrica->crear(datos));
        emit listaActualizada();
    } catch (const std::exception& ex) {
        emit operacionFallida(QString::fromUtf8(ex.what()));
    }
}

void ActividadController::cargarCsvLegacy(const QString& rutaArchivo) {
    try {
        m_repositorio.importarDesdeCsv(rutaArchivo);
        emit listaActualizada();
    } catch (const std::exception& ex) {
        emit operacionFallida(QString::fromUtf8(ex.what()));
    }
}

std::vector<ActividadDTO> ActividadController::obtenerLista() const {
    std::vector<ActividadDTO> resultado;
    for (const auto& act : m_repositorio.listar()) {
        resultado.push_back(ActividadDTO{
            .tipo = act->tipo(),
            .titulo = act->titulo(),
            .fecha = act->fechaEntrega().toString(Qt::ISODate),
            .detalle = act->resumenDetalle()
        });
    }
    return resultado;
}
