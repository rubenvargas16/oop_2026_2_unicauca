#include <iostream>
#include "Carro.hpp"
#include "Excepciones.hpp"

using namespace std;

int main(){
  
  vector <Vehiculo*> vehiculos;
  //vector <Registros*> registros;
  
  try{
    Vehiculo *v = new Carro("EMQ111", 2);
    //Vehiculo *m = new Moto("LFE119", 220);
    int counterCarros = 0;
    int counterMotos = 0;
    int counterBus = 0;
    int counterCamion = 0;

    /*
    Caseta caseta = new Caseta(//UN OPERADOR);
    Propietario pVecino = new Propietario("123123", "Ruben", true);
    Propietario pNoVecino = new Propietario("2222", "Dario", false);

    CASO 1:
    Vehiculo *v = new Carro("ABC123", 3, &pNoVecino);
    caseta.pasoUnVehiculo(v->getPlaca(), v->getTipo(), v->cobrar())
    CASO 2:
    *v->setPropietario(&pVecino);
    caseta.pasoUnVehiculo(v->getPlaca(), v->getTipo(), v->cobrar())
    */

    for(int i=0; i<vehiculos.size(); i++){
      Vehiculo *tmp = vehiculos[i];
      if(tmp->getTipo() == "CARRO"){
        counterCarros++;
      } else if(tmp->getTipo() == "MOTO"){
        counterMotos++;
      } else if(tmp->getTipo() == "BUS"){
        counterBus++;
      } else{
        counterCamion++;
      }
    }

    vehiculos.push_back(v);

    //vehiculos.push_back(m);
    
    cout << *v << endl;
  } catch(exception &e){
    cout << e.what() << endl;
  }
  
  return 0;
}
