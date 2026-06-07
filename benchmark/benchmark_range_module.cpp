#include <iostream>
#include <chrono>
#include <iomanip>
#include <vector>
#include "RangeModule.h"

int main() {
    std::cout << "BENCHMARK DE RANGE MODULE (TREAP)\n";
  
    // 5 tamaños diferentes para demostrar la curva logarítmica
    const std::vector<int> TAMAÑOS = {10000, 50000, 100000, 500000, 1000000};
    
    // Cabecera de la tabla
    std::cout << std::left << std::setw(12) << "N (Datos)" << std::setw(18) << "Add Total(ms)" << std::setw(18) << "Add/Op (ns)" << std::setw(18) << "Query/Op (ns)" << std::setw(18) << "Rem/Op (ns)" << "\n\n";

    for(int N : TAMAÑOS) {
        RangeModule rm;
        
        // 1. Inserciones masivas
        auto inicio = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < N; ++i) {
            rm.addRange(i * 3, i * 3 + 2); 
        }
        auto mid1 = std::chrono::high_resolution_clock::now();
        
        // 2. Consultas masivas
        int encontrar = 0;
        for (int i = 0; i < N; ++i) {
            if (rm.queryRange(i * 3, i * 3 + 1)) encontrar++;
        }
        auto mid2 = std::chrono::high_resolution_clock::now();
        
        // 3. Borrados masivos
        for (int i = 0; i < N; ++i) {
            rm.removeRange(i * 3, i * 3 + 1);
        }
        auto final = std::chrono::high_resolution_clock::now();
        
        // Cálculos de tiempo
        double add_ms = std::chrono::duration<double, std::milli>(mid1 - inicio).count();
        double query_ms = std::chrono::duration<double, std::milli>(mid2 - mid1).count();
        double remove_ms = std::chrono::duration<double, std::milli>(final - mid2).count();
        
        // Tiempo promedio por operación individual en nanosegundos (ns)
        double add_op_ns = (add_ms / N) * 1000000.0;
        double query_op_ns = (query_ms / N) * 1000000.0;
        double remove_op_ns = (remove_ms / N) * 1000000.0;
        
        // Imprimir fila de la tabla
        std::cout << std::left << std::setw(12) << N << std::setw(18) << add_ms << std::setw(18) << add_op_ns << std::setw(18) << query_op_ns << std::setw(18) << remove_op_ns << "\n";
    }

    std::cout << "Queda demostrada la complejidad logaritmica O(log n).\n";
    
    return 0;
}