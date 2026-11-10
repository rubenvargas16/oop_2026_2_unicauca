#include <iostream>
#include "Carro.hpp"
#include "Excepciones.hpp"

using namespace std;

int main(){
  vector <Vehiculo*> vehiculos;
  
  try{
    Vehiculo *v = new Carro("EMQ111", 2);
    //Vehiculo *m = new Moto("LFE119", 220);
    int counterCarros = 0;
    int counterMotos = 0;
    int counterBus = 0;
    int counterCamion = 0;

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
