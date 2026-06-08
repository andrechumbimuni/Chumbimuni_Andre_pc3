# Reporte de Pruebas
A continuación se describen las 5 pruebas fundamentales realizadas sobre el `RangeModule`, abarcando los escenarios exigidos para asegurar la robustez de la estructura Treap.

### 1. Caso con estructura vacía (Frontera)
- **Entrada usada:** Se crea el `RangeModule` e inmediatamente se ejecuta `queryRange(10, 20)`.
- **Salida esperada:** `false`.
- **Salida obtenida:** `false` (Validado mediante `assert`).
- **Qué aspecto valida:** Verifica que el constructor inicializa correctamente los punteros nulos (árbol vacío) y que las funciones de búsqueda no generan errores de acceso a memoria (Segmentation fault) al recorrer un Treap inexistente.

### 2. Caso mínimo
- **Entrada usada:** `addRange(10, 20)`. Luego se realizan tres consultas: `queryRange(10, 14)`, `queryRange(13, 15)` y `queryRange(9, 15)`.
- **Salida esperada:** `true`, `true`, `false`.
- **Salida obtenida:** `true`, `true`, `false` (Validado mediante `assert`).
- **Qué aspecto valida:** Comprueba la correcta inserción de un nodo raíz y verifica que las búsquedas respeten estrictamente los límites semiabiertos `[left, right)`. El último caso (`9 a 15`) falla correctamente porque el 9 está fuera del límite inferior.

### 3. Caso con duplicados o empates (Adyacencia)
- **Entrada usada:** `addRange(10, 20)` seguido de `addRange(20, 30)`. Posteriormente se consulta `queryRange(10, 30)`.
- **Salida esperada:** `true`.
- **Salida obtenida:** `true` (Validado mediante `assert`).
- **Qué aspecto valida:** Verifica el comportamiento de "empate" en los límites. Como los intervalos son semiabiertos `[10, 20)` y `[20, 30)`, el algoritmo debe detectar la adyacencia exacta en el valor `20` y fusionarlos matemáticamente en un solo nodo contiguo `[10, 30)` en lugar de tratarlos de forma aislada.

### 4. Caso extremo pequeño verificable manualmente (Fragmentación)
- **Entrada usada:** Se inserta un rango grande `addRange(10, 20)`. Luego se "perfora" borrando el centro con `removeRange(14, 16)`. Se consultan las zonas: `queryRange(10, 14)`, `queryRange(13, 15)` y `queryRange(16, 20)`.
- **Salida esperada:** `true`, `false`, `true`.
- **Salida obtenida:** `true`, `false`, `true` (Validado mediante `assert`).
- **Qué aspecto valida:** Valida la lógica de división (`split`) durante el borrado. Un solo nodo de rango `[10, 20)` debe destruirse y generar dos nuevos nodos separados: `[10, 14)` y `[16, 20)`, demostrando que el Treap maneja la fragmentación de la memoria sin fugas ni sobreposiciones.

### 5. Caso de absorción masiva (Equivalente a evaluación ingenua)
- **Entrada usada:** Se insertan múltiples rangos disjuntos `addRange(10, 20)` y `addRange(30, 40)`. Luego, se inserta un rango gigante que los engulle a todos: `addRange(5, 50)`. Se consulta `queryRange(5, 50)`.
- **Salida esperada:** `true`.
- **Salida obtenida:** `true` (Validado mediante `assert`).
- **Qué aspecto valida:** Actúa como comprobación frente a una solución ingenua (un arreglo booleano). Si usáramos un arreglo booleano, marcaríamos índices iterativamente. En nuestro Treap, al introducir `[5, 50)`, el algoritmo debe navegar, detectar todos los nodos internos previamente insertados que caen en esa zona, eliminarlos limpiamente para evitar redundancias, y reemplazarlos por un único nodo universal.

### 6. Prueba específica del invariante principal (Disyunción y Max-Heap)
- **Entrada usada:** Inserción de múltiples rangos que se cruzan caóticamente: `addRange(10, 20)`, `addRange(15, 25)`, `addRange(5, 12)`.
- **Salida esperada:** El árbol debe contener un único nodo `[5, 25)`. Se valida con `queryRange(5, 25)` esperando `true`, y `queryRange(4, 26)` esperando `false`.
- **Salida obtenida:** `true` y `false` respectivamente.
- **Qué aspecto valida:** Valida el **invariante principal de disyunción**: el Treap prohíbe que existan nodos superpuestos. Obliga a las funciones internas a extraer, fusionar y destruir los nodos redundantes, recalculando las prioridades (Max-Heap) para mantener el árbol unificado y balanceado.