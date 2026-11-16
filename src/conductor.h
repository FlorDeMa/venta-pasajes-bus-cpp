#pragma once
#include <iostream>
#include <string>
#include "persona.h"
//Esta clase se usa con bus y esta mas detalla en el cpp
template<typename T1, typename T2>
class Conductor:public Persona<T1,T2>
{
public:
	Conductor():Persona <T1,T2>() {
		this->codconductor = T1();
		this->horario = T1();
		this->bus = T1();
	}

	Conductor(T1 Cconductor, T1 Chorario, T1 Cbus, T1 Eid, T1 Enombres, T1 Eapellidos, T1 Etelefono, T1 Ecategoria):Persona <T1,T2>(nombre, apellido, edad, fechaNacimiento, dni, celular) {
		this->codconductor = Cconductor;
		this->horario = Chorario;
		this->bus = Cbus;
	}

	void setCodconductor(T1 Cconductor) { this->codconductor = Cconductor; }
	T1 getCodconductor() { return this->codconductor; }

	void setHorario(T1 Chorario) { this->horario = Chorario; }
	T1 getHorario() { return this->horario; }

	void setBus(T1 Cbus) { this->bus = Cbus; }
	T1 getBus() { return this->bus; }


	void mostrardatosConductor()
	{
		cout << "\n";
		cout << "===========Conductor Asignado =========" << endl;
		cout << "Codigo: " << this->codconductor << endl;
		cout << "Horario: " << this->horario << endl;
		cout << "bus: " << this->bus << endl;
		this->mostrarPersona();
	}

private:
	T1 codconductor;
	T1 horario;
	T1 bus;
};

