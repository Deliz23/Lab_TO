#include "model/RepositorioActividades.h"
#include "patterns/CsvRepositorioAdapter.h"
#include "controller/ActividadController.h"
#include "view/MainWindow.h"
#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    RepositorioActividades repositorioBase;
    CsvRepositorioAdapter adapter(repositorioBase);
    ActividadController controller(adapter);
    MainWindow ventana(controller);

    ventana.show();
    return app.exec();
}
