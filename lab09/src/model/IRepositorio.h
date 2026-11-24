#pragma once

#include "Actividad.h"
#include <memory>
#include <vector>

class IRepositorio {
public:
    virtual ~IRepositorio() = default;
    virtual void agregar(std::unique_ptr<Actividad> actividad) = 0;
    virtual const std::vector<std::unique_ptr<Actividad>>& listar() const = 0;
    virtual void limpiar() = 0;
};
