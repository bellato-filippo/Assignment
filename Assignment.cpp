#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include "LaserScannerDrive.h"



int main() {
	srand(time(NULL));
	std::vector<double> dati(180);
	for (int i = 0; i < 180; i++) { //creo un vector di prova
		dati[i] = (double)rand() / 1000;
	}

	LaserScannerDrive oggetto;
	oggetto.new_scan(dati);
	std::cout << oggetto.get_distance(2) << "\n";
	std::cout << oggetto.get_distance(50) << "\n";
	std::cout << oggetto.get_distance(179) << "\n";
	std::vector<double> dati2 = oggetto.get_scan();
	oggetto.new_scan(dati2);
	std::cout << oggetto;
	return 0;
}

