#pragma once
#include <string>
#include <exception>

using namespace std;

class PlacaInvalidaException : public exception{
  private:
    string message;
  public:
  PlacaInvalidaException(string message);
  const char* what() const noexcept override;
};

class DatosInvalidosException : public exception{
  private:
    string message;
  public:
    DatosInvalidosException(string message);
    const char* what() const noexcept override;
};
