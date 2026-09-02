#include <iostream>
#include <string>
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

int main()
{
  Libro myBook;

  myBook.setTitle("El jugador");
  // myBook.setAuthor("Fiodor Dostoievsky");
  myBook.setReleaseYear(1861);
  myBook.setISBN("ISBN_FAKE");
  myBook.setStock(20);

  Autor autor("Fiodor Dostoievsky", "Rusia", "1700-01-01", "1763-01-01", 10);
  myBook.setAuthor(autor);
  // Imprimir la data del libro
  myBook.print();
  return 0;
}