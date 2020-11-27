#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>




int const BUFFER_DIM = 10;
int const DEG = 180;

class LaserScannerDrive {
private:
	double* buffer;
	int last_index;
	int last_dim;

public:
	LaserScannerDrive() : buffer{ new double[BUFFER_DIM * DEG] }, last_index{ 0 }, last_dim{ 0 } {}; //inizializzo il costruttore allocando il buffer nel freespace e inizializzando a zero last_index e last_dim
	void new_scan(std::vector<double> v);
	std::vector<double> get_scan();
	void clear_buffer();
	double get_distance(double grad);
	std::vector<double> get_scan_no_del();
	friend std::ostream& operator<<(std::ostream& os, const LaserScannerDrive obj) {
		for (int i = 0; i < 180; i++) {
			os << obj.buffer[i] << " ";
		}
		return os;
	}
};




int main() {
	srand(time(NULL));
	std::vector<double> dati(180);
	for (int i = 0; i < 180; i++) { //creo un vector di prova
		dati[i] = (double) rand()/1000;
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

void LaserScannerDrive::new_scan(std::vector<double> v) {
	for (int i = 0; i < 180; i++) {
		buffer[i] = v[i];
	}
}

std::vector<double> LaserScannerDrive::get_scan() {
	std::vector<double> f(180);
	for (int i = 0; i < 180; i++) {
		f[i] = buffer[i];
	}
	delete[] buffer;
	buffer = new double[BUFFER_DIM * DEG];
	return f;
}

void LaserScannerDrive::clear_buffer() {
	delete[] buffer;
	buffer = new double[BUFFER_DIM * DEG];
}

double LaserScannerDrive::get_distance(double grad) {
	grad = grad + 0.5;
	int y = (int)grad;
	return buffer[y];
}

std::vector<double> LaserScannerDrive::get_scan_no_del() {
	std::vector<double> f(180);
	for (int i = 0; i < 180; i++) {
		f[i] = buffer[i];
	}
	return f;
}