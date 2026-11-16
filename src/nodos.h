#pragma once
template <class T>
class Nodo
{
private:
    T elem;
    Nodo* izq;
    Nodo* der;
    Nodo<T>* sgte;

public:
    // Constructor por defecto
    Nodo()
    {
        izq = nullptr;
        der = nullptr;
    }

    // Constructor con el elemento
    Nodo(T pelem)
    {
        elem = pelem;
        izq = nullptr;
        der = nullptr;
    }

    // Métodos setters y getters
    void set_Elem(T pelem)
    {
        elem = pelem;
    }

    T get_Elem()
    {
        return elem;
    }

    void set_Izq(Nodo* pIzq)
    {
        izq = pIzq;
    }

    Nodo* get_Izq()
    {
        return izq;
    }

    void set_Der(Nodo* pDer)
    {
        der = pDer;
    }

    Nodo* get_Der()
    {
        return der;
    }

    // Métodos para obtener referencias a los punteros
    Nodo*& get_IzqRef()
    {
        return izq;
    }

    Nodo*& get_DerRef()
    {
        return der;
    }
    void set_Sgte(Nodo<T>* pSgte)
    {
        sgte = pSgte;
    }

    Nodo<T>* get_Sgte() const
    {
        return sgte;
    }
    bool es_vacio()
    {
        return izq == nullptr && der == nullptr;
    }
};
