#include <iostream>
#include <string>
using namespace std;

class Libro{
  private:
    string title;
    string author;
    int releaseYear;
    string isbn;
    int stock; //Cantidad
  public:
    string getTitle() const { return this->title; }
    string getAuthor() const { return this->author; }
    int getReleaseYear() const { return this->releaseYear; }
    string getISBN() const { return this->isbn; }
    int getStock() const { return this->stock; }

    void setTitle(string title){ this->title = title; }
    void setAuthor(string author){ this->author = author; }
    void setReleaseYear(int releaseYear){ this->releaseYear = releaseYear; }
    void setISBN(string isbn) { 
      this->isbn = isbn;
    }
    void setStock(int stock){
      if(stock < 0){
        this->stock = 0;
        cout << "El stock no puede ser negativo" << endl;
      } else{
        this->stock = stock;
      }
    }

    void print(){
      cout << "Información del libro:" << endl;
      cout << "Titulo: " << this->title << endl;
      cout << "Año de publicación: " << this->releaseYear << endl;
      cout << "ISBN: " << this->isbn << endl;
      cout << "Stock: " << this ->stock << endl;
    }
};

int main(){
  Libro myBook;
  myBook.setTitle("El jugador");
  myBook.setAuthor("Fiodor Dostoievsky");
  myBook.setReleaseYear(1861);
  myBook.setISBN("ISBN_FAKE");
  myBook.setStock(20);
  
  //Imprimir la data del libro
  myBook.print();
  return 0;
}