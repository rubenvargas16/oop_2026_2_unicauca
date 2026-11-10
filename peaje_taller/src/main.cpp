#include <iostream>
#include "Carro.hpp"
#include "Excepciones.hpp"

using namespace std;

int main(){
  try{
    Vehiculo *v = new Carro("3", 2);
    cout << *v << endl;
  } catch(exception &e){
    cout << e.what() << endl;
  }
  
  return 0;
}
