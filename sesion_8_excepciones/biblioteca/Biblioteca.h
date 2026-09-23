#pragma once
#include <string>
#include <vector>
#include "Estante.h"
using namespace std;
class Biblioteca
{
private:
  string nombre;
  vector<Estante *> estantes;

public:
  Biblioteca(string nombre, vector<Estante *> estantes);
  void setNombre(string nombre);
  void setEstantes(vector<Estante *> estantes);
  string getNombre();
  vector<Estante *> getEstantes();
  void agregarEstante(Estante *estante);
  void buscarLibro(string title);
};