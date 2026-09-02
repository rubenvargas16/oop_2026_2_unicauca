#include <iostream>
#include <string>
using namespace std;

class Libro {
private:
    string titulo;
    string autor;
    int cantidadEjemplares;
    bool prestado;

public:
    Libro() {
        titulo = "Sin titulo";
        autor = "Desconocido";
        cantidadEjemplares = 0;
        prestado = false;
        cout << "[Constructor por defecto] Se creo un libro vacio." << endl;
    }

    Libro(string titulo, string autor, int cantidadEjemplares) {
        this->titulo = titulo;
        this->autor = autor;
        setCantidadEjemplares(cantidadEjemplares);
        this->prestado = false;
        cout << "[Constructor parametrizado] Se creo \"" << titulo << "\"." << endl;
    }

    Libro(string titulo, string autor) : Libro(titulo, autor, 1) {
        cout << "[Constructor delegado] \"" << titulo << "\" con 1 ejemplar por defecto." << endl;
    }

    string getTitulo() const { return titulo; }
    string getAutor() const { return autor; }
    int getCantidadEjemplares() const { return cantidadEjemplares; }
    bool getPrestado() const { return prestado; }

    void setCantidadEjemplares(int cantidad) {
        if (cantidad >= 0) {
            cantidadEjemplares = cantidad;
        } else {
            cout << "Aviso: cantidad invalida (" << cantidad
                 << "). Se asigna 0 por defecto." << endl;
            cantidadEjemplares = 0;
        }
    }

    void prestar() {
        if (cantidadEjemplares > 0 && !prestado) {
            prestado = true;
            cantidadEjemplares--;
            cout << "\"" << titulo << "\" fue prestado. Quedan "
                 << cantidadEjemplares << " ejemplares." << endl;
        } else {
            cout << "No se puede prestar \"" << titulo << "\" en este momento." << endl;
        }
    }

    void devolver() {
        if (prestado) {
            prestado = false;
            cantidadEjemplares++;
            cout << "\"" << titulo << "\" fue devuelto. Ahora hay "
                 << cantidadEjemplares << " ejemplares." << endl;
        } else {
            cout << "\"" << titulo << "\" no estaba prestado." << endl;
        }
    }

    void mostrarInfo() const {
        cout << "----------------------------------" << endl;
        cout << "Titulo: " << titulo << endl;
        cout << "Autor: " << autor << endl;
        cout << "Ejemplares disponibles: " << cantidadEjemplares << endl;
        cout << "Prestado: " << (prestado ? "Si" : "No") << endl;
    }
};

int main() {
    cout << "=== Creando libros con distintos constructores ===" << endl;

    Libro libroVacio;                                              // constructor por defecto
    Libro libro1("Ficciones", "Jorge Luis Borges", 3);              // constructor parametrizado
    Libro libro2("El Jugador", "Fiodor Dostoievski");               // constructor delegado (1 ejemplar)

    cout << "\n=== Estado inicial ===" << endl;
    libroVacio.mostrarInfo();
    libro1.mostrarInfo();
    libro2.mostrarInfo();

    cout << "\n=== Constructor de copia (automatico) ===" << endl;
    Libro copiaDeLibro1 = libro1;  // se invoca el constructor de copia generado por C++
    cout << "Se copio \"" << libro1.getTitulo() << "\" hacia una nueva variable." << endl;
    copiaDeLibro1.mostrarInfo();

    cout << "\n=== Verificando que son objetos independientes ===" << endl;
    copiaDeLibro1.prestar();
    cout << "Estado de la copia:" << endl;
    copiaDeLibro1.mostrarInfo();
    cout << "Estado del original (no debe cambiar):" << endl;
    libro1.mostrarInfo();

    return 0;
}