#include "Vehiculo.hpp"
#include "Excepciones.hpp"

Vehiculo::Vehiculo(string placa){
  if(placa.length() < 4){
    throw PlacaInvalidaException("Las placas no pueden tener menos de 4 caracteres");
  } else{
    this->placa = placa;
  }
}

Vehiculo::~Vehiculo(){
  cout << "Destruyendo vehiculo " << this->getPlaca() << endl;
}

string Vehiculo::getPlaca() const {
  return this->placa;
}

string Vehiculo::resumen() const {
  return this->getTipo() + " " + this->getPlaca();
}

const ostream &operator<<(ostream &os, Vehiculo &vehiculo){
  os << vehiculo.resumen();
}