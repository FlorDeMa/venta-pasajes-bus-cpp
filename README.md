# Sistema de venta de pasajes de bus (C++)

Aplicación de consola para gestionar la venta de pasajes de una empresa de buses: clientes, conductores, buses, destinos, promociones y comprobantes de pago. Proyecto final del curso **Algoritmos y Estructura de Datos (CC182)** de Ingeniería de Software en la UPC, desarrollado en un equipo de 3 integrantes (noviembre de 2024).

El objetivo del proyecto fue implementar a mano las estructuras de datos y algoritmos del curso, sin usar las colecciones de la librería estándar para la lógica principal.

## Estructuras de datos y algoritmos

| Componente | Archivo | Uso en la aplicación |
|---|---|---|
| Árbol binario de búsqueda | `ArbolB.h` | Registro y búsqueda de comprobantes de pago |
| Grafo + algoritmo de Dijkstra | `grafoDestino.h`, `destino.h` | Ruta más corta entre destinos |
| Tabla hash | `hashTable.h`, `hashEntidad.h` | Búsqueda rápida de entidades |
| Heap + HeapSort | `heap.h` | Ordenamiento de horarios de buses |
| Listas enlazadas genéricas | `listas.h`, `nodos.h` | Colecciones de clientes, pasajes y buses |
| Ordenamientos recursivos | `diseñoMenu.h`, `hito2.v1.cpp` | Ordenamiento del menú y récord por edades |

El programa trabaja con un dataset de más de 1,000 personas ficticias (`datosPersona.txt`) generado para probar el rendimiento de las estructuras.

## Mi aporte

- Árbol binario de búsqueda para los comprobantes de pago.
- Clases de destinos y grafo, con el algoritmo de Dijkstra.
- Ordenamiento recursivo del menú y ordenamiento para el récord de edades.
- Diseño de la interfaz de consola.
- Generación del dataset y de los archivos de datos (`pasajes.txt`, `datosPersona.txt`).
- Integración final para que la aplicación compile y funcione completa.

## Cómo ejecutarlo

Proyecto creado en Visual Studio (C++). Para compilarlo:

1. Crea un proyecto de consola C++ en Visual Studio.
2. Agrega los archivos de la carpeta `src/`.
3. Compila y ejecuta. Los archivos `.txt` deben estar en el directorio de trabajo.

## Tecnologías

C++ · Visual Studio · estructuras de datos implementadas desde cero
