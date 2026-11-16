#pragma once
#include <iostream>
#include <vector>

using namespace std;
/*
    Clase Heap que implementa el algoritmo de ordenamiento Heap Sort
    y las operaciones necesarias para manipular un monton maximo (Max Heap).
    - heapsort: Ordena un vector de enteros usando el algoritmo Heap Sort.
    - mostrarEdadesOrdenadas: Muestra el contenido del vector de edades ordenado.
    - maxHeapify: Mantiene la propiedad del monton maximo (Max Heap) ajustando el monton.
    - buildMaxHeap: Construye un monton maximo a partir de un vector de enteros.
*/
class Heap {
public:

    void heapsort(vector<int>& A) {
        int n = A.size();
        buildMaxHeap(A);
        for (int i = n - 1; i > 0; i--) {
        	swap(A[0], A[i]);
        	maxHeapify(A, i, 0);
        }
    }

    void mostrarEdadesOrdenadas(const vector<int>& edades) {
        for (int edad : edades) {
        	cout << edad << " ";
        }
        cout << endl;
    }

private:
    int parent(int i){ return (i - 1) / 2; }

    int left(int i){ return 2 * i + 1; }

    int right(int i){ return 2 * i + 2; }

    void maxHeapify(vector<int>& A, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        
        if (left < n && A[left] > A[largest]) {
            largest = left;
        }
        
        if (right < n && A[right] > A[largest]) {
            largest = right;
        }
        
        if (largest != i) {
        	swap(A[i], A[largest]);
        	maxHeapify(A, n, largest);
        }
    }

    void buildMaxHeap(vector<int>& A) {
        int n = A.size();

        for (int i = n / 2 - 1; i >= 0; i--) {
        	maxHeapify(A, n, i);
        }
    }


};

