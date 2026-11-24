#include "LegacyCsvReader.h"
#include <QFile>
#include <QTextStream>
#include <stdexcept>

std::vector<QStringList> LegacyCsvReader::leerFilasCrudas(const QString& rutaArchivo) const {
    QFile archivo(rutaArchivo);
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw std::runtime_error("No se pudo abrir el archivo CSV heredado.");
    }

    std::vector<QStringList> filas;
    QTextStream in(&archivo);
    bool primeraLinea = true;

    while (!in.atEnd()) {
        QString linea = in.readLine().trimmed();
        if (linea.isEmpty()) continue;

        if (primeraLinea) { // Omitir cabecera legacy
            primeraLinea = false;
            continue;
        }
        filas.push_back(linea.split(';'));
    }
    return filas;
}
