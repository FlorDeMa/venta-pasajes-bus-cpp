#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>  // Para rand() y srand()
#include <ctime>    // Para time()
#include <vector>
#include <string>

using namespace std;

/*
    Clase Persona que gestiona la información de una persona.
    Esta clase utiliza plantillas (template) para permitir la flexibilidad de tipos de datos
    para los atributos como nombre, apellido, edad, fecha de nacimiento, dni, y celular.

    - El constructor por defecto genera datos aleatorios para los atributos.
    - El constructor con parámetros permite crear objetos de tipo Persona con datos específicos.
    - Incluye getters y setters para manipular los atributos.
    - Tiene un método para mostrar los detalles de la persona en consola.
    - Incluye un método para guardar los datos de la persona en un archivo de texto ("datosPersona.txt").
    - Se utilizan vectores para almacenar nombres y apellidos aleatorios.
    - Se utiliza srand() y time() para inicializar la semilla de los números aleatorios.
    - La clase es flexible y puede adaptarse a diferentes tipos de datos para los atributos debido al uso de plantillas (template).
*/
template <typename T1, typename T2>
class Persona {
private:
    T1 nombre;
    T1 apellido;
    T2 edad;
    T1 fechaNacimiento;
    T1 dni;
    T1 celular;

public:
    // Constructor por defecto con datos aleatorios
    Persona() {
        vector<T1> nombres = { "Carlos", "Maria", "Jose", "Ana", "Pedro", "Luisa" };
        vector<T1> apellidos = { "Perez", "Lopez", "Garcia", "Rodriguez", "Fernandez", "Gomez" };

        srand(time(0));  // Inicializa la semilla para aleatoriedad

        this->nombre = nombres[rand() % nombres.size()];
        this->apellido = apellidos[rand() % apellidos.size()];
        this->edad = rand() % 100;  // Edad aleatoria entre 0 y 99
        this->fechaNacimiento = "01/01/19" + to_string(rand() % 100);  // Año entre 1900 y 1999
        this->dni = to_string(10000000 + rand() % 90000000);  // DNI aleatorio
        this->celular = to_string(900000000 + rand() % 100000000);  // Celular aleatorio

        //Esto ayudara al generador de data set 
    }

    // Constructor con parámetros
    Persona(T1 pnombre, T1 papellido, T2 pedad,
        T1 pfechaNacimiento, T1 pdni, T1 pcelular) {
        this->nombre = pnombre;
        this->apellido = papellido;
        this->edad = pedad;
        this->fechaNacimiento = pfechaNacimiento;
        this->dni = pdni;
        this->celular = pcelular;
    }

    ~Persona() {}

    // Getters y setters
    void setnombre(T1 pnombre) { this->nombre = pnombre; }
    T1 getnombre() const { return this->nombre; }

    void setapellido(T1 papellido) { this->apellido = papellido; }
    T1 getapellido() const { return this->apellido; }

    void setedad(T2 pedad) { this->edad = pedad; }
    T2 getedad() const { return this->edad; }

    void setfechaNacimiento(T1 pfechaNacimiento) { this->fechaNacimiento = pfechaNacimiento; }
    T1 getfechaNacimiento() const { return this->fechaNacimiento; }

    void setdni(T1 pdni) { this->dni = pdni; }
    T1 getdni() const { return this->dni; }

    void setcelular(T1 pcelular) { this->celular = pcelular; }
    T1 getcelular() const { return this->celular; }

    // Mostrar datos por consola
    void mostrarPersona() const {
        cout << "Nombre: " << this->nombre << endl;
        cout << "Apellido: " << this->apellido << endl;
        cout << "Edad: " << this->edad << endl;
        cout << "Fecha de nacimiento: " << this->fechaNacimiento << endl;
        cout << "DNI: " << this->dni << endl;
        cout << "Celular: " << this->celular << endl;
    }

    // Guardar los datos en un archivo
    void guardarDatosEnArchivo() const {
        ofstream archivoClientes("datosPersona.txt", ios::app);

        if (!archivoClientes.is_open()) {
            cout << "Error al abrir el archivo para escribir." << endl;
            return;
        }

        archivoClientes << "Nombre: " << this->getnombre() << endl;
        archivoClientes << "Apellido: " << this->getapellido() << endl;
        archivoClientes << "Edad: " << this->getedad() << endl;
        archivoClientes << "Fecha de nacimiento: " << this->getfechaNacimiento() << endl;
        archivoClientes << "DNI: " << this->getdni() << endl;
        archivoClientes << "Celular: " << this->getcelular() << endl;
        archivoClientes << "-------------------------" << endl;

        archivoClientes.close();
        cout << "Datos guardados correctamente." << endl;
    }
};


