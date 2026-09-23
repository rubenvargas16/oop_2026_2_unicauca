#include "Libro.h"

Libro::Libro()
{
  this->title = "No title";
  this->releaseYear = 0;
  this->isbn = "NO-ISBN";
  this->stock = 0;
}

Libro::Libro(string title, Autor author, int stock)
{
  this->title = title;
  this->author = author;
  this->stock = stock;
}

Libro::Libro(string title, Autor author) : Libro(title, author, 1)
{
  this->releaseYear = 2026;
  this->isbn = "NO-ISBN";
}

string Libro::getTitle() const { return this->title; }
Autor Libro::getAuthor() const { return this->author; }
int Libro::getReleaseYear() const { return this->releaseYear; }
string Libro::getISBN() const { return this->isbn; }
int Libro::getStock() const { return this->stock; }

void Libro::setTitle(string title) { this->title = title; }
void Libro::setAuthor(Autor author) { this->author = author; }
void Libro::setReleaseYear(int releaseYear) { this->releaseYear = releaseYear; }
void Libro::setISBN(string isbn) { this->isbn = isbn; }

void Libro::setStock(int stock)
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

void Libro::print()
{
  cout << "Informacion del libro:" << endl;
  cout << "Titulo: " << this->title << endl;
  this->author.print();
  cout << "Anio de publicacion: " << this->releaseYear << endl;
  cout << "ISBN: " << this->isbn << endl;
  cout << "Stock: " << this->stock << endl;
}

bool Libro::operator==(const Libro &otro) const { return this->isbn == otro.isbn; }
bool Libro::operator!=(const Libro &otro) const { return !(*this == otro); }
bool Libro::operator<(const Libro &otro) const { return this->title < otro.title; }

Libro &Libro::operator+=(int cantidad)
{
  this->setStock(this->stock + cantidad);
  return *this;
}

Libro &Libro::operator-=(int cantidad)
{
  this->setStock(this->stock - cantidad);
  return *this;
}

Libro &Libro::operator++()
{
  this->setStock(this->stock + 1);
  return *this;
}

Libro Libro::operator++(int)
{
  Libro copia = *this;
  ++(*this);
  return copia;
}

bool Libro::operator!() const { return this->stock == 0; }

ostream &operator<<(ostream &os, const Libro &libro)
{
  os << "\"" << libro.title << "\" (ISBN " << libro.isbn << ", stock " << libro.stock << ")";
  return os;
}