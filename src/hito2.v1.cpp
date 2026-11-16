#include "pch.h"
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "bus.h"
#include "cliente.h"
#include "pasaje.h"
#include "conductor.h"
#include "diseñoMenu.h"
#include "hashTable.h"
#include "promocion.h"
#include "tipoPasaje.h"
#include "vendedorPasaje.h"
#include "grafoDestino.h"
#include "comprobante.h"
#include "ArbolB.h"
#include "listas.h"
#include <cstdlib>  // Para rand() y srand()
#include <ctime>    // Para time()
#include "heap.h"
//1. * *Estructura de datos usadas : **
//-**Listas y vectores : **Se utilizan listas(clase `Lista`) y vectores para manejar colecciones de clientes y pasajes, permitiendo almacenamiento dinámico y acceso rápido.
//	- **Hash Table : **Se usa la tabla hash `busesHash` para buscar y almacenar códigos de pasajes asociados a buses, mejorando la eficiencia en búsquedas.El método `busesHash.insertar` asocia claves(ID de pasajes) con valores(códigos de pasajes), mientras que `busesHash.buscar` permite recuperar estos datos en tiempo constante promedio.
//	- **Árbol binario(ArbolBB) :**Sirve para almacenar comprobantes ordenados.Su implementación permite búsquedas, inserciones y comparaciones rápidas, gracias al método `compararComprobantes`.
//	- **Heap:**Posiblemente utilizado para priorización, aunque su propósito específico no se detalla en el código presentado.
//
//	2. * *Programación funcional y lambdas : **
//	-Se incluye una función lambda `numAleatorio` que genera números aleatorios dentro de un rango(`min` y `max`), empleando la función `rand()` para tareas relacionadas con descuentos y promociones.Su implementación mejora la modularidad al encapsular esta lógica en una sola línea.
//
using namespace std;

//Trabajo realizado por:
//Flor De Maria Contreras Leon
//Fatima Shimabukuro Florez
//Elizabhet Ápaza Bocanegra

Lista<Pasaje<string>*>* lst_pasajes = new Lista<Pasaje<string>*>();
Lista<Cliente<string, float>*>* lst_cliente = new Lista<Cliente<string, float>*>();
HashTabla<int, string> busesHash;
vector<Pasaje<string>> arregloPasajes;
int pasajeID = 1;


function<int(int, int)>numAleatorio = [](int max, int min) {
	return rand() % (max - min + 1) + min;
	};

//buses disponibles (PRIME)
buses<string> primeBus[3] = {
	buses<string>("BUS01", "08:00", "50", "Jorge", "PRIME"),
	buses<string>("BUS02", "12:00", "50", "Maria", "PRIME"),
	buses<string>("BUS03", "15:00", "50", "Manuel", "PRIME"),
};


//buses disponibles (ELITE)
buses<string> eliteBus[3] = {
	buses<string>("BUS01", "10:00", "50", "Carlos", "ELITE"),
	buses<string>("BUS02", "15:30", "50", "Luis", "ELITE"),
	buses<string>("BUS03", "18:10", "50", "Ana", "ELITE"),
};

//buses disponibles (GOLD)
buses<string> goldBus[3] = {
	buses<string>("BUS01", "10:40", "50", "Diana", "GOLD"),
	buses<string>("BUS02", "13:50", "50", "Sofia", "GOLD"),
	buses<string>("BUS03", "20:00", "50", "Angela", "GOLD"),
};


int compararComprobantes(Comprobante a, Comprobante b) {
	if (a.getNumComprobante() < b.getNumComprobante()) return -1;
	if (a.getNumComprobante() > b.getNumComprobante()) return 1;
	return 0;
}

void mostrarComprobante(Comprobante c) {
	c.mostrarComprobante();
}

void seleccionarHorario(int tipoPasaje) {
	buses<string>* arregloBus;
	int numBuses = 3;

	switch (tipoPasaje)
	{
	case 1:
		Console::SetCursorPosition(10, 10);
		cout << "BUSES PRIME" << endl;
		arregloBus = primeBus;
		break;

	case 2:
		cout << "BUSES ELITE" << endl;
		arregloBus = eliteBus;
		break;

	case 3:
		cout << "BUSES GOLD" << endl;
		arregloBus = goldBus;
		break;

	default:
		Console::SetCursorPosition(10, 10); cout << "OPCION NO VALIDA" << endl;
		break;
	}

	int posY = 12;
	Console::SetCursorPosition(5, posY);

	for (int i = 0; i < numBuses; i++) {
		Console::SetCursorPosition(5, posY + i);

		cout << i + 1 << ". Bus ID: " << arregloBus[i].getId()
			<< ", Horario: " << arregloBus[i].gethorario()
			<< ", Asientos en total: " << arregloBus[i].getasientos()
			<< ", Conductor: " << arregloBus[i].getConductor()
			<< endl;
	}

	int elegido;
	cout << "Seleccione el horario --> ";
	cin >> elegido;
	cout << endl;

	if (elegido >= 1 && elegido <= numBuses) {
		cout << "Ha seleccionado el bus " << arregloBus[elegido - 1].getId()
			<< " con horario " << arregloBus[elegido - 1].gethorario() << endl;
	}
	else {
		cout << "Selección no válida." << endl;
	}
}

//buscar informacion del cliente utilizando el ID del pasaje
void buscarInfoCliente() {
	string codigoPasaje;
	Console::SetCursorPosition(10, 10); cout << "Ingrese el codigo de su pasaje: ";
	cin >> codigoPasaje;

	// Busca el código en el hash table
	for (int i = 0; i < pasajeID; ++i) {
		string resultado = busesHash.buscar(i);
		if (resultado == codigoPasaje) {
			Console::SetCursorPosition(10, 11); cout << "PASAJE ENCONTRADO EN LA TABLA HASH" << endl;
			for (const auto& pasaje : arregloPasajes) {
				if (pasaje.getCodPasaje() == resultado) {
					pasaje.mostrarDatosPasaje();
					return;
				}
			}
			Console::SetCursorPosition(10, 13); cout << "PASAJE NO ENCONTRADO EN LA TABLA HASH" << endl;
			return;
		}
	}
	Console::SetCursorPosition(10, 16); cout << "No se encontro el pasaje" << endl;
}

//Registro de datos del pasaje 
string ingresarPasaje(int i) {
	generarMapaLogin(mapaLogin);
	string cod, tipo, fechaD, fechaE, numeroPasajes, pre, disponible;
	Comprobante comp;
	/*Pago pag;*/
	insertarColor(15);
	cout << "\n";

	Console::SetCursorPosition(10, 4); cout << "========REGISTRAR DATOS DEL PASAJE==========" << endl;
	Console::SetCursorPosition(10, 5); cout << "Ingresar Codigo: "; cin >> cod;
	Console::SetCursorPosition(10, 6); cout << "Ingresar Tipo de Pasajes: "; cin >> tipo;
	Console::SetCursorPosition(10, 7); cout << "Ingresar Fecha Disponible: "; cin >> fechaD;
	Console::SetCursorPosition(10, 8); cout << "Ingresar Fecha Elegida: "; cin >> fechaE;
	Console::SetCursorPosition(10, 9); cout << "Ingresar numero de Asientos: "; cin >> numeroPasajes;
	Console::SetCursorPosition(10, 10); cout << "Ingresar Precio: "; cin >> pre;
	Console::SetCursorPosition(10, 11); cout << "Ingresar Pasaje Disponible: "; cin >> disponible;

	Pasaje<string>* pasaje = new Pasaje<string>(cod, tipo, fechaD, fechaE, numeroPasajes, pre, disponible, comp);
	lst_pasajes->agregaPos(pasaje, i);
	arregloPasajes.push_back(*pasaje);

	// colocar ID del pasaje en la tabla hash
	Console::SetCursorPosition(5, 13);
	int codigoInt = pasajeID++;
	busesHash.insertar(codigoInt, cod); //codigoInt == clave y cod == valor
	Console::SetCursorPosition(5, 14); cout << "Pasaje registrado con Codigo: " << cod << endl;
	//En este punto el codigo ayuda en la busqueda de las hash tables 
	return cod;
}


int menu() {

	int opcion;
	do
	{
		insertarColor(13); cin >> opcion;
		insertarColor(15);
		if (opcion < 0 || opcion>2)
			cout << "Ingrese una opcion valida... ";
	} while (opcion < 0 || opcion>2);
	return opcion;
}

void aplicarPromociones(Cliente<string, float>& cliente, TipoPasaje<string, float>& tipoPasaje) {
	srand(time(0));

	Promocion<string, float> promo;

	float precioBase = tipoPasaje.getPrecioB();
	float precioFinal = precioBase;
	float porcentajeDescuento = numAleatorio(20, 10);

	// Sin promoción, sin anciano y sin niño
	if (!cliente.getPromocion() && !cliente.getEsAnciano() && !cliente.getTieneNino()) {
		Console::SetCursorPosition(10, 4);
		cout << "SIN PROMOCION" << endl;
		precioFinal = promo.aplicarDescuento(precioBase, cliente);
		Console::SetCursorPosition(10, 5);
		cout << "Precio final (adulto) --> S/" << precioFinal << endl;
	}

	// Con promoción, sin anciano y sin niño
	if (cliente.getPromocion() && !cliente.getEsAnciano() && !cliente.getTieneNino()) {
		promo.setCodProm(cliente.getCodPromocion());
		promo.setPorDescuento(porcentajeDescuento);
		precioFinal = promo.aplicarDescuento(precioFinal, cliente);
	}

	// Anciano, sin niño
	if (cliente.getEsAnciano()) {
		precioFinal = promo.aplicarDescuentoSinPromoAnciano(precioFinal, cliente);
		Console::SetCursorPosition(10, 8);
		cout << "Precio final (anciano) --> S/" << precioFinal << endl;
	}

	// Anciano con promoción
	if (cliente.getPromocion() && cliente.getEsAnciano()) {
		precioFinal = promo.aplicarDescuentoSinPromoAnciano(precioFinal, cliente);
	}

	// Con niño, sin promoción ni anciano
	if (!cliente.getPromocion() && !cliente.getEsAnciano() && cliente.getTieneNino()) {
		Console::SetCursorPosition(10, 4);
		cout << "SIN PROMOCION" << endl;
		Console::SetCursorPosition(10, 5);
		cout << "Precio adulto --> S/" << precioFinal << endl;
		precioFinal = promo.aplicarDescuentoSinPromoNino(precioFinal, cliente);
		Console::SetCursorPosition(10, 13);
		cout << "Precio final (adulto y niño) --> S/" << precioFinal << endl;
	}

	// Anciano con niño, sin promoción
	if (!cliente.getPromocion() && cliente.getEsAnciano() && cliente.getTieneNino()) {
		Console::SetCursorPosition(10, 4);
		cout << "SIN PROMOCION" << endl;
		precioFinal = promo.aplicarDescuentoSinPromoNino(precioFinal, cliente);
		Console::SetCursorPosition(10, 14);
		cout << "Precio final (anciano y niños) --> S/" << precioFinal << endl;
	}

	// Anciano con niño y con promoción
	if (cliente.getPromocion() && cliente.getEsAnciano() && cliente.getTieneNino()) {
		promo.setCodProm(cliente.getCodPromocion());
		promo.setPorDescuento(porcentajeDescuento);
		precioFinal = promo.aplicarDescuento(precioFinal, cliente);
		precioFinal = promo.aplicarDescuentoConPromoNino(precioFinal, cliente);
		Console::SetCursorPosition(10, 13);
		cout << "Precio final (anciano y niño) --> S/" << precioFinal << endl;
	}

	// Con niño y con promoción, sin anciano
	if (cliente.getPromocion() && !cliente.getEsAnciano() && cliente.getTieneNino()) {
		promo.setCodProm(cliente.getCodPromocion());
		promo.setPorDescuento(porcentajeDescuento);
		precioFinal = promo.aplicarDescuento(precioFinal, cliente);
		precioFinal = promo.aplicarDescuentoConPromoNino(precioFinal, cliente);
		Console::SetCursorPosition(10, 13);
		cout << "Precio final (adulto y niño) --> S/" << precioFinal << endl;
	}
}


void ingresarCliente(int i) {
	generarMapaLogin(mapaLogin);

	string nom, ape, dni, tele, tarjetaCredito, codigoPromocion;
	int edad, opcionPromo, opcionTieneNino, tipoPasaje;
	bool prom, tieneNino;
	int numNinos;

	insertarColor(15);



	cout << endl;
	Console::SetCursorPosition(10, 4); cout << "======== INGRESAR DATOS DEL CLIENTE ========" << endl;
	Console::SetCursorPosition(10, 5); cout << "Ingresar Nombres: "; cin >> nom;
	Console::SetCursorPosition(10, 6); cout << "Ingresar Apellidos: "; cin >> ape;
	Console::SetCursorPosition(10, 7); cout << "Ingresar DNI: "; cin >> dni;
	Console::SetCursorPosition(10, 8); cout << "Ingresar Telefono: "; cin >> tele;
	Console::SetCursorPosition(10, 9); cout << "Ingresar Edad: "; cin >> edad;
	Console::SetCursorPosition(10, 10); cout << "Ingresar Tarjeta de Credito: "; cin >> tarjetaCredito;



	ofstream TextCliente("datosPersona.txt", ios::app);
	ofstream TextCliente2("pasajes.txt", ios::app);
	if (!TextCliente.is_open()) {
		cout << "No se pudo abrir el archivo" << endl;
	}
	else {
		TextCliente << "\n";
		TextCliente << "Nombres: " << nom << endl;
		TextCliente << "Apellidos: " << ape << endl;
		TextCliente << "DNI: " << dni << endl;
		TextCliente << "Telefono: " << tele << endl;
		TextCliente << "Edad: " << edad << endl;
		TextCliente << "Tarjeta de Credito: " << tarjetaCredito << endl;
	}

	if (!TextCliente2.is_open()) {
		cout << "No se pudo abrir el archivo" << endl;
	}
	else {
		TextCliente2 << "\n";
		TextCliente2 << "Nombres: " << nom << endl;
		TextCliente2 << "Apellidos: " << ape << endl;
		TextCliente2 << "DNI: " << dni << endl;
		TextCliente2 << "Edad: " << edad << endl;
	}

	Console::SetCursorPosition(20, 12); system("pause");
	system("cls");






	generarMapaLogin(mapaLogin);
	TipoPasaje<string, float> pasajeSeleccionado;
	do
	{
		Console::SetCursorPosition(10, 5); cout << "Seleccionar tipo de pasaje (1 = Prime, 2 = Elite, 3 = Gold): ";
		cin >> tipoPasaje;


		if (tipoPasaje == 1) {
			pasajeSeleccionado.setCate("1");
		}
		else if (tipoPasaje == 2) {
			pasajeSeleccionado.setCate("2");
		}
		else if (tipoPasaje == 3) {
			pasajeSeleccionado.setCate("3");
		}
		else {
			Console::SetCursorPosition(10, 6); cout << "Tipo de pasaje no v·lido" << endl;

		}
	} while (tipoPasaje != 1 && tipoPasaje != 2 && tipoPasaje != 3);

	TextCliente << "\n";
	TextCliente << "Tipo pasaje: " << tipoPasaje << endl;






	do {
		Console::SetCursorPosition(10, 10); cout << "Tiene promocion --> (1 = Si, 2 = No): ";
		cin >> opcionPromo;

		if (opcionPromo == 1) {
			prom = true;
			do {
				Console::SetCursorPosition(10, 11); cout << "Ingrese codigo de promocion (6 characteres): ";
				cin >> codigoPromocion;

				if (codigoPromocion.length() != 6) {
					Console::SetCursorPosition(10, 12); cout << "Codigo invalido" << endl;
				}
			} while (codigoPromocion.length() != 6);

			TextCliente << "\n";
			TextCliente << "Promocion --> SI" << endl;
			TextCliente << "Codigo de promocion --> " << codigoPromocion << endl;

			Console::SetCursorPosition(10, 13); cout << "Codigo ingresado --> " << codigoPromocion << endl;
		}
		else if (opcionPromo == 2) {
			prom = false;
			TextCliente << "Promocion --> NO" << endl;
		}
		else {
			Console::SetCursorPosition(5, 10); cout << "OpciÛn no v·lida" << endl;
		}
	} while (opcionPromo != 1 && opcionPromo != 2);



};



vector<int> cargarEdadesArchivo(const string& clienteArchivo) {
	ifstream archivo(clienteArchivo);
	vector<int> edades;
	string linea;

	if (!archivo.is_open()) {
		cout << "No se pudo abrir el archivo" << endl;
		return edades;
	}

	while (getline(archivo, linea)) {
		// Buscar "Edad:" manualmente
		if (linea.size() > 5 && linea[0] == 'E' && linea[1] == 'd' &&
			linea[2] == 'a' && linea[3] == 'd' && linea[4] == ':') {

			// eztraer el número
			int edad = 0;
			for (size_t i = 5; i < linea.size(); ++i) {
				if (linea[i] >= '0' && linea[i] <= '9') {
					edad = edad * 10 + (linea[i] - '0');
				}
				else if (edad > 0) {
					break;  
				}
			}
			edades.push_back(edad);
		}
	}

	archivo.close();
	return edades;
	
}


void cargarDatosArchivo(const string& clienteArchivo, vector<string>& nombres, vector<int>& edades) {
	ifstream archivo(clienteArchivo);
	string linea;

	if (!archivo.is_open()) {
		cout << "No se pudo abrir el archivo" << endl;
		return;  // Retorna si no se pudo abrir el archivo
	}

	string nombre;
	int edad;

	while (getline(archivo, linea)) {
		// Buscar el nombre en la línea, se asume que el nombre está al principio de la línea
		size_t pos = linea.find("Nombre:");
		if (pos != string::npos) {
			// Extraer el nombre
			nombre = linea.substr(pos + 7);  // Asumimos que "Nombre:" tiene 7 caracteres
		}

		// Buscar "Edad:" manualmente
		pos = linea.find("Edad:");
		if (pos != string::npos) {
			// Extraer la edad
			edad = 0;
			for (size_t i = pos + 5; i < linea.size(); ++i) {
				if (linea[i] >= '0' && linea[i] <= '9') {
					edad = edad * 10 + (linea[i] - '0');
				}
				else if (edad > 0) {
					break;
				}
			}
		}

		// Añadir el nombre y la edad a las listas
		if (!nombre.empty() && edad > 0) {
			nombres.push_back(nombre);
			edades.push_back(edad);
		}
	}

	archivo.close();
}
void mostrarClientesDesdeArchivo() {
	ifstream TextCliente("datosPersona.txt");

	if (!TextCliente.is_open()) {
		cout << "No se pudo abrir el archivo para leer los datos del cliente." << endl;
		return;
	}

	string linea;
	while (getline(TextCliente, linea)) {
		cout << linea << endl;
	}
	TextCliente.close();
}

int historialdeVentasMenu() {
	srand(time(0));

	Console::SetWindowSize(80, 28);

	buses<string> bus1;
	Cliente<string, int>cliente1;
	Persona<string, int> cliente;
	Destino<string> destino;
	Heap heap;


	cliente.guardarDatosEnArchivo();

	vector<int> edades = cargarEdadesArchivo("datosPersona.txt");
	Pasaje<string> pasaje1;
	ArbolBB<Comprobante> arbol;
	
	string archivo = "datosPersona.txt";  
	vector<string> nombres;
	


	// int nro_conductores = 0;
	int nro_clientes = 0;
	int nro_pasajes = 0;
	int precioBase = 0;
	int nro_vendedores = 0;

	int option2;
	
	bool continuar = true;
	while (continuar) {
		system("cls");
		generarMapaLogin(mapaLogin);
		Console::SetCursorPosition(5, 9);  cout << "1. Mostrar Pasajes" << endl;
		Console::SetCursorPosition(5, 10); cout << "2. Buscar comprobante" << endl;
		Console::SetCursorPosition(5, 11); cout << "3. Buscar informacion usuario - Tabla Hash" << endl;
		Console::SetCursorPosition(5, 12); cout << "4. Ordenar por edad - Heap" << endl;
		Console::SetCursorPosition(5, 13); cout << "5. Regresar al Menu Principal" << endl;
		Console::SetCursorPosition(5, 14); cout << "Opcion: "; cin >> option2;
		insertarColor(1); cout << endl;
		system("pause");
		insertarColor(1); cout << endl;
		system("cls");
		insertarColor(15); cout << endl;

		switch (option2) {
		case 1:
			cout << "Mostrar Pasajes" << endl;
			mostrarClientesDesdeArchivo();
			cout << "Registro del ultimo Pasaje asignado:";
			for (int i = 0; i < lst_pasajes->longitud(); i++) {
				cout << "Pasaje: " << i + 1 << endl;
				lst_pasajes->obtenerPos(i)->mostrarDatosPasaje();
			}
			system("pause");
			system("cls");
			break;
		case 2:
			cout << "Buscar Comprobante" << endl;
			cliente1.mostrardatosOrdenSort();
		
			/*ingresarBoleta(0);*/

			arbol.Insertar(Comprobante(1001, "12-11-2023", "20123456789", 500.75, "Factura"));
			arbol.Insertar(Comprobante(1002, "13-11-2023", "20123456789", 350.50, "Boleta"));
			arbol.Insertar(Comprobante(1003, "14-11-2023", "20123456789", 1000.25, "Factura"));

			// Buscar un comprobante directamente en el árbol
			if (arbol.Buscar(Comprobante(1002, "", "", 0, ""))) {
				cout << "Comprobante encontrado!" << endl;
			}
			else {
				cout << "Comprobante no encontrado!" << endl;
			}

			// Mostrar todos los comprobantes en orden
			cout << "Comprobantes en orden:" << endl;
			arbol.EnOrden();
			system("pause");
			system("cls");
			break;
		case 3:
			cout << "Buscar información usuario - Tabla Hash" << endl;
			buscarInfoCliente();
			system("pause");
			system("cls");
			break;
		case 4:
			insertarColor(14); cout << "Ordenar por Edad - Resultados Presentados a la RENIEC" << endl;
			insertarColor(4); cout << "Este es el record de edades que como empresa (ALLINBUS) debe presentar al Registro Nacional de Identificación y Estado Civil" << endl;
			insertarColor(4); cout << "Un record de edades que como empresa se prersenta, para el control de viaje de menores de edad. Necesario para el registro. De salidas y entradas" << endl;
			insertarColor(15);
			if (edades.empty()) {
				cout << "No se encontraron edades en el archivo." << endl;
				
			}

			// Ordenar las edades usando heapsort
			heap.heapsort(edades);


			cout << "Edades de menor a mayor --> ";
			heap.mostrarEdadesOrdenadas(edades);
			cargarDatosArchivo(archivo, nombres, edades);

			// Mostrar los datos en formato de tabla
			cout << endl;
			insertarColor(4); cout << "Resultados presentados al ENDES - Instituto Nacional de Estadistica e Informatica " << endl;
			cout << endl;
			insertarColor(15);
			cout << "Nombre\t\tEdad" << endl;
			cout << "---------------------" << endl;

			for (size_t i = 0; i < nombres.size(); ++i) {
				cout << nombres[i] << "\t" << edades[i] << endl;
			}
			system("pause");
			system("cls");
			break;
		case 5:
			generarMapaMenu(mapaMenu);
			logoMenu();
			letrasTitulo();
			system("pause");
			continuar = false; // Salir del menú y regresar al menú principal
			break;
		default:
			cout << "Opción inválida" << endl;
			break;
		}
	}
	return 0;
}

int reservarPasajesMenu() {

	srand(time(0));

	Console::SetWindowSize(80, 28);

	buses<string> bus1;
	Cliente<string, int>cliente1;
	Persona<string, int> cliente;
	Destino<string> destino;
	Heap heap;


	cliente.guardarDatosEnArchivo();
	
	vector<int> edades = cargarEdadesArchivo("datosPersona.txt");
	Pasaje<string> pasaje1;
	ArbolBB<Comprobante> arbol;
	



	// int nro_conductores = 0;
	int nro_clientes = 0;
	int nro_pasajes = 0;
	int precioBase = 0;
	int nro_vendedores = 0;

	int option3;
	int comp;
	string cod;
	bool continuar = true;
	
	while (continuar) {

		system("cls");
		generarMapaLogin(mapaLogin);

		Console::SetCursorPosition(5, 9);  cout << "1. Rutas" << endl;
		Console::SetCursorPosition(5, 10); cout << "2. Agregar Pasajeros" << endl;
		Console::SetCursorPosition(5, 11); cout << "3. Asignar Bus y horario" << endl;
		Console::SetCursorPosition(5, 12); cout << "4. Cambiar horario" << endl;
		Console::SetCursorPosition(5, 13); cout << "5. Regresar al Menu Principal" << endl;
		Console::SetCursorPosition(5, 14); cout << "Opcion: "; cin >> option3;
		insertarColor(1); cout << endl;
		system("pause");
		insertarColor(1); cout << endl;
		system("cls");
		insertarColor(15); cout << endl;
		switch (option3) {
		case 1:
			/*ingresarFactura(0);*/
			destino.agregarCiudades();
			destino.mostrarCiudades();

			// Agregar rutas entre ciudades al grafo
			destino.agregarRutaEnGrafo("Lima", "Huaraz", 100);
			destino.agregarRutaEnGrafo("Lima", "Trujillo", 200);
			destino.agregarRutaEnGrafo("Trujillo", "Chiclayo", 300);

			// Mostrar las rutas en el grafo
			cout << "\nRutas disponibles entre las ciudades:" << endl;
			destino.mostrarRutasEnGrafo();

			// Calcular la ruta más corta desde Lima
			cout << "\nCalculando la ruta más corta desde Lima:" << endl;
			destino.calcularRutaMasCorta("Lima");
			system("pause");
			system("cls");
			break;
		case 2:
			cout << "Agregar Pasajeros" << endl;
			ingresarCliente(nro_clientes);
			nro_clientes++;
			cod = ingresarPasaje(nro_pasajes);
			nro_pasajes++;
			
			system("pause");
			system("cls");
			break;
		case 3:
			cout << "Asignar Bus y Horario" << endl;
			for (int i = 0; i < lst_pasajes->longitud(); i++) {
				cout << "Pasaje: " << i + 1 << endl;
				lst_pasajes->obtenerPos(i)->mostrarDatosPasaje();
			}
			bus1.mostrarhorario();

			
			
			int tipoPasaje;
			cout << endl;
			Console::SetCursorPosition(10, 4); cout << "Selecciona el tipo de su pasaje" << endl;
			Console::SetCursorPosition(10, 5); cout << "1. PRIME" << endl;
			Console::SetCursorPosition(10, 6); cout << "2. ELITE" << endl;
			Console::SetCursorPosition(10, 7); cout << "3. GOLD" << endl;
			Console::SetCursorPosition(10, 8); cout << "TIPO PASAJE --> ";
			cin >> tipoPasaje;

			seleccionarHorario(tipoPasaje);
			system("pause");
			system("cls");
			break;
		case 4:
			cout << "Pasaje Existente por comprobante:" << endl;
			cout << "Ingresar Primer numero del Comprobante:"; cin >> comp;
			if (comp == comp) {
				arbol.Insertar(Comprobante(1001, "12-11-2023", "20123456789", 500.75, "Factura"));
				arbol.Insertar(Comprobante(1001, "12-11-2023", "20123456789", 500.75, "Factura"));
				arbol.Insertar(Comprobante(1002, "13-11-2023", "20123456789", 350.50, "Boleta"));
				arbol.Insertar(Comprobante(1004, "14-11-2023", "20123456789", 1000.25, "Factura"));
				arbol.Insertar(Comprobante(1005, "14-11-2023", "20123456789", 1000.25, "Factura"));
				arbol.Insertar(Comprobante(1006, "14-11-2023", "20123456789", 1000.25, "Factura"));
				arbol.Insertar(Comprobante(1007, "14-11-2023", "20123456789", 1000.25, "Factura"));
			}


			// Buscar un comprobante directamente en el árbol
			if (arbol.Buscar(Comprobante(1004, "", "", 0, ""))) {
				cout << "Comprobante encontrado!" << endl;
				bus1.mostrarhorario();



				int tipoPasaje;
				cout << endl;
				Console::SetCursorPosition(10, 4); cout << "Selecciona el tipo de su pasaje" << endl;
				Console::SetCursorPosition(10, 5); cout << "1. PRIME" << endl;
				Console::SetCursorPosition(10, 6); cout << "2. ELITE" << endl;
				Console::SetCursorPosition(10, 7); cout << "3. GOLD" << endl;
				Console::SetCursorPosition(10, 8); cout << "TIPO PASAJE --> ";
				cin >> tipoPasaje;

				seleccionarHorario(tipoPasaje);
				system("pause");
				system("cls");
			}
			else if (arbol.Buscar(Comprobante(1005, "", "", 0, ""))) {
				cout << "Comprobante encontrado!" << endl;
				bus1.mostrarhorario();



				int tipoPasaje;
				cout << endl;
				Console::SetCursorPosition(10, 4); cout << "Selecciona el tipo de su pasaje" << endl;
				Console::SetCursorPosition(10, 5); cout << "1. PRIME" << endl;
				Console::SetCursorPosition(10, 6); cout << "2. ELITE" << endl;
				Console::SetCursorPosition(10, 7); cout << "3. GOLD" << endl;
				Console::SetCursorPosition(10, 8); cout << "TIPO PASAJE --> ";
				cin >> tipoPasaje;

				seleccionarHorario(tipoPasaje);
				system("pause");
				system("cls");
			}
			else if (arbol.Buscar(Comprobante(1006, "", "", 0, ""))) {
				cout << "Comprobante encontrado!" << endl;
				bus1.mostrarhorario();



				int tipoPasaje;
				cout << endl;
				Console::SetCursorPosition(10, 4); cout << "Selecciona el tipo de su pasaje" << endl;
				Console::SetCursorPosition(10, 5); cout << "1. PRIME" << endl;
				Console::SetCursorPosition(10, 6); cout << "2. ELITE" << endl;
				Console::SetCursorPosition(10, 7); cout << "3. GOLD" << endl;
				Console::SetCursorPosition(10, 8); cout << "TIPO PASAJE --> ";
				cin >> tipoPasaje;

				seleccionarHorario(tipoPasaje);
				system("pause");
				system("cls");
			}
			else if (arbol.Buscar(Comprobante(1007, "", "", 0, ""))) {
				cout << "Comprobante encontrado!" << endl;
				bus1.mostrarhorario();



				int tipoPasaje;
				cout << endl;
				Console::SetCursorPosition(10, 4); cout << "Selecciona el tipo de su pasaje" << endl;
				Console::SetCursorPosition(10, 5); cout << "1. PRIME" << endl;
				Console::SetCursorPosition(10, 6); cout << "2. ELITE" << endl;
				Console::SetCursorPosition(10, 7); cout << "3. GOLD" << endl;
				Console::SetCursorPosition(10, 8); cout << "TIPO PASAJE --> ";
				cin >> tipoPasaje;

				seleccionarHorario(tipoPasaje);
				system("pause");
				system("cls");
			}
			else {
				cout << "Comprobante no encontrado!" << endl;
				cout << "Revise nuevamente su base de datos";
			}
			system("pause");
			system("cls");
			break;
		case 5:
			generarMapaMenu(mapaMenu);
			logoMenu();
			letrasTitulo();
			system("pause");
			continuar = false;// Regresar al menú principal
			break;

		default:
			cout << "Opción inválida" << endl;
			break;
		}
	}
	return 0;
}

int main() {
	srand(time(0));

	Console::SetWindowSize(80, 28);
	generarMapaMenu(mapaMenu);
	logoMenu();
	letrasTitulo();
	system("pause");
	int opcionMenu;

	while (true) {
		opcionMenu = menu();

		switch (opcionMenu) {
		case 1:
			historialdeVentasMenu();  // Muestra el menú de Historial de Ventas
			break;
		case 2:
			reservarPasajesMenu();  // Muestra el menú de Buscar Pasajeros
			break;
		case 3:
			cout << "Saliendo del programa." << endl;
			return 0;
		default:
			cout << "Opción no válida. Por favor elige una opción válida." << endl;
			break;
		}
		system("pause");
		system("cls");
	}

	/***Técnicas avanzadas : **
		-**Árboles binarios : **Aunque no se detalla completamente su implementación, se usan para almacenar comprobantes de manera ordenada.
		- **Ordenamiento : **Se emplea una función de comparación para organizar comprobantes o datos en estructuras como el árbol binario.
		- **Uso de referencias y punteros : **Los objetos como clientes y pasajes son manejados mediante referencias y punteros para optimizar la memoria.*/

}
