#pragma once

#include <QString>
#include <QDate>

struct DatosActividad {
    QString tipo;       // "Tarea", "Examen", "Proyecto"
    QString titulo;
    QDate fechaEntrega;
    QString extra;      // Curso (Tarea), Peso (Examen) o Equipo (Proyecto)
};

class Actividad {
public:
    Actividad(QString titulo, QDate fechaEntrega);
    virtual ~Actividad() = default;

    QString titulo() const;
    QDate fechaEntrega() const;

    virtual QString tipo() const = 0;
    virtual QString resumenDetalle() const = 0;

protected:
    QString m_titulo;
    QDate m_fechaEntrega;
};

class Tarea final : public Actividad {
public:
    Tarea(QString titulo, QDate fechaEntrega, QString curso);
    QString tipo() const override;
    QString resumenDetalle() const override;

private:
    QString m_curso;
};

class Examen final : public Actividad {
public:
    Examen(QString titulo, QDate fechaEntrega, double pesoPorcentual);
    QString tipo() const override;
    QString resumenDetalle() const override;

private:
    double m_pesoPorcentual;
};

class Proyecto final : public Actividad {
public:
    Proyecto(QString titulo, QDate fechaEntrega, QString equipo);
    QString tipo() const override;
    QString resumenDetalle() const override;

private:
    QString m_equipo;
};
