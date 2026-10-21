#pragma once
#include <string>

using namespace std;

class Vehiculo
{
protected:
  string placa;
  string color;
  int modelo;

public:
  Vehiculo();  
  Vehiculo(string placa, int modelo, string color);

  void setPlaca(string placa);
  void setColor(string color);
  void setModelo(int modelo);

  string getPlaca();
  string getColor();
  int getModelo();
};
