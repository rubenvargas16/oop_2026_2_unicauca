#pragma once
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
  Autor();
  Autor(string nombre, string nacionalidad, string fechaNacimiento, string fechaMuerte, int librosPublicados);
  void setNombre(string nombre);
  void setNacionalidad(string nacionalidad);
  void setFechaNacimiento(string fechaNacimiento);
  void setFechaMuerte(string fechaMuerte);
  void setLibrosPublicados(int librosPublicados);
  string getNombre();
  string getNacionalidad();
  string getFechaNacimiento();
  string getFechaMuerte();
  int getLibrosPublicados();
  void print();
};