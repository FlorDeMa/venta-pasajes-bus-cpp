#pragma once
#include <iostream>
#include <string>
#include "listas.h"
#include "persona.h"

using namespace std;

template<typename T1, typename T2>
class VendedorPasaje:public Persona<T1,T2>
{
public:

    VendedorPasaje(T1 nombre, T1 apellido, T2 edad, T1 fechaNacimiento, T1 dni, T1 celular)
        : Persona<T1, T2>(nombre, apellido, edad, fechaNacimiento, dni, celular) {}


    void mostrarDatosVendedor() {
        cout << "========== DATOS DEL VENDEDOR =========" << endl;
        this->mostrarPersona();
    }
    void setId(T1 Eid) { this->id = Eid; }
    T1 getId() { return this->id; }

    void setCategoria(T1 Ecategoria) { this->categoria = Ecategoria; }
    T1 getCategoria() { return this->categoria; }

    void mostrarDatosEmpleado()
    {

        cout << "          ID Empleado: " << this->id << endl;
        cout << "          Categoria: " << this->categoria << endl;
    }
private:

};
