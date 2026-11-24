#pragma once

#include "model/Actividad.h"
#include <memory>

class ActividadFactory {
public:
    virtual ~ActividadFactory() = default;
    virtual std::unique_ptr<Actividad> crear(const DatosActividad& datos) const = 0;

    // Método selector conveniente para desacoplar al cliente de fábricas concretas
    static std::unique_ptr<ActividadFactory> obtenerFabrica(const QString& tipo);

protected:
    static void validarComun(const DatosActividad& datos);
};

class TareaFactory final : public ActividadFactory {
public:
    std::unique_ptr<Actividad> crear(const DatosActividad& datos) const override;
};

class ExamenFactory final : public ActividadFactory {
public:
    std::unique_ptr<Actividad> crear(const DatosActividad& datos) const override;
};

class ProyectoFactory final : public ActividadFactory {
public:
    std::unique_ptr<Actividad> crear(const DatosActividad& datos) const override;
};
