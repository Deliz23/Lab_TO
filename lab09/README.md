# Laboratorio N.° 09: Patrones de Diseño y Arquitectura MVC con Qt 6

Aplicación de seguimiento académico desarrollada en **C++20** y **Qt 6 Widgets** aplicando separación **MVC**, el patrón creacional **Factory Method** y el patrón estructural **Adapter**.

## Requisitos
- Qt 6.12.0 (Core, Widgets, Test)
- Compilador C++20 (MinGW 13.1.0)
- CMake 3.16+

## Compilación (fuera del árbol)
```bash
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
```

## Ejecución de pruebas unitarias (sin GUI)
```bash
ctest --test-dir build --output-on-failure
```

## Ejecución de la aplicación
```bash
./build/lab09_app.exe
```