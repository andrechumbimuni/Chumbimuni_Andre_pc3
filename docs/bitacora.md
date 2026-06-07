# Bitácora de Desarrollo - PC3

## Día 1
- Lectura y análisis del problema LeetCode 715 - Range Module.
- Creación de la estructura de directorios principales y configuración del `.gitignore` y `CMakeLists.txt ` inicial, creando los archivos en cada subcarpeta como la demo, el test, el RangeModule.h y el RangeModule.pp y el README.md.

## Día 2:
- Avanzando los RangeModule.h y RangeModule.cpp usando el treap.
- Creación del archivo `benchmark/bench_range.cpp` sin codigo.
- Configuración integral de `CMakeLists.txt` para enlazar la librería con los objetivos de demo, test y benchmark.

## Día 3:
- Renombramiento de `test_Range_Module.cpp` a `test_range_module.cpp` y cambiandolo en el CMakeLists.txt.
- Implementación de un caso de prueba inicial que verifica el comportamiento del módulo al realizar consultas sobre una estructura vacía.
- Desarrollo de un demo funcional.
- Creación del archivo `benchmark/benchmark_range_module.cpp` implementando únicamente el esqueleto de la función `main`.
- Resolución de errores de enlazado de C++ (`undefined reference to 'main'`) implementando el main a el tests, benchmark y demo.

## Día 4: (Hoy)
-Arreglando el error de punteros por referencia en las funciones de partición para evitar la ruptura de los enlaces del árbol donde `RangeModule.cpp`en `dividir_derecha` y `dividir_izquierda` para correr el `benchmark_range_module.cpp`.
- Implementación de pruebas  `test_range_module.cpp` cubriendo casos borde: solapamientos parciales, colisiones adyacentes y absorción total.
- Codificación del benchmark utilizando `<chrono>` para realizar 5 bloques de operaciones de inserción, búsqueda y borrado para demostrar la complejidad amortizada de $O(\log n)$ por operación (crecimiento total $O(N \log N)$), evidenciando optimizaciones a nivel de hardware (Cache Locality y Branch Prediction).