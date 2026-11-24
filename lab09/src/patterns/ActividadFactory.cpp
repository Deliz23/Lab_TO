#include "ActividadFactory.h"
#include <stdexcept>

void ActividadFactory::validarComun(const DatosActividad& datos) {
    if (datos.titulo.trimmed().isEmpty()) {
        throw std::invalid_argument("El título de la actividad no puede estar vacío.");
    }
    if (!datos.fechaEntrega.isValid()) {
        throw std::invalid_argument("La fecha de entrega no es válida.");
    }
}

std::unique_ptr<ActividadFactory> ActividadFactory::obtenerFabrica(const QString& tipo) {
    const QString normalizado = tipo.trimmed().toLower();
    if (normalizado == "tarea") {
        return std::make_unique<TareaFactory>();
    }
    if (normalizado == "examen") {
        return std::make_unique<ExamenFactory>();
    }
    if (normalizado == "proyecto") {
        return std::make_unique<ProyectoFactory>();
    }
    throw std::invalid_argument("Tipo de actividad no soportado: " + tipo.toStdString());
}

std::unique_ptr<Actividad> TareaFactory::crear(const DatosActividad& datos) const {
    validarComun(datos);
    QString curso = datos.extra.trimmed().isEmpty() ? "General" : datos.extra.trimmed();
    return std::make_unique<Tarea>(datos.titulo.trimmed(), datos.fechaEntrega, curso);
}

std::unique_ptr<Actividad> ExamenFactory::crear(const DatosActividad& datos) const {
    validarComun(datos);
    bool ok = false;
    double peso = datos.extra.trimmed().toDouble(&ok);
    if (!ok || peso <= 0.0 || peso > 100.0) {
        throw std::invalid_argument("El examen requiere un peso numérico válido entre 1 y 100.");
    }
    return std::make_unique<Examen>(datos.titulo.trimmed(), datos.fechaEntrega, peso);
}

std::unique_ptr<Actividad> ProyectoFactory::crear(const DatosActividad& datos) const {
    validarComun(datos);
    if (datos.extra.trimmed().isEmpty()) {
        throw std::invalid_argument("El proyecto requiere especificar el nombre del equipo.");
    }
    return std::make_unique<Proyecto>(datos.titulo.trimmed(), datos.fechaEntrega, datos.extra.trimmed());
}
