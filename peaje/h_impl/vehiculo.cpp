#include "vehiculo.hpp"

//Constructores
Vehiculo::Vehiculo(){
  this->placa="";
  this->color="";
  this->modelo=1900;
}
Vehiculo::Vehiculo(string placa, int modelo, string color){
  this->placa=placa;
  this->modelo=modelo;
  this->color=color;
}
//Setters y getters
string Vehiculo::getColor(){ return this->color; }
string Vehiculo::getPlaca(){ return this->placa; }
int Vehiculo::getModelo(){ return this->modelo; }

void Vehiculo::setColor(string color){ this->color = color; }
void Vehiculo::setPlaca(string placa) { this->placa = placa; }
void Vehiculo::setModelo(int modelo){ this->modelo = modelo; }