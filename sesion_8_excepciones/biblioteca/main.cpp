#include "Biblioteca.h"

int main()
{
  Autor autor("Fiodor Dostoievsky", "Rusia", "1700-01-01", "1763-01-01", 10);
  Libro libro("El jugador", autor, 5);

  Estante estante("Estante A");
  estante.agregarLibro(&libro);

  vector<Estante> estantes;
  estantes.push_back(estante);
  Biblioteca biblioteca("Biblioteca Central", estantes);

  libro.print();
  cout << libro << endl;

  biblioteca.buscarLibro("El jugador");
  biblioteca.buscarLibro("No existe");

  return 0;
}