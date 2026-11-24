#pragma once

#include "IRepositorio.h"

class RepositorioActividades : public IRepositorio {
public:
    void agregar(std::unique_ptr<Actividad> actividad) override;
    const std::vector<std::unique_ptr<Actividad>>& listar() const override;
    void limpiar() override;

private:
    std::vector<std::unique_ptr<Actividad>> m_actividades;
};
