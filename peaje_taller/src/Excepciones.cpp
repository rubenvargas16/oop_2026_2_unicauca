#include "Excepciones.hpp"

PlacaInvalidaException::PlacaInvalidaException(string message){
  this->message=message;
}

const char* PlacaInvalidaException::what() const noexcept{
  return this->message.c_str();
}

DatosInvalidosException::DatosInvalidosException(string message){
  this->message = message;
}

const char* DatosInvalidosException::what() const noexcept{
  return this->message.c_str();
}
