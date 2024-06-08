#ifndef SERIES_H
#define SERIES_H

#include <iostream>
#include <sstream>
const int N = 20;

class Episodio {
	private:
	std::string nombre;
	int duracion;
	public:
	Episodio(std::string, int);
	Episodio():nombre("0"),duracion(0){};
	std::string getNombre(){ return nombre; }
	void setNombre(std::string _nombre){ nombre = _nombre; }
	int getDuracion(){ return duracion; }
	void setDuracion(int _duracion){ duracion = _duracion; }
	std::string to_string() const;
};

Episodio::Episodio(std::string _nombre, int _duracion) {
	nombre = _nombre;
	duracion = _duracion;
}

std::string Episodio::to_string() const{
	std::stringstream ss;
	ss << nombre << ". Duracion: " << duracion;
	return ss.str();
}

class Temporada {
		private:
		int numTemporada;
		int numEpisodios;
		Episodio episodios[N];
		public:
		Temporada():numTemporada(0),numEpisodios(0){};
		Temporada(int num):numTemporada(num),numEpisodios(0){};
		int getNumTemporada(){ return numTemporada; }
		void setNumTemporada(int num){ numTemporada = num; }
		int getNumEpisodios(){ return numEpisodios; }
		void lanzaEpisodio(Episodio);
		std::string to_string() const;
		std::string info_episodio(int x)const{return episodios[x].to_string();}
		void modificaEpisodio(int, Episodio);
		Episodio consultaEpisodio(int x){ return episodios[x]; }
};

void Temporada::lanzaEpisodio(Episodio nuevo) {
	episodios[numEpisodios] = nuevo;
	++numEpisodios;
}

std::string Temporada::to_string() const{
	std::stringstream ss;
	ss << "Temporada #" << numTemporada << "\n";
	ss << "No. de episodios: " << numEpisodios << "\n";
	for( int i=0; i<numEpisodios; i++ ) {
		ss << "\tEpisodio # " << i+1 << " "
			<< episodios[i].to_string() << "\n";
	}
	return ss.str();
}

void Temporada::modificaEpisodio(int x, Episodio nuevo) {
	episodios[x] = nuevo;
}

#endif