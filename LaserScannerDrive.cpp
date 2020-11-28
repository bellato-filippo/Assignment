#include "LaserScannerDrive.h"



LaserScannerDrive::LaserScannerDrive() : BUFFER_DIM{10}, DEG{180}, buffer{ new double[BUFFER_DIM * DEG] }, last_index{ 0 }, last_dim{ 0 } {};

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

std::ostream& operator<<(std::ostream& os, const LaserScannerDrive obj) {
	for (int i = 0; i < 180; i++) {
		os << obj.buffer[i] << " ";
	}
	return os;
}