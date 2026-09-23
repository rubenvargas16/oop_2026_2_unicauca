#pragma once
#include <string>
#include <exception>

using namespace std;

class StockInvalidException : public exception{
  private:
    string message;
  public:
    StockInvalidException(string mensaje);
    const char *what() const noexcept override;
};

class LibroNotFoundException : public exception{
  private:
    string mensaje;
  public:
    LibroNotFoundException(string mensaje);
    const char* what() const noexcept override;
};