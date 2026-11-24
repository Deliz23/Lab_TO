cmake_minimum_required(VERSION 3.16)
project(Lab09_MVC_Patrones VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/6.12.0/mingw_64")
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Test)

# Librería núcleo (Modelo, Patrones y Controlador) - Independiente de GUI
add_library(lab09_core STATIC
    src/model/Actividad.h
    src/model/Actividad.cpp
    src/model/IRepositorio.h
    src/model/RepositorioActividades.h
    src/model/RepositorioActividades.cpp
    src/patterns/ActividadFactory.h
    src/patterns/ActividadFactory.cpp
    src/patterns/LegacyCsvReader.h
    src/patterns/LegacyCsvReader.cpp
    src/patterns/CsvRepositorioAdapter.h
    src/patterns/CsvRepositorioAdapter.cpp
    src/controller/ActividadController.h
    src/controller/ActividadController.cpp
)

target_include_directories(lab09_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(lab09_core PUBLIC Qt6::Core)

# Ejecutable principal (Vista Qt Widgets)
add_executable(lab09_app
    src/main.cpp
    src/view/MainWindow.h
    src/view/MainWindow.cpp
)
target_link_libraries(lab09_app PRIVATE lab09_core Qt6::Widgets)

# Ejecutable de pruebas unitarias (Qt Test sin GUI)
enable_testing()
add_executable(lab09_tests
    tests/TestMvcPatrones.cpp
)
target_link_libraries(lab09_tests PRIVATE lab09_core Qt6::Test)
add_test(NAME TestMvcPatrones COMMAND lab09_tests)
