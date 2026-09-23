#include "Estante.h"

Estante::Estante(string nombre) { this->nombre = nombre; }

Estante::Estante(string nombre, vector<Libro *> libros)
{
  this->nombre = nombre;
  this->libros = libros;
}

void Estante::setNombre(string nombre) { this->nombre = nombre; }
void Estante::setVector(vector<Libro *> libros) { this->libros = libros; }
string Estante::getNombre() { return this->nombre; }
vector<Libro *> Estante::getLibros() { return this->libros; }

void Estante::agregarLibro(Libro *libro) { this->libros.push_back(libro); }

int Estante::buscarLibro(string title)
{
  for (int i = 0; i < this->libros.size(); i++)
  {
    Libro *tmp = this->libros[i];
    if (tmp->getTitle() == title)
    {
      return i;
    }
  }
  return -1;
}

Libro *Estante::operator[](int index) const { return this->libros[index]; }