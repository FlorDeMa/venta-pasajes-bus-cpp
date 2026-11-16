#pragma once
#include <iostream>
#include <string>
#include "cliente.h"

/*
    Clase Promocion que gestiona los descuentos aplicables a los clientes.
    Esta clase utiliza plantillas (template) para permitir la flexibilidad de tipos de datos
    para los atributos como el código de promoción, porcentaje de descuento y otros valores relacionados con los descuentos.

    - Tiene métodos para validar si un cliente puede aplicar una promoción.
    - Incluye un método para mostrar los detalles del descuento aplicado.
    - Se puede aplicar descuentos dependiendo de si el cliente tiene niños o si es anciano.
    - Los descuentos pueden ser aleatorios o fijos, y se calculan en función del precio original.
    - La clase permite gestionar descuentos tanto con promociones específicas como sin ellas, y tener en cuenta las condiciones de los niños o ancianos en los clientes.
    - La clase también utiliza la clase `Cliente` para asociar los datos de la promoción al cliente, validando la elegibilidad para los descuentos.
    - Utiliza la función `numAleatorio` para generar valores aleatorios que afectan los descuentos aplicados.
    - Los métodos permiten aplicar múltiples tipos de descuentos (porcentaje general, para niños y para ancianos), lo que hace a la clase flexible para diferentes situaciones.
*/
template<typename T1, typename T2>
class Promocion
{
public:
    Promocion() {
        this->codigoPromocion = T1();
        this->porcentajeDescuento = T2();
        this->descuentoAnciano = 7;
        this->descuentoNino = 5;
    }

    Promocion(T1 codProm, T2 porcenDes) {
        this->codigoPromocion = codProm;
        this->porcentajeDescuento = porcenDes;
    }

    void setCodProm(T1 codProm) { this->codigoPromocion = codProm; }
    T1 getCodProm() { return codigoPromocion; }


    bool validarPromo(Cliente<T1, T2>& cliente) {
        return this->codigoPromocion == cliente.getCodPromocion();
    }


    void setPorDescuento(T2 porcenDes) { this->porcentajeDescuento = porcenDes; }
    T2 getPorDescuento() { return porcentajeDescuento; }




    void mostrarDescuento(int porcentaje, T2 descuento, T2 precioFinal) {
        Console::SetCursorPosition(10, 6); cout << "PROMOCION APLICADA" << endl;
        Console::SetCursorPosition(10, 7); cout << "Porcentaje: " << porcentaje << "%" << endl;
        Console::SetCursorPosition(10, 8); cout << "Descuento: S/" << descuento << endl;
        Console::SetCursorPosition(10, 9); cout << "Precio final: S/" << precioFinal << endl;
    }

    T2 aplicarDescuento(T2 precioOriginal, Cliente<T1, T2>& cliente) {

        int porcentajeAleatorio = numAleatorio(20, 10);

        if (cliente.getPromocion() && validarPromo(cliente)) {
            T2 descuento = precioOriginal * (porcentajeAleatorio / 100.0);
            T2 precioFinal = precioOriginal - descuento;
            mostrarDescuento(porcentajeAleatorio, descuento, precioFinal);
            return precioFinal;
        }
        else if (!cliente.getPromocion()) {
            return precioOriginal;
        }
    }



    T2 calcularDescuentoNino(T2 precio, int i) {
        if (i <= 0) {
            return 0;
        }
        return (precio * (descuentoNino / 100)) + calcularDescuentoNino(precio, i - 1);
    }

    T2 aplicarDescuentoSinPromoNino(T2 precioOriginal, Cliente<T1, T2>& cliente) {

        T2 precioFinal = precioOriginal;

        if (cliente.getTieneNino()) {
            T2 descuentoTotal = 0;
            int cantNinos = cliente.getCantNino();

            for (int i = 0; i < cantNinos; i++)
            {
                T2 descuentoNino = calcularDescuentoNino(precioOriginal, 1);
                descuentoTotal += descuentoNino;

                Console::SetCursorPosition(10, 9); cout << "Descuento en soles aplicado por cada nino --> S/" << descuentoNino << endl;
            }

            precioFinal -= descuentoTotal;



        }

        return precioFinal;


    }

    T2 aplicarDescuentoConPromoNino(T2 precioOriginal, Cliente<T1, T2>& cliente) {

        Promocion<T1, T2> promo(cliente.getCodPromocion(), numAleatorio(10, 20));


        T2 precioFinal = promo.aplicarDescuento(precioOriginal, cliente);

        if (cliente.getTieneNino()) {
            int cantNinos = cliente.getCantNino();
            T2 descuentoTotal = 0;

            for (int i = 0; i < cantNinos; i++) {
                T2 descuentoNino = calcularDescuentoNino(precioFinal, 1);
                descuentoTotal += descuentoNino;
                Console::SetCursorPosition(10, 10); cout << "Descuento aplicado por nino --> S/" << descuentoNino << endl;
            }

            precioFinal -= descuentoTotal;

        }

        return precioFinal;
    }




    T2 calcularDescuentoAnciano(T2 precio, int i) {
        if (i <= 0) {
            return 0;
        }
        return (precio * (descuentoAnciano / 100)) + calcularDescuentoAnciano(precio, i - 1);

    }


    T2 aplicarDescuentoSinPromoAnciano(T2 precioOriginal, Cliente<T1, T2>& cliente) {
        T2 precioFinal = precioOriginal;

        if (cliente.getEsAnciano()) {
            T2 descuentoAnciano = calcularDescuentoAnciano(precioOriginal, 1);

            Console::SetCursorPosition(10, 6);
            std::cout << "Descuento aplicado para anciano --> S/" << descuentoAnciano << std::endl;

            precioFinal -= descuentoAnciano;
        }

        if (cliente.getTieneNino()) {
            int cantNinos = cliente.getCantNino();
            T2 descuentoTotal = 0;

            for (int i = 0; i < cantNinos; ++i) {
                T2 descuentoNino = calcularDescuentoNino(precioFinal, 1);
                descuentoTotal += descuentoNino;
            }

            precioFinal -= descuentoTotal;
        }
        return precioFinal;
    }




protected:
    T1 codigoPromocion;
    T2 porcentajeDescuento;
    T2 descuentoNino;
    T2 descuentoAnciano;
};



