#include <iostream>
#include <cassert>
#include "RangeModule.h"

// 1. Caso con estructura vacía (Frontera)
void test_estructura_vacia() {
    RangeModule rm;
    assert(rm.queryRange(10, 20) == false);
    std::cout << "1. test_estructura_vacia superado." << std::endl;
}

// 2. Caso mínimo
void test_caso_minimo() {
    RangeModule rm;
    rm.addRange(10, 20);
    assert(rm.queryRange(10, 14) == true);
    assert(rm.queryRange(13, 15) == true);
    assert(rm.queryRange(9, 15) == false);  // Límite izquierdo fuera
    std::cout << "2. test_caso_minimo superado." << std::endl;
}

// 3. Caso con duplicados o empates y adyacencia
void test_empates_adyacencia() {
    RangeModule rm;
    rm.addRange(10, 20);
    rm.addRange(20, 30);
    assert(rm.queryRange(10, 30) == true); // Fusión matemática de adyacentes
    std::cout << "3. test_empates_adyacencia superado." << std::endl;
}

// 4. Caso extremo pequeño verificable manualmente
void test_fragmentacion_borrado() {
    RangeModule rm;
    rm.addRange(10, 20);
    rm.removeRange(14, 16); // Perfora el centro
    assert(rm.queryRange(10, 14) == true);
    assert(rm.queryRange(13, 15) == false); // Zona borrada
    assert(rm.queryRange(16, 20) == true);
    std::cout << "4. test_fragmentacion_borrado superado." << std::endl;
}

// 5. Caso de absorción masiva
void test_absorcion_masiva() {
    RangeModule rm;
    rm.addRange(10, 20);
    rm.addRange(30, 40);
    rm.addRange(5, 50); // Rango gigante que engulle los anteriores
    assert(rm.queryRange(5, 50) == true);
    std::cout << "5. test_absorcion_masiva superado." << std::endl;
}

// 6. Prueba específica del invariante principal
void test_invariante_disyuncion() {
    RangeModule rm;
    rm.addRange(10, 20);
    rm.addRange(15, 25);
    rm.addRange(5, 12);
    // Todos deben haberse fusionado en un solo nodo [5, 25)
    assert(rm.queryRange(5, 25) == true);
    assert(rm.queryRange(4, 26) == false);
    std::cout << "6. test_invariante_disyuncion superado." << std::endl;
}

int main() {
    std::cout << "Ejecutando Suite de Pruebas (Treap)" << std::endl;
    
    test_estructura_vacia();
    test_caso_minimo();
    test_empates_adyacencia();
    test_fragmentacion_borrado();
    test_absorcion_masiva();
    test_invariante_disyuncion();

    std::cout << "Todos los tests pasaron correctamente." << std::endl;
    
    return 0;
}