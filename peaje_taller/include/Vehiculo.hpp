#pragma once
#include <string>
#include <iostream>

using namespace std;

class Vehiculo{
  protected:
    string placa;
  public:
    Vehiculo(string placa);
    virtual ~Vehiculo();

    string getPlaca() const;
    //virtual <tipo_dato> <nombre_funcion>([...args]) const = 0;

    virtual string getTipo() const = 0; //SOY UN CARRO, SOY UNA MOTO, "CARRO", "MOTO"
    virtual int cobrar() const = 0; 
    virtual string resumen() const;
};

ostream &operator<<(ostream &os, const Vehiculo &vehiculo);
