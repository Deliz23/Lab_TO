#include "CsvRepositorioAdapter.h"
#include "ActividadFactory.h"
#include <stdexcept>

CsvRepositorioAdapter::CsvRepositorioAdapter(IRepositorio& repositorioDestino)
    : m_destino(repositorioDestino) {}

QString CsvRepositorioAdapter::traducirCodigoTipo(const QString& codigoLegacy) {
    const QString cod = codigoLegacy.trimmed().toUpper();
    if (cod == "TAR") return "Tarea";
    if (cod == "EXA") return "Examen";
    if (cod == "PRO") return "Proyecto";
    throw std::invalid_argument("Código legacy desconocido en CSV: " + cod.toStdString());
}

void CsvRepositorioAdapter::importarDesdeCsv(const QString& rutaArchivo) {
    const auto filas = m_lectorLegacy.leerFilasCrudas(rutaArchivo);

    for (const auto& cols : filas) {
        if (cols.size() < 4) {
            throw std::runtime_error("Registro CSV incompleto (se esperaban 4 columnas).");
        }

        DatosActividad datos{
            .tipo = traducirCodigoTipo(cols[0]),
            .titulo = cols[1].trimmed(),
            .fechaEntrega = QDate::fromString(cols[2].trimmed(), Qt::ISODate),
            .extra = cols[3].trimmed()
        };

        auto fabrica = ActividadFactory::obtenerFabrica(datos.tipo);
        m_destino.agregar(fabrica->crear(datos));
    }
}

void CsvRepositorioAdapter::agregar(std::unique_ptr<Actividad> actividad) {
    m_destino.agregar(std::move(actividad));
}

const std::vector<std::unique_ptr<Actividad>>& CsvRepositorioAdapter::listar() const {
    return m_destino.listar();
}

void CsvRepositorioAdapter::limpiar() {
    m_destino.limpiar();
}
