#pragma once

#include "controller/ActividadController.h"
#include <QMainWindow>
#include <QComboBox>
#include <QLineEdit>
#include <QDateEdit>
#include <QTableWidget>
#include <QLabel>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(ActividadController& controller, QWidget* parent = nullptr);

private slots:
    void onAgregarClicked();
    void onImportarCsvClicked();
    void onTipoCambiado(const QString& tipo);
    void refrescarTabla();
    void mostrarError(const QString& mensaje);

private:
    void configurarInterfaz();

    ActividadController& m_controller;
    QComboBox* m_comboTipo{nullptr};
    QLineEdit* m_txtTitulo{nullptr};
    QDateEdit* m_dateEntrega{nullptr};
    QLabel* m_lblExtra{nullptr};
    QLineEdit* m_txtExtra{nullptr};
    QTableWidget* m_tabla{nullptr};
};
