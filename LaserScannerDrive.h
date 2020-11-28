#include <iostream>
#include <vector>

class LaserScannerDrive {
private:
	int const BUFFER_DIM;
	int const DEG;
	double* buffer;
	int last_index;
	int last_dim;

public:
	LaserScannerDrive();
	void new_scan(std::vector<double> v);
	std::vector<double> get_scan();
	void clear_buffer();
	double get_distance(double grad);
	std::vector<double> get_scan_no_del();
	friend std::ostream& operator<<(std::ostream& os, const LaserScannerDrive obj);
};