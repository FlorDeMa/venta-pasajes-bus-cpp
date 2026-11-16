
#pragma once
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

const int MAX = 100;
// Clase buses: Es una plantilla generica que maneja informacion sobre buses, como su id, horario, cantidad de asientos,
// conductor y categoria. Incluye un constructor por defecto que inicializa estos atributos con valores por defecto y 
// un constructor parametrizado para asignar valores especificos. Proporciona metodos para establecer y obtener los 
// valores de cada atributo, asi como un metodo para ordenar y mostrar los horarios de los buses desde un archivo de texto. 
// Ademas, tiene un metodo recursivo para imprimir los horarios disponibles. Facilita la gestion de los datos relacionados 
// con los buses y su horario en una aplicacion.
template <typename T>
class buses {
public:
    buses() {
        this->id = T();
        this->horario = T();
        this->asientos = T();
        this->conductor = T();
        this->categoria = T();
    }

    buses(T Bid, T Bhorario, T Basientos, T Bconductor, T Bcategoria) {
        this->id = Bid;
        this->horario = Bhorario;
        this->asientos = Basientos;
        this->conductor = Bconductor;
        this->categoria = Bcategoria;
    }

    ~buses() {
    }

    void setId(T Bid) { this->id = Bid; }
    T getId() { return this->id; }

    void sethorario(T Bhorario) { this->horario = Bhorario; }
    T gethorario() { return this->horario; }

    void setasientos(T Basientos) { this->asientos = Basientos; }
    T getasientos() { return this->asientos; }

    void setConductor(T Bconductor) { this->conductor = Bconductor; }
    T getConductor() { return this->conductor; }

    void setCategoria(T Bcategoria) { this->categoria = Bcategoria; }
    T getCategoria() { return this->categoria; }


    void ordenarHorarios(string horarios[], int count) {
        for (int i = 0; i < count - 1; i++) {
            for (int j = i + 1; j < count; j++) {
                if (horarios[i] > horarios[j]) {

                    string temp = horarios[i];
                    horarios[i] = horarios[j];
                    horarios[j] = temp;
                }
            }
        }
    }


    void mostrarhorarioRecursivo(string horarios[], int count, int index) {
        int posY = 4;
        if (index >= count) {
            return;
        }
        cout << endl;
        cout << "    Los horarios disponibles son: " << horarios[index] << endl;
        mostrarhorarioRecursivo(horarios, count, index + 1);

    }

    void mostrarhorario() {
        ifstream nomArch;
        string horarios[MAX];
        string hora;
        int count = 0;

        nomArch.open("horario.txt", ios::in);
        if (nomArch.is_open()) {
            while (getline(nomArch, hora) && count < MAX) {
                horarios[count] = hora;
                count++;
            }
            nomArch.close();
        }

        mostrarhorarioRecursivo(horarios, count, 0);
    }

    void mostrarHorarioBuses() {
        cout << "==== Horarios Disponibles para el Bus ID: " << id << " ====" << endl;

        for (int i = 0; i < horarioTabla.size(); i++) {
            int asientosDisponibles = horarioTabla.buscar(i);
            if (asientosDisponibles != -1) {
                cout << "Hora " << i << ": " << asientosDisponibles << " asientos disponibles" << endl;
            }
        }
        cout << "=========================================" << endl;
    }



private:
    T id;
    T horario;
    T asientos;
    T conductor;
    T categoria;
};