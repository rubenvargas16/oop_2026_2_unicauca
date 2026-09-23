#include <iostream>
#include "Autor.h"

Autor::Autor()
{
  this->nombre = "";
  this->nacionalidad = "";
  this->fechaNacimiento = "";
  this->fechaMuerte = "";
  this->librosPublicados = 1;
}

Autor::Autor(string nombre, string nacionalidad, string fechaNacimiento, string fechaMuerte, int librosPublicados)
{
  this->nombre = nombre;
  this->nacionalidad = nacionalidad;
  this->fechaNacimiento = fechaNacimiento;
  this->fechaMuerte = fechaMuerte;
  this->librosPublicados = librosPublicados;
}

void Autor::setNombre(string nombre) { this->nombre = nombre; }
void Autor::setNacionalidad(string nacionalidad) { this->nacionalidad = nacionalidad; }
void Autor::setFechaNacimiento(string fechaNacimiento) { this->fechaNacimiento = fechaNacimiento; }
void Autor::setFechaMuerte(string fechaMuerte) { this->fechaMuerte = fechaMuerte; }
void Autor::setLibrosPublicados(int librosPublicados) { this->librosPublicados = librosPublicados; }

string Autor::getNombre() { return this->nombre; }
string Autor::getNacionalidad() { return this->nacionalidad; }
string Autor::getFechaNacimiento() { return this->fechaNacimiento; }
string Autor::getFechaMuerte() { return this->fechaMuerte; }
int Autor::getLibrosPublicados() { return this->librosPublicados; }

void Autor::print()
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