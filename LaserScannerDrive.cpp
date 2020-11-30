#include "LaserScannerDrive.h"

LaserScannerDrive::LaserScannerDrive() {
	resolution = 1;
	BUFFER_DIM = 10;
	size = 0;
	buffer = new double* [BUFFER_DIM];
	index = 0;
	for (int i = 0; i < BUFFER_DIM; i++) {
		buffer[i] = { nullptr };
	}
}

LaserScannerDrive::LaserScannerDrive(double r) {
	resolution = r;
	BUFFER_DIM = 10;
	size = 0;
	buffer = new double* [BUFFER_DIM];
	index = 0;
	for (int i = 0; i < BUFFER_DIM; i++) {
		buffer[i] = { nullptr };
	}
}

void LaserScannerDrive::new_scan(std::vector<double> v) {
	buffer[index] = new double[180 / resolution];
	if (v.size() < (180 / resolution)) {
		for (int i = 0; i < v.size(); i++) {
			buffer[index][i] = v[i];
		}
		for (int i = v.size(); i < (180 / resolution); i++) {
			buffer[index][i] = 0.0;
		}
	}
	
	for (int i = 0; i < (180 / resolution); i++) {
		buffer[index][i] = v[i];
	}
	if (index >= (BUFFER_DIM - 1))
		index = 0;
	else
		index++;

	if (size >= 10)
		size = 10;
	else
		size++;
}

std::vector<double> LaserScannerDrive::get_scan() throw(std::string) {
	std::vector<double> scans(180 / resolution);
	if (isEmpty())
		throw "Il buffer è vuoto";
	else
	{
		for (int i = 0; i < 180 / resolution; i++) {
			scans[i] = buffer[index - 1][i];
		}
		delete[] buffer[index - 1]; //da modificare
		if (index <= 0)
			index = 9;
		else
			index--;
	}
	size--;
	return scans;
}

void LaserScannerDrive::clear_buffer() {
	for (int i = 0; i < BUFFER_DIM; i++) {
		delete[] buffer[i];
		buffer[i] = { nullptr };
	}
	index = 0;
	size = 0;
}

double LaserScannerDrive::get_distance(double d) throw(std::string){ //verificare che esista
	int arr_index = (int)(d / resolution) + 0.5;
	if (isEmpty()) {
		throw "Xe vodo nino";
	}
	else
	{
		if (index = 0)
			return buffer[9][arr_index];
		else
			return buffer[index - 1][arr_index];
	}
}

std::ostream& operator<<(std::ostream& os, const LaserScannerDrive obj) {
	for (int i = 0; i < 180 / obj.resolution; i++) {
		os << obj.buffer[obj.index][i];
	}
	return os;
}

bool LaserScannerDrive::isEmpty() {
	return size < 1;
}