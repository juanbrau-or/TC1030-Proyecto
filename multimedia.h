#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H

#include <iostream>
#include "series.h"
#include "streaming.h"

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
	void setNombre(std::string _nombre){ nombre = _nombre; }
	std::string getNombre() const{ return nombre; }
	void setYear(int _year){ year = _year; }
	int getYear()const { return year; }
	void setCalificacion(float calif){ calificacion = calif; }
	float getCalificacion() const{ return calificacion; }
	virtual std::string to_string()const = 0; // vuelve a la clase abstracta
	void setBlock(bool b){ blocked = b; }
	bool bloqueado() const{ return blocked; }
	std::string getTipo() const{ return tipo; }
};

Multimedia::Multimedia(std::string _nombre, int _year, float _calificacion, 
		bool _bloqueado, std::string t) {
	nombre = _nombre;
	year = _year;
	calificacion = _calificacion;
	blocked = _bloqueado;
	tipo = t;
}

/*
* Cada Serie comienza vacia, sin temporadas
*/
class Serie: public Multimedia {
	private:
	int numTemporadas;
	Temporada temporadas[N];
	public:
	Serie(std::string _nombre, bool b):Multimedia(_nombre, b,"serie"),numTemporadas(0){};
	Serie(std::string name, bool b, int year, float calif):
		Multimedia(name, year, calif, b, "serie"),numTemporadas(0){};
	int getNumTemporadas()const{ return numTemporadas; }
	void lanzaTemporada();
	std::string temporada_string(int) const;
	std::string to_string() const;
	Temporada consulta_temporada(int x)const{ return temporadas[x]; }
	void lanzaEpisodio(int,Episodio);
	void modificaEpisodio(int,int,Episodio);
};

void Serie::lanzaTemporada() {
	temporadas[numTemporadas] = Temporada(numTemporadas+1);
	++numTemporadas;
}

std::string Serie::temporada_string(int x) const {
	std::stringstream ss;
	ss << temporadas[x].to_string();
	return ss.str();
}

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

void Serie::lanzaEpisodio(int x, Episodio nuevo) {
	temporadas[x].lanzaEpisodio(nuevo);
}

void Serie::modificaEpisodio(int temp, int ep, Episodio nuevo) {
	temporadas[temp].modificaEpisodio(ep, nuevo);
}

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
	int getDuracion(){ return duracion; }
	void setDuracion(int _duracion){ duracion = _duracion; }
	std::string to_string() const;
};

std::string Pelicula::to_string() const{
	std::stringstream ss;
	ss << "Pelicula: " << nombre << std::endl;
	return ss.str();
}

#endif