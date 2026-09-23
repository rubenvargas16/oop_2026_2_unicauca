#pragma once
#include <string>
#include <vector>
#include "Libro.h"
using namespace std;
class Estante
{
private:
  string nombre;
  vector<Libro *> libros;

public:
  Estante(string nombre);
  Estante(string nombre, vector<Libro *> libros);
  void setNombre(string nombre);
  void setVector(vector<Libro *> libros);
  string getNombre();
  vector<Libro *> getLibros();
  void agregarLibro(Libro *libro);
  int buscarLibro(string title);
  Libro *operator[](int index) const;
};