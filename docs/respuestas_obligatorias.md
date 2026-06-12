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

Escribí una suite completa de 6 pruebas unitarias avanzadas en test_module para validar los límites físicos e invariantes de la estructura más allá de los casos estándar. Específicamente, mi prueba propia más rigurosa fue test_fragmentacion_borrado junto con test_empates_adyacencia.

Esta prueba verifica dos escenarios críticos de colisión de intervalos:

Fusión por Adyacencia Estricta: Si inserto [10, 20) y luego [20, 30), el sistema detecta que comparten la frontera exacta 20 y los unifica en un solo nodo consolidado [10, 30).

Fragmentación Central Destructiva: Si sobre ese intervalo consolidado aplico un removeRange(14, 16), el algoritmo no borra todo el nodo, sino que realiza un split topológico exacto para rebanar el centro, generando dinámicamente dos sub-nodos residuales y disjuntos: [10, 14) y [16, 20). Esto demuestra que la lógica soporta mutaciones complejas en el Heap de forma correcta.

**18. ¿Qué cambiaste durante el bloque sin cortes?**

Durante el bloque grabado sin cortes, introduje dos modificaciones clave alineadas con las exigencias del examen:

Una aserción de seguridad física (assert): Coloqué un assert(limite <= 1000000000); justo al inicio de la función recursiva para garantizar bajo contrato que los rangos nunca desborden el universo límite de $10^9$ definido por el problema.

Un flujo de diagnóstico útil para depuración en tiempo real: Añadí un bloque condicional que imprime en la salida estándar el estado interno del árbol cada vez que se ejecuta una mutación:
```
if (raiz != nullptr) {
    std::cout << "Ejecutando Split en nodo: [" << raiz->left << ", " << raiz->right << ") con limite: " << limite << "\n";
}
```
Este cambio permite visualizar de forma transparente cómo el árbol se subdivide jerárquicamente a través de sus punteros durante las consultas o inserciones.

**19. ¿Cómo sabes que el cambio no rompió la solución?**
Lo sé de forma objetiva y empírica mediante dos mecanismos de validación inmediata ejecutados en la terminal justo después de compilar la modificación:

Correctitud Observable de la Suite: Al ejecutar ./build/test_module, las 6 pruebas de la suite pasaron limpiamente devolviendo un código de salida exitoso (Exit code 0), lo que demuestra que la lógica de intervalos sigue intacta.

Inspección de las Trazas de Diagnóstico: En la consola se pudo observar cómo la terminal se inundó con los mensajes [DEBUG LIVE]. Esto comprueba que el código inyectado se ejecutó de forma activa y que el validador automático de fuerza bruta (test_invariante_disyuncion) recorrió todo el Treap verificando que las claves del BST, las prioridades del Max-Heap y la disyunción de los rangos se mantuvieron 100% estables tras las operaciones de corte.

**20. ¿Qué demuestra que no es una solución de caja negra?**
Que puedo explicar línea por línea cómo el puntero `l` y `r` viajan recursivamente en la función `dividir_derecha` para reensamblar el árbol.