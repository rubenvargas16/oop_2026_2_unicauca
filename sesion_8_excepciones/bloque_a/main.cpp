#include <iostream>
#include <stdexcept>

using namespace std;

double dividir(double a, double b)
{
  if (b == 0)
  {
    throw invalid_argument("No se puede dividir entre 0");
  }
  return a / b;
}

int main()
{
  double a = 10;
  double b = 0;

  try
  {
    cout << " B / A => 0 / 10 = " << to_string(dividir(b, a)) << endl;
    cout << " A / B => 10 / 0 = " << to_string(dividir(a, b)) << endl;
  }
  catch (const invalid_argument &e)
  {
    cout << "Algo pasó: información del error: " << e.what() << endl;
  }
}