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
  vector<Libro> libros;

public:
  Estante()
  {
    this->nombre = "";
  }

  Estante(string nombre)
  {
    this->nombre = nombre;
  }

  string getNombre() const { return this->nombre; }

  void agregarLibro(Libro libro)
  {
    this->libros.push_back(libro);
  }

  int cantidadLibros() const
  {
    return this->libros.size();
  }

  void listarLibros()
  {
    cout << "Estante: " << this->nombre << endl;
    for (int i = 0; i < this->libros.size(); i++)
    {
      this->libros[i].print();
    }
  }
};

class Biblioteca
{
private:
  string nombre;
  vector<Estante> estantes;

public:
  Biblioteca()
  {
    this->nombre = "";
  }

  Biblioteca(string nombre)
  {
    this->nombre = nombre;
  }

  string getNombre() const { return this->nombre; }

  void agregarEstante(Estante estante)
  {
    this->estantes.push_back(estante);
  }

  int cantidadEstantes() const
  {
    return this->estantes.size();
  }

  void listarTodo()
  {
    cout << "Biblioteca: " << this->nombre << endl;
    for (int i = 0; i < this->estantes.size(); i++)
    {
      this->estantes[i].listarLibros();
    }
  }
};

int main()
{
  Autor autor1("Fiodor Dostoievsky", "Rusia", "1700-01-01", "1763-01-01", 10);
  Autor autor2("Jorge Luis Borges", "Argentina", "1899-08-24", "1986-06-14", 15);
  Autor autor3("Gabriel Garcia Marquez", "Colombia", "1927-03-06", "2014-04-17", 20);

  Libro libro1("El jugador", autor1, 5);
  Libro libro2("Ficciones", autor2, 3);
  Libro libro3("El Aleph", autor2);
  Libro libro4("Cien anios de soledad", autor3, 2);
  Libro libro5;
  libro5.setTitle("Sin autor asignado");
  libro5.setReleaseYear(2020);
  libro5.setISBN("ISBN_TEST");
  libro5.setStock(1);

  Estante estanteA("Estante A - Literatura Rusa");
  estanteA.agregarLibro(libro1);

  Estante estanteB("Estante B - Literatura Latinoamericana");
  estanteB.agregarLibro(libro2);
  estanteB.agregarLibro(libro3);
  estanteB.agregarLibro(libro4);

  Estante estanteC("Estante C - Sin clasificar");
  estanteC.agregarLibro(libro5);

  Biblioteca biblioteca("Biblioteca Central Unicauca");
  biblioteca.agregarEstante(estanteA);
  biblioteca.agregarEstante(estanteB);
  biblioteca.agregarEstante(estanteC);

  cout << "Cantidad de estantes en la biblioteca: " << biblioteca.cantidadEstantes() << endl;
  cout << "Cantidad de libros en estanteB: " << estanteB.cantidadLibros() << endl;
  cout << "----------------------------------------" << endl;

  biblioteca.listarTodo();

  return 0;
}