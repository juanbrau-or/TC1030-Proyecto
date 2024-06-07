#include <iostream>
#include "streaming.h"
#include "multimedia.h"
#include "menus.h"

bool menu(Streaming &biblioteca, Streaming *servicios, int &nServ, int &nMult) {
	std::cout << "\n";
	std::cout << "---------------MENU PRINCIPAL---------------\n";
	std::cout << "Las posibles operaciones son las siguientes:\n";
	std::cout << "1. Consulta de contenido/plataforma\n";
	std::cout << "2. Actualizacion de contenido/plataforma\n";
	std::cout << "0. Salir\n";
	std::cout << "--------------------------------------------\n";
	bool continua = true;
	while( continua ) {
		continua = false;
		std::cout << "Ingrese el numero de operacion a realizar: ";
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
	Streaming servicios[20], biblioteca; // biblioteca contiene todo el contenido
	int nServ = 0, nMult = 0;
	std::cout << "\n";
	std::cout << "BIENVENIDO A ESTE ADMINISTRADOR DE PELICULAS\n";
	while( !termina ) {
		termina = menu(biblioteca, servicios, nServ, nMult);
	}
	std::cout << "\nMuchas gracias por usar este servicio, vuelva pronto!";
	return 0;
}