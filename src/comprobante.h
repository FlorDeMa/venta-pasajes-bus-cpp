#pragma once
#include <string>
#include <iostream>
#include <fstream>

class Comprobante {
private:
    int numeroComprobante;
    string fecha;
    string ruc;
    float montoTotal;
    string tipoComprobante;

public:
    Comprobante() : numeroComprobante(0), montoTotal(0.0) {}

    Comprobante(int numComp, string fe, string ru, float montoT, string tipoComp) {
        this->numeroComprobante = numComp;
        this->fecha = fe;
        this->ruc = ru;
        this->montoTotal = montoT;
        this->tipoComprobante = tipoComp;
    }

    int getNumComprobante() const { return numeroComprobante; }
    string getFecha() const { return fecha; }
    string getRuc() const { return ruc; }
    float getMontoTotal() const { return montoTotal; }
    string getTipoCompro() const { return tipoComprobante; }

    void mostrarComprobante() const {
        cout << "Numero de Comprobante: " << numeroComprobante << endl;
        cout << "Fecha: " << fecha << endl;
        cout << "RUC: " << ruc << endl;
        cout << "Monto Total: " << montoTotal << endl;
        cout << "Tipo de Comprobante: " << tipoComprobante << endl;
        cout << "-------------------------------" << endl;
    }

    friend ostream& operator<<(ostream& os, const Comprobante& comprobante) {
        os << "Numero de Comprobante: " << comprobante.numeroComprobante << endl;
        os << "Fecha: " << comprobante.fecha << endl;
        os << "RUC: " << comprobante.ruc << endl;
        os << "Monto Total: " << comprobante.montoTotal << endl;
        os << "Tipo de Comprobante: " << comprobante.tipoComprobante << endl;
        os << "-------------------------------";
        return os;
    }

    // Sobrecarga de operadores
    bool operator<(const Comprobante& otro) const {
        return this->numeroComprobante < otro.numeroComprobante;
    }

    bool operator>(const Comprobante& otro) const {
        return this->numeroComprobante > otro.numeroComprobante;
    }

    bool operator==(const Comprobante& otro) const {
        return this->numeroComprobante == otro.numeroComprobante;
    }
};
