#include <iostream>
#include "Biblioteca.h"

Biblioteca::Biblioteca(string nombre, vector<Estante *> estantes)
{
  this->nombre = nombre;
  this->estantes = estantes;
}

void Biblioteca::setNombre(string nombre) { this->nombre = nombre; }
void Biblioteca::setEstantes(vector<Estante *> estantes) { this->estantes = estantes; }
string Biblioteca::getNombre() { return this->nombre; }
vector<Estante *> Biblioteca::getEstantes() { return this->estantes; }

void Biblioteca::agregarEstante(Estante *estante) { this->estantes.push_back(estante); }

void Biblioteca::buscarLibro(string title)
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
         << " en la posicion " << indexLibro << endl;
  }
  else
  {
    cout << "El libro no esta en la biblioteca" << endl;
  }
}