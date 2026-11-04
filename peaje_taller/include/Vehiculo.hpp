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
    virtual string getTipo() const = 0;
    virtual int cobrar() const = 0;
    virtual string resumen() const;
};

ostream &operator<<(ostream &os, const Vehiculo &vehiculo);