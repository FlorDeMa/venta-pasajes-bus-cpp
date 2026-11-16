#pragma once
#include <iostream>
#include "HashEntidad.h"
using namespace std;
/*
   Clase HashTabla:
   Esta clase implementa una tabla hash genérica utilizando un arreglo de punteros a la clase HashEntidad.
   Permite almacenar pares clave-valor, donde la clave y el valor pueden ser de tipos genéricos T1 y T2, respectivamente.
   La tabla utiliza una técnica de manejo de colisiones por sondeo lineal.

   Atributos:
   - tabla: Un arreglo de punteros a objetos de tipo HashEntidad, donde cada elemento es una entidad
     que almacena una clave y su valor asociado.
   - numElementos: Un contador que indica cuántos elementos han sido insertados en la tabla.
   - capacidad: La capacidad actual de la tabla, que es el tamaño del arreglo.

   Métodos:
   - calcularIndice(): Calcula el índice de la tabla basado en la clave utilizando la operación de módulo.
   - insertar(): Inserta un nuevo par clave-valor en la tabla, manejando colisiones con sondeo lineal.
   - size(): Devuelve la capacidad actual de la tabla.
   - sizeactual(): Devuelve el número actual de elementos almacenados en la tabla.
   - buscar(): Busca un valor asociado a una clave específica en la tabla.
*/

//Al contar con nuestra tabla Hash cumplimos con "ener en cuenta, que se debe crear una función hash propia compleja"
template<typename T1, typename T2>
class HashTabla {
private:
    HashEntidad<T1, T2>** tabla;
    int numElementos;
    int capacidad;

    int calcularIndice(T1 key) {
        return key % capacidad;
    }

public:
    HashTabla(int capacidadInicial = 200) {
        this->capacidad = capacidadInicial;
        tabla = new HashEntidad<T1, T2>* [capacidad];
        for (int i = 0; i < capacidad; ++i) {
            tabla[i] = nullptr;
        }
        numElementos = 0;
    }

    ~HashTabla() {
        if (tabla != nullptr) {
            for (int i = 0; i < capacidad; ++i) {
                if (tabla[i] != nullptr) {
                    delete tabla[i];
                    tabla[i] = nullptr;
                }
            }
            delete[] tabla;
            tabla = nullptr;
        }
    }

    void insertar(T1 key, T2 value) {
        if (numElementos == capacidad) {
            cout << "No hay espacio en la tabla" << endl;
            return;
        }

        int indice = calcularIndice(key);
        int siguiente = 0;

        while (tabla[indice] != nullptr) {
            indice = (indice + siguiente++) % capacidad;
        }

        tabla[indice] = new HashEntidad<T1, T2>(key, value);
        numElementos++;
        cout << "Insertado " << value << " en indice " << indice << " con clave " << key << endl;
    }

    int size() const {
        return capacidad;
    }

    int sizeactual() const {
        return numElementos;
    }

    T2 buscar(T1 key) {
        int indice = calcularIndice(key);
        int siguiente = 0;

        while (tabla[indice] != nullptr) {
            if (tabla[indice]->getKey() == key) {
                return tabla[indice]->getValue();
            }
            indice = (indice + siguiente++) % capacidad;
        }

        return T2();
    }
};
