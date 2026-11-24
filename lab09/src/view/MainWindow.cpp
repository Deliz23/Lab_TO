#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(ActividadController& controller, QWidget* parent)
    : QMainWindow(parent), m_controller(controller) {
    configurarInterfaz();

    // Conexiones MVC estrictas mediante Signals & Slots
    connect(&m_controller, &ActividadController::listaActualizada,
            this, &MainWindow::refrescarTabla);
    connect(&m_controller, &ActividadController::operacionFallida,
            this, &MainWindow::mostrarError);
}

void MainWindow::configurarInterfaz() {
    setWindowTitle("Seguimiento Académico - MVC + Factory Method + Adapter (Qt 6)");
    resize(760, 480);

    auto* central = new QWidget(this);
    auto* layoutPrincipal = new QVBoxLayout(central);

    // Formulario de registro
    auto* form = new QFormLayout();
    m_comboTipo = new QComboBox();
    m_comboTipo->addItems({"Tarea", "Examen", "Proyecto"});

    m_txtTitulo = new QLineEdit();
    m_txtTitulo->setPlaceholderText("Ej. Laboratorio 09 - Patrones");

    m_dateEntrega = new QDateEdit(QDate::currentDate());
    m_dateEntrega->setCalendarPopup(true);
    m_dateEntrega->setDisplayFormat("yyyy-MM-dd");

    m_lblExtra = new QLabel("Curso:");
    m_txtExtra = new QLineEdit();
    m_txtExtra->setPlaceholderText("Ej. Tecnología de Objetos");

    form->addRow("Tipo de actividad:", m_comboTipo);
    form->addRow("Título:", m_txtTitulo);
    form->addRow("Fecha de entrega:", m_dateEntrega);
    form->addRow(m_lblExtra, m_txtExtra);
    layoutPrincipal->addLayout(form);

    // Botones de acción
    auto* barraBotones = new QHBoxLayout();
    auto* btnAgregar = new QPushButton("Registrar Actividad");
    auto* btnImportar = new QPushButton("Importar CSV Heredado...");
    barraBotones->addWidget(btnAgregar);
    barraBotones->addWidget(btnImportar);
    layoutPrincipal->addLayout(barraBotones);

    // Tabla de visualización (solo lectura)
    m_tabla = new QTableWidget(0, 4);
    m_tabla->setHorizontalHeaderLabels({"Tipo", "Título", "Fecha", "Detalle"});
    m_tabla->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_tabla->setEditTriggers(QAbstractItemView::NoEditTriggers);
    layoutPrincipal->addWidget(m_tabla);

    setCentralWidget(central);

    connect(m_comboTipo, &QComboBox::currentTextChanged, this, &MainWindow::onTipoCambiado);
    connect(btnAgregar, &QPushButton::clicked, this, &MainWindow::onAgregarClicked);
    connect(btnImportar, &QPushButton::clicked, this, &MainWindow::onImportarCsvClicked);
}

void MainWindow::onTipoCambiado(const QString& tipo) {
    if (tipo == "Tarea") {
        m_lblExtra->setText("Curso:");
        m_txtExtra->setPlaceholderText("Ej. Tecnología de Objetos");
    } else if (tipo == "Examen") {
        m_lblExtra->setText("Peso (%):");
        m_txtExtra->setPlaceholderText("Ej. 25.0");
    } else {
        m_lblExtra->setText("Equipo:");
        m_txtExtra->setPlaceholderText("Ej. Equipo Alpha");
    }
}

void MainWindow::onAgregarClicked() {
    m_controller.registrarActividad(
        m_comboTipo->currentText(),
        m_txtTitulo->text(),
        m_dateEntrega->date(),
        m_txtExtra->text()
    );
    m_txtTitulo->clear();
    m_txtExtra->clear();
}

void MainWindow::onImportarCsvClicked() {
    QString ruta = QFileDialog::getOpenFileName(
        this, "Seleccionar CSV heredado", "data", "Archivos CSV (*.csv)");
    if (!ruta.isEmpty()) {
        m_controller.cargarCsvLegacy(ruta);
    }
}

void MainWindow::refrescarTabla() {
    const auto lista = m_controller.obtenerLista();
    m_tabla->setRowCount(static_cast<int>(lista.size()));

    for (int i = 0; i < static_cast<int>(lista.size()); ++i) {
        m_tabla->setItem(i, 0, new QTableWidgetItem(lista[i].tipo));
        m_tabla->setItem(i, 1, new QTableWidgetItem(lista[i].titulo));
        m_tabla->setItem(i, 2, new QTableWidgetItem(lista[i].fecha));
        m_tabla->setItem(i, 3, new QTableWidgetItem(lista[i].detalle));
    }
}

void MainWindow::mostrarError(const QString& mensaje) {
    QMessageBox::warning(this, "Validación / Error", mensaje);
}
