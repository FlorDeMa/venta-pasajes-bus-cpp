#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "comprobante.h"
using namespace std;
/*
	Clase Pasaje que gestiona la informacion de un pasaje de transporte.
	Esta clase usa plantillas (template) para permitir la flexibilidad de tipos de datos
	para los atributos como codigo de pasaje, tipo de pasaje, fechas, numero de pasajes, precio, etc.

	- Tiene funciones para guardar los detalles de un pasaje en un archivo de texto
	- Incluye un metodo para mostrar los detalles del pasaje
	- Incluye un metodo para guardar en un archivo de texto ("pasajes.txt") los detalles de un pasaje junto con un comprobante de pago.
	- Usa la clase Comprobante para asociar los datos del comprobante al pasaje.
	- Se puede adaptar a distintos tipos de datos debido al uso de plantillas (template).
*/
template<typename T1>
class Pasaje
{
public:
	Pasaje() {

		codigoPasaje = "";
		tipoPasaje = " ";
		fechaDisponible = " ";
		fechaElegida = " ";
		numeroPasajes = " ";
		precio = " ";
		asientoDisponible = true;
	}

	Pasaje(T1 codPasaje, T1 tipoP, T1 fDisponible, T1 fElegida,
		T1 numPasajes, T1 pre, T1 aDisponible/*, Pago pag*/, Comprobante comp) {

		this->codigoPasaje = codPasaje;
		this->tipoPasaje = tipoP;
		this->fechaDisponible = fDisponible;
		this->fechaElegida = fElegida;
		this->numeroPasajes = numPasajes;
		this->precio = pre;
		this->asientoDisponible = aDisponible;
		/*this->pagos = pag;*/
		this->comprobante = comp;
	}


	void setCodPasaje(T1 codPasaje) { this->codigoPasaje = codPasaje; }
	T1 getCodPasaje() const { return codigoPasaje; }

	void setTipoP(T1 tipoP) { this->tipoPasaje = tipoP; }
	T1 getTipoP() { return tipoPasaje; }

	void setFeDisponible(T1 fDisponible) { this->fechaDisponible = fDisponible; }
	T1 getFeDisponible() { return fechaDisponible; }

	void setFeElegida(T1 fElegida) { this->fechaElegida = fElegida; }
	T1 getFeElegida() { return fechaElegida; }

	void setNumPasajes(T1 numPasajes) { this->numeroPasajes = numPasajes; }
	T1 getNumPasajes() { return numeroPasajes; }

	void setPre(T1 pre) { this->precio = pre; }
	T1 getPre() { return precio; }

	void setADisponible(T1 aDisponible) { this->asientoDisponible = aDisponible; }
	T1 getADisponible() { return asientoDisponible; }

	/*void setPagos(Pago pag) { this->pagos = pag; }
	Pago getPagos() { return pagos; }*/

	void setComp(Comprobante comp) { this->comprobante = comp; }
	Comprobante getComp() { return comprobante; }

	void mostrarDatosPasaje() const {

		cout << "\n";
		Console::SetCursorPosition(10, 18);  cout << "===========Pasaje Asignado =========" << endl;
		Console::SetCursorPosition(10, 19);  cout << "Codigo: " << this->codigoPasaje << endl;
		Console::SetCursorPosition(10, 20); cout << "Tipo Pasaje:" << this->tipoPasaje << endl;
		Console::SetCursorPosition(10, 21);  cout << "Fecha Disponible: " << this->fechaDisponible << endl;
		Console::SetCursorPosition(10, 22);  cout << "Fecha Elegida: " << this->fechaElegida << endl;


	}

	void guardarArchivo() {

		ofstream archivo("pasajes.txt", ios::app);

		if (!archivo.is_open()) {
			cout << "No se pudo abrir el archivo" << endl;
			return;
		}

		archivo << "DETALLES DEL PASAJE" << endl;
		archivo << "Codigo del Pasaje: " << codigoPasaje << endl;
		archivo << "Tipo de Pasaje: " << tipoPasaje << endl;
		archivo << "Fecha Disponible: " << fechaDisponible << endl;
		archivo << "Fecha Elegida: " << fechaElegida << endl;
		archivo << "Numero de Pasajes: " << numeroPasajes << endl;
		archivo << "Precio: " << precio << endl;
		archivo << "Asiento Disponible: " << (asientoDisponible ? "Si" : "No") << endl;

	
		archivo << "-------------------------------" << endl;
		archivo << "DETALLES DEL COMPROBANTE" << endl;
		archivo << "Numero de Comprobante: " << comprobante.getNumComprobante() << endl;
		archivo << "Fecha: " << comprobante.getFecha() << endl;
		archivo << "RUC: " << comprobante.getRuc() << endl;
		archivo << "Monto Total: " << comprobante.getMontoTotal() << endl;
		archivo << "Tipo de Comprobante: " << comprobante.getTipoCompro() << endl;

		archivo.close();
		cout << "Pasaje y pago guardado" << endl;
	}


private:
	T1 codigoPasaje;
	T1 tipoPasaje;
	T1 fechaDisponible;
	T1 fechaElegida;
	T1 numeroPasajes;
	T1 precio;
	T1 asientoDisponible;
	/*Pago pagos;*/
	Comprobante comprobante;
};

