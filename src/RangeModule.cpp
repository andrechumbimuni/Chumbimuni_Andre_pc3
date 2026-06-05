#include "RangeModule.h"

RangeModule::RangeModule() : raiz(nullptr) {} // Inicializa el RangeModule con un árbol vacío

RangeModule::~RangeModule() { // Destructor para liberar memoria
    limpiar(raiz);
}

void RangeModule::limpiar(Treap* nodo) {
    if (!nodo) return;
    limpiar(nodo->hijoIzquierdo);
    limpiar(nodo->hijoDerecho);
    delete nodo;
}

// Corta el árbol en dos: los que terminan antes de 'val', y el resto.
void RangeModule::dividir_derecha(Treap* t, Treap*& l, Treap*& r, int val) {
    if (!t) { l = r = nullptr; return; }
    if (t->derecha < val) {
        dividir_derecha(t->hijoDerecho, l, r, val);
        l = t;
    } else {
        dividir_derecha(t->hijoIzquierdo, l, r, val);
        r = t;
    }
}

// Corta el árbol en dos: los que inician antes de 'val', y el resto.
void RangeModule::dividir_izquierda(Treap* t, Treap*& l, Treap*& r, int val) {
    if (!t) { l = r = nullptr; return; }
    if (t->izquierda < val) {
        dividir_izquierda(t->hijoDerecho, l, r, val);
        l = t;
    } else {
        dividir_izquierda(t->hijoIzquierdo, l, r, val);
        r = t;
    }
}

// Une dos subárboles manteniendo la propiedad del Heap (prioridad)
Treap* RangeModule::intersectar(Treap* l, Treap* r) {
    if (!l) return r;
    if (!r) return l;
    if (l->prioridad > r->prioridad) {
        l->hijoDerecho = intersectar(l->hijoDerecho, r);
        return l;
    } else {
        r->hijoIzquierdo = intersectar(l, r->hijoIzquierdo);
        return r;
    }
}

void RangeModule::addRange(int left, int right) {
    if (left >= right) return;

    Treap* t1, *temp, *superpuesto, *t2;
    
    // 1. Aislar los intervalos que no chocan a la izquierda (terminan antes de 'left')
    dividir_derecha(raiz, t1, temp, left);
    
    // 2. Del resto, aislar los que chocan de los que no chocan a la derecha (inician despues de 'right')
    dividir_izquierda(temp, superpuesto, t2, right + 1);

    // 3. Fusionar: Si hay overlaps, extendemos los límites del nuevo intervalo
    int newL = left;
    int newR = right;
    
    if (superpuesto) {
        Treap* curr = superpuesto;
        while (curr->hijoIzquierdo) {curr = curr->hijoIzquierdo; };
        newL = std::min(newL, curr->izquierda); // Extendemos el límite izquierdo si es necesario
        
        curr = superpuesto;
        while (curr->hijoDerecho) {curr = curr->hijoDerecho; };
        newR = std::max(newR, curr->derecha);// Extendemos el límite derecho si es necesario
        
        limpiar(superpuesto); // Liberar memoria de los nodos viejos que se van a fusionar
    }

    // 4. Crear el nuevo nodo y unir todo de nuevo
    Treap* nuevoNodo = new Treap(newL, newR);
    raiz = intersectar(t1, intersectar(nuevoNodo, t2));
}

bool RangeModule::queryRange(int left, int right) {
    if (left >= right) return false;
    
    Treap* curr = raiz;
    while (curr) {
        if (curr->derecha <= left) {
            curr = curr->hijoDerecho; // Busca a la derecha
        } else if (curr->izquierda > left) {
            curr = curr->hijoIzquierdo;  // Busca a la izquierda
        } else { // Si encontramos un nodo que cubre 'left', verificamos si también cubre 'right'
            return curr->derecha >= right;
        }
    }
    return false;
}

void RangeModule::removeRange(int left, int right) {
    if (left >= right) return;

    Treap *t1, *temp, *superpuesto, *t2;
    
    // Para remover, solo nos importan los que se solapan estrictamente (tienen intersección)
    dividir_derecha(raiz, t1, temp, left + 1);
    dividir_izquierda(temp, superpuesto, t2, right);

    Treap* keepLeft = nullptr;
    Treap* keepRight = nullptr;

    // Si encontramos intervalos que chocan con la zona a borrar, los partimos.
    if (superpuesto) {
        Treap* primero = superpuesto;
        while (primero->hijoIzquierdo) primero = primero->hijoIzquierdo;
        if (primero->izquierda < left) {
            keepLeft = new Treap(primero->izquierda, left); // Guardamos la cola izquierda
        }
        
        Treap* ultimo = superpuesto;
        while (ultimo->hijoDerecho) ultimo = ultimo->hijoDerecho;
        if (ultimo->derecha > right) {
            keepRight = new Treap(right, ultimo->derecha); // Guardamos la cola derecha
        }
        
        limpiar(superpuesto); // Borramos el centro
    }

    // Unimos las 2 partes que no se borran con los extremos que queremos mantener
    raiz = intersectar(t1, intersectar(keepLeft, intersectar(keepRight, t2)));
}
