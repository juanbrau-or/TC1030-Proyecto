#ifndef STREAMING_H
#define STREAMING_H

// importo librerias a utilizar
#include <sstream>
#include "multimedia.h"

/*
* Declaro la clase Streaming que sirve para almacenar apuntadores de
* tipo Multimedia* para tener una base de datos de peliculas y series
*/
class Streaming {
	private:
	std::string nombre;
	Multimedia *contenido[100];
	int numContenido;
	public:
	// constructor vacio
	Streaming():numContenido(0), nombre(""){};
	// constructor con el nombre inicializado
	Streaming(std::string nom):nombre(nom),numContenido(0){};
	// cambia el nombre del servicio de streaming
	void setNombre(std::string _nombre){nombre = _nombre;}
	std::string lanzaMultimedia(Multimedia *nuevo);
	// regresa el nombre del streaming
	std::string getNombre(){return nombre;}
	std::string catalogo() const;
	std::string to_string();
	// regresa un apuntador para consulta de un titulo
	Multimedia* consulta_multimedia(int x)const{ return contenido[x]; }
	// regresa un apuntador para modificar un titulo
	Multimedia* modifica_multimedia(int x){ return contenido[x]; }
	// regresa el numero de los titulos con los que cuenta el streaming
	int getNumContenido(){ return numContenido; }
};

/*
* lanzaMultimedia agrega nuevo contenido al servicio de streaming
* 
* @ param Multimedia*, apuntador al contenido a ser agregado
* @ return string, indica si el contenido se pudo agregar o no
*/
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

/*
* recorre el arreglo de apuntadores y va agregando a una string los
* titulos del contenido del servicio de streaming
* 
* @ param 
* @ return string con los titulos de los contenidos del streaming
*/
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

/*
* to_string convierte todo el servicio a una string, incluyendo el 
* nombre del servicio y la informacion completa de todos los Multimedia
* 
* @ param 
* @ return string con la informacion completa del servicio
*/
std::string Streaming::to_string() {
	std::stringstream ss;
	ss << nombre << "\n";
	for( int i=0; i<numContenido; i++ ) {
		ss << contenido[i]->to_string();
	}
	return ss.str();
}

#endif