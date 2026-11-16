#pragma once
#include "nodos.h"
#include <functional>
#include <iostream>
//Arbol Binario de busqueda para el recod de edades
using namespace std;

template<class T>
class ArbolBB {
    typedef function<int(T, T)> Comp;
    Nodo<T>* raiz;
    Comp comparar;

private:
    bool _buscar(Nodo<T>* nodo, T e) {
        if (nodo == nullptr) return false;
        else {
            int r = comparar(nodo->get_Elem(), e);
            if (r == 0) return true;
            else if (r < 0) {
                return _buscar(nodo->get_Der(), e);
            }
            else {
                return _buscar(nodo->get_Izq(), e);
            }
        }
    }

    bool _insertar(Nodo<T>*& nodo, T e) {
        if (nodo == nullptr) {
            nodo = new Nodo<T>();  // Crear un nuevo nodo
            nodo->set_Elem(e);     // Asignar el valor al nodo
            return true;
        }
        else {
            int r = comparar(nodo->get_Elem(), e);  // Comparar los elementos
            if (r == 0) return false;  // El elemento ya existe
            else if (r < 0) {
                return _insertar(nodo->get_DerRef(), e);  // Insertar en el subárbol derecho
            }
            else {
                return _insertar(nodo->get_IzqRef(), e);  // Insertar en el subárbol izquierdo
            }
        }
    }

    void _enOrden(Nodo<T>* nodo) {
        if (nodo == nullptr) return;
        _enOrden(nodo->get_Izq());
        cout << nodo->get_Elem() << endl;
        _enOrden(nodo->get_Der());
    }

public:
    ArbolBB() {
        this->raiz = nullptr;
        this->comparar = [](Comprobante a, Comprobante b) -> int {
            if (a < b) return -1;
            if (a > b) return 1;
            return 0;
            };
    }

    bool Buscar(T e) {
        return _buscar(raiz, e);
    }

    bool Insertar(T e) {
        return _insertar(raiz, e);
    }

    void EnOrden() {
        _enOrden(raiz);
    }
};
