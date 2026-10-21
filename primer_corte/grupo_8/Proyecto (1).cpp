#include <iostream>
#include <string>
#include <vector> 

using namespace std;

class Autor 
{
private:
    string nombre;
    string nacionalidad;
    string fechaNacimiento;
    string fechaMuerte;
    int librosPublicados;

public:
    Autor()
    {
        this->nombre = "";
        this->nacionalidad = "";
        this->fechaNacimiento = "";
        this->fechaMuerte = "";
        this->librosPublicados = 0;
    }

    Autor(string nombre, string nacionalidad, string fechaNacimiento, string fechaMuerte, int librosPublicados)
    {
        this->nombre = nombre;
        this->nacionalidad = nacionalidad;
        this->fechaNacimiento = fechaNacimiento;
        this->fechaMuerte = fechaMuerte;
        this->librosPublicados = librosPublicados;
    }

    string getNombre() const { return this->nombre; }
    string getNacionalidad() const { return this->nacionalidad; }
    string getFechaNacimiento() const { return this->fechaNacimiento; }
    string getFechaMuerte() const { return this->fechaMuerte; }
    int getLibrosPublicados() const { return this->librosPublicados; }

    void print() const
    {
        cout << "Informacion del Autor" << endl;
        cout << "Nombre: " << this->nombre << endl;
        cout << "Nacionalidad: " << this->nacionalidad << endl;
        cout << "Fecha de nacimiento: " << this->fechaNacimiento << endl;
        cout << "Fecha de muerte: " << this->fechaMuerte << endl;
        cout << "Libros publicados: " << this->librosPublicados << endl;
    }
};

class Libro
{
private:
    string title;
    Autor autor;
    int anio;
    string isbn;

public:
    Libro()
    {
        this->title = "";
        this->anio = 0;
        this->isbn = "";
    }

    Libro(string title, Autor autor, int anio, string isbn)
    {
        this->title = title;
        this->autor = autor;
        this->anio = anio;
        this->isbn = isbn;
    }

    string getTitle() const { return this->title; }
    Autor getAutor() const { return this->autor; }
    int getAnio() const { return this->anio; }
    string getISBN() const { return this->isbn; }

    void print() const
    {
        cout << "Informacion del libro" << endl;
        cout << "Titulo: " << this->title << endl;
        cout << "Ano: " << this->anio << endl;
        cout << "ISBN: " << this->isbn << endl;
        this->autor.print();
    }
};

class Ejemplar
{
private:
    int cantidad;
    Libro* libro;

public:
    Ejemplar()
    {
        this->cantidad = 0;
        this->libro = nullptr;
    }

    Ejemplar(int cantidad, Libro* libro)
    {
        this->cantidad = cantidad;
        this->libro = libro;
    }

    int getCantidad() const { return this->cantidad; }
    Libro* getLibro() const { return this->libro; }

    void setCantidad(int cantidad) { this->cantidad = cantidad; }
    void setLibro(Libro* libro) { this->libro = libro; }

    void print() const
    {
        cout << "Informacion del ejemplar" << endl;
        cout << "Cantidad disponible: " << this->cantidad << endl;
        if (this->libro != nullptr)
        {
            this->libro->print();
        }
    }
};

class Estante
{
private:
    string nombre;
    vector<Ejemplar*> ejemplares;

public:
    Estante()
    {
        this->nombre = "";
    }

    Estante(string nombre)
    {
        this->nombre = nombre;
    }

    string getNombre() const { return this->nombre; }
    vector<Ejemplar*> getEjemplares() const { return this->ejemplares; }

    void agregarEjemplar(Ejemplar* e)
    {
        this->ejemplares.push_back(e);
    }
};

class Biblioteca
{
private:
    string nombre;
    vector<Estante> estantes;

public:
    Biblioteca()
    {
        this->nombre = "";
    }

    Biblioteca(string nombre)
    {
        this->nombre = nombre;
    }

    string getNombre() const { return this->nombre; }
    vector<Estante> getEstantes() const { return this->estantes; }

    void agregarEstante(Estante e)
    {
        this->estantes.push_back(e);
    }

    Estante* obtenerEstante(int indice)
    {
        if (indice < 0 || indice >= (int)this->estantes.size())
        {
            return nullptr;
        }
        return &this->estantes[indice];
    }

    void listarInventario()
    {
        cout << "INVENTARIO DE LA BIBLIOTECA: " << this->nombre << endl;
        
        bool vacio = true;

        for (size_t i = 0; i < this->estantes.size(); i++)
        {
            vector<Ejemplar*> ejemplares = this->estantes[i].getEjemplares();

            for (size_t j = 0; j < ejemplares.size(); j++)
            {
                Ejemplar* ej = ejemplares[j];

                if (ej != nullptr && ej->getLibro() != nullptr)
                {
                    vacio = false;
                    cout << "Estanteria: " << this->estantes[i].getNombre() << endl;
                    cout << "Libro: " << ej->getLibro()->getTitle() << endl;
                    cout << "ISBN: " << ej->getLibro()->getISBN() << endl;
                    cout << "Copias disponibles: " << ej->getCantidad() << endl;
                    cout << "----------------------------------------" << endl;
                }
            }
        }

        if (vacio)
        {
            cout << "No hay libros en esta biblioteca." << endl;
        }
    }

    int contarInventario()
    {
        int total = 0;

        for (size_t i = 0; i < this->estantes.size(); i++)
        {
            vector<Ejemplar*> ejemplares = this->estantes[i].getEjemplares();

            for (size_t j = 0; j < ejemplares.size(); j++)
            {
                if (ejemplares[j] != nullptr)
                {
                    total += ejemplares[j]->getCantidad();
                }
            }
        }

        return total;
    }

    bool actualizarInventario(string isbn, int nuevaCantidad)
    {
        bool actualizado = false;

        for (size_t i = 0; i < this->estantes.size(); i++)
        {
            vector<Ejemplar*> ejemplares = this->estantes[i].getEjemplares();

            for (size_t j = 0; j < ejemplares.size(); j++)
            {
                Ejemplar* ej = ejemplares[j];

                if (ej != nullptr && ej->getLibro() != nullptr)
                {
                    if (ej->getLibro()->getISBN() == isbn)
                    {
                        ej->setCantidad(nuevaCantidad);
                        actualizado = true;
                        cout << "\nInventario actualizado correctamente." << endl;
                        cout << "Libro: " << ej->getLibro()->getTitle() << endl;
                        cout << "Nueva cantidad: " << ej->getCantidad() << endl;
                    }
                }
            }
        }

        return actualizado;
    }
};

class Bibliotecas
{
private:
    vector<Biblioteca> bibliotecas;

public:
    Bibliotecas() {}

    void agregarBiblioteca(Biblioteca b)
    {
        this->bibliotecas.push_back(b);
    }

    vector<Biblioteca>& getBibliotecas()
    {
        return this->bibliotecas;
    }

    Biblioteca* obtenerBiblioteca(int indice)
    {
        if (indice < 0 || indice >= (int)this->bibliotecas.size())
        {
            return nullptr;
        }
        return &this->bibliotecas[indice];
    }

    void listarBibliotecas()
    {
        if (this->bibliotecas.empty())
        {
            cout << "No hay bibliotecas registradas." << endl;
            return;
        }

        cout << "LISTA DE BIBLIOTECAS" << endl;
        for (size_t i = 0; i < this->bibliotecas.size(); i++)
        {
            cout << i << ". " << this->bibliotecas[i].getNombre() << endl;
        }
    }

    void buscarLibro()
    {
        if (this->bibliotecas.empty())
        {
            cout << "No hay bibliotecas registradas." << endl;
            return;
        }

        string tituloBuscado;
        cout << "\nIngrese el titulo del libro a buscar: ";
        getline(cin, tituloBuscado);

        bool encontrado = false;
        
        cout << "DISPONIBILIDAD PARA: " << tituloBuscado << endl;
        
        for (size_t i = 0; i < this->bibliotecas.size(); i++)
        {
            vector<Estante> estantes = this->bibliotecas[i].getEstantes();

            for (size_t j = 0; j < estantes.size(); j++)
            {
                vector<Ejemplar*> ejemplares = estantes[j].getEjemplares();

                for (size_t k = 0; k < ejemplares.size(); k++)
                {
                    Ejemplar* ej = ejemplares[k];
                    if (ej != nullptr && ej->getLibro() != nullptr)
                    {
                        if (ej->getLibro()->getTitle() == tituloBuscado && ej->getCantidad() > 0)
                        {
                            encontrado = true;
                            cout << "Biblioteca: " << this->bibliotecas[i].getNombre() << endl;
                            cout << "Estanteria: " << estantes[j].getNombre() << endl;
                            cout << "ISBN: " << ej->getLibro()->getISBN() << endl;
                            cout << "Copias disponibles: " << ej->getCantidad() << endl;
                            cout << "----------------------------------------" << endl;
                        }
                    }
                }
            }
        }

        if (!encontrado)
        {
            cout << "No se encontraron ejemplares disponibles con el titulo: " << tituloBuscado << endl;
        }
    }

    void listarInventario()
    {
        if (this->bibliotecas.empty())
        {
            cout << "No hay bibliotecas registradas." << endl;
            return;
        }

        cout << "\n¿De que biblioteca desea ver el inventario?" << endl;
        listarBibliotecas();

        int seleccion;
        cout << "Seleccione una biblioteca: ";
        cin >> seleccion;

        if (seleccion < 0 || seleccion >= (int)this->bibliotecas.size())
        {
            cout << "Biblioteca invalida." << endl;
            return;
        }

        this->bibliotecas[seleccion].listarInventario();
    }

    void contarInventario()
    {
        if (this->bibliotecas.empty())
        {
            cout << "No hay bibliotecas registradas." << endl;
            return;
        }

        cout << "\n¿De que biblioteca desea contar el inventario?" << endl;
        listarBibliotecas();

        int seleccion;
        cout << "Seleccione una biblioteca: ";
        cin >> seleccion;

        if (seleccion < 0 || seleccion >= (int)this->bibliotecas.size())
        {
            cout << "Biblioteca invalida." << endl;
            return;
        }

        int total = this->bibliotecas[seleccion].contarInventario();

        cout << "\nBiblioteca: " << this->bibliotecas[seleccion].getNombre() << endl;
        cout << "Total de copias: " << total << endl;
    }

    void actualizarInventario()
    {
        if (this->bibliotecas.empty())
        {
            cout << "No hay bibliotecas registradas." << endl;
            return;
        }

        cout << "\n¿En que biblioteca desea actualizar el inventario?" << endl;
        listarBibliotecas();

        int bibliotecaSeleccionada;
        cout << "Seleccione una biblioteca: ";
        cin >> bibliotecaSeleccionada;

        if (bibliotecaSeleccionada < 0 || bibliotecaSeleccionada >= (int)this->bibliotecas.size())
        {
            cout << "Biblioteca invalida." << endl;
            return;
        }

        cin.ignore(); 

        string isbn;
        cout << "Ingrese el ISBN del libro: ";
        getline(cin, isbn);

        int nuevaCantidad;
        cout << "Ingrese la nueva cantidad: ";
        cin >> nuevaCantidad;

        bool actualizado = this->bibliotecas[bibliotecaSeleccionada].actualizarInventario(isbn, nuevaCantidad);

        if (!actualizado)
        {
            cout << "\nEl libro con ISBN " << isbn << " no se encuentra en esta biblioteca." << endl;
        }
    }
};

class Estudiante
{
private:
    string nombre;
    string codigo;

public:
    Estudiante()
    {
        this->nombre = "";
        this->codigo = "";
    }

    Estudiante(string nombre, string codigo)
    {
        this->nombre = nombre;
        this->codigo = codigo;
    }

    string getNombre() const { return this->nombre; }
    string getCodigo() const { return this->codigo; }

    void print() const
    {
        cout << "Informacion del estudiante" << endl;
        cout << "Nombre: " << this->nombre << endl;
        cout << "Codigo: " << this->codigo << endl;
    }
};

class Prestamo
{
private:
    string fecha;
    Ejemplar* ejemplar;
    Estudiante* estudiante;

public:
    Prestamo()
    {
        this->fecha = "";
        this->ejemplar = nullptr;
        this->estudiante = nullptr;
    }

    Prestamo(string fecha, Ejemplar* ejemplar, Estudiante* estudiante)
    {
        this->fecha = fecha;
        this->ejemplar = ejemplar;
        this->estudiante = estudiante;
    }

    string getFecha() const { return this->fecha; }
    Ejemplar* getEjemplar() const { return this->ejemplar; }
    Estudiante* getEstudiante() const { return this->estudiante; }

    void print() const
    {
        cout << "Informacion del prestamo" << endl;
        cout << "Fecha: " << this->fecha << endl;

        if (this->estudiante != nullptr)
        {
            this->estudiante->print();
        }

        if (this->ejemplar != nullptr)
        {
            this->ejemplar->print();
        }
    }
};

void mostrarMenu()
{
    cout << " SISTEMA BLIBLIOTECAS" << endl;
    cout << "1. Crear autor" << endl;
    cout << "2. Crear libro" << endl;
    cout << "3. Crear ejemplar" << endl;
    cout << "4. Crear estudiante" << endl;
    cout << "5. Crear biblioteca (adicional)" << endl;
    cout << "6. Crear estante" << endl;
    cout << "7. Crear prestamo" << endl;
    cout << "8. Buscar disponibilidad por TITULO" << endl;
    cout << "9. Listar inventario" << endl;
    cout << "10. Contar inventario" << endl;
    cout << "11. Actualizar inventario por ISBN" << endl;
    cout << "12. Listar bibliotecas" << endl;
    cout << "13. Listar prestamos por biblioteca" << endl;
    cout << "14. Listar prestamos por estudiante" << endl;
    cout << "15. Salir" << endl;
}

void crearAutor(vector<Autor*>& autores)
{
    string nombre, nacionalidad, fechaNacimiento, fechaMuerte;
    int librosPublicados;

    cout << "Nombre: ";
    getline(cin, nombre);

    cout << "Nacionalidad: ";
    getline(cin, nacionalidad);

    cout << "Fecha de nacimiento: ";
    getline(cin, fechaNacimiento);

    cout << "Fecha de muerte: ";
    getline(cin, fechaMuerte);

    cout << "Libros publicados: ";
    cin >> librosPublicados;

    Autor* nuevoAutor = new Autor(nombre, nacionalidad, fechaNacimiento, fechaMuerte, librosPublicados);
    autores.push_back(nuevoAutor);

    cout << "\nAutor creado correctamente." << endl;
    nuevoAutor->print();
}

void crearLibro(vector<Autor*>& autores, vector<Libro*>& libros)
{
    if (autores.empty())
    {
        cout << "Primero debes crear un autor." << endl;
        return;
    }

    string titulo, isbn;
    int autorSeleccionado, anio;

    cout << "\nAutores disponibles:" << endl;
    for (size_t i = 0; i < autores.size(); i++)
    {
        cout << i << ". " << autores[i]->getNombre() << endl;
    }

    cout << "Seleccione el autor: ";
    cin >> autorSeleccionado;

    if (autorSeleccionado < 0 || autorSeleccionado >= (int)autores.size())
    {
        cout << "Autor invalido." << endl;
        return;
    }

    cin.ignore(); 

    cout << "Titulo: ";
    getline(cin, titulo);

    cout << "Ano de publicacion: ";
    cin >> anio;

    cin.ignore(); 

    cout << "ISBN: ";
    getline(cin, isbn);

    Libro* nuevoLibro = new Libro(titulo, *autores[autorSeleccionado], anio, isbn);
    libros.push_back(nuevoLibro);

    cout << "\nLibro creado correctamente." << endl;
    nuevoLibro->print();
}

void crearEjemplar(vector<Libro*>& libros, vector<Ejemplar*>& ejemplares, Bibliotecas& red)
{
    if (libros.empty())
    {
        cout << "Primero debes crear un libro." << endl;
        return;
    }

    if (red.getBibliotecas().empty())
    {
        cout << "Primero debes crear una biblioteca." << endl;
        return;
    }

    int libroSeleccionado, cantidad;

    cout << "\nLibros disponibles:" << endl;
    for (size_t i = 0; i < libros.size(); i++)
    {
        cout << i << ". " << libros[i]->getTitle() << " - ISBN: " << libros[i]->getISBN() << endl;
    }

    cout << "Seleccione el libro: ";
    cin >> libroSeleccionado;

    if (libroSeleccionado < 0 || libroSeleccionado >= (int)libros.size())
    {
        cout << "Libro invalido." << endl;
        return;
    }

    cout << "Cantidad de copias: ";
    cin >> cantidad;

    cout << "\n¿En que biblioteca desea guardar el ejemplar?" << endl;
    red.listarBibliotecas();

    int bibliotecaSeleccionada;
    cout << "Seleccione la biblioteca: ";
    cin >> bibliotecaSeleccionada;

    Biblioteca* biblioteca = red.obtenerBiblioteca(bibliotecaSeleccionada);
    if (biblioteca == nullptr)
    {
        cout << "Biblioteca invalida." << endl;
        return;
    }

    vector<Estante> estantes = biblioteca->getEstantes();
    if (estantes.empty())
    {
        cout << "Esta biblioteca no tiene estantes." << endl;
        return;
    }

    cout << "\nEstantes disponibles:" << endl;
    for (size_t i = 0; i < estantes.size(); i++)
    {
        cout << i << ". " << estantes[i].getNombre() << endl;
    }

    int estanteSeleccionado;
    cout << "Seleccione el estante: ";
    cin >> estanteSeleccionado;

    Estante* estante = biblioteca->obtenerEstante(estanteSeleccionado);
    if (estante == nullptr)
    {
        cout << "Estante invalido." << endl;
        return;
    }

    Ejemplar* nuevoEjemplar = new Ejemplar(cantidad, libros[libroSeleccionado]);
    ejemplares.push_back(nuevoEjemplar);
    estante->agregarEjemplar(nuevoEjemplar);
    cout << "\nEjemplar creado y agregado al estante correctamente." << endl;
}

void crearEstudiante(vector<Estudiante*>& estudiantes)
{
    string nombre, codigo;

    cout << "Nombre del estudiante: ";
    getline(cin, nombre);

    cout << "Codigo del estudiante: ";
    getline(cin, codigo);

    Estudiante* nuevoEstudiante = new Estudiante(nombre, codigo);
    estudiantes.push_back(nuevoEstudiante);

    cout << "\nEstudiante creado correctamente." << endl;
}

void crearBiblioteca(Bibliotecas& red)
{
    string nombre;

    cout << "Nombre de la biblioteca: ";
    getline(cin, nombre);

    Biblioteca nuevaBiblioteca(nombre);
    red.agregarBiblioteca(nuevaBiblioteca);

    cout << "Biblioteca creada correctamente." << endl;
}

void crearEstante(Bibliotecas& red)
{
    if (red.getBibliotecas().empty())
    {
        cout << "Primero debes crear una biblioteca." << endl;
        return;
    }

    string nombre;
    cout << "Nombre del estante: ";
    getline(cin, nombre);

    cout << "\n¿En que biblioteca desea crear el estante?" << endl;
    red.listarBibliotecas();

    int bibliotecaSeleccionada;
    cout << "Seleccione la biblioteca: ";
    cin >> bibliotecaSeleccionada;

    Biblioteca* biblioteca = red.obtenerBiblioteca(bibliotecaSeleccionada);
    if (biblioteca == nullptr)
    {
        cout << "Biblioteca invalida." << endl;
        return;
    }

    Estante nuevoEstante(nombre);
    biblioteca->agregarEstante(nuevoEstante);

    cout << "Estante creado correctamente." << endl;
}

void crearPrestamo(vector<Estudiante*>& estudiantes, vector<Ejemplar*>& ejemplares, vector<Prestamo*>& prestamos)
{
    if (ejemplares.empty())
    {
        cout << "Primero debes crear un ejemplar." << endl;
        return;
    }

    if (estudiantes.empty())
    {
        cout << "Primero debes crear un estudiante." << endl;
        return;
    }

    bool hayDisponibles = false;
    for (Ejemplar* ejemplar : ejemplares)
    {
        if (ejemplar != nullptr && ejemplar->getCantidad() > 0)
        {
            hayDisponibles = true;
            break;
        }
    }

    if (!hayDisponibles)
    {
        cout << "No hay ejemplares disponibles para prestar." << endl;
        return;
    }

    string fecha;
    int ejemplarSeleccionado, estudianteSeleccionado;

    cout << "Fecha del prestamo: ";
    getline(cin, fecha);

    cout << "\nEjemplares disponibles:" << endl;
    for (size_t i = 0; i < ejemplares.size(); i++)
    {
        if (ejemplares[i] == nullptr || ejemplares[i]->getCantidad() <= 0)
        {
            continue;
        }

        cout << i << ". ";
        if (ejemplares[i]->getLibro() != nullptr)
        {
            cout << ejemplares[i]->getLibro()->getTitle() << " - ISBN: " << ejemplares[i]->getLibro()->getISBN();
        }
        else
        {
            cout << "Sin libro";
        }

        cout << " - Copias disponibles: " << ejemplares[i]->getCantidad() << endl;
    }

    cout << "Seleccione el ejemplar: ";
    cin >> ejemplarSeleccionado;

    if (ejemplarSeleccionado < 0 || ejemplarSeleccionado >= (int)ejemplares.size() || ejemplares[ejemplarSeleccionado] == nullptr)
    {
        cout << "Ejemplar invalido." << endl;
        return;
    }

    if (ejemplares[ejemplarSeleccionado]->getCantidad() <= 0)
    {
        cout << "El ejemplar seleccionado no tiene copias disponibles." << endl;
        return;
    }

    cout << "\nEstudiantes disponibles:" << endl;
    for (size_t i = 0; i < estudiantes.size(); i++)
    {
        cout << i << ". " << estudiantes[i]->getNombre() << " - Codigo: " << estudiantes[i]->getCodigo() << endl;
    }

    cout << "Seleccione el estudiante: ";
    cin >> estudianteSeleccionado;

    if (estudianteSeleccionado < 0 || estudianteSeleccionado >= (int)estudiantes.size())
    {
        cout << "Estudiante invalido." << endl;
        return;
    }

    Prestamo* nuevoPrestamo = new Prestamo(fecha, ejemplares[ejemplarSeleccionado], estudiantes[estudianteSeleccionado]);
    prestamos.push_back(nuevoPrestamo);

    ejemplares[ejemplarSeleccionado]->setCantidad(ejemplares[ejemplarSeleccionado]->getCantidad() - 1);

    cout << "\nPrestamo creado correctamente." << endl;
    cout << "Copias disponibles restantes: " << ejemplares[ejemplarSeleccionado]->getCantidad() << endl;
}

void listarPrestamosBiblioteca(Bibliotecas& red, vector<Prestamo*>& prestamos)
{
    if (red.getBibliotecas().empty())
    {
        cout << "No hay bibliotecas registradas." << endl;
        return;
    }

    cout << "\n¿De que biblioteca desea ver los prestamos?" << endl;
    red.listarBibliotecas();

    int bibliotecaSeleccionada;
    cout << "Seleccione una biblioteca: ";
    cin >> bibliotecaSeleccionada;

    Biblioteca* biblioteca = red.obtenerBiblioteca(bibliotecaSeleccionada);
    if (biblioteca == nullptr)
    {
        cout << "Biblioteca invalida." << endl;
        return;
    }

    vector<Estante> estantes = biblioteca->getEstantes();
    bool encontrado = false;

    cout << "PRESTAMOS DE LA BIBLIOTECA" << endl;
    cout << "Biblioteca: " << biblioteca->getNombre() << endl;

    for (size_t i = 0; i < estantes.size(); i++)
    {
        vector<Ejemplar*> ejemplaresEstante = estantes[i].getEjemplares();

        for (size_t j = 0; j < ejemplaresEstante.size(); j++)
        {
            Ejemplar* ejemplar = ejemplaresEstante[j];
            if (ejemplar == nullptr) continue;

            for (Prestamo* prestamo : prestamos)
            {
                if (prestamo == nullptr || prestamo->getEjemplar() != ejemplar)
                {
                    continue;
                }

                encontrado = true;
                cout << "\nEstanteria: " << estantes[i].getNombre() << endl;

                if (ejemplar->getLibro() != nullptr)
                {
                    cout << "Libro: " << ejemplar->getLibro()->getTitle() << endl;
                    cout << "ISBN: " << ejemplar->getLibro()->getISBN() << endl;
                }

                if (prestamo->getEstudiante() != nullptr)
                {
                    cout << "Estudiante: " << prestamo->getEstudiante()->getNombre() << endl;
                    cout << "Codigo: " << prestamo->getEstudiante()->getCodigo() << endl;
                }

                cout << "Fecha del prestamo: " << prestamo->getFecha() << endl;
                cout << "----------------------------------------" << endl;
            }
        }
    }

    if (!encontrado)
    {
        cout << "\nNo hay ejemplares actualmente prestados en esta biblioteca." << endl;
    }
}

void listarPrestamosEstudiante(vector<Estudiante*>& estudiantes, vector<Prestamo*>& prestamos)
{
    if (estudiantes.empty())
    {
        cout << "No hay estudiantes registrados." << endl;
        return;
    }

    cout << "\nEstudiantes registrados:" << endl;
    for (size_t i = 0; i < estudiantes.size(); i++)
    {
        cout << i << ". " << estudiantes[i]->getNombre() << " - Codigo: " << estudiantes[i]->getCodigo() << endl;
    }

    int estudianteSeleccionado;
    cout << "Seleccione el estudiante: ";
    cin >> estudianteSeleccionado;

    if (estudianteSeleccionado < 0 || estudianteSeleccionado >= (int)estudiantes.size())
    {
        cout << "Estudiante invalido." << endl;
        return;
    }

    Estudiante* estudiante = estudiantes[estudianteSeleccionado];
    bool encontrado = false;

    cout << "PRESTAMOS DEL ESTUDIANTE" << endl;
    cout << "Estudiante: " << estudiante->getNombre() << endl;
    cout << "Codigo: " << estudiante->getCodigo() << endl;

    for (Prestamo* prestamo : prestamos)
    {
        if (prestamo == nullptr || prestamo->getEstudiante() != estudiante)
        {
            continue;
        }

        encontrado = true;
        Ejemplar* ejemplar = prestamo->getEjemplar();

        if (ejemplar != nullptr && ejemplar->getLibro() != nullptr)
        {
            cout << "\nLibro: " << ejemplar->getLibro()->getTitle() << endl;
            cout << "ISBN: " << ejemplar->getLibro()->getISBN() << endl;
        }

        cout << "Fecha del prestamo: " << prestamo->getFecha() << endl;
        cout << "----------------------------------------" << endl;
    }

    if (!encontrado)
    {
        cout << "\nEl estudiante no tiene libros actualmente en prestamo." << endl;
    }
}

int main()
{
    vector<Autor*> autores;
    vector<Libro*> libros;
    vector<Ejemplar*> ejemplares;
    vector<Estudiante*> estudiantes;
    vector<Prestamo*> prestamos;

    Bibliotecas red;

    red.agregarBiblioteca(Biblioteca("Biblioteca Central José María Serrano"));
    red.agregarBiblioteca(Biblioteca("Biblioteca El Carmen"));
    red.agregarBiblioteca(Biblioteca("Biblioteca de Ciencias de la Salud"));
    red.agregarBiblioteca(Biblioteca("Biblioteca de Ciencias Agropecuarias"));
    red.agregarBiblioteca(Biblioteca("Biblioteca de Artes / Música"));

    int opcion;

    do
    {
        mostrarMenu();
        cout << "\nSeleccione una opcion: ";
        cin >> opcion;

        cin.ignore(); 

        switch (opcion)
        {
        case 1:
            crearAutor(autores);
            break;
        case 2:
            crearLibro(autores, libros);
            break;
        case 3:
            crearEjemplar(libros, ejemplares, red);
            break;
        case 4:
            crearEstudiante(estudiantes);
            break;
        case 5:
            crearBiblioteca(red);
            break;
        case 6:
            crearEstante(red);
            break;
        case 7:
            crearPrestamo(estudiantes, ejemplares, prestamos);
            break;
        case 8:
            red.buscarLibro();
            break;
        case 9:
            red.listarInventario();
            break;
        case 10:
            red.contarInventario();
            break;
        case 11:
            red.actualizarInventario();
            break;
        case 12:
            red.listarBibliotecas();
            break;
        case 13:
            listarPrestamosBiblioteca(red, prestamos);
            break;
        case 14:
            listarPrestamosEstudiante(estudiantes, prestamos);
            break;
        case 15:
            cout << "Saliendo del programa..." << endl;
            break;
        default:
            cout << "Opcion invalida." << endl;
            break;
        }

    } while (opcion != 15);

    return 0;
}