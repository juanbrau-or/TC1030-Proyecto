#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H

const int N = 500;

struct Multimedia {
	private:
	std::string nombre;
	int year;
	int calificacion;
	public:
	Multimedia(std::string _nombre):nombre(_nombre){};
	Multimedia(std::string, int, int);
	void setNombre(std::string);
	std::string getNombre();
	void setYear(int);
	int getYear();
	void setCalificacion(int);
	int getCalificacion();
};

Multimedia::Multimedia(std::string _nombre, int _year, int _calificacion) {
	nombre = _nombre;
	year = _year;
	calificacion = _calificacion;
}

void Multimedia::setNombre(std::string _nombre) {
	nombre = _nombre;
}

std::string Multimedia::getNombre() {
	return nombre;
}

void Multimedia::setYear(int _year) {
	year = _year;
}

int Multimedia::getYear() {
	return year;
}

void Multimedia::setCalificacion(int _calificacion) {
	calificacion = _calificacion;
}

int Multimedia::getCalificacion() {
	return calificacion;
}

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
};

Episodio::Episodio(std::string _nombre, int _duracion, int _numEpisodio) {
	nombre = _nombre;
	duracion = _duracion;
	numEpisodio = _numEpisodio;
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
};

void Temporada::lanzaEpisodio(Episodio nuevo) {
	episodios[cnt] = nuevo;
	++cnt;
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
};

void Serie::lanzaTemporada(Temporada nueva) {
	temporadas[cnt] = nueva;
	++cnt;
}

class Pelicula: public Multimedia {
	private:
	int duracion;
	public:
	Pelicula(std::string _nombre):Multimedia(_nombre){};
	int getDuracion(){ return duracion; }
	void setDuracion(int _duracion){ duracion = _duracion; }
};

#endif