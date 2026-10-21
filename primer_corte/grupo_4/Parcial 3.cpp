#include <iostream>
#include <string>
#include <list>
#include <limits>

using namespace std;

void pausa() {
    cout << "\nPresione Enter para continuar...";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

string leerLinea(const string& mensaje) {
    string valor;
    cout << mensaje;
    getline(cin, valor);
    return valor;
}

int leerEntero(const string& mensaje) {
    string valor;
    cout << mensaje;
    getline(cin, valor);

    while (valor.empty()) {
        cout << mensaje;
        getline(cin, valor);
    }

    try {
        return stoi(valor);
    } catch (...) {
        cout << ">> Error: Debe ingresar un numero valido.\n";
        return 0;
    }
}

// 1. CLASES BASE

class Autor {
private:
    string nombre;
    string nacionalidad;
    string fechaNacimiento;
    string fechaMuerte;
    int librosPublicados;

public:
    Autor(string nombre, string nacionalidad, string fechaNacimiento, string fechaMuerte, int librosPublicados) {
        this->nombre = nombre;
        this->nacionalidad = nacionalidad;
        this->fechaNacimiento = fechaNacimiento;
        this->fechaMuerte = fechaMuerte;
        this->librosPublicados = librosPublicados;
    }
    string getNombre() const { return this->nombre; }
    void print() const {
        cout << "Autor: " << this->nombre << " (" << this->nacionalidad << ")" << endl;
    }
};

class Libro {
private:
    string title;
    Autor* author;
    int releaseYear;
    string isbn;

public:
    Libro(string title, Autor* author, int releaseYear, string isbn) {
        this->title = title;
        this->author = author;
        this->releaseYear = releaseYear;
        this->isbn = isbn;
    }
    string getTitle() const { return this->title; }
    string getISBN() const { return this->isbn; }
    Autor* getAuthor() const { return this->author; }
    void print() const {
        cout << "Titulo: " << this->title << " | ISBN: " << this->isbn << " | Anio: " << this->releaseYear << endl;
        if (this->author != nullptr) {
            cout << "  ";
            this->author->print();
        }
    }
};

class Ejemplar {
private:
    Libro* libro;
    int cantidadDisponible;

public:
    Ejemplar(Libro* libro, int cantidad) {
        this->libro = libro;
        this->cantidadDisponible = cantidad;
    }
    Libro* getLibro() const { return this->libro; }
    int getCantidadDisponible() const { return this->cantidadDisponible; }
    void setCantidadDisponible(int cant) { this->cantidadDisponible = cant; }
};

class Estante {
private:
    string nombre;
    list<Ejemplar> ejemplares;

public:
    Estante(string nombre) : nombre(nombre) {}
    string getNombre() const { return this->nombre; }
    list<Ejemplar>& getEjemplares() { return this->ejemplares; }
    Ejemplar* agregarEjemplar(Libro* libro, int cant) {
        this->ejemplares.push_back(Ejemplar(libro, cant));
        return &this->ejemplares.back();
    }
};

class Biblioteca {
private:
    string nombre;
    list<Estante> estantes;

public:
    Biblioteca(string nombre) : nombre(nombre) {}
    string getNombre() const { return this->nombre; }
    list<Estante>& getEstantes() { return this->estantes; }
    Estante* agregarEstante(string nombreEstante) {
        this->estantes.push_back(Estante(nombreEstante));
        return &this->estantes.back();
    }
};

class Estudiante {
private:
    string nombre;
    string codigoUniversitario;

public:
    Estudiante(string nombre, string codigoUniversitario) {
        this->nombre = nombre;
        this->codigoUniversitario = codigoUniversitario;
    }
    string getNombre() const { return this->nombre; }
    string getCodigoUniversitario() const { return this->codigoUniversitario; }
};

class Prestamo {
private:
    Ejemplar* ejemplarPrestado;
    Estudiante* estudiante;

public:
    Prestamo(Ejemplar* ej, Estudiante* est) {
        this->ejemplarPrestado = ej;
        this->estudiante = est;
    }
    Ejemplar* getEjemplar() const { return this->ejemplarPrestado; }
    Estudiante* getEstudiante() const { return this->estudiante; }
};

// 2. CLASE GLOBAL

class Universidad {
private:
    list<Autor> autores;
    list<Libro> libros;
    list<Biblioteca> bibliotecas;
    list<Estudiante> estudiantes;
    list<Prestamo> prestamos;

public:
    Universidad() {}

    Autor* buscarAutor(string nombre) {
        for (auto &a : autores) {
            if (a.getNombre() == nombre) return &a;
        }
        return nullptr;
    }

    Libro* buscarLibro(string titulo) {
        for (auto &l : libros) {
            if (l.getTitle() == titulo) return &l;
        }
        return nullptr;
    }

    Biblioteca* buscarBiblioteca(string nombre) {
        for (auto &b : bibliotecas) {
            if (b.getNombre() == nombre) return &b;
        }
        return nullptr;
    }

    Estudiante* buscarEstudiante(string codigo) {
        for (auto &e : estudiantes) {
            if (e.getCodigoUniversitario() == codigo) return &e;
        }
        return nullptr;
    }

    void registrarAutor(string nom, string nac, string fn, string fm, int lp) {
        if (nom.empty() || nac.empty() || fn.empty()) {
            cout << ">> Error: Faltan datos para registrar el autor.\n";
            return;
        }
        autores.push_back(Autor(nom, nac, fn, fm, lp));
        cout << ">> Autor registrado correctamente.\n";
    }

    void registrarLibro(string tit, string nombreAut, int anio, string isbn) {
        if (tit.empty() || nombreAut.empty() || isbn.empty() || anio <= 0) {
            cout << ">> Error: Faltan datos o valores invalidos para registrar el libro.\n";
            return;
        }
        Autor* aut = buscarAutor(nombreAut);
        if (!aut) { cout << ">> Error: El autor no existe.\n"; return; }

        libros.push_back(Libro(tit, aut, anio, isbn));
        cout << ">> Libro catalogado correctamente.\n";
    }

    void registrarEstanteriaEnBiblioteca(string nombreBib, string nombreEst) {
        if (nombreBib.empty() || nombreEst.empty()) {
            cout << ">> Error: Debe indicar la biblioteca y la estanteria.\n";
            return;
        }
        Biblioteca* bib = buscarBiblioteca(nombreBib);
        if (!bib) { cout << ">> Error: La biblioteca no existe.\n"; return; }

        bib->agregarEstante(nombreEst);
        cout << ">> Estanteria registrada y asignada.\n";
    }

    void registrarEjemplar(string tituloLib, string nombreBib, string nombreEst, int cant) {
        if (tituloLib.empty() || nombreBib.empty() || nombreEst.empty() || cant <= 0) {
            cout << ">> Error: Faltan datos o cantidad invalida para registrar el ejemplar.\n";
            return;
        }
        Libro* lib = buscarLibro(tituloLib);
        Biblioteca* bib = buscarBiblioteca(nombreBib);
        if (!lib || !bib) { cout << ">> Error: Libro o Biblioteca no encontrados.\n"; return; }

        for (auto &est : bib->getEstantes()) {
            if (est.getNombre() == nombreEst) {
                est.agregarEjemplar(lib, cant);
                cout << ">> Ejemplar asignado a la estanteria con exito.\n";
                return;
            }
        }
        cout << ">> Error: Estanteria no encontrada en esa biblioteca.\n";
    }

    void registrarBiblioteca(string nom) {
        if (nom.empty()) {
            cout << ">> Error: Debe ingresar el nombre de la biblioteca.\n";
            return;
        }
        bibliotecas.push_back(Biblioteca(nom));
        cout << ">> Biblioteca creada con exito.\n";
    }

    void consultarDisponibilidad(string titulo) {
        bool encontrado = false;
        for (auto &b : bibliotecas) {
            for (auto &est : b.getEstantes()) {
                for (auto &ej : est.getEjemplares()) {
                    if (ej.getLibro()->getTitle() == titulo) {
                        cout << "-> Biblioteca: " << b.getNombre()
                             << " | Estante: " << est.getNombre()
                             << " | Disponibles: " << ej.getCantidadDisponible() << "\n";
                        encontrado = true;
                    }
                }
            }
        }
        if (!encontrado) cout << ">> No se encontraron existencias del libro.\n";
    }

    void listarInventarioBiblioteca(string nombreBib) {
        Biblioteca* bib = buscarBiblioteca(nombreBib);
        if (!bib) { cout << ">> Biblioteca no existe.\n"; return; }
        cout << "--- Inventario de " << nombreBib << " ---\n";
        for (auto &est : bib->getEstantes()) {
            for (auto &ej : est.getEjemplares()) {
                cout << "Libro: " << ej.getLibro()->getTitle()
                     << " | Estante: " << est.getNombre()
                     << " | Cantidad: " << ej.getCantidadDisponible() << "\n";
            }
        }
    }

    void conteoInventarioTotal(string nombreBib) {
        Biblioteca* bib = buscarBiblioteca(nombreBib);
        if (!bib) { cout << ">> Biblioteca no existe.\n"; return; }
        int total = 0;
        for (auto &est : bib->getEstantes()) {
            for (auto &ej : est.getEjemplares()) {
                total += ej.getCantidadDisponible();
            }
        }
        cout << ">> Total de ejemplares en la biblioteca: " << total << "\n";
    }

    void actualizarInventario(string titulo, string nombreBib, string nombreEst, int nuevaCant) {
        Biblioteca* bib = buscarBiblioteca(nombreBib);
        if (!bib) { cout << ">> Biblioteca no existe.\n"; return; }
        for (auto &est : bib->getEstantes()) {
            if (est.getNombre() == nombreEst) {
                for (auto &ej : est.getEjemplares()) {
                    if (ej.getLibro()->getTitle() == titulo) {
                        ej.setCantidadDisponible(nuevaCant);
                        cout << ">> Inventario actualizado correctamente.\n";
                        return;
                    }
                }
            }
        }
        cout << ">> Ejemplar no encontrado para actualizar.\n";
    }

    void registrarEstudiante(string nom, string cod) {
        if (nom.empty() || cod.empty()) {
            cout << ">> Error: Debe ingresar nombre y codigo del estudiante.\n";
            return;
        }
        estudiantes.push_back(Estudiante(nom, cod));
        cout << ">> Estudiante registrado con exito.\n";
    }

    void registrarPrestamo(string codigoEst, string tituloLib, string nombreBib) {
        if (codigoEst.empty() || tituloLib.empty() || nombreBib.empty()) {
            cout << ">> Error: Faltan datos para registrar el prestamo.\n";
            return;
        }

        Estudiante* est = buscarEstudiante(codigoEst);
        Biblioteca* bib = buscarBiblioteca(nombreBib);
        if (!est || !bib) { cout << ">> Estudiante o Biblioteca no registrados.\n"; return; }

        for (auto &e : bib->getEstantes()) {
            for (auto &ej : e.getEjemplares()) {
                if (ej.getLibro()->getTitle() == tituloLib && ej.getCantidadDisponible() > 0) {
                    ej.setCantidadDisponible(ej.getCantidadDisponible() - 1);
                    prestamos.push_back(Prestamo(&ej, est));
                    cout << ">> Prestamo registrado con exito.\n";
                    return;
                }
            }
        }
        cout << ">> Error: No hay ejemplares disponibles en esta biblioteca.\n";
    }

    void listarPrestadosBiblioteca(string nombreBib) {
        cout << "--- Libros Prestados en " << nombreBib << " ---\n";
        for (auto &p : prestamos) {
            bool pertenece = false;
            Biblioteca* bib = buscarBiblioteca(nombreBib);
            if (bib) {
                for (auto &e : bib->getEstantes()) {
                    for (auto &ej : e.getEjemplares()) {
                        if (&ej == p.getEjemplar()) pertenece = true;
                    }
                }
            }
            if (pertenece) {
                cout << "Libro: " << p.getEjemplar()->getLibro()->getTitle()
                     << " | Prestado a: " << p.getEstudiante()->getNombre() << "\n";
            }
        }
    }

    void listarPrestamosEstudiante(string codigoEst) {
        cout << "--- Libros prestados al codigo " << codigoEst << " ---\n";
        for (auto &p : prestamos) {
            if (p.getEstudiante()->getCodigoUniversitario() == codigoEst) {
                cout << "- " << p.getEjemplar()->getLibro()->getTitle() << "\n";
            }
        }
    }
};

// 3. MENU DE OPERACIÓN EN CONSOLA 

int main() {
    Universidad uni;
    int opcion = 0;

    cout << "=========================================\n";
    cout << "  SISTEMA DE GESTION BIBLIOTECARIA \n";
    cout << "=========================================\n";

    do {
        cout << "\n--- MENU DE OPCIONES ---\n";
        cout << "1. Registrar Autor\n";
        cout << "2. Registrar Libro\n";
        cout << "3. Registrar Estanteria\n";
        cout << "4. Registrar Ejemplar (Inventario)\n";
        cout << "5. Registrar Biblioteca\n";
        cout << "6. Consultar Disponibilidad de un Libro\n";
        cout << "7. Listado de Inventario de una Biblioteca\n";
        cout << "8. Conteo Total de Inventario\n";
        cout << "9. Actualizar Inventario\n";
        cout << "10. Registrar Estudiante\n";
        cout << "11. Registrar Prestamo\n";
        cout << "12. Listar Libros Prestados por Biblioteca\n";
        cout << "13. Listar Libros de un Estudiante\n";
        cout << "14. Salir\n";

        opcion = leerEntero("Seleccione una opcion: ");

        string nom, nac, fn, fm, tit, isbn, bib, est, cod;
        int lp, anio, cant;

        switch (opcion) {
            case 1:
                nom = leerLinea("Nombre: ");
                nac = leerLinea("Nacionalidad: ");
                fn = leerLinea("Anio Nacimiento: ");
                fm = leerLinea("Anio Muerte (vacio si vive): ");
                lp = leerEntero("Libros Publicados: ");
                uni.registrarAutor(nom, nac, fn, fm, lp);
                break;
            case 2:
                tit = leerLinea("Titulo: ");
                nom = leerLinea("Nombre exacto del Autor: ");
                anio = leerEntero("Anio Publicacion: ");
                isbn = leerLinea("ISBN: ");
                uni.registrarLibro(tit, nom, anio, isbn);
                break;
            case 3:
                bib = leerLinea("Nombre de la Biblioteca de destino: ");
                est = leerLinea("Nombre o Codigo de la Estanteria: ");
                uni.registrarEstanteriaEnBiblioteca(bib, est);
                break;
            case 4:
                tit = leerLinea("Titulo del Libro: ");
                bib = leerLinea("Nombre de la Biblioteca: ");
                est = leerLinea("Nombre del Estante: ");
                cant = leerEntero("Cantidad de ejemplares a ingresar: ");
                uni.registrarEjemplar(tit, bib, est, cant);
                break;
            case 5:
                bib = leerLinea("Nombre de la Biblioteca: ");
                uni.registrarBiblioteca(bib);
                break;
            case 6:
                tit = leerLinea("Titulo del libro a buscar: ");
                uni.consultarDisponibilidad(tit);
                break;
            case 7:
                bib = leerLinea("Nombre de la Biblioteca: ");
                uni.listarInventarioBiblioteca(bib);
                break;
            case 8:
                bib = leerLinea("Nombre de la Biblioteca: ");
                uni.conteoInventarioTotal(bib);
                break;
            case 9:
                tit = leerLinea("Titulo del Libro: ");
                bib = leerLinea("Nombre de la Biblioteca: ");
                est = leerLinea("Nombre del Estante: ");
                cant = leerEntero("Nueva cantidad disponible: ");
                uni.actualizarInventario(tit, bib, est, cant);
                break;
            case 10:
                nom = leerLinea("Nombre del Estudiante: ");
                cod = leerLinea("Codigo Universitario: ");
                uni.registrarEstudiante(nom, cod);
                break;
            case 11:
                cod = leerLinea("Codigo del Estudiante: ");
                tit = leerLinea("Titulo del Libro: ");
                bib = leerLinea("Biblioteca de origen: ");
                uni.registrarPrestamo(cod, tit, bib);
                break;
            case 12:
                bib = leerLinea("Nombre de la Biblioteca: ");
                uni.listarPrestadosBiblioteca(bib);
                break;
            case 13:
                cod = leerLinea("Codigo del Estudiante: ");
                uni.listarPrestamosEstudiante(cod);
                break;
            case 14:
                cout << "Finalizando ejecucion del sistema...\n";
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo.\n";
        }

        if (opcion != 14) {
            pausa();
        }
    } while (opcion != 14);

    return 0;
}