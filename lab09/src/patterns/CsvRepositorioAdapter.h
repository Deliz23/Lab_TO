#pragma once

#include "model/IRepositorio.h"
#include "LegacyCsvReader.h"
#include <QString>

class CsvRepositorioAdapter : public IRepositorio {
public:
    explicit CsvRepositorioAdapter(IRepositorio& repositorioDestino);

    void importarDesdeCsv(const QString& rutaArchivo);

    // Delegación estándar de IRepositorio
    void agregar(std::unique_ptr<Actividad> actividad) override;
    const std::vector<std::unique_ptr<Actividad>>& listar() const override;
    void limpiar() override;

private:
    static QString traducirCodigoTipo(const QString& codigoLegacy);

    IRepositorio& m_destino;
    LegacyCsvReader m_lectorLegacy;
};
