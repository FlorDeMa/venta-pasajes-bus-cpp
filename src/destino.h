#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "grafoDestino.h" /*-->Uso de grafos para la clase destinos*/

using namespace std;
//Usi de templates para el punto 
//Todas las estructuras de datos desarrolladas en la aplicación deben ser genéricas
//(implementadas con templates)
template<typename T>
class Destino {
public:
    Destino() {
        this->ciudadOrigen = T();
        this->ciudadDestino = T();
    }

    Destino(T ciudadO, T ciudadD) {
        this->ciudadOrigen = ciudadO;
        this->ciudadDestino = ciudadD;
    }

    void setCiudadO(T ciudadO) { this->ciudadOrigen = ciudadO; }
    T getCiudadO() { return ciudadOrigen; }

    void setCiudadD(T ciudadD) { this->ciudadDestino = ciudadD; }
    T getCiudadD() { return ciudadDestino; }

    void agregarCiudades() {
        ciudades.push_back("Lima");
        ciudades.push_back("Huaraz");
        ciudades.push_back("Chiclayo");
        ciudades.push_back("Chepen");
        ciudades.push_back("Lambayeque");
        ciudades.push_back("Libertad");
        ciudades.push_back("Trujillo");
        ciudades.push_back("Chimbote");

        /*ciudades agregadas a la lista, uso de listas para todas las clases genericas 
        estas son colocadas manualmente*/
    }

    void mostrarCiudades() {
        int posY = 4;
        Console::SetCursorPosition(2, posY);

        cout << "Destinos Disponibles: " << endl;

        for (int i = 0; i < ciudades.size(); i++) {
            posY++;
            Console::SetCursorPosition(2, posY);
            cout << i + 1 << " " << ciudades[i] << endl;
        }
    }

    T getPosCiudad(int pos) {
        if (pos >= 0 && pos < ciudades.size()) {
            return ciudades[pos];
        }
        else {
            Console::SetCursorPosition(4, 25);
            cout << "Posición no válida" << endl;
            return T();
        }
    }

    // Métodos relacionados con el grafo
    void agregarRutaEnGrafo(string origen, string destino, int peso) {
        grafo.agregarArista(origen, destino, peso);
    }

    void mostrarRutasEnGrafo() {
        grafo.mostrarGrafo();
    }

    void calcularRutaMasCorta(string origen) {
        grafo.dijkstra(origen);
    }

private:
    T ciudadOrigen;
    T ciudadDestino;
    vector<T> ciudades;
    Grafo<string> grafo;  // Instancia del grafo para gestionar las rutas
    int posY;
};

