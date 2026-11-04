#include "Carro.hpp"
#include "Excepciones.hpp"
#include "Variante.hpp"

Carro::Carro(string placa, int pasajeros) : Vehiculo(placa){
  if(pasajeros < 1){
    throw DatosInvalidosException("Un carro debe llevar por lo menos un pasajero");
  }
  this->pasajeros = pasajeros;
}

Carro::~Carro(){
  cout << "Destruyendo carro " << this->placa << endl;
}

int Carro::getPasajeros() const{
  return this->pasajeros;
}

void Carro::setPasajeros(int pasajeros){
  if(pasajeros < 1){
    throw DatosInvalidosException("Un carro debe llevar un pasajero al menos");
  }
  this->pasajeros = pasajeros;
}

string Carro::getTipo() const{
  return "CARRO";
}

int Carro::cobrar() const{
  return 10000 + 200 * UNIDAD;
}

string Carro::resumen() const {
  return Vehiculo::resumen() + ", pasajeros: " + to_string(this->pasajeros);
}