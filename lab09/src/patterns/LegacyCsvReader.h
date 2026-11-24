#pragma once

#include <QString>
#include <QStringList>
#include <vector>

// Componente heredado con interfaz incompatible con IRepositorio
class LegacyCsvReader {
public:
    std::vector<QStringList> leerFilasCrudas(const QString& rutaArchivo) const;
};
