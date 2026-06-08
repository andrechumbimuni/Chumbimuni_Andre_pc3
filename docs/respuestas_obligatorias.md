### Preguntas comunes obligatorias

**1. ¿Cuál es el problema exacto asignado?**
LeetCode 715: Implementar un "Range Module" para añadir, consultar y eliminar rangos de números de forma eficiente.

**2. ¿Qué recibe la entrada y qué produce la salida?**
Recibe llamadas a métodos: `addRange(left, right)`, `removeRange(left, right)` (sin retorno) y `queryRange(left, right)` que produce un `booleano` (true si el rango completo está siendo monitoreado).

**3. ¿Cuál es la restricción que vuelve insuficiente una solución ingenua?**
Los valores de los límites pueden llegar hasta $10^9$, y se pueden ejecutar miles de operaciones.

**4. ¿Cuál sería la solución ingenua y cuál es su complejidad?**
Un arreglo booleano de tamaño $10^9$ (`bool arr[1000000000]`). Cada operación requeriría iterar con un bucle `for` desde `left` hasta `right`, tomando $O(N)$ por operación y colapsando la memoria (Out of Memory).

**5. ¿Qué estructura de datos elegiste?**
Un Treap (Árbol de Búsqueda Binaria + Heap aleatorizado).

**6. ¿Qué estructura de la librería cc232 se parece más?**
La estructura `Treap.h` de la Semana 6, que a su vez hereda conceptos de `BinarySearchTree.h` y `BinaryHeap.h` de la Semana 5.

**7. ¿Qué operación domina el tiempo?**
Las operaciones de partición (`split` / `dividir_izquierda`, `dividir_derecha`) y fusión (`merge` / `intersectar`).

**8. ¿Qué invariante mantiene tu estructura?**
1. **BST:** Nodos ordenados por límite izquierdo.
2. **Max-Heap:** Prioridad aleatoria del padre >= hijos.
3. **Disyunción:** Ningún par de nodos tiene intervalos que se solapen.

**9. ¿Dónde se actualiza ese invariante en el código?**
La disyunción en `addRange` y `removeRange`. El Max-Heap se mantiene en la función recursiva `intersectar` al comparar las prioridades antes de enlazar los hijos.

**10. ¿Qué caso borde puede romper una solución superficial?**
La fragmentación total. Insertar `[10, 100)` y luego pedir `removeRange(50, 51)`. Una solución superficial borraría todo o no sabría cómo partir el nodo en dos.

**11. ¿Cómo manejas duplicados, empates o elementos obsoletos?**
Si dos intervalos son exactamente adyacentes (`[10, 20)` y `[20, 30)`), la lógica de búsqueda los intercepta y los fusiona en uno solo `[10, 30)`. Los nodos obsoletos se liberan de memoria usando `delete` en la función `limpiar()`.

**12. ¿Cuál es la complejidad temporal por operación?**
$O(\log n)$ amortizado por operación.

**13. ¿Cuál es la complejidad total?**
$O(N \log n)$ para $N$ operaciones.

**14. ¿Cuál es la complejidad espacial?**
$O(n)$, donde $n$ es la cantidad de intervalos fragmentados activos. Es mucho menor a $10^9$.

**15. ¿Qué parte del código sería más fácil de romper?**
La función de división (`split`). Si el paso de punteros por referencia (`Treap*&`) se maneja mal, se pierden los hijos del árbol provocando "Segmentation Fault".

**16. ¿Qué alternativa de estructura existe y qué perderías con ella?**
Un Árbol de Segmentos Dinámico con Lazy Propagation. Perdería simplicidad, ya que el factor constante de tiempo y uso de memoria es mayor cuando los intervalos son muy dispersos.

**17. ¿Qué prueba propia escribiste?**

**18. ¿Qué cambiaste durante el bloque sin cortes?**


**19. ¿Cómo sabes que el cambio no rompió la solución?**


**20. ¿Qué demuestra que no es una solución de caja negra?**
Que puedo explicar línea por línea cómo el puntero `l` y `r` viajan recursivamente en la función `dividir_derecha` para reensamblar el árbol.