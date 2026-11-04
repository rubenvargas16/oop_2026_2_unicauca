#pragma once
#include "Vehiculo.hpp"
#include "Variante.hpp"

class Carro : public Vehiculo{
  private:
    int pasajeros;
  public:
    Carro(string placa, int pasajeros);
    ~Carro() override;
    int getPasajeros() const;
    void setPasajeros(int pasajeros);

    string getTipo() const override;
    int cobrar() const override;
    string resumen() const override;
};