#ifndef MENUS_H
#define MENUS_H

#include <iostream>
#include <string.h>
#include <vector>
#include <set>
#include "streaming.h"

bool isnum(const std::string &s) {
	int i=0;
	if( s[i] == '-' )
		++i;
	for( i; i<s.size(); i++ ) {
		if( s[i] < '0' || s[i] > '9' )
			return false;
	}
	return true;
}

bool isdecimal(const std::string &s) {
	int i=0;
	if( s[i] == '-' )
		++i;
	bool decimal = false;
	for( i; i<s.size(); i++ ) {
		if( s[i] == '.' ) {
			if( decimal )
				return false;
			decimal = true;
		}
		else if( s[i] < '0' || s[i] > '9' )
			return false;
	}
	return true;
}

bool afirmativo(std::string instruccion) {
	std::string op;
	bool continua = true;
	while( continua ) {
		std::cout << instruccion << " (s/n)\n> ";
		continua = false;
		fflush(stdin); getline(std::cin, op);
		if( op == "S" || op == "s" || op == "si" || op == "Si" 
			|| op == "SI" )
			return true;
		else if( op == "n" || op == "N" || op == "no" || op == "NO" 
			|| op == "No" )
			return false;
		std::cout << "Comando invalido, intente de nuevo\n";
		continua = true;
	}
	return true; // no deberia ejecutarse
}

void lanza_multimedia(Streaming &biblioteca, 
  Streaming *servicios, int &nServ, int &nMult){
	Multimedia *nuevo;
	bool bloqueado;
	if( afirmativo("¿El contenido a lanzar es una pelicula?") ) {
		// lanza pelicula
		std::string nombre;
		int year, duracion;
		float calificacion;
		std::cout << "Ingrese el nombre de la pelicula: ";
		fflush(stdin); getline(std::cin, nombre);
		bool continua = true;
		std::string num;
		while( continua ) {
			continua = false;
			std::cout << "Ingrese el año de lanzamiento: ";
			fflush(stdin); getline(std::cin, num);
			if( !isnum(num) ) {
				std::cout << "Numero invalido, intente de nuevo\n";
				continua = true;
			}
			else {
				year = stoi(num);
			}
		}
		continua = true;
		while( continua ) {
			continua = false;
			std::cout << "Ingrese la duracion de la pelicula: ";
			fflush(stdin); getline(std::cin, num);
			if( !isnum(num) ) {
				std::cout << "Ingrese un numero valido\n";
				continua = true;
			}
			else {
				duracion = stoi(num);
			}
		}
		if( afirmativo("¿La pelicula ya cuenta con calificacion?") ) {
			continua = true;
			while( continua ) {
				continua = false;
				std::cout << "Ingrese la calificacion: ";
				fflush(stdin); getline(std::cin, num);
				if( !isdecimal(num) ) {
					std::cout << "Numero invalido, intente de nuevo\n";
					continua = true;
					continue;
				}
				calificacion = stof(num);
				if( calificacion < 0 || calificacion > 5 ) {
					std::cout << "La calificacion debe estar entre 0 y 5\n";
					continua = true;
					continue;
				}
			}
		}
		else {
			calificacion = 5;
		}
		if( afirmativo("¿La pelicula es exclusiva de alguna plataforma?") )
			bloqueado = true;
		else bloqueado = false;
		nuevo = new Pelicula(nombre, bloqueado, duracion);
		nuevo->setYear(year);
		nuevo->setCalificacion(calificacion);
	}
	else {
		// lanza serie, temporada o episodio
		if( afirmativo("¿El contenido es una nueva serie?") ) {
			// lanza serie
			std::string nombre;
			int year;
			float calificacion;
			std::cout << "Ingrese el nombre de la serie: ";
			fflush(stdin); getline(std::cin, nombre);
			
			std::string num;
			bool continua = true;
			
			while( continua ) {
				continua = false;
				std::cout << "Ingrese el año de lanzamiento: ";
				fflush(stdin); getline(std::cin, num);
				if( !isnum(num) ) {
					std::cout << "Numero invalido, intente de nuevo\n";
					continua = true;
				}
				else {
					year = stoi(num);
				}
			}
			
			continua = true;
			if( afirmativo("¿La serie ya cuenta con calificacion?") ) {
				continua = true;
				while( continua ) {
					continua = false;
					std::cout << "Ingrese la calificacion: ";
					fflush(stdin); getline(std::cin, num);
					if( !isdecimal(num) ) {
						std::cout << "Numero invalido, intente de nuevo\n";
						continua = true;
						continue;
					}
					calificacion = stof(num);
					if( calificacion < 0 || calificacion > 5 ) {
						std::cout << "La calificacion debe estar entre 0 y 5\n";
						continua = true;
						continue;
					}
				}
			}
			else {
				calificacion = 5;
			}
			if( afirmativo("¿La serie es exclusiva de alguna plataforma?") )
				bloqueado = true;
			else bloqueado = false;
			nuevo = new Serie(nombre, bloqueado);
			nuevo->setCalificacion(calificacion);
			nuevo->setYear(year);
		}
		else {
			// lanza temporada o episodio
			std::vector<int> posibles;
			for( int i=0; i<nMult; i++ ) {
				if( biblioteca.consulta_multimedia(i)->getTipo() == "serie" ) {
					posibles.push_back(i);
				}
			}
			if( posibles.size() == 0 ) {
				std::cout << "No hay series disponibles para lanzar nuevas "
					<< "temporadas\n";
				return;
			}
			for( int i=0; i<posibles.size(); i++ ) {
				std::cout << i+1 << ". " <<
				biblioteca.consulta_multimedia(posibles[i])->getNombre() << "\n";
			}
			bool continua = true;
			std::string num;
			int x;
			while( continua ) {
				continua = false;
				std::cout << "Ingrese el numero de la serie de la que se "
					<< "lanzara contenido: ";
				fflush(stdin); getline(std::cin, num);
				if( !isnum(num) ) {
					std::cout << "Comando invalido, intente de nuevo\n";
					continua = true;
					continue;
				}
				x = stoi(num)-1;
				if( x < 0 || x >= posibles.size() ) {
					std::cout << "Numero invalido, intente de nuevo\n";
					continua = true;
					continue;
				}
				x = posibles[x];
			}
			// modifica multimedia x de la biblioteca
			Serie* aux = (Serie*)biblioteca.modifica_multimedia(x);
			if(afirmativo("¿Se desea lanzar una nueva temporada en esta serie?")){
				aux->lanzaTemporada();
				std::cout << "Temporada lanzada con exito, ahora se pueden "
					<< "agregar episodios a esta\n";
			}
			else {
				// lanzar episodio
				if( aux->getNumTemporadas() == 0 ) {
					std::cout << "No se puede lanzar un episodio en esta serie "
						<< "porque no tiene temporadas disponibles\n";
					return;
				}
				std::cout << "La serie cuenta con " << aux->getNumTemporadas()
				<< " temporadas\n";
				continua = true;
				while( continua ) {
					std::cout << "Ingrese el numero de temporada al que "
					<< "pertenece el episodio: ";
					continua = false;
					fflush(stdin); getline(std::cin, num);
					if( !isnum(num) ) {
						std::cout << "Comando invalido, intente de nuevo\n";
						continua = true;
						continue;
					}
					x = stoi(num)-1;
					if( x < 0 || x >= aux->getNumTemporadas() ) {
						std::cout << "Numero invalido, intente de nuevo\n";
						continua = true;
						continue;
					}
				}
				// agregar episodio a la temporada x
				std::string nombre;
				int duracion;
				std::cout << "Ingrese el nombre del episodio: ";
				fflush(stdin); getline(std::cin, nombre);
				continua = true;
				while( continua ) {
					continua = false;
					std::cout << "Ingrese la duracion del episodio: ";
					fflush(stdin); getline(std::cin, num);
					if( !isnum(num) ) {
						std::cout << "Ingrese un numero valido\n";
						continua = true;
					}
					else {
						duracion = stoi(num);
					}
				}
				aux->lanzaEpisodio(x,Episodio(nombre,duracion));
			}
			return;
		}
	}
	nuevo->setBlock(false);
	biblioteca.lanzaMultimedia(nuevo);
	++nMult;
	if( nServ == 0 ) {
		nuevo->setBlock(bloqueado);
		std::cout << "Contenido lanzado con exito\n";
		return;
	}
	std::cout<<"Los servicios de streaming disponibles son los siguientes:\n";
	for( int i=0; i<nServ; i++ ) {
		std::cout << i+1 << ". " << servicios[i].getNombre() << "\n";
	}
	bool continua = true;
	std::string num;
	std::cout << "Ingrese el numero de las plataformas donde se encuentra "
		<< "disponible el contenido, uno por uno, cuando termine de ingresar "
		<< "los numeros presionar enter o escribir 0\n";
	std::cout << "Nota: Si un numero es incorrecto simplemente no se agregara "
		<< "el contenido a esa plataforma\n";
	int x;
	std::set<int> agregados;
	while( continua ) {
		std::cout << "Ingrese el numero: ";
		fflush(stdin); getline(std::cin, num);
		if( num == "" || num == "0" )
			break;
		if( !isnum(num) ) {
			std::cout << "Numero invalido\n";
			continue;
		}
		x = stoi(num)-1;
		if( x < 0 || x >= nServ ) {
			std::cout << "Numero invalido\n";
			continue;
		}
		if( agregados.count(x) > 0 ) {
			std::cout << "Este contenido ya fue agregado a esta plataforma\n";
			continue;
		}
		agregados.insert(x);
		servicios[x].lanzaMultimedia(nuevo);
	}
	nuevo->setBlock(bloqueado);
}

void lanza_plataforma(Streaming &biblioteca, 
  Streaming *servicios, int &nServ, int &nMult){
	std::cout << "Ingrese el nombre de la plataforma de streaming: ";
	std::string nombre;
	fflush(stdin); getline(std::cin, nombre);
	servicios[nServ] = Streaming(nombre);
	++nServ;
	return;
}

void modifica_multimedia(Streaming &biblioteca,
  Streaming *servicios,int &nServ, int &nMult){
	if( nMult == 0 ) {
		std::cout << "No hay contenido multimedia disponible "
			<< "para modificar\n";
		return;
	}
	std::cout << "El contenido disponible es el siguiente:\n";
	for( int i=0; i<nMult; i++ ) {
		std::cout << i+1 << ". " <<
			biblioteca.consulta_multimedia(i)->getNombre() << "\n";
	}
	std::string num;
	bool continua = true;
	int x;
	while( continua ) {
		continua = false;
		std::cout << "Ingrese el numero del contenido a modificar: ";
		fflush(stdin); getline(std::cin, num);
		if( !isnum(num) ) {
			std::cout << "Numero invalido, intente de nuevo\n";
			continua = true;
			continue;
		}
		x = stoi(num)-1;
		if( x < 0 || x >= nMult ) {
			std::cout << "Numero invalido, intente de nuevo\n";
			continua = true;
			continue;
		}
	}
	// modificar elemento x de biblioteca
	std::cout << "Las posibles modificaciones son:\n";
	std::cout << "1. Nombre\n";
	std::cout << "2. Año de publicacion\n";
	std::cout << "3. Calificacion\n";
	std::cout << "4. Bloquear/Desbloquear contenido\n";
	std::cout << "5. ";
	Multimedia* aux = biblioteca.modifica_multimedia(x);
	if( aux->getTipo() == "serie" ) {
		std::cout << "Episodio\n";
	}
	else {
		std::cout << "Duracion\n";
	}
	std::cout << "0. Cancelar\n";
	continua = true;
	while( continua ) {
		std::cout << "Ingrese el numero de la opcion a modificar: ";
		continua = false;
		fflush(stdin); getline(std::cin, num);
		if( num == "1" ) {
			std::string nombre;
			std::cout << "Ingrese el nuevo nombre: ";
			fflush(stdin); getline(std::cin, nombre);
			aux->setNombre(nombre);
			return;
		}
		else if( num == "2" ) {
			int year;
			continua = true;
			while( continua ) {
				continua = false;
				std::cout << "Ingrese el nuevo año: ";
				fflush(stdin); getline(std::cin, num);
				if( !isnum(num) ) {
					std::cout << "Ingrese un numero valido\n";
					continua = true;
					continue;
				}
				year = stoi(num);
			}
			aux->setYear(year);
			return;
		}
		else if( num == "3" ) {
			float calificacion;
			continua = true;
			while( continua ) {
				continua = false;
				std::cout << "Ingrese la nueva calificacion: ";
				fflush(stdin); getline(std::cin, num);
				if( !isdecimal(num) ) {
					std::cout << "Ingrese un numero valido\n";
					continua = true;
					continue;
				}
				calificacion = stof(num);
				if( calificacion < 0 || calificacion > 5 ) {
					std::cout << "La calificacion debe estar entre 0 y 5\n";
					continua = true;
					continue;
				}
			}
			aux->setCalificacion(calificacion);
		}
		else if( num == "4" ) {
			if( afirmativo("¿Desea desbloquear el contenido?") )
				aux->setBlock(false);
			else aux->setBlock(true);
		}
		else if( num == "5" ) {
			// si es pelicula modificar duracion
			if( aux->getTipo() == "pelicula" ) {
				int duracion;
				continua = true;
				while( continua ) {
					continua = false;
					std::cout << "Ingrese la nueva duracion: ";
					fflush(stdin); getline(std::cin, num);
					if( !isnum(num) ) {
						std::cout << "Ingrese un numero valido\n";
						continua = true;
						continue;
					}
					duracion = stoi(num);
				}
				((Pelicula*)aux)->setDuracion(duracion);
				return;
			}
			// si es serie modificar temporada o episodio
			Serie* pt = (Serie*)aux;
			if( pt->getNumTemporadas() == 0 ) {
				std::cout << "No hay contenido para modificar en esta"
					<< "serie\n";
				return;
			}
			std::cout << "La serie cuenta con " << pt->getNumTemporadas()
				<< " temporadas\n";
			continua = true;
			int x;
			while( continua ) {
				std::cout << "Ingrese el numero de temporada a modificar: ";
				continua = false;
				fflush(stdin); getline(std::cin, num);
				if( !isnum(num) ) {
					std::cout << "Ingrese un numero valido\n";
					continua = true;
					continue;
				}
				x = stoi(num)-1;
				if( x < 0 || x >= pt->getNumTemporadas() ) {
					std::cout << "Ingrese un numero valido\n";
					continua = true;
					continue;
				}
			}
			// modificar temporada x
			Temporada temp = pt->consulta_temporada(x);
			if( temp.getNumEpisodios() == 0 ) {
				std::cout << "Esta temporada no cuenta con episodios "
					<< "para modificar\n";
				return;
			}
			std::cout << "Esta temporada cuenta con " << 
				temp.getNumEpisodios() << " episodio(s)\n";
			int y;
			continua = true;
			while( continua ) {
				std::cout << "Ingrese el numero de episodio a modificar: ";
				continua = false;
				fflush(stdin); getline(std::cin, num);
				if( !isnum(num) ) {
					std::cout << "Numero invalido, intente de nuevo\n";
					continua = true;
					continue;
				}
				y = stoi(num)-1;
				if( y < 0 || y >= temp.getNumEpisodios() ) {
					std::cout << "Numero invalido, intente de nuevo\n";
					continua = true;
					continue;
				}
			}
			// modificar episodio y
			Episodio nuevo = temp.consultaEpisodio(y);
			if( afirmativo("¿Desea modificar el nombre del episodio?") ) {
				std::string nombre;
				std::cout << "Ingrese el nuevo nombre del episodio: ";
				fflush(stdin); getline(std::cin, nombre);
				nuevo.setNombre(nombre);
			}
			if( afirmativo("¿Desea modificar la duracion del episodio?") ) {
				int duracion;
				continua = true;
				while( continua ) {
					continua = false;
					std::cout << "Ingrese la nueva duracion: ";
					fflush(stdin); getline(std::cin, num);
					if( !isnum(num) ) {
						std::cout << "Numero invalido, intente de nuevo\n";
						continua = true;
						continue;
					}
					duracion = stoi(num);
				}
				nuevo.setDuracion(duracion);
			}
			pt->modificaEpisodio(x,y,nuevo);
		}
		else if( num == "0" ) {
			return;
		}
		else {
			continua = true;
			std::cout << "Comando invalido, intente de nuevo\n";
		}
	}
}

void modifica_plataforma(Streaming &biblioteca,
  Streaming *servicios,int &nServ, int &nMult){
	if( nServ == 0 ) {
		std::cout << "Por el momento no se cuentan con plataformas para"
			<< " modificar\n";
		return;
	}
	std::cout << "Las plataformas disponibles son:\n";
	for( int i=0; i<nServ; i++ ) {
		std::cout << i+1 << ". ";
		std::cout << servicios[i].getNombre() << "\n";
	}
	bool continua = true;
	std::string num;
	int x;
	while( continua ) {
		continua = false;
		std::cout << "Ingrese el numero de la plataforma a modificar: ";
		fflush(stdin); getline(std::cin, num);
		if( !isnum(num) ) {
			std::cout << "Numero invalido, intente de nuevo\n";
			continua = true;
			continue;
		}
		x = stoi(num)-1;
		if( x < 0 || x >= nServ ) {
			std::cout << "Numero invalido, intente de nuevo\n";
			continua = true;
			continue;
		}
	}
	// modifica streaming x
	if( afirmativo("¿Desea cambiar el nombre del servicio?") ) {
		std::cout << "Ingrese el nuevo nombre de la plataforma: ";
		std::string aux;
		fflush(stdin); getline(std::cin, aux);
		servicios[x].setNombre(aux);
		return;
	}
	// agrega un multimedia
	if( nMult == 0 ) {
		std::cout << "Por el momento no hay contenido disponible para "
			<< "agregar\n";
		return;
	}
	std::cout << "El catalogo disponible es el siguiente:\n";
	for( int i=0; i<nMult; i++ ) {
		std::cout << i+1 << ". " 
			<< biblioteca.consulta_multimedia(i)->getNombre() << "\n";
	}
	continua = true;
	int otro;
	while( continua ) {
		continua = false;
		std::cout << "Ingrese el numero del contenido a agregar: ";
		fflush(stdin); getline(std::cin, num);
		if( !isnum(num) ) {
			std::cout << "Ingrese un numero valido\n";
			continua = true;
			continue;
		}
		otro = stoi(num)-1;
		if( otro < 0 || otro >= nMult ) {
			std::cout << "Ingrese un numero valido\n";
			continua = true;
			continue;
		}
	}
	// agrega elemento otro de la biblioteca al streaming x
	if( biblioteca.consulta_multimedia(otro)->bloqueado() ) {
		std::cout << "El elemento seleccionado es exclusivo de otra"
			<< " plataforma, para agregarlo primero debe liberarse\n";
		return;
	}
	servicios[x].lanzaMultimedia(biblioteca.consulta_multimedia(otro));
}

void actualiza_contenido(Streaming &biblioteca,
  Streaming *servicios,int &nServ, int &nMult){
	// actualiza contenido
	std::cout << "Las posibles actualizaciones son las siguientes:\n";
	std::cout << "1. Lanzamiento de nuevo contenido/plataforma\n";
	std::cout << "2. Modificar contenido/plataforma ya existente\n";
	std::cout << "0. Cancelar\n";
	bool continua = true;
	std::string op;
	while( continua ) {
		continua = false;
		std::cout << "Ingrese el numero de operacion a realizar: ";
		fflush(stdin);
		getline(std::cin, op);
		if( op == "1" ) {
			std::cout << "Los posibles lanzamientos son los siguientes:\n";
			std::cout << "1. Nueva serie/pelicula/episodio\n";
			std::cout << "2. Nueva plataforma de streaming\n";
			std::cout << "0. Cancelar\n";
			continua = true;
			while( continua ) {
				std::cout << "Ingrese el numero de lo que se desea lanzar: ";
				continua = false;
				fflush(stdin); getline(std::cin, op);
				if( op == "1" ) {
					lanza_multimedia(biblioteca, servicios, nServ, nMult);
				}
				else if( op == "2" ) {
					lanza_plataforma(biblioteca, servicios, nServ, nMult);
				}
				else if( op == "0" )
					return;
				else continua = true;
			}
		}
		else if( op == "2" ) {
			std::cout << "Las posibles modificaciones son las siguientes:\n";
			std::cout << "1. Modificar serie/pelicula/episodio\n";
			std::cout << "2. Modificar plataforma de streaming\n";
			std::cout << "0. Cancelar\n";
			continua = true;
			while( continua ) {
				std::cout<<"Ingrese el numero de lo que se desea modificar: ";
				continua = false;
				fflush(stdin); getline(std::cin, op);
				if( op == "1" ) {
					modifica_multimedia(biblioteca, servicios, nServ, nMult);
				}
				else if( op == "2" ) {
					modifica_plataforma(biblioteca, servicios, nServ, nMult);
				}
				else if( op == "0" )
					return;
				else continua = true;
			}
		}
		else if( op == "0" )
			return;
		else {
			std::cout << "Operacion invalida, intente de nuevo\n";
			continua = true;
		}
	}
}

void consulta_streaming(Streaming *servicios, int &nServ) {
	std::cout<<"Los servicios de streaming disponibles son los siguientes:\n";
	for( int i=0; i<nServ; i++ ) {
		std::cout << i+1 << ". " << servicios[i].getNombre() << "\n";
	}
	std::string num;
	bool continua = true;
	while( continua ) {
		std::cout << "Ingrese el numero del servicio a consultar: ";
		continua = false;
		fflush(stdin); getline(std::cin, num);
		if( !isnum(num) ) {
			continua = true;
			std::cout << "Numero invalido, intente de nuevo\n";
			continue;
		}
		int x = stoi(num)-1;
		if( x < 0 || x >= nServ ) {
			continua = true;
			std::cout << "Numero invalido, intente de nuevo\n";
			continue;
		}
		std::string aux = servicios[x].catalogo();
		if( aux == "" ) {
			std::cout << "Por el momento " << servicios[x].getNombre();
			std::cout << " no cuenta con contenido disponible :(\n";
		}
		else {
			std::cout << "El catalogo disponible en ";
			std::cout << servicios[x].getNombre() << " es:\n";
			std::cout << aux;
		}
	}
}

void consulta_multimedia(const Streaming &plataforma, const int &id) {
	const Multimedia* copia = plataforma.consulta_multimedia(id);
	if( copia->getTipo() == "serie" ) {
		// consulta serie
		std::cout << "1. Consultar episodio\n";
		std::cout << "2. Informacion temporada completa\n";
		std::cout << "3. Informacion serie completa\n";
		std::cout << "0. Cancelar\n";
		bool continua = true;
		std::string op;
		while( continua ) {
			continua = false;
			std::cout << "Ingrese la opcion a consultar: ";
			fflush(stdin); getline(std::cin, op);
			const Serie* nuevo = (Serie*)copia;
			if( op == "1" ) {
				if( nuevo->getNumTemporadas() == 0 ) {
					std::cout << "Por el momento esta serie no cuenta"
						<< " con episodios para mostrar\n";
					return;
				}
				std::cout << "La serie cuenta con " << nuevo->getNumTemporadas()
					<< " temporadas\n";
				continua = true;
				std::string num;
				int x;
				while( continua ) {
					std::cout << "Ingrese el numero de temporada donde se "
						<< "encuentra el episodio: ";
					continua = false;
					fflush(stdin); getline(std::cin, num);
					if( !isnum(num) ) {
						std::cout << "Numero invalido, intente de nuevo\n";
						continua = true;
						continue;
					}
					x = stoi(num)-1;
					if( x < 0 || x >= nuevo->getNumTemporadas() ) {
						std::cout << "Numero invalido, intente de nuevo\n";
						continua = true;
						continue;
					}
				}
				// consultar episodio de temporada x
				Temporada aux = nuevo->consulta_temporada(x);
				if( aux.getNumEpisodios() == 0 ) {
					std::cout << "Esta temporada no cuenta con episodios\n";
					return;
				}
				std::cout << "Esta temporada cuenta con " << aux.getNumEpisodios()
					<< " episodios\n";
				continua = true;
				while( continua ) {
					std::cout << "Ingrese el numero de episodio a consultar: ";
					continua = false;
					fflush(stdin); getline(std::cin, num);
					if( !isnum(num) ) {
						std::cout << "Numero invalido, intente de nuevo\n";
						continua = true;
						continue;
					}
					x = stoi(num)-1;
					if( x < 0 || x >= aux.getNumEpisodios() ) {
						std::cout << "Numero invalido, intente de nuevo\n";
						continua = true;
						continue;
					}
				}
				std::cout << "Informacion del episodio " << x << "\n";
				std::cout << aux.info_episodio(x) << "\n";
			}
			else if( op == "2" ) {
				if( nuevo->getNumTemporadas() == 0 ) {
					std::cout << "Por el momento esta serie "
						<< "no cuenta con temporadas\n";
					return;
				}
				std::cout<< "La serie cuenta con " << nuevo->getNumTemporadas()
					<< " temporadas\n";
				continua = true;
				std::string num;
				while( continua ) {
					std::cout << "Ingrese el numero de la temporada a"
						<< " consultar: ";
					continua = false;
					fflush(stdin); getline(std::cin, num);
					if( !isnum(num) ) {
						std::cout << "Numero invalido, intente de nuevo\n";
						continua = true;
						continue;
					}
					int x = stoi(num)-1;
					if( x < 0 || x >= nuevo->getNumTemporadas() ) {
						std::cout << "Numero invalido, intente de nuevo\n";
						continua = true;
						continue;
					}
					std::cout << "Informacion sobre la temporada "
						<< x+1 << " de la serie " << nuevo->getNombre()<< "\n";
					std::cout << nuevo->temporada_string(x) << "\n";
				}
			}
			else if( op == "3" ) {
				std::cout << "Datos de la serie " << copia->getNombre() <<"\n";
				std::cout << copia->to_string() << "\n";
			}
			else if( op == "0" )
				return;
			else {
				continua = true;
				std::cout << "Comando invalido, intente de nuevo\n";
			}
		}
	}
	else {
		// consulta pelicula
		std::cout << "Datos de la pelicula " << copia->getNombre() << "\n";
		std::cout << "Nombre: " << copia->getNombre() << "\n";
		std::cout << "Año de lanzamiento: " << copia->getYear() << "\n";
		std::cout<<"Duracion: "<<((Pelicula*)copia)->getDuracion()<<"\n";
		std::cout << "Calificacion: " << copia->getCalificacion() << "\n";
	}
}

void consulta_multimedia_biblioteca(const Streaming &biblioteca, 
		const int &nMult) {
	if( nMult == 0 ) {
		std::cout << "Por el momento esta plataforma no cuenta ";
		std::cout << "con contenido disponible :(\n";
		return;
	}
	std::cout << "El contenido disponible es el siguiente:\n";
	std::cout << biblioteca.catalogo();
	std::string num;
	bool continua = true;
	while( continua ) {
		continua = false;
		std::cout << "Ingrese el numero del contenido a consultar: ";
		fflush(stdin); getline(std::cin, num);
		if( !isnum(num) ) {
			std::cout << "Numero invalido, intente de nuevo\n";
			continua = true;
			continue;
		}
		int x = stoi(num)-1;
		if( x < 0 || x >= nMult ) {
			std::cout << "Numero invalido, intente de nuevo\n";
			continua = true;
			continue;
		}
		// consulta pelicula o serie
		consulta_multimedia(biblioteca, x);
	}
}

void consulta_multimedia_streaming(Streaming *servicios, int &nServ) {
	if( nServ == 0 ) {
		std::cout << "Por el momento no se cuentan con";
		std::cout << " servicios de streaming :(\n";
		return;
	}
	std::cout << "Los servicios de streaming disponibles son:\n";
	for( int i=0; i<nServ; i++ ) {
		std::cout << i+1 << ". " << servicios[i].getNombre() << "\n";
	}
	std::string num;
	bool continua = true;
	while( continua ) {
		std::cout << "Ingrese el numero de la plataforma donde se ";
		std::cout << "encuentra el contenido a consultar: ";
		continua = false;
		fflush(stdin); getline(std::cin, num);
		if( !isnum(num) ) {
			std::cout << "Numero invalido, intente de nuevo\n";
			continua = true;
			continue;
		}
		int x = stoi(num)-1;
		if( x < 0 || x >= nServ ) {
			std::cout << "Numero invalido, intente de nuevo\n";
			continua = true;
			continue;
		}
		consulta_multimedia_biblioteca(servicios[x], servicios[x].getNumContenido());
	}
	return;
}

void consulta_contenido(Streaming &biblioteca,
  Streaming *servicios,int &nServ, int &nMult){
	std::cout << "1. Consultar catalogo de servicio de streaming\n";
	std::cout << "2. Consultar pelicula/serie\n";
	std::cout << "0. Cancelar\n";
	bool continua = true;
	std::string op;
	while( continua ) {
		continua = false;
		std::cout << "Ingrese el numero de operacion a realizar: ";
		fflush(stdin);
		getline(std::cin, op);
		if( op == "1" ) {
			consulta_streaming(servicios, nServ);
		}
		else if( op == "2" ) {
			std::cout << "Indicar si el contenido se encuentra en un ";
			std::cout << "servicio de streaming:\n";
			std::cout << "1. Si\n2. No\n3. No lo se\n";
			continua = true;
			while( continua ) {
				std::cout << "Ingrese el numero de la opcion a seleccionar: ";
				continua = false;
				fflush(stdin); getline(std::cin, op);
				if( op == "1" ) {
					consulta_multimedia_streaming(servicios, nServ);
				}
				else if( op == "2" || op == "3" ) {
					consulta_multimedia_biblioteca(biblioteca, nMult);
				}
				else {
					continua = true;
					std::cout << "Comando invalido, intente de nuevo\n";
				}
			}
		}
		else if( op == "0" )
			return;
		else {
			std::cout << "Operacion invalida, intente de nuevo\n";
			continua = true;
		}
	}
}

#endif