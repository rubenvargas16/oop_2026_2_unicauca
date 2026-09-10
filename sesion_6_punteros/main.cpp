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

class Estante
{
private:
  string nombre;
  vector<Libro*> libros;

public:
  Estante(string nombre){
    this->nombre = nombre;
  }

  Estante(string nombre, vector<Libro*> libros)
  {
    this->nombre = nombre;
    this->libros = libros;
  }

  void setNombre(string nombre) { this->nombre = nombre; }
  void setVector(vector<Libro*> libros) { this->libros = libros; }
  string getNombre() { return this->nombre; }
  vector<Libro*> getLibros() { return this->libros; }

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

class Biblioteca
{
private:
  string nombre;
  vector<Estante> estantes;

public:
  Biblioteca(string nombre, vector<Estante> estantes)
  {
    this->nombre = nombre;
    this->estantes = estantes;
  }

  void setNombre(string nombre) { this->nombre = nombre; }
  void setEstantes(vector<Estante> estantes) { this->estantes = estantes; }
  string getNombre() { return this->nombre; }
  vector<Estante> getEstantes() { return this->estantes; }

  void agregarEstante(Estante estante)
  {
    this->estantes.push_back(estante);
  }

  void buscarLibro(string title)
  {
    int indexEstante = -1;
    int indexLibro = -1;
    for (int i = 0; i < this->estantes.size(); i++)
    {
      Estante tmp = this->estantes[i];
      int tmpIndex = tmp.buscarLibro(title);
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
           << this->estantes[indexEstante].getNombre()
           << " en la posición " << indexLibro << endl;
    }
    else
    {
      cout << "El libro no está en la biblioteca" << endl;
    }
  }
};

//Demo 1 del porqué de la necesidad de punteros.
void intentarCambiarStock(Libro *libro, int nuevoStock)
{
  libro->setStock(nuevoStock);
  cout << "  [Dentro de la funcion] Stock del libro (copia local): "
       << libro->getStock() << endl;
}

//Demo 2 de porque usar punteros en vez de variabls en el heap
void intentarAgregarLibro(Estante estante, Libro *libro)
{
  estante.agregarLibro(libro);
  cout << "  [Dentro de la funcion] El estante (copia local) recibio el libro." << endl;
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

  Libro *myBookPointer = &myBook;

  cout << "DIR_MEMORIA: " << &myBook << endl;
  Libro myBook2 = myBook;

  
  cout << myBook.getTitle() << endl;
  cout << (*myBookPointer).getTitle() << endl;
  cout << myBookPointer->getTitle() << endl;

  intentarCambiarStock(&myBook, 14);
  cout << myBook.getStock() << endl;
  intentarCambiarStock(myBookPointer, 10);
  cout << myBook.getStock() << endl;

  Estante estante("Estante prueba");
  estante.agregarLibro(&myBook);
  myBook.setTitle("Nombre diferente");
  cout << "Nombre del libro en estante: " << estante.getLibros()[0]->getTitle() << endl;
  cout << "Nombre del libro en main: " << myBook.getTitle() << endl;

  cout << "Nombre del libro en estante2: " << estante.getLibros()[0]->getTitle() << endl;
  return 0;
}