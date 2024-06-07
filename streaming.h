#ifndef STREAMING_H
#define STREAMING_H

#include <sstream>
#include "multimedia.h"

class Streaming {
	private:
	std::string nombre;
	Multimedia *contenido[100];
	int numContenido;
	public:
	Streaming():numContenido(0), nombre(""){};
	Streaming(std::string nom):nombre(nom),numContenido(0){};
	void setNombre(std::string _nombre){nombre = _nombre;}
	std::string lanzaMultimedia(Multimedia *nuevo);
	std::string getNombre(){return nombre;}
	std::string catalogo() const;
	std::string to_string();
	Multimedia* consulta_multimedia(int x)const{ return contenido[x]; }
	Multimedia* modifica_multimedia(int x){ return contenido[x]; }
	int getNumContenido(){ return numContenido; }
};

std::string Streaming::lanzaMultimedia(Multimedia *nuevo) {
	if( nuevo->bloqueado() ) {
		std::string aux = "No se puede agregar este contenido porque es ";
		aux+="exclusivo de otra(s) plataforma(s)";
		return aux;
	}
	contenido[numContenido] = nuevo;
	++numContenido;
	return "Contenido agregado con exito";
}

std::string Streaming::catalogo() const {
	std::stringstream ss;
	if( numContenido == 0 ) {
		return ss.str();
	}
	for( int i=0; i<numContenido; i++ ) {
		ss << i+1 << ". " << contenido[i]->getNombre() << "\n";
	}
	return ss.str();
}

std::string Streaming::to_string() {
	std::stringstream ss;
	ss << nombre << "\n";
	for( int i=0; i<numContenido; i++ ) {
		ss << contenido[i]->to_string();
	}
	return ss.str();
}

#endif