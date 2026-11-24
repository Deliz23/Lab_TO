#include "RepositorioActividades.h"
#include <stdexcept>

void RepositorioActividades::agregar(std::unique_ptr<Actividad> actividad) {
    if (!actividad) {
        throw std::invalid_argument("No se puede registrar una actividad nula.");
    }
    m_actividades.push_back(std::move(actividad));
}

const std::vector<std::unique_ptr<Actividad>>& RepositorioActividades::listar() const {
    return m_actividades;
}

void RepositorioActividades::limpiar() {
    m_actividades.clear();
}
