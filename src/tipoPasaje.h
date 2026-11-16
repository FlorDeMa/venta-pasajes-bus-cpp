#pragma once
#include <iostream>
#include <string>

using namespace std;
/*
   Clase TipoPasaje:
   Esta clase representa un tipo de pasaje de un sistema de transporte o aerolínea.
   Utiliza plantillas genéricas para los atributos relacionados con las categorías, tipo de pasaje,
   tipo de equipaje, y el precio base, lo que permite flexibilidad en el tipo de datos usados.

   Atributos:
   - categoria: Representa la categoría del pasaje (por ejemplo, "Prime", "Elite", "Gold").
   - tipoPasaje: Representa el tipo de pasaje, como puede ser ida, vuelta, o especial.
   - tipoEquipaje: Representa el tipo de equipaje permitido (por ejemplo, de mano, facturado).
   - precioBase: El precio base del pasaje, que se ajusta según la categoría del pasaje.

   Métodos:
   - Constructor por defecto: Inicializa los atributos a sus valores por defecto.
   - Constructor parametrizado: Inicializa los atributos con los valores proporcionados y asigna un precio base.
   - Métodos `set` y `get` para los atributos: Permiten modificar y acceder a los atributos.
   - `asignarPrecioOriginal()`: Asigna un precio base a un tipo de pasaje según su categoría, mostrando un mensaje en la consola.
*/
template <typename T1, typename T2>

class TipoPasaje
{
public:
    TipoPasaje() {
        this->categoria = T1();
        this->tipoPasaje = T1();
        this->tipoEquipaje = T1();
        this->precioBase = T2();
    }

    TipoPasaje(T1 cat, T1 tipoP, T1 tipoE) {

        this->categoria = cat;
        this->tipoPasaje = tipoP;
        this->tipoEquipaje = tipoE;
        this->asignarPrecioOriginal();

    }

    void setCate(T1 cat) { this->categoria = cat; }
    T1 getCate() { return categoria; }

    void setTipoPasaje(T1 tipoP) { 
        this->tipoPasaje = tipoP; 
        this->asignarPrecioOriginal();
    }
    T1 getTipoPasaje() { return tipoPasaje; }


    void setTipoEquipaje(T1 tipoE) { this->tipoEquipaje = tipoE; }
    T1 getTipoEquipaje() { return tipoEquipaje; }

    T2 getPrecioB() { return precioBase; }


    void asignarPrecioOriginal() {
        if (categoria == "1") {
            precioBase = 50;
            Console::SetCursorPosition(5, 7); cout << "TIPO PASAJE -> PRIME" << endl;
        }
        else if (categoria == "2") {
            precioBase = 80;
            Console::SetCursorPosition(5, 7); cout << "TIPO PASAJE -> ELITE" << endl;
        }
        else if (categoria == "3") {
            precioBase = 100;
            Console::SetCursorPosition(5, 7); cout << "TIPO PASAJE -> GOLD" << endl;
        }
        else {
            Console::SetCursorPosition(5, 6); cout << "Opcion no valida" << endl;
        }



    }



private:
    T1 categoria;
    T1 tipoPasaje;
    T1 tipoEquipaje;
    T2 precioBase;
};