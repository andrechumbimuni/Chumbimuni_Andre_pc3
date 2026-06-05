#ifndef RANGE_MODULE_H
#define RANGE_MODULE_H

#include <cstdlib> // usar rand
#include <algorithm> // usar std::min y std::max

// Nodo del Treap para intervalos disjuntos
struct Treap {
    int izquierda;
    int derecha;
    int prioridad; // Para mantenerse balanceado
    Treap* hijoIzquierdo;
    Treap* hijoDerecho;

    Treap(int l, int r) : izquierda(l), derecha(r), prioridad(std::rand()), hijoIzquierdo(nullptr), hijoDerecho(nullptr) {} //inicializa el nodo con un intervalo [l, r) y una prioridad aleatoria
};

class RangeModule {
private:
    Treap* raiz;

    // Operaciones de Treap
    void dividir_derecha(Treap* t, Treap*& l, Treap*& r, int val);
    void dividir_izquierda(Treap* t, Treap*& l, Treap*& r, int val);
    Treap* intersectar(Treap* l, Treap* r);
    void limpiar(Treap* node);

public:
    RangeModule();
    ~RangeModule();

    void addRange(int left, int right);
    bool queryRange(int left, int right);
    void removeRange(int left, int right);
};

#endif