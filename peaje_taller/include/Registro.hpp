#include <string>

using namespace std;

class Registro{
  private:
    string placa;
    string categoria; //CARRO
    int valorCobrado; //2312322
  public:
  Registro(string placa, string categoria, int valorCobrado);
  string getPlaca();
  string categoria();
  int valorCobrado();
};

