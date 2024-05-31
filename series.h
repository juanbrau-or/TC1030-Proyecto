#ifndef SERIES_H
#define SERIES_H

#include <iostream>
#include <sstream>
const int N = 20;

class Episodio {
	private:
	std::string nombre;
	int duracion;
	int numEpisodio;
	public:
	Episodio(std::string, int, int);
	Episodio():nombre("0"),duracion(0),numEpisodio(-1){};
	std::string getNombre(){ return nombre; }
	void setNombre(std::string _nombre){ nombre = _nombre; }
	int getDuracion(){ return duracion; }
	void setDuracion(int _duracion){ duracion = _duracion; }
	int getNumEpisodio(){ return numEpisodio; }
	void setNumEpisodio(int num){ numEpisodio = num; }
	std::string to_string();
};

Episodio::Episodio(std::string _nombre, int _duracion, int _numEpisodio) {
	nombre = _nombre;
	duracion = _duracion;
	numEpisodio = _numEpisodio;
}

std::string Episodio::to_string() {
	std::stringstream ss;
	ss << nombre << " ";
	return ss.str();
}

class Temporada {
		private:
		int numTemporada;
		int numEpisodios;
		Episodio episodios[N];
		int cnt;
		public:
		Temporada():numTemporada(0),numEpisodios(0),cnt(0){};
		Temporada(int num):numTemporada(num),numEpisodios(0),cnt(0){};
		int getNumTemporada(){ return numTemporada; }
		void setNumTemporada(int num){ numTemporada = num; }
		int getNumEpisodios(){ return numEpisodios; }
		void lanzaEpisodio(Episodio);
		std::string to_string();
};

void Temporada::lanzaEpisodio(Episodio nuevo) {
	episodios[cnt] = nuevo;
	++cnt;
}

std::string Temporada::to_string() {
	std::stringstream ss;
	ss << "Temporada #" << numTemporada << std::endl;
	for( int i=0; i<cnt; i++ )
		ss << episodios[i].to_string();
	ss << std::endl;
	return ss.str();
}

#endif