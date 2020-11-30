#include<iostream>
#include <vector>
#include "LaserScannerDrive.h"
#include <ctime>

int main() {

	srand(time(NULL));
	std::vector<double> dati(180);
	for (int i = 0; i < 180; i++) { //creo un vector di prova
		dati[i] = (double)rand() / 1000;
	}

	LaserScannerDrive oggetto(1);
	oggetto.new_scan(dati);
	std::vector<double> prova = oggetto.get_scan();

	for (int i = 0; i < prova.size(); i++) {
		std::cout << prova[i] << "\n";
	}

	//oggetto.clear_buffer();
	return 0;
}

