//Katheryn sofia cabezas silva
//Jeison Camilo Macias Ijaji

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Autor 
{
private:
	string nombre;
	string nacionalidad;
	string fechaNacimiento;
	string fechaMuerte;
	int librosPublicados;
	vector<string> libros; // Vector para almacenar los títulos de los libros del autor
public:
	Autor() {
		this->nombre = "Sin nombre";
		this->nacionalidad = "Sin nacionalidad";
		this->fechaNacimiento = "Sin fecha de nacimiento";
		this->fechaMuerte = "Sin fecha de muerte";
		this->librosPublicados = 0;
	}
	Autor(string nombre, string nacionalidad) {
		this->nombre = nombre;
		this->nacionalidad = nacionalidad;
		this->fechaNacimiento = "Sin fecha de nacimiento";
		this->fechaMuerte = "Sin fecha de muerte";
		this->librosPublicados = 0;
	}
	void setNombre(string nombre) { this->nombre = nombre; }
	void setNacionalidad(string nacionalidad){this->nacionalidad = nacionalidad;}
	void setFechaNacimiento(string fechaNacimiento) { this->fechaNacimiento = fechaNacimiento; }
	void setFechaMuerte(string fechaMuerte) { this->fechaMuerte = fechaMuerte; }
	void setLibrosPublicados(int librosPublicados) { this->librosPublicados = librosPublicados; }
	void agregarLibro(string titulo) {
		this->libros.push_back(titulo);
		this->librosPublicados = this->libros.size();
	}
	
	string getNombre() { return this->nombre; }
	string getNacionalidad(){return this->nacionalidad;}
	string getFechaNacimiento() { return this->fechaNacimiento; }
	string getFechaMuerte() { return this->fechaMuerte; }
	int getLibrosPublicados() { return this->librosPublicados; }
	vector<string> getLibros() { return this->libros; }
	
	void ListaLibros(){
		cout << "Libros del autor " << this->nombre << ":" << endl;
		for(const auto& libro : this->libros){ // auto& es 
			cout << "- " << libro << endl;
		}
	}
		
		void printAutor() {
			cout << "Nombre del autor: " << this->nombre << endl;
			cout << "Nacionalidad: " << this->nacionalidad << endl;
			cout << "Fecha de nacimiento: " << this->fechaNacimiento << endl;
			cout << "Fecha de muerte: " << this->fechaMuerte << endl;
			cout << "Libros publicados: " << this->librosPublicados << endl;
		}
		// muestra una lista de los libros publicados
		void listaPublicados(){
			cout << "Libros publicados por " << this->nombre << ":" << endl;
			
			if (this->libros.empty()) {
				cout << "- No hay libros publicados." << endl;
				return;
			}
			for (size_t i = 0; i < this->libros.size(); i++) {
				cout << i + 1 << ". " << this->libros[i] << endl;
			}
		}
			
};

class Ejemplar;
class Estante;

class Libro {
private:
	string titulo;
	int fechaPublicacion;
	Autor* autor;
	vector<string> Listaestantes;
public:
	Libro() {
		titulo = "Sin título";
		fechaPublicacion = 0;
		autor = nullptr;
	}
	Libro(string titulo, Autor* autor)
		: titulo(titulo), fechaPublicacion(0), autor(autor) {}
	Libro(string titulo, Autor* autor, int fechaPublicacion)
		: titulo(titulo), fechaPublicacion(fechaPublicacion), autor(autor) {}
	
	void setTitulo(string titulo) { this->titulo = titulo; }
	void setAutor(Autor* autor) { this->autor = autor; }
	void setAgregarEstante(string estante){this->Listaestantes.push_back(estante);}
	void setFechaPublicacion(int fechaPublicacion) { this->fechaPublicacion = fechaPublicacion; }
	
	string getTitulo() { return this->titulo; }
	int getFechaPublicacion() { return this->fechaPublicacion; } 
	Autor* getAutor() { return this->autor; }
	vector<string> getListaEstantes(){return this->Listaestantes;}
	
	void printLibro() {
		cout << "Título del libro: " << titulo << endl;
		cout << "Año de publicación: " << fechaPublicacion << endl; 
		autor->printAutor();
	}
	
	void listaEstantes(){
		cout << "Lista de estantes en la se encuentra el libro " << this->titulo << endl;
		for(const auto& estante : this->Listaestantes){ // Itera sobre cada estante en el vector de estantes
			cout << "- Estante: " << estante << endl;
		}
	}
		
		
		
};

class Ejemplar {
private:
	Libro* libro;
	int numeroEjemplar;
	vector<string> estantes;
public:
	Ejemplar() {
		libro = nullptr;
		numeroEjemplar = 0;
	}
	Ejemplar(Libro* libro, int numeroEjemplar) : libro(libro) {
		this->numeroEjemplar = numeroEjemplar;
	}
	void setLibro(Libro* libro) { this->libro = libro; }
	void setNumeroEjemplar(int numeroEjemplar) { this->numeroEjemplar = numeroEjemplar; }
	void setAgregarEstante(string estante){this->estantes.push_back(estante);}
	
	Libro* getLibro() {return this->libro; }
	int getNumeroEjemplar() { return this->numeroEjemplar; }
	vector<string> getEstantes(){return this->estantes;}
	
	void printEjemplar() {
		cout << "Número de ejemplar: " << numeroEjemplar << endl;
		libro->printLibro();
	}
	void printEjemplarInformacion() {
		cout  << "# Título: " << libro->getTitulo() << endl
			<< "-- Autor: " << libro->getAutor()->getNombre() << endl
			<< "-- Número de ejemplares: " << numeroEjemplar  << endl
			<< "--Cantidad disponible: " << this->numeroEjemplar << endl;
	}
};

class Estudiante
{
private:
	string nombre;
	string codigo;
public: 
	Estudiante(){
		this->nombre=" ";
		this->codigo=" ";
	}
	Estudiante(string nombre, string codigo){
		this->nombre = nombre;
		this->codigo = codigo;
	}
		//setters
		void setNombre(string nombre){this->nombre= nombre;}
		void setCodigo(string codigo){this->codigo=codigo;}
		//getters
		string getNombre(){return this->nombre;}
		string getCodigo(){return this->codigo;}
		
		void print(){
			cout<< "Información del estudiante: " << endl;
			cout<<"Nombre: "<<this->nombre <<endl;
			cout<<"Código: "<<this->codigo <<endl;
		}
};

class Prestamo
{
private:
	string fecha;
	Estudiante* estudiante;
	Ejemplar* ejemplarPrestado;
public: 
	Prestamo(){
		this->fecha = " ";
		this->estudiante = nullptr;
		this->ejemplarPrestado = nullptr;
	}
	Prestamo(string fecha, Estudiante* estudiante, Ejemplar* ejemplarPrestado){
		this->fecha = fecha;
		this->estudiante = estudiante;
		this->ejemplarPrestado = ejemplarPrestado;
	}
		//getters
		Estudiante* getEstudiante(){return this->estudiante;}
		Ejemplar* getEjemplarPrestado(){return this->ejemplarPrestado;}
		
		void print()
		{
			cout<<"Prestamo realizado: " << endl;
			cout<<"Fecha: " <<this->fecha <<endl;
			cout<<"Datos del estudiante: " <<endl;
			cout<<"Estudiante: "<<this->estudiante->getNombre()<<endl;
			cout<<"Codigo: "<<this->estudiante->getCodigo()<< endl;
			cout<<"Ejemplar: "<<endl;
			cout <<"Libro: "<< this->ejemplarPrestado->getLibro()->getTitulo()<<endl;
		}
};

class Estante {
private:
	string nombreEstante;
	vector<Ejemplar> ejemplares; 
public:
	Estante() {
		nombreEstante = "Sin nombre";
	}
	Estante(string nombreEstante) {
		this->nombreEstante = nombreEstante;
	}
	void setNombreEstante(string nombreEstante) { this->nombreEstante = nombreEstante; }
	string getNombreEstante() { return this->nombreEstante; }
	vector<Ejemplar>& getEjemplares() {
		return this->ejemplares;
	}
	void agregarEjemplar(Ejemplar ejemplar) {
		ejemplares.push_back(ejemplar);
	}
	// Método para mostrar los ejemplares en el estante
	
	void mostrarEjemplares() {
		
		if (this->ejemplares.empty()) { // Verifica si el vector de ejemplares está vacío
			cout << "El estante está vacío." << endl;
		}else{
			cout << "Estante: " << this->nombreEstante << endl;
			for (int i = 0; i < this->ejemplares.size(); i++) {
				this->ejemplares[i].printEjemplarInformacion(); // Llama al método printEjemplarInformacion() de cada ejemplar
			}
		}
	}
	
	int buscarLibro(string title){
		int index = -1;
		for (int i = 0; i < this->ejemplares.size(); i++){
			Libro *tmp = this->ejemplares[i].getLibro();
			if (tmp->getTitulo() == title){
				index = i;
				break;
			}
		}
		return index;
	}
};

class Biblioteca {
private:
	string nombreBiblioteca;
	vector<Estante*> estantes;
public:
	Biblioteca() {
		nombreBiblioteca = "Sin nombre";
	}
	Biblioteca(string nombreBiblioteca) {
		this->nombreBiblioteca = nombreBiblioteca;
	}
	void setNombreBiblioteca(string nombreBiblioteca) { this->nombreBiblioteca = nombreBiblioteca; }
	string getNombreBiblioteca() { return this->nombreBiblioteca; }
	vector<Estante*>& getEstantes() {
		return this->estantes;
	}
	void agregarEstante(Estante* estante) {
		estantes.push_back(estante);
	}
	void mostrarEstantes() {
		cout << "Biblioteca: " << this->nombreBiblioteca << endl;
		for (int i = 0; i < this->estantes.size(); i++) {
			cout << "Estante: " << this->estantes[i]->getNombreEstante() << endl;
			//this->estantes[i]->mostrarEjemplares();
		}
	}
	
	void listaDeLibros() {
		cout << "Lista de libros en la biblioteca " << this->nombreBiblioteca << ":" << endl;
		for (int i = 0; i < this->estantes.size(); i++) {
			cout << "Estante: " << this->estantes[i]->getNombreEstante() << endl;
			this->estantes[i]->mostrarEjemplares();
		}
	}
	
	void buscarLibro(string title){
		int indexEstante = -1;
		int indexLibro = -1;
		for (int i = 0; i < this->estantes.size(); i++){
			Estante* tmp = this->estantes[i];
			int tmpIndex = tmp->buscarLibro(title);
			if (tmpIndex >= 0){
				indexLibro = tmpIndex;
				indexEstante = i;
				break;
			}
		}
		if (indexEstante >= 0){
			cout << "El libro " << title << ", se encuentra en la estanteria "
				<< this->estantes[indexEstante]->getNombreEstante()
				<< " en la posición " << indexLibro << endl;
		}else{
			cout << "El libro no está en la biblioteca" << endl;
		}
	}
		
};

void registrarAutor(vector<Autor>& autores) {
	string nombre, nacionalidad, fechaNacimiento, fechaMuerte;
	cout << "--Nombre del autor: ";
	cin.ignore();
	getline(cin, nombre);
	cout << "Nacionalidad del autor: ";
	getline(cin, nacionalidad);
	cout << "Fecha de nacimiento (dd/mm/aaaa): ";
	getline(cin, fechaNacimiento);
	cout << "Fecha de muerte (dd/mm/aaaa o 'Vivo'): ";
	getline(cin, fechaMuerte);
	
	autores.emplace_back(nombre, nacionalidad);
	autores.back().setFechaNacimiento(fechaNacimiento);
	autores.back().setFechaMuerte(fechaMuerte);
	// librosPublicados empieza en 0 y se actualiza al agregar libros
	cout << "# Autor registrado.\n";
}

void registrarLibro(vector<Autor>& autores, vector<Libro>& libros) {
	if (autores.empty()) {
		cout << "  Primero registra un autor.\n";
		return;
	}
	string titulo;
	int fechaPublicacion;
	int N_autor;
	
	cout << "--Título: ";
	cin.ignore();
	getline(cin, titulo);
	
	cout << "--Año de publicación: ";   
	cin >> fechaPublicacion;            
	
	cout << "Seleccione un autor de la lista:\n";
	for (size_t i = 0; i < autores.size(); i++)
		cout << i << ". " << autores[i].getNombre() << "\n";
	cout << "Autor (índice): ";
	cin >> N_autor;
	
	if (N_autor >= 0 && N_autor < (int)autores.size()) {
		libros.emplace_back(titulo, &autores[N_autor], fechaPublicacion); 
		autores[N_autor].agregarLibro(titulo); 
	} else {
		cout << "[X] Índice inválido.\n";
	}
}

//Generado con IA
void listarPrestamosBiblioteca(vector<Biblioteca>& bibliotecas,
                               vector<Prestamo>& prestamos) {
	string nombreBiblioteca;

	cout << "Nombre de la biblioteca: ";
	cin.ignore();
	getline(cin, nombreBiblioteca);

	for (size_t i = 0; i < bibliotecas.size(); i++) {
		if (bibliotecas[i].getNombreBiblioteca() == nombreBiblioteca) {
			vector<Estante*>& estantes = bibliotecas[i].getEstantes();

			for (size_t j = 0; j < estantes.size(); j++) {
				vector<Ejemplar>& ejemplares = estantes[j]->getEjemplares();

				for (size_t k = 0; k < ejemplares.size(); k++) {
					for (size_t l = 0; l < prestamos.size(); l++) {
						if (prestamos[l].getEjemplarPrestado() == &ejemplares[k]) {
							cout << "Libro: "
							     << ejemplares[k].getLibro()->getTitulo() << endl;
							cout << "Estudiante: "
							     << prestamos[l].getEstudiante()->getNombre() << endl;
						}
					}
				}
			}

			return;
		}
	}

	cout << "Biblioteca no encontrada.\n";
}

void registrarEstudiante(vector<Estudiante>& estudiantes) {
	string nombre;
	string codigo;

	cout << "Nombre del estudiante: ";
	cin.ignore();
	getline(cin, nombre);

	cout << "Codigo del estudiante: ";
	getline(cin, codigo);

	estudiantes.emplace_back(nombre, codigo);

	cout << "Estudiante registrado.\n";
}

Estudiante* buscarEstudiante(vector<Estudiante>& estudiantes, string codigo) {
	for (size_t i = 0; i < estudiantes.size(); i++) {
		if (estudiantes[i].getCodigo() == codigo) {
			return &estudiantes[i];
		}
	}

	return nullptr;
}

void listarPrestamosEstudiante(vector<Estudiante>& estudiantes,
                               vector<Prestamo>& prestamos) {
	string codigo;

	cout << "Codigo del estudiante: ";
	cin.ignore();
	getline(cin, codigo);

	Estudiante* estudiante = buscarEstudiante(estudiantes, codigo);

	if (estudiante == nullptr) {
		cout << "Estudiante no encontrado.\n";
		return;
	}

	cout << "Libros que tiene " << estudiante->getNombre()
	     << " en prestamo:" << endl;

	for (size_t i = 0; i < prestamos.size(); i++) {
		if (prestamos[i].getEstudiante() == estudiante) {
			cout << "- "
			     << prestamos[i].getEjemplarPrestado()->getLibro()->getTitulo()
			     << endl;
		}
	}
}
								 
void registrarEstante(vector<Estante*>& estantes) {
	string nombreEstante;
	cout << "--Nombre del estante: ";
	cin.ignore();
	getline(cin, nombreEstante);
	estantes.push_back(new Estante(nombreEstante));
	cout << " Estante registrado.\n";
}

void registrarEjemplar(vector<Libro>& libros, vector<Ejemplar>& ejemplares) {
	if (libros.empty()) {
		cout << "  Primero registra un libro.\n";
		return;
	}
	int idx;  // selecciona al libro de la lista
	
	
	int numeroEjemplar;
	
	cout << "Seleccione un libro de la lista:\n";
	for (size_t i = 0; i < libros.size(); i++)          // size_t es un tipo de dato sin signo, por eso se hace el cast a int para la comparación
		cout << i << ". " << libros[i].getTitulo() << "\n";
	
	cout << "Libro (índice): ";
	cin >> idx;
	cout << endl << "--Número de ejemplar: " ;
	cin >> numeroEjemplar;
	
	
	
	if (idx >= 0 && idx < (int)libros.size()) // Verifica que el índice sea válido
		ejemplares.emplace_back(&libros[idx], numeroEjemplar);
	else
		cout << "[X] Índice inválido.\n";
}


Ejemplar* buscarEjemplar(vector<Ejemplar>& ejemplares, int numero) {
	
	for (size_t i = 0; i < ejemplares.size(); i++) {
		
		if (ejemplares[i].getNumeroEjemplar() == numero) {
			return &ejemplares[i];
		}
	}
	
	return nullptr;
}
void registrarBiblioteca(vector<Biblioteca>& bibliotecas, vector<Estante*>& estantes) {
	
	string nombreBiblioteca;
	int idxEstante;
	cout << "Nombre de la biblioteca: ";
	cin.ignore();
	getline(cin, nombreBiblioteca);
	bibliotecas.emplace_back(nombreBiblioteca);
	
	if (estantes.empty()) {
		cout << "  No hay estantes que agregar.\n";
		return;
	}
	
	cout << "/n Agrege un estante\n";
	
	for (size_t i = 0; i < estantes.size(); i++) // Mostrar lista de estantes
		cout << i << ". " << estantes[i]->getNombreEstante() << "\n";
	cout << "Estante agregado: ";
	cin >> idxEstante;
	
	if (idxEstante >= 0 && idxEstante < (int)estantes.size()) // Verifica que el índice sea válido
		bibliotecas.back().agregarEstante(estantes[idxEstante]);
	else
		cout << " Índice inválido.\n";
}

void registrarPrestamo(vector<Estudiante>& estudiantes,
					   vector<Ejemplar>& ejemplares,
					   vector<Prestamo>& prestamos) {
	
	string codigo;
	int numeroEjemplar;
	string fecha;
	
	cout << "Codigo del estudiante: ";
	cin.ignore();
	getline(cin, codigo);
	
	Estudiante* estudiante = buscarEstudiante(estudiantes, codigo);
	
	if (estudiante == nullptr) {
		cout << "El estudiante no esta registrado.\n";
		return;
	}
	
	cout << "Numero del ejemplar: ";
	cin >> numeroEjemplar;
	
	Ejemplar* ejemplar = buscarEjemplar(ejemplares, numeroEjemplar);
	
	if (ejemplar == nullptr) {
		cout << "El ejemplar no esta registrado.\n";
		return;
	}
	
	cout << "Fecha del prestamo: ";
	cin.ignore();
	getline(cin, fecha);
	
	prestamos.emplace_back(fecha, estudiante, ejemplar);
	
	cout << "Prestamo registrado.\n";
}
void agregarEjemplarAEstante(vector<Estante*>& estantes, vector<Ejemplar>& ejemplares) {
	if (estantes.empty()) {
		cout << "  Primero registra un estante.\n";
		return;
	}
	if (ejemplares.empty()) {
		cout << "  Primero registra un ejemplar.\n";
		return;
	}
	cout << " Seleccione el estante:\n";
	int idxEstante, idxEjemplar;
	for (size_t i = 0; i < estantes.size(); i++) // Mostrar lista de estantes
		cout << i << ". " << estantes[i]->getNombreEstante() << "\n";
	cin >> idxEstante;
	
	cout << " Seleccione el ejemplar:\n";
	for (size_t i = 0; i < ejemplares.size(); i++) // Mostrar lista de ejemplares
		cout << i << ". " << ejemplares[i].getLibro()->getTitulo() << " (#" << ejemplares[i].getNumeroEjemplar() << ")\n"; // ejemplares[i].getLibro()->getTitulo() hace
	//cout << "Ejemplar (índice): ";
	cin >> idxEjemplar;
	
	if (idxEstante >= 0 && idxEstante < (int)estantes.size() &&
		idxEjemplar >= 0 && idxEjemplar < (int)ejemplares.size()) {// Verifica que los índices sean válidos
		
		estantes[idxEstante]->agregarEjemplar(ejemplares[idxEjemplar]);
		ejemplares[idxEjemplar].setAgregarEstante(estantes[idxEstante]->getNombreEstante());
		cout << " Ejemplar agregado al estante.\n";
	} else {
			cout << " Índice inválido.\n";
		}
}

void agregarEstanteABiblioteca(vector<Biblioteca>& bibliotecas, vector<Estante*>& estantes) {
	if (bibliotecas.empty()) {
		cout << "  Primero registra una biblioteca.\n";
		return;
	}
	if (estantes.empty()) {
		cout << "  Primero registra un estante.\n";
		return;
	}
	cout << " Agrege un estante a biblioteca\n";
	int idxBiblioteca, idxEstante;
	for (size_t i = 0; i < bibliotecas.size(); i++) // Mostrar lista de bibliotecas
		cout << i << ". " << bibliotecas[i].getNombreBiblioteca() << "\n";
	cout << "Biblioteca (índice): ";
	cin >> idxBiblioteca;
	
	for (size_t i = 0; i < estantes.size(); i++) // Mostrar lista de estantes
		cout << i << ". " << estantes[i]->getNombreEstante() << "\n";
	cout << "Estante a agregar a la biblioteca (índice): ";
	cin >> idxEstante;
	
	if (idxBiblioteca >= 0 && idxBiblioteca < (int)bibliotecas.size() &&
		idxEstante >= 0 && idxEstante < (int)estantes.size()) { // Verifica que los índices sean válidos
		
		bibliotecas[idxBiblioteca].agregarEstante(estantes[idxEstante]);
		cout << " Estante agregado a la biblioteca.\n";
	} else {
			cout << " Índice inválido.\n";
		}
}

void buscarAutor(vector<Autor>& autores) {
	if (autores.empty()) { // revisa si la lista esta vasia
		cout << "  No hay autores registrados.\n";
		return;
	}
	string nombre;
	cout << "Nombre del autor a buscar: ";
	cin.ignore();
	getline(cin, nombre);
	bool encontrado = false;
	for (size_t i = 0; i < autores.size(); i++) { // sizet_t es un tipo de dato sin signo, por eso se hace el cast a int para la comparación
		if (autores[i].getNombre() == nombre) {
			autores[i].printAutor();
			encontrado = true;
			break;
		}
	}
	if (!encontrado)
		cout << " Autor no encontrado.\n";
}
//idex
void buscarLibro(vector<Libro>& libros) {
	if (libros.empty()) {
		cout << "  No hay libros registrados.\n";
		return;
	}
	string titulo;
	cout << "Título del libro a buscar: ";
	cin.ignore();
	getline(cin, titulo);
	bool encontrado = false;
	for (size_t i = 0; i < libros.size(); i++) {
		if (libros[i].getTitulo() == titulo) {
			libros[i].printLibro();
			cout << "Estantes donde se encuentra el libro: " << endl;
			libros[i].getListaEstantes();
			encontrado = true;
			break;
		}
	}
	if (!encontrado)
		cout << " Libro no encontrado.\n";
}

void buscarEjemplar(vector<Ejemplar>& ejemplares) {
	if (ejemplares.empty()) {
		cout << "  No hay ejemplares registrados.\n";
		return;
	}
	int numeroEjemplar;
	cout << "Número de ejemplar a buscar: ";
	cin >> numeroEjemplar;
	bool encontrado = false;
	for (size_t i = 0; i < ejemplares.size(); i++) {
		if (ejemplares[i].getNumeroEjemplar() == numeroEjemplar) {
			ejemplares[i].printEjemplar();
			encontrado = true;
			break;
		}
	}
	if (!encontrado)
		cout << " Ejemplar no encontrado.\n";
}

void buscarEstante(vector<Estante*>& estantes) {
	if (estantes.empty()) {
		cout << "  No hay estantes registrados.\n";
		return;
	}
	string nombreEstante;
	cout << "Nombre del estante a buscar: ";
	cin.ignore();
	getline(cin, nombreEstante);
	bool encontrado = false;
	for (size_t i = 0; i < estantes.size(); i++) {
		if (estantes[i]->getNombreEstante() == nombreEstante) {
			cout << "Estante encontrado: " << estantes[i]->getNombreEstante() << endl;
			encontrado = true;
			break;
		}
	}
	if (!encontrado)
		cout << " Estante no encontrado.\n";
}

void MostrarEstantes(vector<Biblioteca>& bibliotecas) {
	if (bibliotecas.empty()) {
		cout << "  No hay bibliotecas registradas.\n";
		return;
	}
	
	int indexBiblioteca;
	cout << "Seleccione la biblioteca para mostrar sus estantes:\n";
	for (size_t i = 0; i < bibliotecas.size(); i++) {
		cout << i << ". " << bibliotecas[i].getNombreBiblioteca() << "\n";
	}
	cout << "Ingrese el número de la biblioteca: ";
	cin >> indexBiblioteca;
	
	if (static_cast<size_t>(indexBiblioteca) >= bibliotecas.size()) {
		cout << "[X]Índice inválido.\n";
		return;
	}
	bibliotecas[indexBiblioteca].mostrarEstantes();
}

void MostarLibros(vector<Biblioteca>& bibliotecas) {
	if (bibliotecas.empty()) {
		cout << "  No hay bibliotecas registradas.\n";
		return;
	}
	
	int indexBiblioteca;
	cout << "Seleccione la biblioteca para mostrar sus libros:\n";
	for (size_t i = 0; i < bibliotecas.size(); i++) {
		cout << i << ". " << bibliotecas[i].getNombreBiblioteca() << "\n";
	}
	cout << "Ingrese el número de la biblioteca: ";
	cin >> indexBiblioteca;
	
	if (static_cast<size_t>(indexBiblioteca) >= bibliotecas.size()) {
		cout << "[X]Índice inválido.\n";
		return;
	}
	bibliotecas[indexBiblioteca].listaDeLibros();
}

void menuRegistrar(vector<Autor>& autores, vector<Libro>& libros, vector<Ejemplar>& ejemplares, vector<Estante*>& estantes, vector<Biblioteca>& bibliotecas){
	int opcion;
	do {
		cout << "---------------------------------------------------------" << endl;
		cout << "Registrar objetos de la biblioteca:" << endl;
		
		cout << "1. Rejistar Autor" << endl
			<< "2. Registrar Libro" << endl
			<< "3. Registrar Ejemplar" << endl
			<< "4. Registrar Estante" << endl
			<< "5. Registrar Biblioteca" << endl
			<< "6. Agregar Ejemplar a Estante" << endl
			<< "7. Agregar Estante a Biblioteca" << endl
			<< "0. Salir\n> ";
		cin >> opcion;
		
		switch (opcion) {
		case 1: registrarAutor(autores); break;
		case 2: registrarLibro(autores, libros); break;
		case 3: registrarEjemplar(libros, ejemplares); break;
		case 4: registrarEstante(estantes); break;
		case 6: agregarEjemplarAEstante(estantes, ejemplares); break;
		case 5: registrarBiblioteca(bibliotecas, estantes); break;
		case 7: agregarEstanteABiblioteca(bibliotecas, estantes); break;
		
		//case 7: mostrarTodo(autores, libros, ejemplares, biblioteca); break;
		case 0: break;
		default: cout << "Opción inválida.\n";
		break;
		}
	} while (opcion != 0);
	
}
	
void menuBuscar(vector<Autor>& autores, vector<Libro>& libros, vector<Ejemplar>& ejemplares, vector<Estante*>& estantes, vector<Biblioteca>& bibliotecas){
	int opcion;
	do{
		cout << "---------------------------------------------------------" << endl;
		cout << "Buscar información de la biblioteca:" << endl;

		cout << "1. Buscar Autor" << endl
		     << "2. Buscar Libro" << endl
		     << "3. Buscar Ejemplar" << endl
		     << "4. Buscar Estante" << endl
		     << "5. Ver estantes de una biblioteca" << endl
		     << "6. Ver libros de una biblioteca" << endl
		     << "0. Salir\n> ";
		cin >> opcion;

		switch (opcion) {
		case 1: buscarAutor(autores); break;
		case 2: buscarLibro(libros); break;
		case 3: buscarEjemplar(ejemplares); break;
		case 4: buscarEstante(estantes); break;
		case 5: MostrarEstantes(bibliotecas); break;
		case 6: MostarLibros(bibliotecas); break;
		case 0: break;
		default:
			cout << "Opción inválida.\n";
			break;
		}
	} while (opcion != 0);
}

void menuPrestamos(vector<Estudiante>& estudiantes,
				  vector<Ejemplar>& ejemplares,
				  vector<Prestamo>& prestamos,
				  vector<Biblioteca>& bibliotecas) {
	int opcion;

	do {
		cout << "Gestion de prestamos:";
		cout << "\n1. Registrar estudiante";
		cout << "\n2. Registrar prestamo";
		cout << "\n3. Ver prestamos de una biblioteca";
		cout << "\n4. Ver libros en prestamo de un estudiante";
		cout << "\n0. Salir\n> ";

		cin >> opcion;

		switch (opcion) {
		case 1:
			registrarEstudiante(estudiantes);
			break;
		case 2:
			registrarPrestamo(estudiantes, ejemplares, prestamos);
			break;
		case 3:
			listarPrestamosBiblioteca(bibliotecas, prestamos);
			break;
		case 4:
			listarPrestamosEstudiante(estudiantes, prestamos);
			break;
		case 0:
			break;
		default:
			cout << "Opcion invalida.\n";
			break;
		}
	} while (opcion != 0);
}

int main() {
	vector<Autor> autores;
	vector<Libro> libros;
	vector<Ejemplar> ejemplares;
	vector<Estante*> estantes;
	vector<Biblioteca> bibliotecas;
	vector<Estudiante> estudiantes;
	vector<Prestamo> prestamos;

	int opcion;
	do {
		cout << "\n=========================================\n";
		cout << "        SISTEMA DE BIBLIOTECA\n";
		cout << "=========================================\n";
		cout << "1. Registrar\n";
		cout << "2. Buscar\n";
		cout << "3. Gestión prestamos\n";
		cout << "0. Salir\n";
		cout << "> ";
		cin >> opcion;

		switch (opcion) {
		case 1:
			menuRegistrar(autores, libros, ejemplares, estantes, bibliotecas);
			break;
		case 2:
			menuBuscar(autores, libros, ejemplares, estantes, bibliotecas);
			break;
		case 3:
			menuPrestamos(estudiantes, ejemplares, prestamos, bibliotecas);
			break;
		case 0:
			cout << "fin \n";
			break;
		default:
			cout << " Opción inválida.\n";
			break;
		}
	} while (opcion != 0);

	// Liberar memoria de los estantes creados con new.
	for (auto e : estantes) {
		delete e;
	}

	return 0;
}