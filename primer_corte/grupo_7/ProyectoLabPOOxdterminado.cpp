#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;
//declaracion de metodos que no se donde se colocan, ayudame ivan
void registrarAutor(){}
void registrarLibro(){}
void registroEstanteria(){}
void registroDeEjemplar(){}
void registrarBibliotecaYAsigEstantes(){}
void conteoInventario(){}
void actualizarInventario(){}
//


class Libro; //definida antes de tiempo para que la clase autor sepa de su existencia
class Autor{
private:
	string nombre;
	string nacionalidad;
	string fechaNacimiento;
	string fechaMuerte;
	int librosPublicados;
	
public:
	//constructores
	Autor(string nombre, string nacionalidad, string fechaNacimiento, string fechaMuerte,int librosPublicados)
	{
		this->nombre = nombre;
		this->nacionalidad = nacionalidad;
		this->fechaNacimiento = fechaNacimiento;
		this->fechaMuerte = fechaMuerte;
	}
	// Setters
	void setNombre(string nombre) { this->nombre = nombre; }
	void setNacionalidad(string nacionalidad) { this->nacionalidad = nacionalidad; }
	void setFechaNacimiento(string fechaNacimiento) { this->fechaNacimiento = fechaNacimiento; }
	void setFechaMuerte(string fechaMuerte) { this->fechaMuerte = fechaMuerte; }
	void setLibrosPublicados(int librosPublicados) { this->librosPublicados= librosPublicados; }
	// Getters
	string getNombre() { return this->nombre; }
	string getNacionalidad() { return this->nacionalidad; }
	string getFechaNacimiento() { return this->fechaNacimiento; }
	string getFechaMuerte() { return this->fechaMuerte; }
	int getLibrosPublicados() {return this->librosPublicados; }
	
	void mostrarInfo()
	{
		cout << "Informacion del autor" << endl;
		cout << "Nombre: " << this->nombre << endl;
		cout << "Nacionalidad: " << this->nacionalidad << endl;
		cout << "Fecha de nacimiento: " << this->fechaNacimiento << endl;
		if (this->fechaMuerte.length() > 0)
		{
			cout << "Fecha de muerte: " << this->fechaMuerte << endl;
		}
		cout << "Libros publicados: " << this->librosPublicados << endl;
	}
};

class Libro {
	private:
		string title;
		Autor *author;
		int releaseYear;
		string isbn;
	public:
	// Constructor
		Libro(string title, Autor *author, int releaseYear, string isbn) {
			this->title = title;
			this->author = author;
			this->releaseYear = releaseYear;
			this->isbn = isbn;
		}
	//getters
		string getTitle() { return this->title; }
		Autor *getAuthor() { return this->author; }
		int getReleaseYear() { return this->releaseYear; }
		string getISBN(){ return this->isbn; }
	//setters
		void setTitle(string title) { this->title = title; }
		void setReleaseYear(int releaseYear) { this->releaseYear = releaseYear; }
		void setISBN(string isbn){ this->isbn = isbn; }
		void mostrarInfoL(){
			cout << "Informacion del libro:" << endl;
			cout << "Titulo: " << this->title << endl;
			this->author->mostrarInfo();
			cout << "AÒo de publicacion: " << this->releaseYear << endl;
			cout << "ISBN: " << this->isbn << endl;
		};
	};

class Stock{
	private:
		Libro *libro;
		int cantidad;
		bool disponible;
	public:
		Stock(Libro *libro, int cant, bool disp)
	{
		this->libro = libro;
		this->cantidad = cant;
		this->disponible= disp;
	}

	//setters
	void setLibro(Libro *libro) { this->libro = libro; }
	void setCantidad(int cant) {
		if (cant < 0) {
			this->cantidad = 0;
			cout << "El stock no puede ser negativo" << endl; 
		}else{ this->cantidad = cant;}}
	void setDisponibilidad(bool disp){this->disponible = disp; }

	//getters
	Libro *getLibro() { return this->libro; }
	int getCantidad() { return this->cantidad; }
	bool getDisponibilidad(){ return this->disponible; }
};

class Estante{
	private:
		string nombre;
		vector<Stock*> ejemplares;
	public:
		Estante(string nombre)
	{
		this->nombre = nombre;
	}

	//setters
	void setNombre(string nombre) { this->nombre = nombre; }

	//getters
	string getNombre() { return this->nombre; }
	vector<Stock*> getEjemplares() { return this->ejemplares; }
	
	//Metodos
	void agregarLibro(Stock *ejemplar){this->ejemplares.push_back(ejemplar);}
	int buscarLibro(string title)
	{
		int index = -1;
		for (long long unsigned int i = 0; i < ejemplares.size(); i++)
		{
			Stock *tmp = this->ejemplares[i];
			if (tmp->getLibro()->getTitle() == title)
			{
				index = i;
				break;
			}
		}
		return index;
	}

	void imprimirInformacionEstante(){
		cout <<"================================" << endl;
		cout << "Nombre: " << nombre << endl;
		for (long long unsigned int i = 0; i<ejemplares.size(); i++) {
        cout << "Libro: " << ejemplares[i]->getLibro()->getTitle()<< endl;
		cout << "N∞ de ejemplares: " << ejemplares[i]->getCantidad()<<endl;
    }
	}
};

class Biblioteca{
private:
	string nombre;
	vector<Estante*> estantes;
	
public:
	Biblioteca(string nombre){this->nombre = nombre;}
	
	void setNombre(string nombre) { this->nombre = nombre; }
	void setEstantes(vector<Estante*> estantes) { this->estantes = estantes; }
	string getNombre() { return this->nombre; }
	vector<Estante*> getEstantes() { return this->estantes; }

	void agregarEstante(Estante *estante){this->estantes.push_back(estante);}
	int buscarEstante(string nombre)
	{
		int index = -1;
		for (long long unsigned int i=0; i<this->estantes.size(); i++)
		{
			Estante *tmp = this->estantes[i];
			if (tmp->getNombre() == nombre)
			{
				index = i;
				break;
			}
		}
		return index;
	}

	void disponibilidadLibro(string nombre, string title){
		int posicionEstante,posicionLibro;
		posicionEstante=buscarEstante(nombre);
		if (posicionEstante != -1){
			Estante* tmp= this->estantes[posicionEstante];
			posicionLibro=tmp->buscarLibro(title);
			if (posicionLibro !=-1){
				bool tmp2=tmp->getEjemplares()[posicionLibro]->getDisponibilidad();
				if(tmp2==true){cout <<"El Libro "<< title << " se encuentra disponible en la estanteria "<< nombre <<endl;}
			}else{cout <<"El libro" << title << "No se encuentra disponible" <<endl; }
		}else{cout <<"El estante no existe, o ha sido removido"<<endl;}
	}

	void inventarioBiblioteca(){
		cout << "===Inventario Biblioteca " << getNombre() << "===" <<endl;
		for(long long unsigned int i=0; i < this->estantes.size();i++){
			cout << "Estante: " << i+1 <<endl;
			estantes[i]->imprimirInformacionEstante();
		}
	}
};

class Estudiante{
private:
	string codigo;
	string nombre;
	
public:
	Estudiante(string codigo, string nombre){
		this->codigo = codigo;
		this->nombre = nombre;
	}
	
	string getCodigo(){
		return this->codigo;
	}
	string getNombre(){
		return this->nombre;
	}
	void mostrarInfo(){
		cout << "Codigo: " << codigo << endl;
		cout << "Nombre: " << nombre << endl;
	}
};

class Prestamo{
private:
	Stock *ejemplar;
	Estudiante *estudiante;
	Biblioteca *biblioteca;
	bool activo;
	
public:
	Prestamo(Stock *ejemplar, Estudiante *estudiante, Biblioteca *biblioteca){
		this->ejemplar = ejemplar;
		this->estudiante = estudiante;
		this->biblioteca = biblioteca;
		this->activo = true;
	}
	
	Stock *getEjemplar(){
		return this->ejemplar;
	}
	Estudiante *getEstudiante(){
			return this->estudiante;}
	Biblioteca *getBiblioteca(){
		return this->biblioteca;
	}
	bool getActivo(){
		return this->activo;
	}
	void setActivo(bool activo){
		this->activo = activo;}
};
class Universidad{
	private:
    vector<Autor*> autores;
    vector<Libro*> libros;
    vector<Biblioteca*> bibliotecas;
	vector<Estudiante*> estudiantes;
	vector<Prestamo*> prestamos;
public:

	vector<Autor*> getAutores() { return this->autores; }
	vector<Libro*> getLibros() { return this->libros; }
	vector<Biblioteca*> getBibliotecas() { return this->bibliotecas; }
	Autor* buscarAutor(string nombre) {
        for (int i=0;i<autores.size();i++){ 
			if (autores[i]->getNombre() == nombre) return autores[i];
        }
        return nullptr;
    }
	void agregarAutores(Autor* autor) {autores.push_back(autor);}
	void agregarLibros(string tit, string nombreAut, int anio, string isbn) {
		Autor* aut = buscarAutor(nombreAut);
    libros.push_back(new Libro(tit, aut, anio, isbn));
	};
	void agregarBibliotecas(Biblioteca* biblioteca) {bibliotecas.push_back(biblioteca);}

    // Procesos del Menu
void menuBiblioteca(){
    int opc;
    string nombre, nombreEstante;
    Biblioteca* biblioteca = nullptr;
    do{
        cout << "========Registro de Biblioteca========" << endl;
        cout << "Seleccione una opcion: " << endl;
        cout << "1. Ingresar nombre de la biblioteca" << endl;
        cout << "2. Agregar un estante a la biblioteca" << endl;
        cout << "3. Ver inventario de la biblioteca" << endl;
        cout << "0. Volver al menu principal" << endl;
        cout << "Ingrese su opcion: ";
        cin >> opc;
        switch(opc){
        case 1:
            cout << "Nombre de la biblioteca: ";
            cin >> nombre;
            biblioteca = new Biblioteca(nombre);
            break;
        case 2:
            if (biblioteca == nullptr){
                cout << "Primero debe crear la biblioteca." << endl;
                break;
            }
            cout << "Nombre del estante: ";
            cin >> nombreEstante;
            biblioteca->agregarEstante(new Estante(nombreEstante));
            cout << "Estante agregado correctamente." << endl;
            break;
        case 3:
            if (biblioteca == nullptr){
                cout << "No hay biblioteca creada." << endl;
            } else {
                biblioteca->inventarioBiblioteca();
            }
            break;
        case 0:
            cout << "Volviendo al menu..." << endl;
            break;
        default:
            cout << "Opcion invalida" << endl;
            break;
        }
    }while(opc != 0);
    if (biblioteca != nullptr){
        agregarBibliotecas(biblioteca);
    }
}

void menuAutor(){
	int opc,cant=0;
	string nom="Anonimo",nac="",fn="",ff="";
	do{
		cout << "========Registro de Autor========" << endl;
		cout << "Seleccione una opcion: " << endl;
		cout << "1. Ingresar nombre del autor: " << endl;
		cout << "2. Ingresar nacionalidad del autor: " << endl;
		cout << "3. Ingresar fecha de nacimiento del autor: " << endl;
		cout << "4. Ingresar fecha de muerte del autor: " << endl;
		cout << "5. Ingresar libros publicados por el autor: " << endl;
		cout << "0. Volver al menu principal" << endl;
		cout << "Ingrese su opcion: ";
		cin >> opc;
		switch (opc){
		case 1:
			cout <<"Nombre: "; cin>> nom;
			break;
		case 2:
			cout <<"Nacionalidad: "; cin>> nac;
			break;
		case 3:
			cout <<"Fecha de nacimiento: "; cin>> fn;
			break;
		case 4:
			cout <<"Fecha de fallecimiento: "; cin>> ff;
			break;
		case 5:
			cout <<"N de libros: "; cin>> cant;
			break;
		case 0:
			cout <<"Volviendo al menu..."<<endl;
			break;
		default:
			cout <<"Opcion invalida"<<endl;
			break;
		};
	}while(opc!=0);
		Autor* autor= new Autor(nom,nac,fn,ff,cant);
		agregarAutores(autor);
}

void menuLibro(){
		int opc,n,year;
		string tit,isbn,nom;
		Autor*autor;
		do{
			cout << "========Registro de Libro========" << endl;
			cout << "Seleccione una opcion: " << endl;
			cout << "1. Ingresar titulo del libro: " << endl;
			cout << "2. Ingresar autor del libro: " << endl;
			cout << "3. Ingresar anio de publicacion del libro: " << endl;
			cout << "4. Ingresar ISBN del libro: " << endl;
			cout << "5. Ingresar cantidad de ejemplares" << endl;
			cout << "0. Salir" << endl;
			cout << "Ingrese su opcion: ";
			cin >> opc;

			switch (opc){
			case 1:
				cout <<"Titulo: "; cin>> tit;
				break;
			case 2:
				cout <<"Autor: "; cin>> nom;

				break;
			case 3:
				cout <<"Anio publicacion: "; cin>> year;
				break;
			case 4:
				cout <<"ISBN: "; cin>> isbn;
				break;
			case 5:
				cout <<"N de ejemplares: "; cin>> n;
				break;
			case 0:
				cout <<"Volviendo al menu..."<<endl;
				break;
			default:
				cout <<"Opcion invalida"<<endl;
				break;
			};
		}while (opc!=0);
		agregarLibros(tit,nom,year,isbn);
	}

void menuEstante(){
	int opc, cantidad = 0;
    string nombre = "Estante", titulo = "";
    Estante* estante = nullptr;
    do{
        cout << "========Registro de Estanteria========" << endl;
        cout << "Seleccione una opcion: " << endl;
        cout << "1. Ingresar nombre del estante" << endl;
        cout << "2. Ingresar titulo del libro" << endl;
        cout << "3. Ingresar cantidad de ejemplares" << endl;
        cout << "4. Agregar libro al estante" << endl;
        cout << "0. Volver al menu principal" << endl;
        cout << "Ingrese su opcion: ";
        cin >> opc;

        switch(opc){
        case 1:
            cout << "Nombre del estante: ";cin >> nombre;
            break;
        case 2:
            cout << "Titulo del libro: "; cin >> titulo;
            break;
        case 3:
            cout << "Cantidad de ejemplares: ";cin >> cantidad;
            break;
        case 4:
            if (nombre == "" || titulo == ""){
                cout << "Debes ingresar primero el nombre del estante y el titulo del libro." << endl;
            } else {
                if (estante == nullptr){
                    estante = new Estante(nombre);
                }
                Libro* libro = new Libro(titulo, nullptr, 0, "SIN_ISBN");
                Stock* ejemplar = new Stock(libro, cantidad, true);
                estante->agregarLibro(ejemplar);
                cout << "Libro agregado al estante: " << nombre << endl;
            }
            break;
        case 0:
            cout << "Volviendo al menu principal..." << endl;
            break;
        default:
            cout << "Opcion invalida" << endl;
            break;
        }
    }while(opc != 0);
	}
	void menuPrestamo(){
		int seleccionBiblioteca;
		string codigoEstudiante;
		string tituloLibro;
		
		cout << " Registro de Prestamo " << endl;
		cout << "Codigo del estudiante: ";
		cin >> codigoEstudiante;
		Estudiante* estudiante = buscarEstudiante(codigoEstudiante);
		if(estudiante == nullptr){
			cout << "Estudiante no encontrado." << endl;
			return;
		}
		if(bibliotecas.size() == 0){
			cout << "No hay bibliotecas registradas." << endl;
			return;
		}
		cout << "Bibliotecas disponibles:" << endl;
		for(int i = 0; i < bibliotecas.size(); i++){
			cout << i + 1 << ". " << bibliotecas[i]->getNombre() << endl;
		}
		cout << "Seleccione una biblioteca: ";
		cin >> seleccionBiblioteca;
		if(seleccionBiblioteca < 1 || seleccionBiblioteca > bibliotecas.size()){
			cout << "Biblioteca invalida." << endl;
			return;
		}
		Biblioteca* bibliotecaSeleccionada = bibliotecas[seleccionBiblioteca - 1];
		cout << "Titulo del libro: ";
		cin >> tituloLibro;
		vector<Estante*> estantes = bibliotecaSeleccionada->getEstantes();
		for(int i = 0; i < estantes.size(); i++){
			vector<Stock*> ejemplares = estantes[i]->getEjemplares();
			for(int j = 0; j < ejemplares.size(); j++){
				Stock* stock = ejemplares[j];
				if(stock->getLibro()->getTitle() == tituloLibro){
					registrarPrestamo(codigoEstudiante, bibliotecaSeleccionada, stock);
					return;
				}
			}
		}
		cout << "El libro no se encuentra en esta biblioteca." << endl;
	}
int menuPrincipal(){
	int opc;
		do{
			system("cls");
			cout << "========SISTEMA UNIFICADO DE CONTROL DE BIBLIOTECAS=======" << endl;
			cout << "BIENVENIDO"<< endl;
			cout << "Seleccione una opcion: "<< endl;
			cout << "1. Registrar autor" << endl;
			cout << "2. Registrar libro."<< endl;
			cout << "3. Registrar estanteria."<< endl;
			cout << "4. Registro de una biblioteca y asignacion de una o mas estanterias a dicha biblioteca." << endl;
			cout << "5. Registrar estudiante" << endl;
			cout << "6. Registrar prestamo" << endl;
			cout << "7. Ver prestamos de una biblioteca" << endl;
			cout << "0. Cerrar sistema." << endl;
			cout << "Ingrese su opcion: ";
			cin >> opc;

			switch(opc){
			case 1:
				menuAutor();
				break;
			case 2:
				menuLibro();
				break;
			case 3:
				menuEstante();
				break;
			case 4:
				menuBiblioteca();
				break;
			case 5:
				menuEstudiante();
				break;
			case 6:
				menuPrestamo();
			case 7:
				if(bibliotecas.size() == 0){
					cout << "No hay bibliotecas registradas." << endl;
					break;
				}
				cout << " Prestamos de Biblioteca " << endl;
				for(int i = 0; i < bibliotecas.size(); i++){
					cout << i + 1 << ". " << bibliotecas[i]->getNombre() << endl;
				}
				int seleccion;
				cout << "Seleccione una biblioteca: ";
				cin >> seleccion;
				if(seleccion < 1 || seleccion > bibliotecas.size()){
					cout << "Biblioteca invalida." << endl;
				}
				else{
					Biblioteca* bibliotecaSeleccionada = bibliotecas[seleccion - 1];
					listarPrestamosBiblioteca(bibliotecaSeleccionada);
				}
				break;
			case 0:
				cout <<"Bye Bye"<<endl;
				break;
			default:
				cout <<"Opcion invalida"<< endl;
				break;
			}
		}while (opc !=0);
		return opc;
	}
	void agregarEstudiante(Estudiante *estudiante){
		estudiantes.push_back(estudiante);
	}
	
	Estudiante* buscarEstudiante(string codigo){
		for(int i=0;i<estudiantes.size();i++){
			if(estudiantes[i]->getCodigo()==codigo){
				return estudiantes[i];
			}
		}
		return nullptr;
	}
	void agregarPrestamo(Prestamo *prestamo){
		prestamos.push_back(prestamo);
	}
	
	void listarPrestamosBiblioteca(Biblioteca *biblioteca){
		cout << "Prestamos de la biblioteca " << biblioteca->getNombre() << endl;
		cout << "==========================" << endl;
		bool encontrado = false;
		for(int i=0;i<prestamos.size();i++){
			Prestamo *tmp = prestamos[i];
			if(tmp->getActivo() && tmp->getBiblioteca()==biblioteca){
				encontrado = true;
				cout << "Libro: " << tmp->getEjemplar()->getLibro()->getTitle() << endl;
				cout << "Estudiante: " << tmp->getEstudiante()->getNombre() << endl;
			}
		}
	if(!encontrado){
		cout << "No existen prestamos registrados" << endl;
	}
	}
	void menuEstudiante(){
		int opc;
		string codigo="";
		string nombre="";
		do{
			cout << " REGISTRO ESTUDIANTE " << endl;
			cout << "1. Ingresar codigo" << endl;
			cout << "2. Ingresar nombre" << endl;
			cout << "0. Guardar estudiante" << endl;
			cin >> opc;
			switch(opc){
				case 1:
					cout << "Codigo: ";
					cin >> codigo;
					break;
				case 2:
					cout << "Nombre: ";
					cin >> nombre;
					break;
				case 0:
					break;
				default:
					cout << "Opcion invalida" << endl;
			}
		}while(opc!=0);
		Estudiante *nuevo = new Estudiante(codigo,nombre);
		agregarEstudiante(nuevo);
	}
	void registrarPrestamo(string codigoEstudiante, Biblioteca *biblioteca, Stock *ejemplar){
		Estudiante *est = buscarEstudiante(codigoEstudiante);
		if(est==nullptr){
			cout << "Estudiante no encontrado" << endl;
			return;
		}
		if(ejemplar->getCantidad()<=0){
			cout << "No hay ejemplares disponibles" << endl;
				return;
			}
		ejemplar->setCantidad(ejemplar->getCantidad()-1);
			Prestamo *nuevo = new Prestamo(ejemplar, est, biblioteca);
			agregarPrestamo(nuevo);
			cout << "Prestamo registrado" << endl;
		}
};

int main() {
	Universidad unicauca;
	int opc;
	unicauca.menuPrincipal();
	return 0;
}
