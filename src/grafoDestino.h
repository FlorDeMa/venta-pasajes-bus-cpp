#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <limits>

using namespace std;

// Clase Grafo 

//En esta clase implementamos el grafo para la distancia en km de las ciudades ingresadas
template<typename T>
class Grafo {
private:
    // Estructura para representar las conexiones entre los nodos
    map<T, vector<pair<T, int>>> adjList;  // Nodo -> (nodo conectado, peso)
    map<T, int> tiemposEstimados;

public:
    // Método para agregar una arista (conexión entre dos nodos)
    void agregarArista(T origen, T destino, int peso) {
        adjList[origen].push_back(make_pair(destino, peso));
        adjList[destino].push_back(make_pair(origen, peso)); // Si es no dirigido
    }

    // Método para mostrar el grafo (para depuración)
    void mostrarGrafo() {
        for (auto nodo : adjList) {
            cout << "Ciudad " << nodo.first << " esta conectado a: ";
            for (auto vecino : nodo.second) {
                cout << vecino.first << " (KM: " << vecino.second << "), ";
            }
            cout << endl;
        }
    }

    // Método para implementar Dijkstra (encontrar ruta más corta)
    void dijkstra(T origen) {
        map<T, int> distancias;
        int operacion;
        // Establecer las distancias a "infinito" para todos los nodos
        for (auto nodo : adjList) {
            distancias[nodo.first] = INT_MAX;  // Usamos INT_MAX para representar "infinito"
        }

        distancias[origen] = 0;  // La distancia al nodo origen es 0

        // Cola de prioridad para manejar los nodos con menor distancia
        priority_queue<pair<int, T>, vector<pair<int, T>>, greater<pair<int, T>>> pq;
        pq.push(make_pair(0, origen));

        while (!pq.empty()) {
            T nodoActual = pq.top().second;
            int distanciaActual = pq.top().first;
            pq.pop();

            // Recorrer los nodos vecinos del nodo actual
            for (auto vecino : adjList[nodoActual]) {
                T nodoVecino = vecino.first;
                int peso = vecino.second;
                // Si encontramos una ruta más corta hacia el nodo vecino
                if (distanciaActual + peso < distancias[nodoVecino]) {
                    distancias[nodoVecino] = distanciaActual + peso;
                    pq.push(make_pair(distancias[nodoVecino], nodoVecino));
                }
            }
        }

        //Uso de recursividad para el calculo de horas en distancia este aplicado despues en el timepo estimado
        for (auto distancia : distancias) {
    tiemposEstimados[distancia.first] = distancia.second / 100; // Calcula el tiempo
}
        // Mostrar distancias desde el nodo origen
        for (auto distancia : distancias) {
           
            cout << "Distancia desde " << origen << " a " << distancia.first << " es " << distancia.second
                << ". El tiempo estimado de traslado es: " << tiemposEstimados[distancia.first] << " horas." << endl;

        }
    }
};

