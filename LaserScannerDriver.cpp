#include "LaserScannerDriver.h"

/*Costruttore di default con risoluzione = 1*/
LaserScannerDriver::LaserScannerDriver() {
	index = 0;
	size = 0;
	scan_dimension = 181;
	resolution = 1;
	buffer = new double* [BUFFER_DIM];
	for (int i = 0; i < BUFFER_DIM; i++) {
		buffer[i] = { nullptr };
	}
}

/*Costruttore con parametro la risoluzione. Inizializza tutte le variabili e tutti
gli elementi del buffer a nullptr*/
LaserScannerDriver::LaserScannerDriver(double r) {
	index = 0;
	size = 0;
	scan_dimension = (int) std::floor(180 / r) + 1;
	resolution = r;
	buffer = new double* [BUFFER_DIM];
	for (int i = 0; i < BUFFER_DIM; i++) {
		buffer[i] = { nullptr };
	}
}


/*Inserisce una nuova scansione nel buffer. Alloca nuova memoria solo se 
il buffer si sta riempiendo. Una volta pieno sovrascrive solo i dati*/
void LaserScannerDriver::new_scan(std::vector<double> v) {
	if (buffer[index] == nullptr) { //verifica se quell'elemento � ancora vuoto
		buffer[index] = new double[scan_dimension];
	}

	for (int i = 0; i < v.size(); i++) {
		buffer[index][i] = v[i];
	}

	if (v.size() < scan_dimension) { //se il vettore � pi� corto dell'array aggiunge 0.0
		for (int i = v.size(); i < scan_dimension; i++) {
			buffer[index][i] = 0.0;
		}
	}

	if (index >= BUFFER_DIM - 1) //incrementa l'indice. Se � arrivato alla fine torna indietro visto che � un array circolare
		index = 0;
	else
		index++;

	if (size >= BUFFER_DIM) //aumenta la dimensione solo se non � gi� pieno
		size = BUFFER_DIM;
	else
		size++;
}

/*Ritorna un vector con la pi� vecchia scansione. */
std::vector<double> LaserScannerDriver::get_scan() {
	if (isEmpty()) { //se il buffer � vuoto ritorna un vettore di dimensione 0
		std::cout << "Buffer vuoto";
		std::vector<double> no(0);
		return no;
	}

	std::vector<double> vettore(scan_dimension);

	if (size <= index) { //in base alla posizione di index e size calcola dove si trova la scansione pi� vecchia
		for (int i = 0; i < scan_dimension; i++) {
			vettore[i] = buffer[index - size][i];
		}
	}
	else
	{
		for (int i = 0; i < scan_dimension; i++) {
			vettore[i] = buffer[index + BUFFER_DIM - size][i];
		}
	}

	size--; //dimensione diminuisce di 1
	return vettore;
}

/*Rimuove tutte le scansioni e ripristina tutti gli elementi a nullptr*/
void LaserScannerDriver::clear_buffer() {
	for (int i = 0; i < BUFFER_DIM; i++) {
		delete[] buffer[i];
		buffer[i] = { nullptr };
	}
	index = 0;
	size = 0;
}

/*Datogli un angolo restituisce la distanza corrispondente dell'ultima lettura*/
double LaserScannerDriver::get_distance(double angolo) {
	if (angolo < 0 || angolo > 180) { //ritorna -1 se l'angolo non � valido
		std::cout << "Angolo fuori dall'intervallo(0-180)";
		return -1;
	}

	if (isEmpty()) { //ritorna -1 se il buffer � vuoto
		std::cout << "Buffer vuoto";
		return -1;
	}

	int indice = (int)(angolo / resolution) + 0.5; //calcola l'indice al quale si trova l'angolo richiesto

	if (index > 0) //in base a dove si trova l'indice restituisce la distanza
		return buffer[index - 1][indice];
	else
		return buffer[BUFFER_DIM - 1][indice];
}

/*Overloading dell'operatore <<*/
std::ostream& operator<<(std::ostream& os, const LaserScannerDriver obj) {
	if (obj.isEmpty()) {
		os << "Buffer vuoto";
		return os;
	}

	if (obj.index > 0) { //calcola l'indice al quale si trova la scansione pi� recente
		for (int i = 0; i < obj.scan_dimension; i++) {
			os << obj.buffer[obj.index - 1][i] << "\n";
		}
	}
	else
	{
		for (int i = 0; i < obj.scan_dimension; i++) {
			os << obj.buffer[obj.BUFFER_DIM - 1][i];
		}
	}
	return os;
}

/*Costruttore di copia*/
LaserScannerDriver::LaserScannerDriver(const LaserScannerDriver& other) 
	: resolution{ other.resolution }, 
	size{ other.size }, 
	index{ other.index },
	scan_dimension{ other.scan_dimension }
{
	buffer = new double* [BUFFER_DIM];
	for (int i = 0; i < BUFFER_DIM; i++) {
		if (other.buffer[i] == nullptr) {
			buffer[i] = { nullptr };
		}
		else
		{
			buffer[i] = new double[scan_dimension];
			for (int j = 0; j < scan_dimension; j++) {
				buffer[i][j] = other.buffer[i][j];
			}
		}
	}
}

/*Overloading operatore di assegnamento per la copia*/
LaserScannerDriver& LaserScannerDriver::operator=(const LaserScannerDriver& other) {
	double** temp = new double* [other.BUFFER_DIM];
	for (int i = 0; i < other.BUFFER_DIM; i++) {
		if (other.buffer[i] == nullptr) {
			temp[i] = { nullptr };
		}
		else
		{
			temp[i] = new double[other.scan_dimension];
			for (int j = 0; j < other.scan_dimension; j++) {
				temp[i][j] = other.buffer[i][j];
			}
		}
	}
	size = other.size;
	index = other.index;
	scan_dimension = other.scan_dimension;
	resolution = other.resolution;
	clear_buffer();
	buffer = temp;
	return *this;
}


/*Costruttore di spostamento*/
LaserScannerDriver::LaserScannerDriver(LaserScannerDriver&& other) noexcept {
	resolution = other.resolution;
	index = other.resolution;
	size = other.size;
	scan_dimension = other.scan_dimension;
	buffer = other.buffer;

	other.size = 0;
	other.buffer = nullptr;
}

/*Operatore di assegnamento per lo spostamento*/
LaserScannerDriver& LaserScannerDriver::operator=(LaserScannerDriver&& other) noexcept {
	clear_buffer();
	buffer = other.buffer;
	resolution = other.resolution;
	index = other.resolution;
	size = other.size;
	scan_dimension = other.scan_dimension;
	other.buffer = nullptr;
	other.size = 0;
	return *this;
}

/*Distruttore*/
LaserScannerDriver::~LaserScannerDriver() {
	for (int i = 0; i < BUFFER_DIM; i++) {
		delete[] buffer[i];
	}
	delete[] buffer;
}

bool LaserScannerDriver::isEmpty() const{
	return size <= 0;
}