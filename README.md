## PC3 - CC232
### Estudiante
- Nombre: Chumbimuni Ricci Andre Dylan
- Código: 20230303J
- Problema asignado: LeetCode 715 - Range Module
- Enlace oficial: https://leetcode.com/problems/range-module/

### Referencia oficial
- CSV oficial: 
https://github.com/kapumota/CC-232/blob/main/Practicas/Practica3_CC232/Problemas-Evaluacion3.csv

### Relación con Semanas 4-6
- Semana principal: Semana 6 (Priority Queues, Heaps mezclables y Treaps).
- Estructura usada: Treap (Árbol de Búsqueda Binaria Aleatorizado).
- Estructura de la librería cc232 relacionada: `Treap.h` (correspondiente al contenido de Semana 6), apoyado en los conceptos base de `BinarySearchTree` y `BinaryHeap` reutilizados desde `Semana5/include`.

### Resumen de la solución
El problema LeetCode 715 (Range Module) requiere gestionar un conjunto de intervalos semiabiertos `[left, right)` soportando adiciones, consultas y eliminaciones masivas sobre un rango de valores muy grande (hasta 10^9). 

Para solucionarlo, se implementó un Treap donde cada nodo almacena un intervalo disjunto. Al realizar las operaciones `addRange` o `removeRange`, se utilizan las operaciones fundamentales del Treap: `dividir` (split) y `intersectar/unir` (merge). En una inserción, los intervalos solapados se fusionan en un único nodo extendido. En una eliminación, si un intervalo cubre la zona a borrar, este se fragmenta en dos nodos separados. El Treap mantiene la estructura óptima, evitando la degradación a O(n).

## Invariante principal
Todo nodo dentro de la estructura Treap debe cumplir estrictamente:
1. **Propiedad de BST (Árbol de Búsqueda Binaria):** Los nodos están ordenados por su límite izquierdo (`left`). El hijo izquierdo tiene intervalos que inician antes que el nodo actual, y el hijo derecho tiene intervalos que inician después.
2. **Propiedad de Max-Heap:** La prioridad aleatoria generada para un nodo padre siempre es mayor o igual a la prioridad de sus nodos hijos, garantizando el balanceo del árbol.
3. **Disyunción:** Ningún par de nodos en el árbol tiene rangos que se solapen. Si se tocan o cruzan, son obligatoriamente fusionados en un solo nodo.

## Complejidad
* **Tiempo por operación:** O(log n) amortizado para las operaciones `addRange`, `queryRange` y `removeRange`, donde `n` es la cantidad de intervalos disjuntos activos en el árbol (gracias al balanceo probabilístico del Treap).
* **Tiempo total:** O(N log n) esperado para procesar una secuencia de `N` operaciones.
* **Espacio:** O(n) en el peor de los casos, donde `n` es el número máximo de intervalos fragmentados disjuntos almacenados simultáneamente.

## Archivos relevantes
* `include/`: Contiene `RangeModule.h` con la definición del nodo y la clase.
* `src/`: Contiene `RangeModule.cpp` con la implementación central del BST de intervalos.
* `tests/`: Contiene `test_range_module.cpp` con las pruebas automatizadas.
* `demos/`: Contiene `demos_range_module.cpp` para pruebas de ejecución manual.
* `docs/respuestas_obligatorias.md`: Respuestas a las preguntas teóricas.
* `docs/bitacora.md`: Registro diario del desarrollo.
* `resultados/`: Contendrá los logs de las pruebas y casos borde.

## Limpieza del repositorio
Se creó un archivo `.gitignore` configurado específicamente para proyectos en C++ con CMake. Este archivo ignora automáticamente la carpeta `build/`, los binarios generados (`.exe`, `.o`), y archivos de configuración del IDE (como `.vscode/`), garantizando que el repositorio de Git se mantenga limpio.

## Compilación
El proyecto compila desde una copia limpia usando CMake:
```bash
cmake -S . -B build
cmake --build build
```
## Ejecución

El proyecto genera distintos módulos ejecutables para pruebas, demostración y análisis de rendimiento.
Para ejecutar las pruebas unitarias automatizadas (validación de casos borde):

```bash
./build/test_module
```
Para ejecutar el análisis de rendimiento (demostración de complejidad O(log n)):
```bash
./build/benchmark_module
```

Para ejecutar la demostración general del programa:
```bash
./build/demos_module
```

## Documentación y Evidencias
Cumpliendo con los requisitos de la rúbrica, la documentación detallada se encuentra en la carpeta `docs/`:
- **[Bitácora de Desarrollo](docs/bitacora.md):** Historial del proceso, errores, soluciones y progreso diario.
- **[Respuestas Obligatorias](docs/respuestas_obligatorias.md):** Justificación teórica.
- **[Reporte de Pruebas](docs/pruebas.md):** Detalle de los 6 casos de prueba.

## Declaración de autoría

Declaro que entiendo el código entregado, que puedo explicarlo, compilarlo, ejecutarlo y modificarlo sin ayuda externa durante la grabación.  
También declaro que el repositorio entregado corresponde al trabajo mostrado en el video y que no contiene builds, ejecutables ni archivos generados usados para aparentar funcionamiento.
