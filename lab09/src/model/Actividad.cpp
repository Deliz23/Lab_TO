#include "Actividad.h"
#include <utility>

Actividad::Actividad(QString titulo, QDate fechaEntrega)
    : m_titulo(std::move(titulo)), m_fechaEntrega(fechaEntrega) {}

QString Actividad::titulo() const { return m_titulo; }
QDate Actividad::fechaEntrega() const { return m_fechaEntrega; }

// --- Tarea ---
Tarea::Tarea(QString titulo, QDate fechaEntrega, QString curso)
    : Actividad(std::move(titulo), fechaEntrega), m_curso(std::move(curso)) {}

QString Tarea::tipo() const { return "Tarea"; }
QString Tarea::resumenDetalle() const { return "Curso: " + m_curso; }

// --- Examen ---
Examen::Examen(QString titulo, QDate fechaEntrega, double pesoPorcentual)
    : Actividad(std::move(titulo), fechaEntrega), m_pesoPorcentual(pesoPorcentual) {}

QString Examen::tipo() const { return "Examen"; }
QString Examen::resumenDetalle() const {
    return QString("Peso: %1%").arg(m_pesoPorcentual, 0, 'f', 1);
}

// --- Proyecto ---
Proyecto::Proyecto(QString titulo, QDate fechaEntrega, QString equipo)
    : Actividad(std::move(titulo), fechaEntrega), m_equipo(std::move(equipo)) {}

QString Proyecto::tipo() const { return "Proyecto"; }
QString Proyecto::resumenDetalle() const { return "Equipo: " + m_equipo; }
