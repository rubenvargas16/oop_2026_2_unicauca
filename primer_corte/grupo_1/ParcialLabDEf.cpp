#include <iostream>
#include <string>
#include <vector>
using namespace std;

//Declaraciones anticipadas
class Biblioteca;
class Estante;
class Ejemplar;
class Autor;
class Libro;
class Estudiante;
class Prestamo;

//======================================
//CLASE AUTOR
//======================================
//Guarda los datos de un autor,Varios libros pueden apuntar al mismo autor.
class Autor {
private:
	string nombre;
	string nacionalidad;
	string fechaNacimiento;
	string fechaFallecimiento;
	int librosPublicados;
public:
	Autor() {
		nombre = "";
		nacionalidad = "";
		fechaNacimiento = "";
		fechaFallecimiento = "";
		librosPublicados = 0;
	}
	Autor(string nombre, string nacionalidad, string fechaNacimiento, string fechaFallecimiento, int librosPublicados) {
		this->nombre = nombre;
		this->nacionalidad = nacionalidad;
		this->fechaNacimiento = fechaNacimiento;
		this->fechaFallecimiento = fechaFallecimiento;
		this->librosPublicados = librosPublicados;
	}
	void setNombre(string nombre) { this->nombre = nombre; }
	void setNacionalidad(string nacionalidad) { this->nacionalidad = nacionalidad; }
	void setFechaNacimiento(string fechaNacimiento) { this->fechaNacimiento = fechaNacimiento; }
	void setFechaFallecimiento(string fechaFallecimiento) { this->fechaFallecimiento = fechaFallecimiento; }
	void setLibrosPublicados(int librosPublicados) { this->librosPublicados = librosPublicados; }
	string getNombre() const { return nombre; }
	string getNacionalidad() const { return nacionalidad; }
	string getFechaNacimiento() const { return fechaNacimiento; }
	string getFechaFallecimiento() const { return fechaFallecimiento; }
	int getLibrosPublicados() const { return librosPublicados; }
	//Muestra los datos del autor (omite el fallecimiento si esta vacio).
	void imprimir() const {
		cout << "Nombre: " << nombre << endl;
		cout << "Nacionalidad: " << nacionalidad << endl;
		cout << "Fecha de nacimiento: " << fechaNacimiento << endl;
		if (!fechaFallecimiento.empty())
			cout << "Fecha de fallecimiento: " << fechaFallecimiento << endl;
		cout << "Libros publicados: " << librosPublicados << endl;
	}
};

//Alias en ingles del nombre de la clase.
using Author = Autor;

//======================================
//CLASE LIBRO
//======================================
// nformacion catalografica del libro(sin cantidades).Apunta a su autor.
class Libro {
private:
	string titulo = "Sin titulo";
	Autor* author;
	int year = 0;
	string isbn = "SIN-ISBN";
public:
	Libro() : author(nullptr) {
		titulo = "Sin titulo";
		year = 0;
		isbn = "SIN-ISBN";
	}
	Libro(string t, Autor* a, int year, string i)
		: titulo(t), author(a), year(year), isbn(i) {}
	void setTitulo(string t) { titulo = t; }
	void setAutor(Autor* a) { author = a; }
	void setYear(int y) { year = y; }
	void setISBN(string i) { isbn = i; }
	string getTitulo() const { return titulo; }
	Autor* getAutor() const { return author; }
	int getYear() const { return year; }
	string getISBN() const { return isbn; }
	// Muestra los datos del libro y de su autor.
	void imprimir() const {
		cout << "Titulo: " << titulo << endl;
		cout << "ISBN: " << isbn << endl;
		cout << "Anio publicacion: " << year << endl;
		if (author) {
			cout << "Autor:" << endl;
			author->imprimir();
		}
	}
};

//======================================
//CLASE ESTUDIANTE
//======================================
//Persona a la que se le pueden prestar libros.
class Estudiante {
private:
	string codigo;
	string nombre;
	string carrera;
public:
	Estudiante() {
		codigo = "SIN-CODIGO";
		nombre = "Sin nombre";
		carrera = "Sin carrera";
	}
	Estudiante(string c, string n, string ca) : codigo(c), nombre(n), carrera(ca) {}
	void setCodigo(string c) { codigo = c; }
	void setNombre(string n) { nombre = n; }
	void setCarrera(string ca) { carrera = ca; }
	string getCodigo() const { return codigo; }
	string getNombre() const { return nombre; }
	string getCarrera() const { return carrera; }
	//Muestra los datos del estudiante.
	void imprimir() const {
		cout << "Codigo: " << codigo << endl;
		cout << "Nombre: " << nombre << endl;
		cout << "Carrera: " << carrera << endl;
	}
};

//======================================
//CLASE PRESTAMO
//======================================
//Registro de un prestamo: que ejemplar se presto y a que estudiante.
class Prestamo {
private:
	Ejemplar* ejemplar;
	Estudiante* estudiante;
	bool activo;
public:
	Prestamo(Ejemplar* eje, Estudiante* est) : ejemplar(eje), estudiante(est), activo(true) {}
	Ejemplar* getEjemplar() const { return ejemplar; }
	Estudiante* getEstudiante() const { return estudiante; }
	bool estaActivo() const { return activo; }
	//Marca el prestamo como terminado(no esta en el menu: el enunciado no pide devolucion).
	void finalizarPrestamo() { activo = false; }
};

//======================================
//CLASE EJEMPLAR
//======================================
// xistencia fisica de un libro en un estante: guarda la cantidad disponible y sus prestamos.
class Ejemplar {
private:
	Libro* libro;
	int cantidadDisponible;
	Estante* estante;
	vector<Prestamo*> prestamos;
public:
	Ejemplar() : libro(nullptr), cantidadDisponible(0), estante(nullptr) {}
	Ejemplar(Libro* lib, int cant, Estante* est) : libro(lib), cantidadDisponible(cant), estante(est) {}
	
	//El ejemplar es dueno de sus prestamos:los libera al destruirse.
	~Ejemplar() {
		for (auto p : prestamos) {
			delete p;
		}
		prestamos.clear();
	}
	
	void setLibro(Libro* lib) { libro = lib; }
	void setEstante(Estante* est) { estante = est; }
	//Solo acepta cantidades >= 0.Devuelve true si se actualizo.
	bool setCantidadDisponible(int cant) {
		if (cant >= 0) {
			cantidadDisponible = cant;
			return true;
		}
		return false;
	}
	Libro* getLibro() const { return libro; }
	int getCantidad() const { return cantidadDisponible; }
	Estante* getEstante() const;
	vector<Prestamo*> getPrestamos() const { return prestamos; }
	//Indica si queda al menos una unidad para prestar.
	bool hayDisponibilidad() const { return cantidadDisponible > 0; }
	
	//Presta una unidad: crea el Prestamo y descuenta 1 de la cantidad disponible.
	bool prestarAEstudiante(Estudiante* est) {
		if (hayDisponibilidad()) {
			Prestamo* nuevoPrestamo = new Prestamo(this, est);
			prestamos.push_back(nuevoPrestamo);
			cantidadDisponible--;
			return true;
		}
		return false;
	}
	//Agrega un prestamo ya creado a la lista del ejemplar.
	void agregarPrestamo(Prestamo* prestamo) {
		prestamos.push_back(prestamo);
	}
};

//======================================
//CLASE ESTANTE
//======================================
//Agrupa los ejemplares de un estante y sabe a que biblioteca pertenece.
class Estante {
private:
	string nombre;
	vector<Ejemplar*> ejemplares;
	Biblioteca* biblioteca;
public:
	Estante(string nom, Biblioteca* bib) : nombre(nom), biblioteca(bib) {}
	
	//El estante es dueno de sus ejemplares:los libera al destruirse.
	~Estante() {
		for (auto e : ejemplares) {
			delete e;
		}
		ejemplares.clear();
	}
	
	void setNombre(string nom) { nombre = nom; }
	void setBiblioteca(Biblioteca* bib) { biblioteca = bib; }
	string getNombre() const { return nombre; }
	Biblioteca* getBiblioteca() const { return biblioteca; }
	vector<Ejemplar*> getEjemplares() const { return ejemplares; }
	//Guarda el puntero al ejemplar (sin copiarlo), asi todos ven la misma cantidad.
	void agregarEjemplar(Ejemplar* eje) {
		ejemplares.push_back(eje);
	}
	//Devuelve el primer ejemplar de este estante con ese titulo, o nullptr si no hay.
	Ejemplar* buscarEjemplarPorTitulo(string titulo) {
		for (auto eje : ejemplares) {
			if (eje->getLibro()->getTitulo() == titulo) {
				return eje;
			}
		}
		return nullptr;
	}
};

Estante* Ejemplar::getEstante() const { return estante; }

//======================================
//CLASE BIBLIOTECA
// ======================================
//Agrupa estantes y ofrece las consultas de inventario y prestamos.
class Biblioteca {
private:
	string nombre;
	vector<Estante*> estantes;
public:
	Biblioteca() {}
	Biblioteca(string nom) : nombre(nom) {}
	
	//La biblioteca es duena de sus estantes: los libera al destruirse.
	~Biblioteca() {
		for (auto e : estantes) {
			delete e;
		}
		estantes.clear();
	}
	
	void setNombre(string nom) { nombre = nom; }
	string getNombre() const { return nombre; }
	vector<Estante*> getEstantes() const { return estantes; }
	//Agrega el estante y le asigna esta biblioteca como duena.
	void agregarEstante(Estante* est) {
		est->setBiblioteca(this);
		estantes.push_back(est);
	}
	
	//Imprime donde hay ejemplares disponibles del libro.
	//Devuelve true si encontro al menos uno en esta biblioteca.
	bool consultarDisponibilidadLibro(string titulo) {
		bool encontrado = false;
		for (auto est : estantes) {
			for (auto eje : est->getEjemplares()) {
				if (eje->getLibro()->getTitulo() == titulo && eje->getCantidad() > 0) {
					cout << "Disponible en: " << nombre << " | Estante: " << est->getNombre()
						<< " | Cantidad: " << eje->getCantidad() << endl;
					encontrado = true;
				}
			}
		}
		return encontrado;
	}
	//Muestra cada estante con sus libros y cantidades.
	void listarInventario() {
		cout << "Inventario de la biblioteca: " << nombre << endl;
		for (auto est : estantes) {
			cout << "--- Estante: " << est->getNombre() << " ---" << endl;
			for (auto eje : est->getEjemplares()) {
				cout << "  Libro: " << eje->getLibro()->getTitulo() << " | Cantidad: " << eje->getCantidad() << endl;
			}
		}
	}
	//Suma las cantidades disponibles de todos los estantes.
	int contarTotalEjemplares() {
		int total = 0;
		for (auto est : estantes) {
			for (auto eje : est->getEjemplares()) {
				total += eje->getCantidad();
			}
		}
		return total;
	}
	//Muestra los prestamos activos de esta biblioteca (se define mas abajo).
	void listarPrestamosActivos();
};

//======================================
//VARIABLES GLOBALES
//======================================
//Almacen central del sistema: cada lista es duena de sus objetos.
vector<Autor*> listaAutores;
vector<Libro*> listaLibros;
vector<Estudiante*> listaEstudiantes;
vector<Biblioteca*> listaBibliotecas;

//======================================
//LIBERACION DE MEMORIA
//======================================
void liberarMemoria() {
	for (auto a : listaAutores) {
		delete a;
	}
	listaAutores.clear();
	
	for (auto l : listaLibros) {
		delete l;
	}
	listaLibros.clear();
	
	for (auto e : listaEstudiantes) {
		delete e;
	}
	listaEstudiantes.clear();
	
	//Eliminar las bibliotecas libera en cascada sus estantes (~Biblioteca),
	//los ejemplares de cada estante (~Estante) y los prestamos de cada
	//ejemplar (~Ejemplar).
	for (auto b : listaBibliotecas) {
		delete b;
	}
	listaBibliotecas.clear();
}

//======================================
//FUNCIONES DE LECTURA
//======================================
//Lee una linea completa (permite espacios y cadenas vacias).
string leerLinea() {
	string s;
	getline(cin, s);
	return s;
}

//Lee un entero validando la entrada y deja el buffer limpio.
int leerEntero() {
	int valor;
	while (!(cin >> valor)) {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Entrada invalida. Ingrese un numero: ";
	}
	cin.ignore(10000, '\n');
	return valor;
}

//======================================
//FUNCIONES
//======================================
//Opcion 1: pide los datos del autor y lo guarda en listaAutores.
void registrarAutor() {
	cout << "--- Registrar Autor ---" << endl;
	cout << "Nombre: ";
	string nombre = leerLinea();
	cout << "Nacionalidad: ";
	string nacionalidad = leerLinea();
	cout << "Fecha de nacimiento: ";
	string fnac = leerLinea();
	cout << "Fecha de fallecimiento (dejar vacio si aplica): ";
	string fmuer = leerLinea();
	cout << "Libros publicados: ";
	int cant = leerEntero();
	listaAutores.push_back(new Autor(nombre, nacionalidad, fnac, fmuer, cant));
	cout << "Autor registrado exitosamente." << endl;
}

//Opcion 2: registra un libro asociado a un autor ya registrado.
void registrarLibro() {
	if (listaAutores.empty()) {
		cout << "Primero registre al menos un autor." << endl;
		return;
	}
	cout << "--- Registrar Libro ---" << endl;
	cout << "Titulo: ";
	string titulo = leerLinea();
	cout << "Anio de publicacion: ";
	int year = leerEntero();
	cout << "ISBN: ";
	string isbn = leerLinea();
	
	cout << "\nSeleccione autor:" << endl;
	for (size_t i = 0; i < listaAutores.size(); ++i) {
		cout << i + 1 << ". " << listaAutores[i]->getNombre() << endl;
	}
	cout << "Opcion: ";
	int autorOp = leerEntero();
	if (autorOp < 1 || autorOp > (int)listaAutores.size()) {
		cout << "Opcion invalida. No se registro el libro." << endl;
		return;
	}
	listaLibros.push_back(new Libro(titulo, listaAutores[autorOp - 1], year, isbn));
	cout << "Libro registrado exitosamente." << endl;
}

//Recorre estantes, ejemplares y prestamos, y muestra solo los activos.
void Biblioteca::listarPrestamosActivos() {
	cout << "--- Prestamos activos en: " << nombre << " ---" << endl;
	bool hayPrestamos = false;
	for (auto est : estantes) {
		for (auto eje : est->getEjemplares()) {
			for (auto prestamo : eje->getPrestamos()) {
				if (prestamo->estaActivo()) {
					cout << "Libro: " << eje->getLibro()->getTitulo()
						<< " | Estudiante: " << prestamo->getEstudiante()->getNombre()
						<< " (" << prestamo->getEstudiante()->getCodigo() << ")" << endl;
					hayPrestamos = true;
				}
			}
		}
	}
	if (!hayPrestamos) {
		cout << "No hay prestamos activos en esta biblioteca." << endl;
	}
}

//Opcion 3:crea una biblioteca.
void registrarBiblioteca() {
	cout << "--- Registrar Biblioteca ---" << endl;
	cout << "Nombre: ";
	string nombre = leerLinea();
	listaBibliotecas.push_back(new Biblioteca(nombre));
	cout << "Biblioteca registrada exitosamente." << endl;
}

//Opcion 4:crea un estante y lo asigna a una biblioteca.
void registrarEstante() {
	if (listaBibliotecas.empty()) {
		cout << "No hay bibliotecas registradas. Por favor, registre una biblioteca primero." << endl;
		return;
	}
	cout << "--- Registrar Estante ---" << endl;
	cout << "Nombre del estante: ";
	string nombre = leerLinea();
	cout << "Seleccione una biblioteca:" << endl;
	for (size_t i = 0; i < listaBibliotecas.size(); ++i) {
		cout << i + 1 << ". " << listaBibliotecas[i]->getNombre() << endl;
	}
	cout << "Opcion: ";
	int bibOp = leerEntero();
	if (bibOp < 1 || bibOp > (int)listaBibliotecas.size()) {
		cout << "Opcion invalida. No se registro el estante." << endl;
		return;
	}
	Estante* nuevoEstante = new Estante(nombre, listaBibliotecas[bibOp - 1]);
	listaBibliotecas[bibOp - 1]->agregarEstante(nuevoEstante);
	cout << "Estante registrado exitosamente." << endl;
}

//Opcion5:crea el ejemplar de un libro con su cantidad y lo ubica en un estante.
void registrarEjemplar() {
	if (listaLibros.empty()) {
		cout << "No hay libros registrados. Por favor, registre un libro primero." << endl;
		return;
	}
	if (listaBibliotecas.empty()) {
		cout << "No hay bibliotecas registradas. Por favor, registre una biblioteca primero." << endl;
		return;
	}
	cout << "--- Registrar Ejemplar ---" << endl;
	cout << "Seleccione un libro:" << endl;
	for (size_t i = 0; i < listaLibros.size(); ++i) {
		cout << i + 1 << ". " << listaLibros[i]->getTitulo() << endl;
	}
	cout << "Opcion: ";
	int libroOp = leerEntero();
	if (libroOp < 1 || libroOp > (int)listaLibros.size()) {
		cout << "Opcion invalida. No se registro el ejemplar." << endl;
		return;
	}
	cout << "Seleccione una biblioteca:" << endl;
	for (size_t i = 0; i < listaBibliotecas.size(); ++i) {
		cout << i + 1 << ". " << listaBibliotecas[i]->getNombre() << endl;
	}
	cout << "Opcion: ";
	int bibOp = leerEntero();
	if (bibOp < 1 || bibOp > (int)listaBibliotecas.size()) {
		cout << "Opcion invalida. No se registro el ejemplar." << endl;
		return;
	}
	if (listaBibliotecas[bibOp - 1]->getEstantes().empty()) {
		cout << "La biblioteca seleccionada no tiene estantes registrados." << endl;
		return;
	}
	cout << "Seleccione un estante:" << endl;
	vector<Estante*> estantes = listaBibliotecas[bibOp - 1]->getEstantes();
	for (size_t i = 0; i < estantes.size(); ++i) {
		cout << i + 1 << ". " << estantes[i]->getNombre() << endl;
	}
	cout << "Opcion: ";
	int estanteOp = leerEntero();
	if (estanteOp < 1 || estanteOp > (int)estantes.size()) {
		cout << "Opcion invalida. No se registro el ejemplar." << endl;
		return;
	}
	cout << "Cantidad disponible: ";
	int cantidad = leerEntero();
	if (cantidad < 0) {
		cout << "Cantidad invalida." << endl;
		return;
	}
	Ejemplar* nuevoEjemplar = new Ejemplar(listaLibros[libroOp - 1], cantidad, estantes[estanteOp - 1]);
	estantes[estanteOp - 1]->agregarEjemplar(nuevoEjemplar);
	cout << "Ejemplar registrado exitosamente." << endl;
}

//Opcion6:muestra en que bibliotecas y estantes hay unidades de un titulo.
void consultarDisponibilidadLibro() {
	if (listaBibliotecas.empty()) {
		cout << "No hay bibliotecas registradas." << endl;
		return;
	}
	cout << "--- Consultar Disponibilidad ---" << endl;
	cout << "Ingrese el titulo del libro: ";
	string titulo = leerLinea();
	bool encontrado = false;
	for (auto bib : listaBibliotecas) {
		if (bib->consultarDisponibilidadLibro(titulo)) {
			encontrado = true;
		}
	}
	if (!encontrado) {
		cout << "El libro '" << titulo << "' no esta disponible en ninguna biblioteca." << endl;
	}
}

//Opcion8:cambia la cantidad de un ejemplar (se elige cual si el titulo esta en varios lugares).
void actualizarCantidadEjemplar() {
	cout << "--- Actualizar Cantidad de Ejemplar ---" << endl;
	cout << "Ingrese el titulo del libro: ";
	string titulo = leerLinea();
	
	//Se reunen todos los ejemplares de ese titulo (pueden estar en varias bibliotecas).
	vector<Ejemplar*> coincidencias;
	for (auto bib : listaBibliotecas) {
		for (auto est : bib->getEstantes()) {
			for (auto eje : est->getEjemplares()) {
				if (eje->getLibro()->getTitulo() == titulo) {
					coincidencias.push_back(eje);
				}
			}
		}
	}
	if (coincidencias.empty()) {
		cout << "No se encuentra el libro en ninguna biblioteca." << endl;
		return;
	}
	
	Ejemplar* elegido = coincidencias[0];
	if (coincidencias.size() > 1) {
		cout << "Seleccione el ejemplar a actualizar:" << endl;
		for (size_t i = 0; i < coincidencias.size(); ++i) {
			cout << i + 1 << ". Biblioteca: " << coincidencias[i]->getEstante()->getBiblioteca()->getNombre()
				<< " | Estante: " << coincidencias[i]->getEstante()->getNombre()
				<< " | Cantidad actual: " << coincidencias[i]->getCantidad() << endl;
		}
		cout << "Opcion: ";
		int op = leerEntero();
		if (op < 1 || op > (int)coincidencias.size()) {
			cout << "Opcion invalida." << endl;
			return;
		}
		elegido = coincidencias[op - 1];
	}
	
	cout << "Nueva cantidad disponible: ";
	int nuevaCant = leerEntero();
	if (elegido->setCantidadDisponible(nuevaCant)) {
		cout << "Cantidad actualizada correctamente." << endl;
	} else {
		cout << "La cantidad no puede ser negativa." << endl;
	}
}

// Opcion9:registra un estudiante.
void registrarEstudiante() {
	cout << "--- Registrar Estudiante ---" << endl;
	cout << "Codigo: ";
	string codigo = leerLinea();
	cout << "Nombre: ";
	string nombre = leerLinea();
	cout << "Carrera: ";
	string carrera = leerLinea();
	listaEstudiantes.push_back(new Estudiante(codigo, nombre, carrera));
	cout << "Estudiante registrado exitosamente." << endl;
}

//Busca el primer ejemplar con ese titulo que tenga unidades disponibles.
//'existeTitulo' indica si el titulo esta registrado en algun ejemplar.
Ejemplar* buscarEjemplarParaPrestamo(string titulo, bool& existeTitulo) {
	existeTitulo = false;
	for (auto bib : listaBibliotecas) {
		for (auto est : bib->getEstantes()) {
			for (auto eje : est->getEjemplares()) {
				if (eje->getLibro()->getTitulo() == titulo) {
					existeTitulo = true;
					if (eje->hayDisponibilidad()) {
						return eje;
					}
				}
			}
		}
	}
	return nullptr;
}

//Opcion 10:presta un ejemplar disponible del titulo a un estudiante.
void registrarPrestamo() {
	if (listaEstudiantes.empty()) {
		cout << "No hay estudiantes registrados." << endl;
		return;
	}
	if (listaBibliotecas.empty()) {
		cout << "No hay bibliotecas registradas." << endl;
		return;
	}
	cout << "--- Registrar Prestamo ---" << endl;
	cout << "Ingrese el titulo del libro: ";
	string titulo = leerLinea();
	
	bool existeTitulo = false;
	Ejemplar* ejemplar = buscarEjemplarParaPrestamo(titulo, existeTitulo);
	if (!existeTitulo) {
		cout << "El libro '" << titulo << "' no se encuentra en ninguna biblioteca." << endl;
		return;
	}
	if (!ejemplar) {
		cout << "No hay ejemplares disponibles para prestar." << endl;
		return;
	}
	cout << "Seleccione un estudiante:" << endl;
	for (size_t i = 0; i < listaEstudiantes.size(); ++i) {
		cout << i + 1 << ". " << listaEstudiantes[i]->getNombre() << endl;
	}
	cout << "Opcion: ";
	int opEst = leerEntero();
	if (opEst < 1 || opEst > (int)listaEstudiantes.size()) {
		cout << "Opcion invalida. No se registro el prestamo." << endl;
		return;
	}
	if (ejemplar->prestarAEstudiante(listaEstudiantes[opEst - 1])) {
		cout << "Prestamo registrado exitosamente." << endl;
	}
}

//Opcion 11:pide una biblioteca y muestra sus prestamos activos.
void listarPrestamosActivos() {
	if (listaBibliotecas.empty()) {
		cout << "No hay bibliotecas registradas." << endl;
		return;
	}
	cout << "--- Listar Prestamos Activos ---" << endl;
	for (size_t i = 0; i < listaBibliotecas.size(); ++i) {
		cout << i + 1 << ". " << listaBibliotecas[i]->getNombre() << endl;
	}
	cout << "Opcion: ";
	int op = leerEntero();
	if (op >= 1 && op <= (int)listaBibliotecas.size()) {
		listaBibliotecas[op - 1]->listarPrestamosActivos();
	} else {
		cout << "Opcion invalida." << endl;
	}
}

//Opcion 7:muestra el inventario de una biblioteca y su total de ejemplares.
void listarInventarioBiblioteca() {
	if (listaBibliotecas.empty()) {
		cout << "No hay bibliotecas registradas." << endl;
		return;
	}
	cout << "--- Listar Inventario ---" << endl;
	for (size_t i = 0; i < listaBibliotecas.size(); ++i) {
		cout << i + 1 << ". " << listaBibliotecas[i]->getNombre() << endl;
	}
	cout << "Opcion: ";
	int op = leerEntero();
	if (op >= 1 && op <= (int)listaBibliotecas.size()) {
		listaBibliotecas[op - 1]->listarInventario();
		cout << "Total de ejemplares: " << listaBibliotecas[op - 1]->contarTotalEjemplares() << endl;
	} else {
		cout << "Opcion invalida." << endl;
	}
}

//Opcion 12:muestra los libros que un estudiante tiene en prestamo.
void verLibrosPrestadosEstudiante() {
	if (listaEstudiantes.empty()) {
		cout << "No hay estudiantes registrados." << endl;
		return;
	}
	cout << "--- Ver Libros Prestados ---" << endl;
	cout << "Seleccione un estudiante:" << endl;
	for (size_t i = 0; i < listaEstudiantes.size(); ++i) {
		cout << i + 1 << ". " << listaEstudiantes[i]->getNombre() << endl;
	}
	cout << "Opcion: ";
	int opEst = leerEntero();
	if (opEst < 1 || opEst > (int)listaEstudiantes.size()) {
		cout << "Opcion invalida." << endl;
		return;
	}
	Estudiante* est = listaEstudiantes[opEst - 1];
	cout << "--- Libros prestados a " << est->getNombre() << " ---" << endl;
	bool tiene = false;
	for (auto bib : listaBibliotecas) {
		for (auto estante : bib->getEstantes()) {
			for (auto eje : estante->getEjemplares()) {
				for (auto prestamo : eje->getPrestamos()) {
					if (prestamo->getEstudiante() == est && prestamo->estaActivo()) {
						cout << "Libro: " << eje->getLibro()->getTitulo() << endl;
						tiene = true;
					}
				}
			}
		}
	}
	if (!tiene) {
		cout << "El estudiante no tiene libros prestados actualmente." << endl;
	}
}

//Imprime las opciones del menu.
void mostrarMenu() {
	cout << "\n===== SISTEMA DE GESTION DE BIBLIOTECAS =====" << endl;
	cout << "1. Registrar Autor" << endl;
	cout << "2. Registrar Libro" << endl;
	cout << "3. Registrar Biblioteca" << endl;
	cout << "4. Registrar Estante" << endl;
	cout << "5. Registrar Ejemplar" << endl;
	cout << "6. Consultar Disponibilidad de Libro" << endl;
	cout << "7. Listar Inventario de Biblioteca" << endl;
	cout << "8. Actualizar Cantidad de Ejemplar" << endl;
	cout << "9. Registrar Estudiante" << endl;
	cout << "10. Registrar Prestamo" << endl;
	cout << "11. Listar Prestamos Activos" << endl;
	cout << "12. Ver Libros Prestados a un Estudiante" << endl;
	cout << "0. Salir" << endl;
	cout << "Seleccione una opcion: ";
}

//Solo orquesta el menu: lee la opcion y delega en la funcion correspondiente.
int main() {
	int opcion;
	do {
		mostrarMenu();
		opcion = leerEntero();
		switch (opcion) {
		case 1: registrarAutor(); break;
		case 2: registrarLibro(); break;
		case 3: registrarBiblioteca(); break;
		case 4: registrarEstante(); break;
		case 5: registrarEjemplar(); break;
		case 6: consultarDisponibilidadLibro(); break;
		case 7: listarInventarioBiblioteca(); break;
		case 8: actualizarCantidadEjemplar(); break;
		case 9: registrarEstudiante(); break;
		case 10: registrarPrestamo(); break;
		case 11: listarPrestamosActivos(); break;
		case 12: verLibrosPrestadosEstudiante(); break;
		case 0: cout << "Saliendo del sistema..." << endl; break;
		default: cout << "Opcion invalida. Intente nuevamente." << endl; break;
		}
	} while (opcion != 0);
	
	liberarMemoria();
	return 0;
}
