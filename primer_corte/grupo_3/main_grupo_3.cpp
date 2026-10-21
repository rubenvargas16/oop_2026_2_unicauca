#include <iostream>
#include <string>
#include <limits>
#include <vector>

using namespace std;

class Autor{
    private:
    string nombre;
    string identificacion;
    string nacionalidad;
    
    public:
    Autor(string nombre, string identificacion, string nacionalidad){
    this->nombre = nombre;
    this->identificacion = identificacion;
    this->nacionalidad = nacionalidad;
  }
  
  void setNombre(string nombre) { this->nombre = nombre; }
  void setIdentificacion(string identificacion) { this->identificacion = identificacion; }
  void setNacionalidad(string nacionalidad) { this->nacionalidad = nacionalidad; }

  string getNombre() const { return this->nombre; }
  string getIdentificacion() const { return this->identificacion; }
  string getNacionalidad() const { return this->nacionalidad; }
};

class Libro{
    private:
    string titulo;
    Autor* autor;
    int releaseYear;
    string isbn;
    
    public:

  Libro(string titulo, Autor* autor, int releaseYear, string isbn){
    this->titulo = titulo;
    this->autor = autor;
    this->releaseYear = releaseYear;
    this->isbn = isbn;
  }
  
  void setTitulo(string titulo) { this->titulo = titulo; }
  void setAutor(Autor* autor) { this->autor = autor; }
  void setReleaseYear(int releaseYear) { this->releaseYear = releaseYear; }
  void setISBN(string isbn) { this->isbn = isbn; }
  
  string getTitulo() const { return this->titulo; }
  Autor* getAutor() const { return this->autor; }
  int getReleaseYear() const { return this->releaseYear; }
  string getISBN() const { return this->isbn; }
};

class Ejemplar {
    private:
    Libro* libro;   
    int stock; 
    
    public:
    Ejemplar(Libro* libro, int stock) {
        this->libro = libro;
        this->stock = stock;
    }

    void setLibro(Libro* libro) { this->libro = libro; }
    void setStock(int stock) { this->stock = stock; }

    Libro* getLibro() const { return this->libro; }
    int getStock() const { return this->stock; }
};

class Estanteria {
    private:
    string id;
    vector<Ejemplar*> ejemplares; 
    
    public:
    Estanteria(string id) {
        this->id = id;
    }

    void setId(string id) { this->id = id; }
    
    string getId() const { return this->id; }
    const vector<Ejemplar*>& getEjemplares() const { return this->ejemplares; } //get de una collection.
    // el & porque no se quieren copias innecesarias (referencia) 
    //y el const para que no se modifique lo que tiene la lista, ya que la pasamos por referencia.
    
    //función de agregación de la colección.
    void agregarEjemplar (Ejemplar* ejemplar){
        this->ejemplares.push_back(ejemplar);
    }
};

class Biblioteca {
    private:
    string nombre;
    vector<Estanteria*> estanterias;
    
    public:
    Biblioteca(string nombre) {
        this->nombre = nombre;
    }

    void setNombre(string nombre) { this->nombre = nombre; }
    
    string getNombre() const { return this->nombre; }
    const vector<Estanteria*>& getEstanterias() const { return this->estanterias; }

    //función de agregación de la colección.
    void agregarEstanteria(Estanteria* estanteria) {
        this->estanterias.push_back(estanteria);
    }
};

class Estudiante {
    private:
    string nombre;
    string codigo;
    
    public:
    Estudiante(string nombre, string codigo) {
        this->nombre = nombre;
        this->codigo = codigo;
    }

    void setNombre(string nombre) { this->nombre = nombre; }
    void setCodigo(string codigo) { this->codigo = codigo; }

    string getNombre() const { return this->nombre; }
    string getCodigo() const { return this->codigo; }
};
  
class Prestamo {
    private:
    Estudiante* estudianteP; 
    Ejemplar* ejemplarP;     
    
    public:
    Prestamo(Estudiante* estudianteP, Ejemplar* ejemplarP) {
        this->estudianteP = estudianteP;
        this->ejemplarP = ejemplarP;
    }

    void setEstudianteP(Estudiante* estudianteP) { this->estudianteP = estudianteP; }
    void setEjemplarP(Ejemplar* ejemplarP) { this->ejemplarP = ejemplarP; }

    Estudiante* getEstudianteP() const { return this->estudianteP; }
    Ejemplar* getEjemplarP() const { return this->ejemplarP; }
};

class SistemaGestion{
    private:
    vector<Autor*> autores;
    vector<Libro*> libros;
    vector<Estanteria*> estanterias;
    vector<Biblioteca*> bibliotecas;
    vector<Estudiante*> estudiantes;
    vector<Prestamo*> prestamos;
    
    public:

    SistemaGestion() {}
    
    void registrarAutor() {
        string nombre, id, nacionalidad;
        cout <<endl<< "--- Registrar Nuevo Autor ---"<<endl;
        cout << "Nombre: "; cin.ignore(); getline(cin, nombre); //el cin.ignore() está ahí para borrar el ENTER del búfer.
        //el getline(cin, variable) sirve para que lea toda la entrada con espacios incluidos y no salte la linea ante un ESPACIO.
        cout << "Identificacion: "; cin >> id;
        cout << "Nacionalidad: "; cin.ignore(); getline(cin, nacionalidad);
        
        for (int i = 0; i < autores.size(); i++){
            if (autores[i]->getIdentificacion() == id){
                cout << "El autor ya está registrado." << endl;
                return;
            }
        }
        
        
        autores.push_back(new Autor(nombre, id, nacionalidad));
        cout<< "Nuevo autor registrado con exito."<<endl;
        }
    
    void registrarLibro() {
        string titulo, isbn, idAutor;
        int releaseYear;
        
        cout <<endl<< "--- Registrar Nuevo Libro ---"<<endl;
        cout << "Título: "; cin.ignore(); getline(cin, titulo); 
        cout << "ISBN: "; cin >> isbn;
        cout << "Identificación del autor: "; cin >> idAutor;
        cout << "Año de publicación: "; cin >> releaseYear;
        
        Autor* autorExistente = nullptr;
        for (int i=0; i<autores.size(); i++){
            if (autores[i]->getIdentificacion()==idAutor){
                autorExistente=autores[i];
                break;
            }
        }
        
        if (autorExistente==nullptr){
            cout << "El autor no está registrado. Primero registre al autor: " << endl;
            return;
        }
        
        for (int i=0 ; i<libros.size(); i++){
            if (libros[i]->getISBN()==isbn){
                cout << "El libro ya fue registrado con ese ISBN." << endl;
                return;
            }
        }
        libros.push_back(new Libro(titulo, autorExistente, releaseYear, isbn));
        cout<< "Nuevo libro registrado con exito."<<endl;
    }
    
    void registrarEstanteria() {
        string idEstanteria;
        cout <<endl<< "--- Registrar Nuevo Estantería ---"<<endl;
        cout << "Código de la estantería: "; cin.ignore(); getline(cin, idEstanteria); 
        
        for (int i = 0; i<estanterias.size(); i++){
            if (estanterias[i]->getId()==idEstanteria){
                cout<<"Ese código de estantería ya está registrado."<<endl;
                return;
            }
        }
        
        estanterias.push_back(new Estanteria(idEstanteria));
        cout<< "Nueva estantería registrada con exito."<<endl;
    }
    
    void registrarEjemplar() {
        string isbn, idEstanteria;
        int stockInicial;
        
        cout <<endl<< "--- Registrar Nuevo Ejemplar ---"<<endl;
        cout << "ISBN: "; cin>>isbn;
        
        Libro* libroExistente = nullptr;
        for (int i = 0; i < libros.size(); i++){
            if (libros[i]->getISBN() == isbn){
                libroExistente = libros[i];
                break;
            }
        }
        
        if (libroExistente==nullptr){
            cout << "El libro no está registrado. Primero registre el libro: " << endl;
            return;
        }
        
        cout << "Ingrese el ID de la estantería: "; cin >> idEstanteria;
        
        Estanteria* estanteriaExistente = nullptr;
        for (int i=0; i<estanterias.size(); i++){
            if (estanterias[i]->getId()==idEstanteria){
                estanteriaExistente=estanterias[i];
                break;
            }
        }
        
        if (estanteriaExistente==nullptr){
            cout << "La estantería no está registrada. Primero registre la estantería: " << endl;
            return;
        }
        
        cout << "Cantidad de ejemplares (Stock): "; cin >> stockInicial;
        
        Ejemplar* nuevoEjemplar = new Ejemplar(libroExistente,stockInicial);
        estanteriaExistente->agregarEjemplar(nuevoEjemplar);     
        
        cout<< "Nuevo ejemplar registrado con exito, en la estantería "<<idEstanteria<<endl;
    }
    
        void registrarBiblioteca() {
        string nombreB, idEstanteria;
        int cantEstanterias;
        
        cout << endl << "--- Registrar Biblioteca ---"<<endl;
        cout << "Nombre de la Biblioteca: "; cin.ignore(); getline(cin, nombreB);
        
        Biblioteca* nuevaBiblioteca = new Biblioteca(nombreB);
        
        cout << "¿Cuantas estanterias ya existentes desea asignarle?: "; cin >> cantEstanterias;
        
        for (int i = 0; i < cantEstanterias; i++) {
            cout << "Ingrese el ID de la estanteria [" << i + 1 << "]: "; cin >> idEstanteria;
         
            Estanteria* estEncontrada = nullptr;
            for (int j = 0; j < estanterias.size(); j++) {
                if (estanterias[j]->getId() == idEstanteria) {
                    estEncontrada = estanterias[j];
                    break;
                }
            }
            
            if (estEncontrada != nullptr) {
                nuevaBiblioteca->agregarEstanteria(estEncontrada);
                cout << "Etanteria " << idEstanteria << " asignada."<<endl;
            } else {
                cout << "Error: La estanteria no existe. No se pudo asignar."<<endl;
            }
        }
        
        bibliotecas.push_back(nuevaBiblioteca);
        cout << "Biblioteca '" << nombreB << "' registrada con exito."<<endl;
    }
    
    void consultarDisponibilidad() {
        string tituloBuscar;
        cout <<endl<< "--- Consultar Disponibilidad por Titulo ---"<<endl;
        cout << "Ingrese el titulo del libro a buscar: "; cin.ignore(); getline(cin, tituloBuscar);
        
        int totalUnidades = 0;
        bool encontrado = false;
        
        cout <<endl<< "Resultados de busqueda:"<<endl;
        for (int i = 0; i < bibliotecas.size(); i++) {
            Biblioteca* bib = bibliotecas[i];
   
            for (int j = 0; j < bib->getEstanterias().size(); j++) {
                Estanteria* est = bib->getEstanterias()[j];
                
                for (int k = 0; k < est->getEjemplares().size(); k++) {
                    Ejemplar* ej = est->getEjemplares()[k];
               
                    if (ej->getLibro()->getTitulo() == tituloBuscar) {
                        cout << "- Biblioteca: " << bib->getNombre() 
                             << "  -Estanteria: " << est->getId() 
                             << "  -Stock disponible: " << ej->getStock() << endl;
                        totalUnidades += ej->getStock();
                        encontrado = true;
                    }
                }
            }
        }
        
        if (encontrado) {
            cout << "Total de unidades físicas encontradas en el sistema: " << totalUnidades << endl;
        } else {
            cout << "No se encontraron ejemplares físicos de un libro con ese titulo."<<endl;
        }
    }

    void listarInventario() {
        string nombreB;
        cout <<endl <<"--- Listar Inventario de una Biblioteca ---"<<endl;
        cout << "Ingrese el nombre exacto de la biblioteca: "; cin.ignore(); getline(cin, nombreB);
        
        Biblioteca* bibEncontrada = nullptr;
        for (int i = 0; i < bibliotecas.size(); i++) {
            if (bibliotecas[i]->getNombre() == nombreB) {
                bibEncontrada = bibliotecas[i];
                break;
            }
        }
        
        if (bibEncontrada == nullptr) {
            cout << "La biblioteca especificada no existe."<<endl;
            return;
        }
        
        cout <<endl<< "--- Inventario de " << bibEncontrada->getNombre() << endl;
        for (int j = 0; j < bibEncontrada->getEstanterias().size(); j++) {
            Estanteria* est = bibEncontrada->getEstanterias()[j];
            cout << "Estanteria ID: " << est->getId() << endl;
            
            if (est->getEjemplares().size() == 0) {
                cout << "  (Estanteria vacia)"<<endl;
            }
            
            for (int k = 0; k < est->getEjemplares().size(); k++) {
                Ejemplar* ej = est->getEjemplares()[k];
                cout << "  - Libro: " << ej->getLibro()->getTitulo() 
                     << " [ISBN: " << ej->getLibro()->getISBN() << "]"
                     << " | Stock: " << ej->getStock() << endl;
            }
        }
    }

    void conteoTotalInventario() {
        string nombreB;
        cout <<endl<< "--- Conteo Total de Inventario ---"<<endl;
        cout << "Ingrese el nombre de la biblioteca: "; cin.ignore(); getline(cin, nombreB);
        
        Biblioteca* bibEncontrada = nullptr;
        for (int i = 0; i < bibliotecas.size(); i++) {
            if (bibliotecas[i]->getNombre() == nombreB) {
                bibEncontrada = bibliotecas[i];
                break;
            }
        }
        
        if (bibEncontrada == nullptr) {
            cout << "La biblioteca especificada no existe."<<endl;
            return;
        }
        
        int sumaStock = 0;
        for (int j = 0; j < bibEncontrada->getEstanterias().size(); j++) {
            Estanteria* est = bibEncontrada->getEstanterias()[j];
            for (int k = 0; k < est->getEjemplares().size(); k++) {
                sumaStock += est->getEjemplares()[k]->getStock();
            }
        }
        
        cout << " La biblioteca '" << bibEncontrada->getNombre() 
             << "' posee un total de " << sumaStock << " unidades fisicas de libros."<<endl;
    }

    void actualizarCantidadEjemplar() {
        string idEstanteria, isbn;
        int nuevoStock;
        
        cout <<endl<< "--- Actualizar Stock de un Ejemplar ---"<<endl;
        cout << "Ingrese el ID de la estanteria donde esta el ejemplar: "; cin >> idEstanteria;
        
        Estanteria* estEncontrada = nullptr;
        for (int i = 0; i < estanterias.size(); i++) {
            if (estanterias[i]->getId() == idEstanteria) {
                estEncontrada = estanterias[i];
                break;
            }
        }
        
        if (estEncontrada == nullptr) {
            cout << "La estanteria con ID " << idEstanteria << " no existe."<<endl;
            return;
        }
        
        cout << "Ingrese el ISBN del libro: "; cin >> isbn;
        
        Ejemplar* ejEncontrado = nullptr;
        for (int j = 0; j < estEncontrada->getEjemplares().size(); j++) {
            if (estEncontrada->getEjemplares()[j]->getLibro()->getISBN() == isbn) {
                ejEncontrado = estEncontrada->getEjemplares()[j];
                break;
            }
        }
        
        if (ejEncontrado == nullptr) {
            cout << "No existe un ejemplar de ese libro en la estanteria " << idEstanteria << endl;
            return;
        }
        
        cout << "Stock actual: " << ejEncontrado->getStock() << ". Ingrese el nuevo Stock: "; cin >> nuevoStock;
        if (nuevoStock < 0) {
            cout << "El stock no puede ser negativo."<<endl;
            return;
        }
        
        ejEncontrado->setStock(nuevoStock);
        cout << "Cantidad actualizada con exito."<<endl;
    }
    
    void gestionarPrestamos() {
        int subOp = 0;
        cout <<endl<< "====== SUBMENU DE PRESTAMOS ======"<<endl;
        cout << "1. Registrar Estudiante"<<endl;
        cout << "2. Registrar Prestamo de Ejemplar"<<endl;
        cout << "3. Listar libros prestados a un estudiante"<<endl;
        cout << "Regresar al menu principal (Cualquier otro numero)"<<endl;
        cout << "Seleccione una opcion: "; cin >> subOp;
        
        if (subOp == 1) {
            string nombreE, codigoE;
            cout << "Nombre del estudiante: "; cin.ignore(); getline(cin, nombreE);
            cout << "Codigo del estudiante: "; cin >> codigoE;
            
            for (int i = 0; i < estudiantes.size(); i++) {
                if (estudiantes[i]->getCodigo() == codigoE) {
                    cout << "Ya existe un estudiante con ese codigo."<<endl;
                    return;
                }
            }
            estudiantes.push_back(new Estudiante(nombreE, codigoE));
            cout << "Estudiante registrado con exito."<<endl;
        } 
        else if (subOp == 2) {
            string codigoE, idEstanteria, isbn;
            cout << "Ingrese el codigo del estudiante: "; cin >> codigoE;
            
            Estudiante* est = nullptr;
            for (int i = 0; i < estudiantes.size(); i++) {
                if (estudiantes[i]->getCodigo() == codigoE) { est = estudiantes[i]; break; }
            }
            if (est == nullptr) { cout << "Estudiante no registrado."<<endl; return; }
            
            cout << "ID de la estanteria de origen: "; cin >> idEstanteria;
            Estanteria* estant = nullptr;
            for (int i = 0; i < estanterias.size(); i++) {
                if (estanterias[i]->getId() == idEstanteria) { estant = estanterias[i]; break; }
            }
            if (estant == nullptr) { cout << "Estanteria no encontrada."<<endl; return; }
            
            cout << "ISBN del libro a prestar: "; cin >> isbn;
            Ejemplar* ejem = nullptr;
            for (int i = 0; i < estant->getEjemplares().size(); i++) {
                if (estant->getEjemplares()[i]->getLibro()->getISBN() == isbn) {
                    ejem = estant->getEjemplares()[i];
                    break;
                }
            }
            
            if (ejem == nullptr) { 
                cout << "No existe ese ejemplar en la estanteria."<<endl; return; }
            
            if (ejem->getStock() <= 0) {
                cout << "No hay unidades disponibles (Stock en 0) para realizar el prestamo."<<endl;
                return;
            }
            
            ejem->setStock(ejem->getStock() - 1);
            prestamos.push_back(new Prestamo(est, ejem));
            cout << "Prestamo registrado con exito. Unidades restantes en estanteria: " << ejem->getStock()<<endl;
        } 
        else if (subOp == 3) {
            string codigoE;
            cout << "Ingrese el codigo del estudiante: "; cin >> codigoE;
            
            cout <<endl<< "Libros prestados actualmente al estudiante: "<<endl;
            bool tienePrestamos = false;
            
            for (int i = 0; i < prestamos.size(); i++) {
                if (prestamos[i]->getEstudianteP()->getCodigo() == codigoE) {
                    cout << "- " << prestamos[i]->getEjemplarP()->getLibro()->getTitulo() 
                         << " [ISBN: " << prestamos[i]->getEjemplarP()->getLibro()->getISBN() << "]"<<endl;
                    tienePrestamos = true;
                }
            }
            if (!tienePrestamos) cout << "El estudiante no registra prestamos activos."<<endl;
        }
    }

};
int menu() {
    int op = 0;
    
    cout << "=================================================="<<endl;
    cout << "  SISTEMA DE GESTION DE BIBLIOTECAS - UNICAUCA    "<<endl;
    cout << "=================================================="<<endl;
    cout << "1.  Registrar Autor."<<endl;
    cout << "2.  Registrar Libro."<<endl;
    cout << "3.  Registrar Estanteria."<<endl;
    cout << "4.  Registrar Ejemplar: Asignar Libro a una Estanteria."<<endl;
    cout << "5.  Registrar Biblioteca y asignar Estanterias a Biblioteca."<<endl;
    cout << "6.  Consultar Disponibilidad de un Libro."<<endl;
    cout << "7.  Listar Inventario de una Biblioteca."<<endl;
    cout << "8.  Conteo Total de Inventario de una Biblioteca."<<endl;
    cout << "9.  Actualizar Cantidad de un Ejemplar."<<endl;
    cout << "10. Gestionar Prestamos: Estudiantes/Ejemplares."<<endl;
    cout << "11. Salir del Sistema."<<endl;
    cout << "--------------------------------------------------"<<endl;
    cout << "Seleccione una opcion (1-11): ";
    
    // Validación de entrada para evitar bucles infinitos si digitan letras
    while (!(cin >> op) || (op < 1) || (op > 11)) {
        cin.clear(); //Reinicia la variable.
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpia el Búfer.
        cout << "Opcion invalida. Por favor, ingrese un numero entre 1 y 11: ";
    }
    return op;
}

int main() {
    SistemaGestion sistema;
    int opc = 0;
    bool ejecutar = true;

    while (ejecutar) {
        opc = menu();
        cout << endl << " Ha seleccionado la opcion " << opc << "..."<<endl;

        switch (opc) {
            case 1:
 
                sistema.registrarAutor();
                break;
            case 2:
                 sistema.registrarLibro();
                break;
            case 3:
                 sistema.registrarEstanteria();
                break;
            case 4:
                 sistema.registrarEjemplar();
                break;
            case 5:
                 sistema.registrarBiblioteca();
                break;
            case 6:
                sistema.consultarDisponibilidad();
                break;
            case 7:
                sistema.listarInventario();
                break;
            case 8:
                 sistema.conteoTotalInventario();
                break;
            case 9:
                 sistema.actualizarCantidadEjemplar();
                break;
            case 10:
                 sistema.gestionarPrestamos(); 
                break;
            case 11:
                cout << "Saliendo del sistema de gestión."<<endl;
                ejecutar = false;
                break;
        }
        
        //Se hace para darle una espera al programa en la pantalla.
        if (ejecutar) { //no se hace comparaciones ni nada porque solo puede ser false.
            cout << "\nPresione ENTER para continuar...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cin.get(); // Espera la pulsación de una tecla
        }
    }
    return 0;
}
