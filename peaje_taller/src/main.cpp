#include <iostream>
#include "Carro.hpp"
#include "Excepciones.hpp"

using namespace std;

int main(){
  Vehiculo *v = new Carro("ABC123", 2);
  cout << *v << endl;
  
  return 0;
}
