// se importan las librerias a utilizar
#include <iostream>
#include "streaming.h"
#include "multimedia.h"
#include "menus.h"

/*
* en caso de ser llamado crea algunos servicios de streaming de ejemplo,
* asi como varias peliculas y series para que el usuario tenga una idea del
* funcionamiento del programa
* 
* @ param Streaming biblioteca, Streaming *servicios, int &nServ, int &nMult
* arreglo de streamings en el main, asi como cuantos hay de cada uno
* @ return
*/
void crea_ejemplos(Streaming &biblioteca, Streaming *servicios, 
		int &nServ, int &nMult ) {
	servicios[0] = Streaming("Netflix Mexico");
	servicios[1] = Streaming("Disney+ Mexico");
	servicios[2] = Streaming("Max US");
	servicios[3] = Streaming("Star+ Mexico");
	// Pelicula -> nombre, bloqueado, año, duracion, calificacion
	Multimedia* increibles =
		new Pelicula("Los Increibles",false,2004,115,4.3);
	Multimedia* about_time = 
		new Pelicula("Cuestion de tiempo",false,2013,123,4.2);
	Multimedia* spirit = 
		new Pelicula("Spirit: el corcel indomable",false,2002,104,4.2);
	Multimedia* fight_club = 
		new Pelicula("El club de la pelea",false,1999,139,4.3);
	Multimedia* castillo = 
		new Pelicula("El increible castillo vagabundo",false,2004,119,4.8);
	Multimedia* pelicula_huevos = 
		new Pelicula("Una pelicula de huevos",false,2006,90,4);
	Multimedia* klaus = 
		new Pelicula("Klaus",false,2019,97,4.3);
	Multimedia* dune = 
		new Pelicula("Dune: Parte Uno",false,2021,155,4);
	Multimedia* beetlejuice = 
		new Pelicula("Beetlejuice",false,1988,92,4.8);
	// Serie -> nombre, bloqueado, año, calificacion
	// Serie -> lanzaTemporada()
	// Serie -> lanzaEpisodio(int temporada, Episodio(nombre, duracion))
	Multimedia* bebe_reno = 
		new Serie("Bebe Reno",false,2024,4.5);
	((Serie*)bebe_reno)->lanzaTemporada();
	((Serie*)bebe_reno)->lanzaEpisodio(0,Episodio("Episodio 1",32));
	((Serie*)bebe_reno)->lanzaEpisodio(0,Episodio("Episodio 2",27));
	((Serie*)bebe_reno)->lanzaEpisodio(0,Episodio("Episodio 3",38));
	Multimedia* rick_morty = 
		new Serie("Rick and Morty",false,2013,4.3);
	((Serie*)rick_morty)->lanzaTemporada();
	((Serie*)rick_morty)->lanzaTemporada();
	((Serie*)rick_morty)->lanzaEpisodio(0,Episodio("Pilot",22));
	((Serie*)rick_morty)->lanzaEpisodio(0,Episodio("Lawnmower Dog",22));
	((Serie*)rick_morty)->lanzaEpisodio(1,Episodio("A Rickle in Time",23));
	((Serie*)rick_morty)->lanzaEpisodio(1,Episodio("Mortynight Run",23));
	// Streaming -> servicios[i].lanzaMultimedia(Multimedia*)
	biblioteca.lanzaMultimedia(increibles); ++nMult;
	biblioteca.lanzaMultimedia(about_time); ++nMult;
	biblioteca.lanzaMultimedia(spirit); ++nMult;
	biblioteca.lanzaMultimedia(fight_club); ++nMult;
	biblioteca.lanzaMultimedia(castillo); ++nMult;
	biblioteca.lanzaMultimedia(pelicula_huevos); ++nMult;
	biblioteca.lanzaMultimedia(klaus); ++nMult;
	biblioteca.lanzaMultimedia(dune); ++nMult;
	biblioteca.lanzaMultimedia(beetlejuice); ++nMult;
	biblioteca.lanzaMultimedia(bebe_reno); ++nMult;
	biblioteca.lanzaMultimedia(rick_morty); ++nMult;
	servicios[0].lanzaMultimedia(spirit); 
	servicios[0].lanzaMultimedia(pelicula_huevos);
	servicios[0].lanzaMultimedia(bebe_reno);
	servicios[1].lanzaMultimedia(about_time);
	servicios[1].lanzaMultimedia(fight_club);
	servicios[1].lanzaMultimedia(dune);
	servicios[2].lanzaMultimedia(spirit);
	servicios[2].lanzaMultimedia(castillo);
	servicios[2].lanzaMultimedia(beetlejuice);
	servicios[3].lanzaMultimedia(klaus);
	servicios[3].lanzaMultimedia(rick_morty);
	servicios[3].lanzaMultimedia(increibles);
	nServ = 4;
	// exclusividad de algunas series para sus plataformas
	bebe_reno->setBlock(true); klaus->setBlock(true);
	increibles->setBlock(true);
}

/*
* imprime el menu principal con las funciones principales para el usuario,
* despues se mandan llamar las funciones pertinentes
* 
* @ param Streaming biblioteca, Streaming *servicios, int &nServ, int &nMult
* arreglo de streamings en el main, y cuantos titulos
* hay en total en el programa
* @ return bool que indica si el programa debe continuar o no
*/
bool menu(Streaming &biblioteca, Streaming *servicios, int &nServ, int &nMult) {
	std::cout << "\n";
	std::cout << "---------------MENU PRINCIPAL---------------\n";
	std::cout << "Las posibles operaciones son las siguientes:\n";
	std::cout << "1. Consulta de contenido/plataforma\n";
	std::cout << "2. Actualizacion/lanzamiento de contenido/plataforma\n";
	std::cout << "0. Salir\n";
	std::cout << "--------------------------------------------\n";
	bool continua = true;
	while( continua ) {
		continua = false;
		std::cout << "\nIngrese el numero de operacion a realizar: ";
		std::string op;
		fflush(stdin);
		getline(std::cin, op);
		if( op == "1" ) {
			// consulta contenido
			consulta_contenido(biblioteca, servicios, nServ, nMult);
		}
		else if( op == "2" ) {
			actualiza_contenido(biblioteca, servicios, nServ, nMult);
		}
		else if( op == "0" )
			return true;
		else {
			std::cout << "Operacion invalida, intente de nuevo\n";
			continua = true;
		}
	}
	return false;
}

int main() {
	bool termina = false;
	Streaming servicios[20], biblioteca;
	// biblioteca contiene todos los titulos creados
	// servicios contiene los servicios de streaming creados
	int nServ = 0, nMult = 0;
	// nServ indica el numero total de servicios de streaming
	std::cout << "\n";
	std::cout << "BIENVENIDO A ESTE ADMINISTRADOR DE PELICULAS\n";
	if( afirmativo("¿Desea crear ejemplos demo?") ) {
		crea_ejemplos(biblioteca, servicios, nServ, nMult);
	}
	while( !termina ) {
		termina = menu(biblioteca, servicios, nServ, nMult);
	}
	std::cout << "\nMuchas gracias por usar este servicio, vuelva pronto!";
	return 0;
}