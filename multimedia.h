#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H

// se importan las librerias a utilizar, que incluye series.h
// para poder utilizar las clases Temporada y Episodio
#include <iostream>
#include "series.h"

/*
* la clase Multimedia es una clase abstracta base para las peliculas
* y series, contiene atributos como el nombre, tipo de contenido,
* año de lanzamiento, calificacion y si esta bloqueado para agregarse
* a un servicio de Streaming
*/
struct Multimedia {
	protected:
	std::string nombre, tipo;
	int year;
	float calificacion;
	bool blocked;
	public:
	Multimedia(std::string _nombre, bool _block, std::string t):
		nombre(_nombre),blocked(_block),tipo(t),year(0),calificacion(5){};
	Multimedia(std::string, int, float, bool, std::string);
	// setter para cambiar el nombre
	void setNombre(std::string _nombre){ nombre = _nombre; }
	// getter para obtener el nombre del titulo
	std::string getNombre() const{ return nombre; }
	// setter para cambiar el año de lanzamiento
	void setYear(int _year){ year = _year; }
	// getter del año de lanzamiento
	int getYear()const { return year; }
	// setter para cambiar la calificacion
	void setCalificacion(float calif){ calificacion = calif; }
	// getter de la calificacion del titulo
	float getCalificacion() const{ return calificacion; }
	virtual std::string to_string()const = 0; // vuelve a la clase abstracta
	// getter para cambiar si el titulo esta bloqueado o no
	void setBlock(bool b){ blocked = b; }
	// setter para preguntar si el titulo esta bloqueado
	bool bloqueado() const{ return blocked; }
	// getter del tipo de contenido que contiene ("serie" o "pelicula")
	std::string getTipo() const{ return tipo; }
};

/*
* Constructor que recibe todos los parametros del titulo a crear
* @ param strint, int, float, bool, string
* @ return 
*/
Multimedia::Multimedia(std::string _nombre, int _year, float _calificacion, 
		bool _bloqueado, std::string t) {
	nombre = _nombre;
	year = _year;
	calificacion = _calificacion;
	blocked = _bloqueado;
	tipo = t;
}

/*
* Serie es una clase hija de Multimedia que permite tener una arreglo de
* temporadas que a su vez pueden contener episodios
* cada Serie comienza vacia, sin temporadas
*/
class Serie: public Multimedia {
	private:
	int numTemporadas;
	Temporada temporadas[N];
	public:
	Serie(std::string _nombre, bool b):
		Multimedia(_nombre, b,"serie"),numTemporadas(0){};
	Serie(std::string name, bool b, int year, float calif):
		Multimedia(name, year, calif, b, "serie"),numTemporadas(0){};
	// getter de cuantas temporadas contiene la serie
	int getNumTemporadas()const{ return numTemporadas; }
	void lanzaTemporada();
	std::string temporada_string(int) const;
	std::string to_string() const;
	// regresa una copia de alguna de las temporadas de la serie
	Temporada consulta_temporada(int x)const{ return temporadas[x]; }
	void lanzaEpisodio(int,Episodio);
	void modificaEpisodio(int,int,Episodio);
};

/*
* crea una nueva temporada inicializandola con el numero de temporada
* que tiene
* @ param 
* @ return 
*/
void Serie::lanzaTemporada() {
	temporadas[numTemporadas] = Temporada(numTemporadas+1);
	++numTemporadas;
}

/*
* regresa una string con la informacion de la temporada con el numero
* indicado
* @ param 
* @ return string con la informacion de la temporada completa
*/
std::string Serie::temporada_string(int x) const {
	std::stringstream ss;
	ss << temporadas[x].to_string();
	return ss.str();
}

/*
* to_string regresa la informacion de la serie completa en una string
* 
* @ param 
* @ return string con la informacion de la serie
*/
std::string Serie::to_string() const{
	std::stringstream ss;
	ss << "Nombre: " << nombre << "\n";
	ss << "Año de lanzamiento: " << year << "\n";
	ss << "Numero de temporadas: " << numTemporadas << "\n";
	ss << "Calificacion: " << calificacion << "\n";
	for( int i=0; i<numTemporadas; i++ )
		ss << temporadas[i].to_string();
	return ss.str();
}

/*
* lanzaEpisodio recibe el numero de temporada en el que se va a lanzar
* el episodio y manda a llamar al metodo de la temporada que permite lanzarlo
* 
* @ param int, Episodio
* @ return 
*/
void Serie::lanzaEpisodio(int x, Episodio nuevo) {
	temporadas[x].lanzaEpisodio(nuevo);
}

/*
* recibe el numero de temporada y del episodio a modificar, y manda
* llamar el metodo de la temporada y episodio que permite este cambio
* 
* @ param int temporada, int episodio, Episodio nuevo
* @ return 
*/
void Serie::modificaEpisodio(int temp, int ep, Episodio nuevo) {
	temporadas[temp].modificaEpisodio(ep, nuevo);
}

/*
* La clase Pelicula hereda de la clase Multimedia y tiene como atributos extra
* la duracion que tiene esta, pues las series no tienen una duracion como tal
*/
class Pelicula: public Multimedia {
	private:
	int duracion;
	public:
	Pelicula(std::string _nombre, bool b):
		Multimedia(_nombre, b,"pelicula"),duracion(-1){};
	Pelicula(std::string _nombre, bool b, int d):
		Multimedia(_nombre,b,"pelicula"),duracion(d){};
	Pelicula(std::string _nombre, bool b, int year, int d, float calif):
		Multimedia(_nombre, year, calif, b, "pelicula"),duracion(d){};
	// getter de la duracion de la pelicula
	int getDuracion(){ return duracion; }
	// setter para cambiar la duracion
	void setDuracion(int _duracion){ duracion = _duracion; }
	std::string to_string() const;
};

/*
* to_string regresa la informacion de la pelicula con forma de string
* 
* @ param 
* @ return string con la informacion de la pelicua
*/
std::string Pelicula::to_string() const{
	std::stringstream ss;
	ss << "Pelicula: " << nombre << "\n";
	ss << "Año de lanzamiento: " << year << "\n";
	ss << "Duracion: " << duracion << "\n";
	ss << "Calificacion: " << calificacion << "\n";
	return ss.str();
}

#endif