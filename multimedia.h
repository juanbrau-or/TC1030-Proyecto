#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H

#include <iostream>
#include "series.h"

struct Multimedia {
	protected:
	std::string nombre;
	int year;
	int calificacion;
	public:
	Multimedia(std::string _nombre):nombre(_nombre){};
	Multimedia(std::string, int, int);
	void setNombre(std::string _nombre){ nombre = _nombre; }
	std::string getNombre(){ return nombre; }
	void setYear(int _year){ year = _year; }
	int getYear(){ return year; }
	void setCalificacion(int calif){ calificacion = calif; }
	int getCalificacion(){ return calificacion; }
	virtual std::string to_string(){ return nombre; }
};

Multimedia::Multimedia(std::string _nombre, int _year, int _calificacion) {
	nombre = _nombre;
	year = _year;
	calificacion = _calificacion;
}

class Serie: public Multimedia {
	private:
	int numTemporadas;
	Temporada temporadas[N];
	int cnt;
	public:
	Serie(std::string _nombre):Multimedia(_nombre),cnt(0){};
	int getNumTemporadas(){ return numTemporadas; }
	void lanzaTemporada(Temporada);
	std::string to_string();
};

void Serie::lanzaTemporada(Temporada nueva) {
	temporadas[cnt] = nueva;
	++cnt;
}

std::string Serie::to_string() {
	std::stringstream ss;
	ss << "Serie: " << nombre << std::endl;
	for( int i=0; i<cnt; i++ )
		ss << temporadas[i].to_string();
	return ss.str();
}

class Pelicula: public Multimedia {
	private:
	int duracion;
	public:
	Pelicula(std::string _nombre):Multimedia(_nombre){};
	int getDuracion(){ return duracion; }
	void setDuracion(int _duracion){ duracion = _duracion; }
	std::string to_string();
};

std::string Pelicula::to_string() {
	std::stringstream ss;
	ss << "Pelicula: " << nombre << std::endl;
	return ss.str();
}

#endif