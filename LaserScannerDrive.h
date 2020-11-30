#include <iostream>
#include <vector>
#include <string>

class LaserScannerDrive {
private:
	int BUFFER_DIM;
	double resolution;
	double *(*buffer);
	int index;
	int size;

	bool isEmpty();

public:
	LaserScannerDrive();
	LaserScannerDrive(double r);
	void new_scan(std::vector<double> v);
	std::vector<double> get_scan();
	void clear_buffer();
	double get_distance(double grad);
	friend std::ostream& operator<<(std::ostream& os, const LaserScannerDrive obj);
};