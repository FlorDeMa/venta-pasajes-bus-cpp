#pragma once
#include "Persona.h"
#include "destino.h"
#include <fstream>
#include <string>
#include <vector>

const int MAX_clientes = 100;

using namespace std;

template <typename T1, typename T2>
/*
   Clase Cliente:
   Esta clase hereda de la clase Persona y se encarga de representar los datos relacionados con los clientes,
   incluyendo su tarjeta de credito, promocion, destinos y detalles sobre los niños a su cargo.
   La clase utiliza plantillas para permitir que los tipos de datos para los atributos sean flexibles
   y puedan adaptarse a diferentes tipos (por ejemplo, numeros enteros, cadenas, etc.).

   Atributos:
   - tarjetaCredito: Almacena el numero de tarjeta de credito del cliente.
   - codigoPromocion: Almacena el codigo de promocion del cliente.
   - promocion: Un valor booleano que indica si el cliente tiene alguna promocion.
   - esAnciano: Un valor booleano que indica si el cliente es considerado anciano (mayor o igual a 70 años).
   - tieneNino: Indica si el cliente tiene niños a su cargo.
   - destinoOrigenElegido: Objeto de la clase Destino que representa el destino de origen del cliente.
   - destinoFinalElegido: Objeto de la clase Destino que representa el destino final del cliente.
   - nombresNinos: Vector que almacena los nombres de los niños a cargo del cliente.
   - apellidosNinos: Vector que almacena los apellidos de los niños a cargo del cliente.
   - edadesNinos: Vector que almacena las edades de los niños a cargo del cliente.

   Metodos:
   - Constructores: Se proporcionan tanto un constructor por defecto como uno parametrizado para inicializar los
	 atributos de la clase Cliente.
   - Setters y Getters: Métodos que permiten obtener y modificar los valores de los atributos de la clase.
   - agregarNino(): Permite agregar un niño al cliente, con su nombre, apellido y edad.
   - mostrarDatos(): Muestra los datos del cliente, incluyendo su información personal y detalles de los niños
	 a su cargo.
   - ordenarDatos(): Un método para ordenar datos (por ejemplo, los nombres de los clientes) de acuerdo a un
	 criterio dado.
   - mostrardatosOrdenSort(): Lee datos de un archivo y los ordena. ---> Metodo de ordenamiento 
*/

//Como usamos sort se cumple el etipulado Aplicación de un algoritmo de ordenamiento avanzado
class Cliente :public Persona<T1, T2>
{
public:

	Cliente() {

		this->tarjetaCredito = T1();
		this->codigoPromocion = T1();
		this->promocion = false;
		this->esAnciano = false;
		this->tieneNino = false;

	}

	Cliente(T1 pCredito, bool pPromocion, T1 codPromocion, Destino<T1>pDestinoOrigen, Destino<T1> pDestinoFinal) :Persona<T1, T2>() {

		this->tarjetaCredito = pCredito;
		this->codigoPromocion = codPromocion;
		this->promocion = pPromocion;
		this->destinoOrigenElegido = pDestinoOrigen;
		this->destinoFinalElegido = pDestinoFinal;

		if (this->getedad() >= 70) {
			this->esAnciano = true;
		}
		else {
			this->esAnciano = false;
		}
	}

	void setTarjetaCredito(T1 pCredito) { this->tarjetaCredito = pCredito; }
	T1 getTarjetaCredito() { return tarjetaCredito; }

	void setCodPromocion(T1 codPromocion) { this->codigoPromocion = codPromocion; }
	T1 getCodPromocion() { return codigoPromocion; }

	void setPromocion(bool pPromocion) { this->promocion = pPromocion; }
	bool getPromocion() { return promocion; }

	void setEsAnciano(bool anciano) { this->esAnciano = anciano; }
	bool getEsAnciano() { return esAnciano; }

	void setDestinoOrigenEle(Destino<T1>pDestinoOrigen) { this->destinoOrigenElegido = pDestinoOrigen; }
	Destino <T1> getDestinoOrigenEle() { return destinoOrigenElegido; }

	void setDestinoFinalEle(Destino<T1>pDestinoFinal) { this->destinoFinalElegido = pDestinoFinal; }
	Destino <T1> getDestinoFinalEle() { return destinoFinalElegido; }

	T2 getCantNino() { return nombresNinos.size(); }

	void setTieneNino(bool tieneN) { this->tieneNino = tieneN; }
	bool getTieneNino() { return tieneNino; }

	void agregarNino(T1 pNomNino, T1 pApeNino, T2 pEdNino) {
		tieneNino = true;
		nombresNinos.push_back(pNomNino);
		apellidosNinos.push_back(pApeNino);
		edadesNinos.push_back(pEdNino);
	}

	T1 getNomNino(int i) { return nombresNinos.at(i); }
	T1 getApeNino(int i) { return apellidosNinos.at(i); }
	T2 getEdadNino(int i) { return edadesNinos.at(i); }

	void mostrarDatosNino() {

		if (!nombresNinos.empty()) {
			cout << "Datos del nino:" << endl;
			for (int i = 0; i < nombresNinos.size(); i++) {
				cout << "NINO " << i + 1 << ":" << endl;
				cout << "Nombre: " << nombresNinos[i] << endl;
				cout << "Apellido: " << apellidosNinos[i] << endl;
				cout << "Edad: " << edadesNinos[i] << endl;
			}
		}
		else {
			cout << "No tiene ninos a su cargo" << endl;
		}
	}

	void mostrarDatos() {
		cout << "Datos del cliente:" << endl;

		Persona<T1, T2>::mostrarPersona();

		cout << "Tarjeta de credito: " << tarjetaCredito << endl;
		cout << "Promocion: ";

		if (promocion) {
			cout << "Tiene promocion" << endl;
		}
		else {
			cout << "No tiene promocion" << endl;
		}

		if (esAnciano) {
			cout << "Este cliente es un anciano" << endl;
		}
		else {
			cout << "Este cliente no es un anciano" << endl;
		}
		mostrarDatosNino();

		cout << "Destino de origen: " << destinoOrigenElegido.getCiudadO() << endl;
		cout << "Destino final: " << destinoFinalElegido.getCiudadD() << endl;
	}
	void ordenarDatos(string dns[], int count) {

		auto comparar = [](const string& a, const string& b) {
			return a > b;
			};

		bool intercambio;
		for (int i = 0; i < count - 1; i++) {
			intercambio = false;

			for (int j = 0; j < count - i - 1; j++) {
				if (comparar(dns[j], dns[j + 1])) {
					string temp = dns[j];
					dns[j] = dns[j + 1];
					dns[j + 1] = temp;
					intercambio = true;
				}
			}

			if (!intercambio) {
				break;
			}
		}
	}


	void mostrardatosOrdenSort() {
		ifstream nomArch;
		string dns[MAX_clientes];
		string tarjeta;
		int count = 0;
		int posY = 4;


		nomArch.open("datosTarjeta.txt", ios::in);
		if (nomArch.is_open()) {
			while (getline(nomArch, tarjetaCredito) && count < MAX) {
				dns[count] = tarjetaCredito;
				count++;
			}
			nomArch.close();
		}


		ordenarDatos(dns, count);


		for (int i = 0; i < count; i++) {
			insertarColor(15);

			Console::SetCursorPosition(10, posY); cout << "Tarjeta de los ultimos  clientes: " << dns[i] << endl;
			posY++;

		}
	}
	void guardarDatosEnArchivo() {
		ofstream archivoClientes("datosTarjeta.txt", ios::app);

		if (!archivoClientes.is_open()) {
			cout << "Error al abrir el archivo para escribir." << endl;
			return;
		}


		archivoClientes << this->getTarjetaCredito() << endl;

		archivoClientes.close();
		cout << "Tarjeta  guardada correctamente." << endl;
	}

	void mostrarClientesDesdeArchivo() const {
		ifstream archivoClientes("datosPersona.txt");

		if (!archivoClientes.is_open()) {
			cout << "Error al abrir el archivo para leer los datos de los clientes." << endl;
			return;
		}

		string linea;
		cout << "===== Lista de Clientes Guardados =====" << endl;

		while (getline(archivoClientes, linea)) {
			cout << linea << endl;
		}

		archivoClientes.close();
		cout << "========================================" << endl;
	}

	void guardarClienteEnArchivo() const {
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

		archivoClientes << "Tarjeta de Credito: " << this->getTarjetaCredito() << endl;
		archivoClientes << "Codigo de Promocion: " << this->getCodPromocion() << endl;
		archivoClientes << "Promocion: " << (this->getPromocion() ? "Sí" : "No") << endl;
		archivoClientes << "Es Anciano: " << (this->getEsAnciano() ? "Sí" : "No") << endl;

		archivoClientes << "Destino de Origen: " << this->getDestinoOrigenEle().getCiudadO() << endl;
		archivoClientes << "Destino Final: " << this->getDestinoFinalEle().getCiudadD() << endl;

		archivoClientes << "-------------------------" << endl;

		archivoClientes.close();
		cout << "Datos guardados correctamente." << endl;
	}

private:
	T1 tarjetaCredito;
	T1 codigoPromocion;
	bool promocion;
	bool esAnciano;
	bool tieneNino;

	vector<T1> nombresNinos;
	vector<T1> apellidosNinos;
	vector<T2> edadesNinos;
	Destino<T1>destinoOrigenElegido;
	Destino<T1> destinoFinalElegido;
};

