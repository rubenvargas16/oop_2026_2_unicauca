#pragma once
#include <string>
#include <iostream>
#include "Autor.h"
using namespace std;
class Libro
{
private:
  string title;
  Autor author;
  int releaseYear;
  string isbn;
  int stock;

public:
  Libro();
  Libro(string title, Autor author, int stock);
  Libro(string title, Autor author);
  string getTitle() const;
  Autor getAuthor() const;
  int getReleaseYear() const;
  string getISBN() const;
  int getStock() const;
  void setTitle(string title);
  void setAuthor(Autor author);
  void setReleaseYear(int releaseYear);
  void setISBN(string isbn);
  void setStock(int stock);
  void print();
  bool operator==(const Libro &otro) const;
  bool operator!=(const Libro &otro) const;
  bool operator<(const Libro &otro) const;
  Libro &operator+=(int cantidad);
  Libro &operator-=(int cantidad);
  Libro &operator++();
  Libro operator++(int);
  bool operator!() const;
  friend ostream &operator<<(ostream &os, const Libro &libro);
};
ostream &operator<<(ostream &os, const Libro &libro);