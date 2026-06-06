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

int main() {
    std::cout << "Ejecutando Tests Básicos" << std::endl;
    
    test_consulta_vacia();
    
    std::cout << "Todos los tests iniciales pasaron correctamente." << std::endl;
    return 0;
}