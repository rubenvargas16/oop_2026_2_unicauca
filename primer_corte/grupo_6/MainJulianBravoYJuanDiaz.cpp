#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <limits>
#include <algorithm>


/*Codigo creado por Juan David Diaz y Julian Andrey Bravo*/
using namespace std;

// Declaraciones adelantadas
class Libro;
class Biblioteca;
class Estanteria;
class Estudiante;

void limpiarBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

class Autor
{
private:
    string nombre;
    string nacionalidad;
    vector<shared_ptr<Libro>> librosPublicados;

public:
    Autor(string nombre, string nacionalidad) : nombre(nombre), nacionalidad(nacionalidad) {}

    string getNombre() const { return nombre; }
    string getNacionalidad() const { return nacionalidad; }

    void anadirLibro(shared_ptr<Libro> lib)
    {
        librosPublicados.push_back(lib);
    }

    void imprimir() const
    {
        cout << "====== Datos del Autor ======" << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Nacionalidad: " << nacionalidad << endl;
    }

    void imprimirLibros() const;
};

class Ejemplar
{
private:
    shared_ptr<Libro> libro;
    Estanteria *estanteria; // Referencia débil sin gestión de pertenencia
    int codigo;
    Estudiante *estudianteConPosesion;

public:
    Ejemplar(shared_ptr<Libro> libro, int cod)
        : libro(libro), estanteria(nullptr), codigo(cod), estudianteConPosesion(nullptr) {}

    shared_ptr<Libro> getLibro() const { return libro; }
    Estanteria *getEstanteria() const { return estanteria; }
    int getCodigo() const { return codigo; }
    Estudiante *getEstudiante() const { return estudianteConPosesion; }

    void setEstanteria(Estanteria *est) { estanteria = est; }
    void setEstudiante(Estudiante *est) { estudianteConPosesion = est; }

    void imprimir() const;
};

class Libro : public enable_shared_from_this<Libro>
{
private:
    string titulo;
    string fecha;
    string ISBN;
    shared_ptr<Autor> autor;
    vector<shared_ptr<Ejemplar>> ejemplaresDisponibles;

public:
    Libro(string titulo, string fecha, string ISBN, shared_ptr<Autor> autor)
        : titulo(titulo), fecha(fecha), ISBN(ISBN), autor(autor) {}

    string getTitulo() const { return titulo; }
    string getFecha() const { return fecha; }
    string getISBN() const { return ISBN; }
    shared_ptr<Autor> getAutor() const { return autor; }

    shared_ptr<Ejemplar> crearEjemplar(int codigo)
    {
        auto ejem = make_shared<Ejemplar>(shared_from_this(), codigo);
        ejemplaresDisponibles.push_back(ejem);
        return ejem;
    }

    void imprimir() const
    {
        cout << "==== Datos del Libro ====" << endl;
        cout << "Titulo: " << titulo << endl;
        cout << "Fecha: " << fecha << endl;
        cout << "ISBN: " << ISBN << endl;
        if (autor)
            cout << "Autor: " << autor->getNombre() << endl;
    }

    void imprimirEjemplares() const
    {
        for (size_t i = 0; i < ejemplaresDisponibles.size(); ++i)
        {
            cout << "----------------------------" << endl;
            cout << "Ejemplar " << i + 1 << ":" << endl;
            ejemplaresDisponibles[i]->imprimir();
        }
    }
};

void Autor::imprimirLibros() const
{
    for (size_t i = 0; i < librosPublicados.size(); ++i)
    {
        cout << "---------------------------" << endl;
        cout << i + 1 << " : " << endl;
        librosPublicados[i]->imprimir();
    }
}

class Estanteria
{
private:
    string nombre;
    int numero;
    vector<shared_ptr<Ejemplar>> ejemplares;
    Biblioteca *biblio;

public:
    Estanteria(string nombre, int numero) : nombre(nombre), numero(numero), biblio(nullptr) {}

    void setBiblioteca(Biblioteca *bib) { biblio = bib; }
    string getNombre() const { return nombre; }
    int getNumero() const { return numero; }
    Biblioteca *getBiblioteca() const { return biblio; }
    const vector<shared_ptr<Ejemplar>> &getEjemplares() const { return ejemplares; }

    void anadirEjemplar(shared_ptr<Ejemplar> ejem)
    {
        ejem->setEstanteria(this);
        ejemplares.push_back(ejem);
    }

    int buscarEjemplar(int cod) const
    {
        for (size_t i = 0; i < ejemplares.size(); ++i)
        {
            if (ejemplares[i]->getCodigo() == cod)
                return static_cast<int>(i);
        }
        return -1;
    }

    shared_ptr<Ejemplar> getEjemplarPorCodigo(int codi)
    {
        int idx = buscarEjemplar(codi);
        if (idx == -1)
            return nullptr;
        return ejemplares[idx];
    }

    void quitarEjemplar(int cod)
    {
        int idx = buscarEjemplar(cod);
        if (idx != -1)
        {
            ejemplares[idx]->setEstanteria(nullptr);
            ejemplares.erase(ejemplares.begin() + idx);
        }
    }

    void imprimirEstanteria() const
    {
        cout << "Estanteria [ID: " << numero << "] - Nombre: " << nombre << endl;
    }

    void imprimirEjemplares() const
    {
        for (size_t i = 0; i < ejemplares.size(); ++i)
        {
            cout << "  Ejemplar #" << i + 1 << ":" << endl;
            ejemplares[i]->imprimir();
        }
    }
};

class Biblioteca
{
private:
    string nombre;
    int codigo;
    vector<Estanteria> estantes;

public:
    Biblioteca(string nombre, int codigo) : nombre(nombre), codigo(codigo) {}

    string getNombre() const { return nombre; }
    int getCodigo() const { return codigo; }

    void anadirEstante(const Estanteria &est)
    {
        estantes.push_back(est);
        estantes.back().setBiblioteca(this);
    }

    vector<Estanteria> &getEstantes() { return estantes; }

    int buscarEstantePorCodigo(int cod) const
    {
        for (size_t i = 0; i < estantes.size(); ++i)
        {
            if (estantes[i].getNumero() == cod)
                return static_cast<int>(i);
        }
        return -1;
    }

    void imprimirBiblioteca() const
    {
        cout << "Biblioteca: " << nombre << " [Codigo: " << codigo << "]" << endl;
    }

    void imprimirEstantes() const
    {
        cout << "Numero de estantes: " << estantes.size() << endl;
        for (size_t i = 0; i < estantes.size(); ++i)
        {
            cout << i + 1 << ". ";
            estantes[i].imprimirEstanteria();
        }
    }
};

void Ejemplar::imprimir() const
{
    cout << "==== Datos del Ejemplar ====" << endl;
    if (libro)
    {
        cout << "  Libro: " << libro->getTitulo() << " (ISBN: " << libro->getISBN() << ")" << endl;
    }
    if (estanteria)
    {
        cout << "  Estanteria: " << estanteria->getNombre() << endl;
        if (estanteria->getBiblioteca())
        {
            cout << "  Biblioteca: " << estanteria->getBiblioteca()->getNombre() << endl;
        }
    }
    else
    {
        cout << "  Ubicacion: Prestado / Fuera de estanteria" << endl;
    }
    cout << "  Codigo Ejemplar: " << codigo << endl;
}

class Estudiante
{
private:
    string nombre;
    int id;
    vector<shared_ptr<Ejemplar>> ejemplaresEnPosesion;

public:
    Estudiante(string nom, int i) : nombre(nom), id(i) {}

    string getNombre() const { return nombre; }
    int getId() const { return id; }
    size_t getCantidadEjemplares() const { return ejemplaresEnPosesion.size(); }
    const vector<shared_ptr<Ejemplar>> &getEjemplaresAlquilados() const { return ejemplaresEnPosesion; }

    void imprimirEstudiante() const
    {
        cout << "==== DATOS ESTUDIANTE =====" << endl;
        cout << "Nombre: " << nombre << " | ID: " << id << endl;
    }

    void imprimirEjemplaresEnPosesion() const
    {
        if (ejemplaresEnPosesion.empty())
        {
            cout << "No tiene ejemplares prestados." << endl;
            return;
        }
        for (size_t i = 0; i < ejemplaresEnPosesion.size(); ++i)
        {
            cout << i + 1 << ": " << endl;
            ejemplaresEnPosesion[i]->imprimir();
        }
    }

    void alquilarEjemplar(shared_ptr<Ejemplar> ejem)
    {
        if (ejem->getEstanteria())
        {
            ejem->getEstanteria()->quitarEjemplar(ejem->getCodigo());
        }
        ejem->setEstudiante(this);
        ejemplaresEnPosesion.push_back(ejem);
        cout << ">> Ejemplar prestado con exito." << endl;
    }

    bool devolverEjemplarPorIndice(size_t idx, Estanteria &destino)
    {
        if (idx >= ejemplaresEnPosesion.size())
            return false;

        auto ejem = ejemplaresEnPosesion[idx];
        ejem->setEstudiante(nullptr);
        destino.anadirEjemplar(ejem);
        ejemplaresEnPosesion.erase(ejemplaresEnPosesion.begin() + idx);
        cout << ">> Ejemplar devuelto exitosamente a la estanteria." << endl;
        return true;
    }
};

class Administrador
{
private:
    vector<Biblioteca> bibliotecas;
    vector<shared_ptr<Autor>> autores;
    vector<Estudiante> estudiantes;
    vector<shared_ptr<Libro>> libros;

    int buscarIndiceEstudiante(int ide)
    {
        for (size_t i = 0; i < estudiantes.size(); ++i)
        {
            if (estudiantes[i].getId() == ide)
                return static_cast<int>(i);
        }
        return -1;
    }

    shared_ptr<Libro> buscarLibroObjetoPorISBN(const string &isbn)
    {
        for (auto &lib : libros)
        {
            if (lib->getISBN() == isbn)
                return lib;
        }
        return nullptr;
    }

public:
    void agregarEstudiante()
    {
        string nombre;
        int id;
        cout << "Ingrese el nombre del estudiante: ";
        limpiarBuffer();
        getline(cin, nombre);
        cout << "Ingrese el ID del estudiante: ";
        cin >> id;

        estudiantes.emplace_back(nombre, id);
        cout << ">> Estudiante registrado correctamente." << endl;
    }

    void eliminarEstudiante()
    {
        int id = 0;
        cout << "Digite el ID del estudiante a eliminar: ";
        cin >> id;
        int idx = buscarIndiceEstudiante(id);
        if (idx == -1)
        {
            cout << ">> Estudiante no encontrado." << endl;
            return;
        }
        if (estudiantes[idx].getCantidadEjemplares() == 0)
        {
            estudiantes.erase(estudiantes.begin() + idx);
            cout << ">> Estudiante eliminado correctamente." << endl;
        }
        else
        {
            cout << ">> El estudiante debe devolver todos sus libros antes de ser eliminado." << endl;
        }
    }

    void listarEstudiantes()
    {
        if (estudiantes.empty())
        {
            cout << ">> No hay estudiantes registrados." << endl;
            return;
        }
        for (size_t i = 0; i < estudiantes.size(); ++i)
        {
            cout << "---------------------------" << endl;
            cout << "Estudiante #" << i + 1 << endl;
            estudiantes[i].imprimirEstudiante();
        }
    }

    void buscarEstudiante()
    {
        int ide;
        cout << "Ingrese el ID del estudiante a consultar: ";
        cin >> ide;
        int idx = buscarIndiceEstudiante(ide);
        if (idx == -1)
        {
            cout << ">> Estudiante no encontrado." << endl;
            return;
        }
        estudiantes[idx].imprimirEstudiante();
        estudiantes[idx].imprimirEjemplaresEnPosesion();
    }

    void crearBiblioteca()
    {
        string nombre;
        int codigo;
        cout << "Ingrese el nombre de la biblioteca: ";
        limpiarBuffer();
        getline(cin, nombre);
        cout << "Ingrese el codigo de la biblioteca: ";
        cin >> codigo;

        bibliotecas.emplace_back(nombre, codigo);
        cout << ">> Biblioteca creada exitosamente." << endl;
    }

    void crearEstante()
    {
        if (bibliotecas.empty())
        {
            cout << ">> Primero debe crear una biblioteca." << endl;
            return;
        }
        int opc = 0;
        cout << "Seleccione la biblioteca a la que desea agregar el estante:" << endl;
        for (size_t i = 0; i < bibliotecas.size(); ++i)
        {
            cout << i + 1 << ". " << bibliotecas[i].getNombre() << endl;
        }
        do
        {
            cout << "Opcion: ";
            cin >> opc;
        } while (opc < 1 || opc > static_cast<int>(bibliotecas.size()));

        string nombre;
        int codi;
        cout << "Ingrese el nombre de la estanteria: ";
        limpiarBuffer();
        getline(cin, nombre);
        cout << "Ingrese el codigo de la estanteria: ";
        cin >> codi;

        bibliotecas[opc - 1].anadirEstante(Estanteria(nombre, codi));
        cout << ">> Estanteria creada exitosamente." << endl;
    }

    void agregarAutor()
    {

        string nombre, nacionalidad;

        cout << "Ingrese el nombre del autor: ";
        cin >> ws; //Tuvimos problemas con los GetLine, entonces le preguntamos a la ia como solucionarlo y esto fue lo que nos dijo que pusieramos
        getline(cin, nombre);

        cout << "Ingrese la nacionalidad del autor: ";
        getline(cin, nacionalidad);

        autores.push_back(make_shared<Autor>(nombre, nacionalidad));
        cout << ">> Autor registrado correctamente." << endl;
    }

    void crearLibro()
    {
        string titulo, fecha, isbn;
        int opc;
        cout << "Ingrese el Titulo del libro: ";
        limpiarBuffer();
        getline(cin, titulo);
        cout << "Ingrese la Fecha de Publicacion: ";
        getline(cin, fecha);
        cout << "Ingrese el codigo ISBN: ";
        getline(cin, isbn);

        if (autores.empty())
        {
            cout << ">> No hay autores registrados. Vamos a crear uno primero." << endl;
            agregarAutor();
            opc = 1;
        }
        else
        {
            cout << "\nAsignar un Autor:" << endl;
            for (size_t i = 0; i < autores.size(); ++i)
            {
                cout << i + 1 << ". " << autores[i]->getNombre() << endl;
            }
            cout << "0. Crear un nuevo autor" << endl;
            do
            {
                cout << "Opcion: ";
                cin >> opc;
            } while (opc < 0 || opc > static_cast<int>(autores.size()));

            if (opc == 0)
            {
                agregarAutor();
                opc = static_cast<int>(autores.size());
            }
        }

        auto nuevoLibro = make_shared<Libro>(titulo, fecha, isbn, autores[opc - 1]);
        libros.push_back(nuevoLibro);
        autores[opc - 1]->anadirLibro(nuevoLibro);
        cout << ">> Libro creado correctamente." << endl;
    }

    void crearEjemplar()
    {
        if (libros.empty() || bibliotecas.empty())
        {
            cout << ">> Debe tener al menos un libro y una biblioteca registrados para crear ejemplares." << endl;
            return;
        }

        string isbn;
        cout << "Ingrese el ISBN del libro: ";
        cin >> isbn;

        auto libro = buscarLibroObjetoPorISBN(isbn);
        if (!libro)
        {
            cout << ">> Libro no encontrado con el ISBN proporcionado." << endl;
            return;
        }

        int codEjemplar;
        cout << "Ingrese el codigo unico para este nuevo ejemplar: ";
        cin >> codEjemplar;

        auto ejem = libro->crearEjemplar(codEjemplar);

        cout << "\nSeleccione la Biblioteca destino:" << endl;
        for (size_t i = 0; i < bibliotecas.size(); ++i)
        {
            cout << i + 1 << ". " << bibliotecas[i].getNombre() << endl;
        }
        int opcB;
        do
        {
            cout << "Opcion: ";
            cin >> opcB;
        } while (opcB < 1 || opcB > static_cast<int>(bibliotecas.size()));

        auto &bibSeleccionada = bibliotecas[opcB - 1];
        if (bibSeleccionada.getEstantes().empty())
        {
            cout << ">> La biblioteca seleccionada no tiene estantes. Cree un estante primero." << endl;
            return;
        }

        cout << "\nSeleccione la Estanteria destino:" << endl;
        bibSeleccionada.imprimirEstantes();
        int opcE;
        do
        {
            cout << "Opcion: ";
            cin >> opcE;
        } while (opcE < 1 || opcE > static_cast<int>(bibSeleccionada.getEstantes().size()));

        bibSeleccionada.getEstantes()[opcE - 1].anadirEjemplar(ejem);
        cout << ">> Ejemplar asignado al estante con exito." << endl;
    }

    void prestarEjemplarEstudiante()
    {
        int ide;
        cout << "Ingrese el ID del estudiante: ";
        cin >> ide;
        int idxEst = buscarIndiceEstudiante(ide);
        if (idxEst == -1)
        {
            cout << ">> Estudiante no encontrado." << endl;
            return;
        }

        int codigoEjem;
        cout << "Ingrese el codigo del ejemplar a prestar: ";
        cin >> codigoEjem;

        shared_ptr<Ejemplar> ejemEncontrado = nullptr;
        for (auto &bib : bibliotecas)
        {
            for (auto &est : bib.getEstantes())
            {
                ejemEncontrado = est.getEjemplarPorCodigo(codigoEjem);
                if (ejemEncontrado)
                    break;
            }
            if (ejemEncontrado)
                break;
        }

        if (!ejemEncontrado)
        {
            cout << ">> Ejemplar no disponible o codigo invalido." << endl;
            return;
        }

        estudiantes[idxEst].alquilarEjemplar(ejemEncontrado);
    }

    void devolverEjemplarEstudiante()
    {
        int ide;
        cout << "Ingrese el ID del estudiante: ";
        cin >> ide;
        int idxEst = buscarIndiceEstudiante(ide);
        if (idxEst == -1)
        {
            cout << ">> Estudiante no encontrado." << endl;
            return;
        }

        auto &est = estudiantes[idxEst];
        if (est.getCantidadEjemplares() == 0)
        {
            cout << ">> El estudiante no tiene ejemplares prestados." << endl;
            return;
        }

        cout << "\nEjemplares prestados al estudiante:" << endl;
        est.imprimirEjemplaresEnPosesion();

        int opc = 0;
        cout << "Ingrese el numero de la opcion a devolver (1 a " << est.getCantidadEjemplares() << "): ";
        cin >> opc;

        if (opc < 1 || opc > static_cast<int>(est.getCantidadEjemplares()))
        {
            cout << ">> Opcion invalida." << endl;
            return;
        }

        if (bibliotecas.empty() || bibliotecas[0].getEstantes().empty())
        {
            cout << ">> No hay estantes disponibles para devolver el ejemplar." << endl;
            return;
        }

        // Se retorna por defecto al primer estante disponible
        est.devolverEjemplarPorIndice(opc - 1, bibliotecas[0].getEstantes()[0]);
    }

    void menuBiblioteca()
    {
        int opc = 0;
        do
        {
            cout << "\n===== MENU BIBLIOTECA =====" << endl;
            cout << "1: Listar Bibliotecas" << endl;
            cout << "2: Listar Bibliotecas, Estantes y Ejemplares" << endl;
            cout << "3: Crear Biblioteca" << endl;
            cout << "4: Crear Estantes" << endl;
            cout << "5: Volver al Menu Principal" << endl;
            cout << "Opcion: ";
            cin >> opc;

            switch (opc)
            {
            case 1:
                for (const auto &b : bibliotecas)
                    b.imprimirBiblioteca();
                break;
            case 2:
                for (auto &b : bibliotecas)
                {
                    b.imprimirBiblioteca();
                    for (const auto &e : b.getEstantes())
                    {
                        e.imprimirEstanteria();
                        e.imprimirEjemplares();
                    }
                }
                break;
            case 3:
                crearBiblioteca();
                break;
            case 4:
                crearEstante();
                break;
            case 5:
                break;
            default:
                cout << ">> Opcion invalida." << endl;
                break;
            }
        } while (opc != 5);
    }

    void menuEstudiante()
    {
        int opc = 0;
        do
        {
            cout << "\n===== MENU ESTUDIANTE =====" << endl;
            cout << "1: Registrar Estudiante" << endl;
            cout << "2: Eliminar Estudiante" << endl;
            cout << "3: Listar Estudiantes" << endl;
            cout << "4: Buscar Estudiante" << endl;
            cout << "5: Prestar Libro a Estudiante" << endl;
            cout << "6: Devolver Libro de Estudiante" << endl;
            cout << "7: Volver al Menu Principal" << endl;
            cout << "Opcion: ";
            cin >> opc;

            switch (opc)
            {
            case 1:
                agregarEstudiante();
                break;
            case 2:
                eliminarEstudiante();
                break;
            case 3:
                listarEstudiantes();
                break;
            case 4:
                buscarEstudiante();
                break;
            case 5:
                prestarEjemplarEstudiante();
                break;
            case 6:
                devolverEjemplarEstudiante();
                break;
            case 7:
                break;
            default:
                cout << ">> Opcion invalida." << endl;
                break;
            }
        } while (opc != 7);
    }

    void menuLibro()
    {
        int opc = 0;
        do
        {
            cout << "\n===== MENU LIBRO Y AUTOR =====" << endl;
            cout << "1: Listar Libros" << endl;
            cout << "2: Listar Libros y Ejemplares" << endl;
            cout << "3: Crear Autor" << endl;
            cout << "4: Crear Libro" << endl;
            cout << "5: Listar Autores y sus Libros" << endl;
            cout << "6: Anadir Ejemplar a Estante" << endl;
            cout << "7: Volver al Menu Principal" << endl;
            cout << "Opcion: ";
            cin >> opc;

            switch (opc)
            {
            case 1:
                for (const auto &l : libros)
                    l->imprimir();
                break;
            case 2:
                for (const auto &l : libros)
                {
                    l->imprimir();
                    l->imprimirEjemplares();
                }
                break;
            case 3:
                agregarAutor();
                break;
            case 4:
                crearLibro();
                break;
            case 5:
                for (const auto &a : autores)
                {
                    a->imprimir();
                    a->imprimirLibros();
                }
                break;
            case 6:
                crearEjemplar();
                break;
            case 7:
                break;
            default:
                cout << ">> Opcion invalida." << endl;
                break;
            }
        } while (opc != 7);
    }

    void menuPrograma()
    {
        int opc = 0;
        do
        {
            cout << "\n==========================================" << endl;
            cout << "     SISTEMA DE GESTION DE BIBLIOTECA     " << endl;
            cout << "==========================================" << endl;
            cout << "1: Menu Estudiantes" << endl;
            cout << "2: Menu Libros y Autores" << endl;
            cout << "3: Menu Bibliotecas y Estantes" << endl;
            cout << "4: Salir" << endl;
            cout << "Opcion: ";
            cin >> opc;

            switch (opc)
            {
            case 1:
                menuEstudiante();
                break;
            case 2:
                menuLibro();
                break;
            case 3:
                menuBiblioteca();
                break;
            case 4:
                cout << "Saliendo del sistema..." << endl;
                break;
            default:
                cout << ">> Opcion invalida." << endl;
                break;
            }
        } while (opc != 4);
    }
};

int main()
{
    Administrador sistema;
    sistema.menuPrograma();
    return 0;
}