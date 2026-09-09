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

public:
  Autor()
  {
    this->nombre = "";
    this->nacionalidad = "";
    this->fechaNacimiento = "";
    this->fechaMuerte = "";
    this->librosPublicados = 1;
  }

  Autor(string nombre, string nacionalidad, string fechaNacimiento, string fechaMuerte, int librosPublicados)
  {
    this->nombre = nombre;
    this->nacionalidad = nacionalidad;
    this->fechaNacimiento = fechaNacimiento;
    this->fechaMuerte = fechaMuerte;
    this->librosPublicados = librosPublicados;
  }
  // Setters
  void setNombre(string nombre) { this->nombre = nombre; }
  void setNacionalidad(string nacionalidad) { this->nacionalidad = nacionalidad; }
  void setFechaNacimiento(string fechaNacimiento) { this->fechaNacimiento = fechaNacimiento; }
  void setFechaMuerte(string fechaMuerte) { this->fechaMuerte = fechaMuerte; }
  void setLibrosPublicados(int librosPublicados) { this->librosPublicados = librosPublicados; }
  // Getters
  string getNombre() { return this->nombre; }
  string getNacionalidad() { return this->nacionalidad; }
  string getFechaNacimiento() { return this->fechaNacimiento; }
  string getFechaMuerte() { return this->fechaMuerte; }
  int getLibrosPublicados() { return this->librosPublicados; }

  void print()
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

class Libro
{
private:
  string title;
  Autor author;
  int releaseYear;
  string isbn;
  int stock; // Cantidad
public:
  // Constructor por defecto ó vacío.
  Libro()
  {
    this->title = "No title";
    this->releaseYear = 0;
    this->isbn = "NO-ISBN";
    this->stock = 0;
  }
  // Constructor
  Libro(string title, Autor author, int stock)
  {
    this->title = title;
    this->author = author;
    this->stock = stock;
  }
  // Sobrecarga de constructor
  Libro(string title, Autor author) : Libro(title, author, 1)
  {
    this->releaseYear = 2026;
    this->isbn = "NO-ISBN";
  }

  string getTitle() const { return this->title; }
  Autor getAuthor() const { return this->author; }
  int getReleaseYear() const { return this->releaseYear; }
  string getISBN() const { return this->isbn; }
  int getStock() const { return this->stock; }

  void setTitle(string title) { this->title = title; }
  void setAuthor(Autor author) { this->author = author; }
  void setReleaseYear(int releaseYear) { this->releaseYear = releaseYear; }
  void setISBN(string isbn)
  {
    this->isbn = isbn;
  }
  void setStock(int stock)
  {
    if (stock < 0)
    {
      this->stock = 0;
      cout << "El stock no puede ser negativo" << endl;
    }
    else
    {
      this->stock = stock;
    }
  }

  void print()
  {
    cout << "Información del libro:" << endl;
    cout << "Titulo: " << this->title << endl;
    this->author.print();
    cout << "Año de publicación: " << this->releaseYear << endl;
    cout << "ISBN: " << this->isbn << endl;
    cout << "Stock: " << this->stock << endl;
  }
};

// Estante ahora guarda PUNTEROS a Libro (vector<Libro*>).
// Cada elemento es la direccion de un Libro que vive en otra
// parte del programa, no una copia.
class Estante
{
private:
  string nombre;
  vector<Libro *> libros;

public:
  Estante(string nombre, vector<Libro *> libros)
  {
    this->nombre = nombre;
    this->libros = libros;
  }

  void setNombre(string nombre) { this->nombre = nombre; }
  void setVector(vector<Libro *> libros) { this->libros = libros; }
  string getNombre() { return this->nombre; }
  vector<Libro *> getLibros() { return this->libros; }

  void agregarLibro(Libro *libro)
  {
    this->libros.push_back(libro);
  }

  int buscarLibro(string title)
  {
    int index = -1;
    for (int i = 0; i < this->libros.size(); i++)
    {
      Libro *tmp = this->libros[i];
      if (tmp->getTitle() == title)
      {
        index = i;
        break;
      }
    }
    return index;
  }
};

// Biblioteca ahora guarda PUNTEROS a Estante (vector<Estante*>).
class Biblioteca
{
private:
  string nombre;
  vector<Estante *> estantes;

public:
  Biblioteca(string nombre, vector<Estante *> estantes)
  {
    this->nombre = nombre;
    this->estantes = estantes;
  }

  void setNombre(string nombre) { this->nombre = nombre; }
  void setEstantes(vector<Estante *> estantes) { this->estantes = estantes; }
  string getNombre() { return this->nombre; }
  vector<Estante *> getEstantes() { return this->estantes; }

  void agregarEstante(Estante *estante)
  {
    this->estantes.push_back(estante);
  }

  void buscarLibro(string title)
  {
    int indexEstante = -1;
    int indexLibro = -1;
    for (int i = 0; i < this->estantes.size(); i++)
    {
      Estante *tmp = this->estantes[i];
      int tmpIndex = tmp->buscarLibro(title);
      if (tmpIndex >= 0)
      {
        indexLibro = tmpIndex;
        indexEstante = i;
        break;
      }
    }
    if (indexEstante >= 0)
    {
      cout << "El libro " << title << ", se encuentra en la estanteria "
           << this->estantes[indexEstante]->getNombre()
           << " en la posición " << indexLibro << endl;
    }
    else
    {
      cout << "El libro no está en la biblioteca" << endl;
    }
  }
};

// ============================================================
// DEMOSTRACION 1: ahora Libro se recibe POR PUNTERO.
// "libro" ya no es una copia: es la direccion del objeto real.
// Modificarlo aqui adentro SI afecta al original.
// ============================================================
void intentarCambiarStock(Libro *libro, int nuevoStock)
{
  libro->setStock(nuevoStock);
  cout << "  [Dentro de la funcion] Stock del libro (via puntero): "
       << libro->getStock() << endl;
}

// ============================================================
// DEMOSTRACION 2: Estante tambien se recibe POR PUNTERO.
// agregarLibro se ejecuta sobre el Estante real de main, no
// sobre una copia.
// ============================================================
void intentarAgregarLibro(Estante *estante, Libro *libro)
{
  estante->agregarLibro(libro);
  cout << "  [Dentro de la funcion] El estante real recibio el libro." << endl;
}

int main()
{
  Libro myBook;

  myBook.setTitle("El jugador");
  myBook.setReleaseYear(1861);
  myBook.setISBN("ISBN_FAKE");
  myBook.setStock(20);

  Autor autor("Fiodor Dostoievsky", "Rusia", "1700-01-01", "1763-01-01", 10);
  myBook.setAuthor(autor);
  myBook.print();

  cout << "\n========================================" << endl;
  cout << "DEMOSTRACION 1: puntero a Libro" << endl;
  cout << "========================================" << endl;

  cout << "Stock de myBook ANTES de llamar la funcion: " << myBook.getStock() << endl;
  intentarCambiarStock(&myBook, 999);
  cout << "Stock de myBook DESPUES de llamar la funcion: " << myBook.getStock() << endl;
  cout << "(Ahora SI cambio: la funcion recibio la direccion real de myBook)" << endl;

  cout << "\n========================================" << endl;
  cout << "DEMOSTRACION 2: puntero a Estante" << endl;
  cout << "========================================" << endl;

  vector<Libro *> librosIniciales; // vector vacio
  Estante estanteA("Estante A", librosIniciales);

  cout << "Busqueda ANTES de llamar la funcion:" << endl;
  cout << "  Posicion encontrada: " << estanteA.buscarLibro("El jugador") << " (-1 = no existe)" << endl;

  intentarAgregarLibro(&estanteA, &myBook);

  cout << "Busqueda DESPUES de llamar la funcion:" << endl;
  cout << "  Posicion encontrada: " << estanteA.buscarLibro("El jugador") << " (-1 = no existe)" << endl;
  cout << "(Ahora SI aparece: el libro se agrego al estante real de main)" << endl;

  cout << "\n========================================" << endl;
  cout << "DEMOSTRACION 3: puntero + ciclo/bloque" << endl;
  cout << "========================================" << endl;

  cout << "Stock real guardado en el estante: "
       << estanteA.getLibros()[0]->getStock() << endl;

  cout << "\nAhora modificamos el stock recorriendo el vector con un ciclo:" << endl;
  vector<Libro *> copiaTemporal = estanteA.getLibros(); // se copian PUNTEROS, no objetos
  for (int i = 0; i < copiaTemporal.size(); i++)
  {
    copiaTemporal[i]->setStock(1);
    cout << "  [Dentro del ciclo] Stock modificado a: " << copiaTemporal[i]->getStock() << endl;
  } // <- aqui termina el scope de "copiaTemporal", pero los Libro* que contenia siguen apuntando a los mismos objetos reales.

  cout << "Stock real dentro del estante DESPUES del ciclo: "
       << estanteA.getLibros()[0]->getStock() << endl;
  cout << "(Ahora SI cambio: copiar el vector solo copia direcciones, no los objetos)" << endl;

  return 0;
}