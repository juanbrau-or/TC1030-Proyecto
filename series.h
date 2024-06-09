#ifndef SERIES_H
#define SERIES_H

/*
* en este archivo se encuentran los elementos que componen una serie,
* es decir, temporadas que contienen capitulos
*/

// se importan las librerias a utilizar
#include <iostream>
#include <sstream>
const int N = 20;

/*
* la clase Episodio solamente almacena el nombre y la duracion de este
*/
class Episodio {
	private:
	std::string nombre;
	int duracion;
	public:
	Episodio(std::string, int);
	Episodio():nombre("0"),duracion(0){};
	// getter que regresa el nombre del episodio
	std::string getNombre(){ return nombre; }
	// setter para cambiar el nombre del episodio
	void setNombre(std::string _nombre){ nombre = _nombre; }
	// getter que regresa la duracion del episodio
	int getDuracion(){ return duracion; }
	// setter para cambiar la duracion del episodio
	void setDuracion(int _duracion){ duracion = _duracion; }
	std::string to_string() const;
};

/*
* Constructor que recibe el nombre y la duracion del episodio a crear
* @ param string nombre, int duracion
* @ return 
*/
Episodio::Episodio(std::string _nombre, int _duracion) {
	nombre = _nombre;
	duracion = _duracion;
}

/*
* to_string devuelve una string con la informacion del episodio
* es decir, su nombre y su duracion
* 
* @ param 
* @ return string con la informacion del episodio
*/
std::string Episodio::to_string() const{
	std::stringstream ss;
	ss << nombre << ". Duracion: " << duracion;
	return ss.str();
}

/*
* La clase Temporada contiene un arreglo de Episodios 
* asi como un contador de estos y funciones que permiten cambiar
* atributos de los episodios
*/
class Temporada {
		private:
		int numTemporada;
		int numEpisodios;
		Episodio episodios[N];
		public:
		Temporada():numTemporada(0),numEpisodios(0){};
		Temporada(int num):numTemporada(num),numEpisodios(0){};
		// getter del numero de temporada
		int getNumTemporada(){ return numTemporada; }
		// setter para cambiar el numero de temporada
		void setNumTemporada(int num){ numTemporada = num; }
		// getter de la cantidad de episodios con los que cuenta la temporada
		int getNumEpisodios(){ return numEpisodios; }
		void lanzaEpisodio(Episodio);
		std::string to_string() const;
		// regresa la string con la informacion del episodio numero x
		std::string info_episodio(int x)const{return episodios[x].to_string();}
		void modificaEpisodio(int, Episodio);
		// regresa una copia de un Episodio para consultar informacion de este
		Episodio consultaEpisodio(int x){ return episodios[x]; }
};

/*
* esta funcion se encarga de agregar un nuevo episodio y aumentar
* el contador de cuantos hay
* 
* @ param Episodio
* @ return 
*/
void Temporada::lanzaEpisodio(Episodio nuevo) {
	episodios[numEpisodios] = nuevo;
	++numEpisodios;
}

/*
* to_string regresa la informacion completa de la temporada y de todos
* los episodios que contiene
* 
* @ param 
* @ return string con la informacion de la temporada completa
*/
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

/*
* modifica el episodio x de la temporada con la informacion del nuevo Episodio
* 
* @ param int, Episodio
* @ return 
*/
void Temporada::modificaEpisodio(int x, Episodio nuevo) {
	episodios[x] = nuevo;
}

#endif