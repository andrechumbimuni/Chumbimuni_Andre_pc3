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

- Problema trabajado: Formalización de la validación matemática de la estructura, alineación de las pruebas unitarias con la rúbrica y redacción de la sustentación teórica.
- Se reestructuró `test_range_module.cpp` para empaquetar las aserciones en 6 funciones independientes que representan casos de uso específicos.
- Pruebas agregadas: Se implementaron y documentaron 6 casos de prueba estrictos:
  1. Estructura vacía (frontera).
  2. Caso mínimo (inserción y consulta básica).
  3. Adyacencia/empates (fusión matemática de bordes).
  4. Fragmentación (perforación del centro de un rango).
  5. Absorción masiva (reemplazo de solución ingenua).
  6. Validación del invariante de disyunción y Max-Heap.
- Cambios importantes: 
  - Redacción de `docs/respuestas_obligatorias.md` y creacion de `docs/pruebas.md` con la justificación técnica.
  - Limpieza final del `README.md` eliminando las instrucciones de la rúbrica y estableciendo enlaces limpios a la documentación.

  ## Día 5: 
- Problema trabajado: agregando partes faltantes en .gitignore
  - Ampliación del benchmark de estrés para evaluar hasta 1,000,000 de operaciones consecutivas.
- Cambios importantes: 
  - Agregando de los archivos en carpeta resultados `tests_pc3.txt`, `ejecucion_pc3.txt`, `casos_borde.txt`.