#include <iostream>
#include "multimedia.h"

int main() {
	Serie percy("Percy Jackson");
	Temporada temp(1);
	Episodio piloto("Piloto",43,1);
	temp.lanzaEpisodio(piloto);
	percy.lanzaTemporada(temp);
	
	std::cout << percy.to_string();
	return 0;
}