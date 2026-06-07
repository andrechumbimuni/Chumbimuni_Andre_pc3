#include <iostream>
#include <cassert>
#include "RangeModule.h"

void test_consulta_vacia() {
    RangeModule rm;
    
    // Al consultar un rango en una estructura recién creada (vacía), debe retornar false
    bool result = rm.queryRange(10, 20);
    assert(result == false);
    
    std::cout << "test_consulta_vacia superado." << std::endl;
}

void test_agrega_y_consulta() {
    RangeModule rm;
    rm.addRange(10, 20);
    assert(rm.queryRange(10, 14) == true);
    assert(rm.queryRange(13, 15) == true);
    assert(rm.queryRange(16, 17) == true);
    assert(rm.queryRange(10, 20) == true);
    assert(rm.queryRange(9, 15) == false);  // Límite izquierdo fuera
    assert(rm.queryRange(15, 21) == false); // Límite derecho fuera
    std::cout << "test_agrega_y_consulta superado." << std::endl;
}

void test_remover_rango() {
    RangeModule rm;
    rm.addRange(10, 20);
    rm.removeRange(14, 16);
    assert(rm.queryRange(10, 14) == true);
    assert(rm.queryRange(13, 15) == false); // Zona borrada
    assert(rm.queryRange(16, 20) == true);
    std::cout << "test_remover_rango superado." << std::endl;
}

void test_interseccion_rangos() {
    RangeModule rm;
    rm.addRange(10, 20);
    rm.addRange(20, 30);
    assert(rm.queryRange(10, 30) == true); // Fusión de adyacentes
    
    rm.addRange(5, 35);
    assert(rm.queryRange(5, 35) == true); // Absorción total
    std::cout << "test_interseccion_rangos superado." << std::endl;
}
int main() {
    std::cout << "Ejecutando Tests Básicos" << std::endl;
    
    test_consulta_vacia();
    test_agrega_y_consulta();
    test_remover_rango();
    test_interseccion_rangos();
    
    std::cout << "Todos los tests iniciales pasaron correctamente." << std::endl;
    return 0;
}