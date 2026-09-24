#include<string>
#include<vector>
#include<iostream>

class Autor{
private:
    std::string nombre;
    std::string fechaNacimiento;
    std::string nacionalidad;
public:
    //constructor
    Autor(std::string nombre = "", std::string fechaNacimiento = "No registrado", std::string nacionalidad = "No registrado"){
        this->nombre = nombre;
        this->fechaNacimiento = fechaNacimiento;
        this->nacionalidad = nacionalidad;
    };
    
    // getters
    std::string getNombre() const {
        return this->nombre;
    }
    std::string getFechaNacimiento() const {
        return this->fechaNacimiento;
    }
    std::string getNacionalidad() const {
        return this->nacionalidad;
    }

    // setters
    void setNombre(std::string nuevoNombre) {
        this->nombre = nuevoNombre;
    }
    void setFechaNacimiento(std::string nuevaFechaNacimiento) {
        this->fechaNacimiento = nuevaFechaNacimiento;
    }
    void setNacionalidad(std::string nuevaNacionalidad) {
        this->nacionalidad = nuevaNacionalidad;
    }
    // mostrar 
    void print()const {
        std::cout<<"Nombre: "<<nombre<<", Fecha Nacimiento: "<<fechaNacimiento<< ",Nacionaldad : "<< nacionalidad <<std::endl;}
};

class Libro{
private:
    std::string titulo;
    int isbn;
    Autor* autor;
    int anio;

public:
    //constructor
    Libro(std::string titulo = "", int isbn = 0, int anio = 0, Autor* autor = nullptr) {
        this->titulo = titulo;
        this->isbn = isbn;
        this->anio = anio;
        this->autor = autor;
    }

    
    // --- GETTERS ---
    std::string getTitulo() const {
        return this->titulo;
    }
    int getIsbn() const {
        return this->isbn;
    }
    Autor* getAutor() const {
        return this->autor;
    }
    int getAnio() const {
        return this->anio;
    }

    // --- SETTERS ---
    void setTitulo(const std::string& nuevoTitulo) {
        this->titulo = nuevoTitulo;
    }
    void setIsbn(int nuevoIsbn) {
        this->isbn = nuevoIsbn;
    }
    void setAutor(Autor* nuevoAutor) {
        this->autor = nuevoAutor;
    }
    void setAnio(int nuevoAnio) {
        this->anio = nuevoAnio;
    }

    // funcion de mostarse
    // Muestra en consola la informacion detallada del libro centralizando el formato
    void print() const {
        std::cout << "Titulo: " << this->titulo 
                  << " | ISBN: " << this->isbn 
                  << " | Anio: " << this->anio;
        if (this->autor != nullptr) {
            std::cout << " | Autor: " << this->autor->getNombre();
        } else {
            std::cout << " | Autor: Anonimo";
        }
        std::cout << std::endl;
    }
    

};

class Estante {
private:
    std::string nombre; 
    std::vector<Libro*> libros; // Almacena las direcciones de los libros
    std::vector<int> cantidades; // Almacena las cantidades en la misma posicion
    bool asignado;

public:
    // constructor
    Estante(std::string nombre = "", bool asignado = false) {
        this->nombre = nombre;
        this->asignado = asignado;
    }

    
    // Getters
    std::string getNombre() const {
        return this->nombre;
    }
    const std::vector<Libro*>& getLibros() const {
        return this->libros;
    }
    const std::vector<int>& getCantidades() const {
        return this->cantidades;
    }

    bool getAsignado() const { 
        return this->asignado;
    }

    //  Setters
    void setNombre(const std::string& nuevoNombre) {
        this->nombre = nuevoNombre;
    }
    void setLibros(const std::vector<Libro*>& nuevosLibros) {
        this->libros = nuevosLibros;
    }
    void setCantidades(const std::vector<int>& nuevasCantidades) {
        this->cantidades = nuevasCantidades;
    }
    void setAsignado(bool nuevoEstado) { 
        this->asignado = nuevoEstado;
    }
    
    
    // Metodos creados 
    void agregarEjemplar(Libro* libro, int cantidad) {
        for (size_t i = 0; i < libros.size(); ++i) {
            if (libros[i] == libro) {
                cantidades[i] += cantidad;
                return;
            }
        }
        libros.push_back(libro);
        cantidades.push_back(cantidad);
    }
    //  Metodo auxiliar para mostrar datos de la estanteria
    void print() const {
            std::cout << "Estante: " << nombre << " | Titulos distintos: " << libros.size();
            if (this->asignado) { // AGREGADO: Muestra si la estanteria ya tiene biblioteca
                std::cout << " | Estado: Asignado";
            } else {
                std::cout << " | Estado: Disponible";
            }
            std::cout << std::endl;
        }

    // Metodo que recorre el vector cantidades y retorna el total de ejemplares en esta estanteria
    int contarTotalEjemplares() const {
        int total = 0;
        for (size_t i = 0; i < cantidades.size(); ++i) {
            total += cantidades[i];
        }
        return total;
    }
    //  Metodo para actualizar directamente la cantidad disponible  de un libro especifico en esta estanteria.

    bool actualizarCantidad(Libro* libro, int nuevaCantidad) {
        if (nuevaCantidad < 0) {
            return false;
        }
        for (size_t i = 0; i < libros.size(); ++i) {
            if (libros[i] == libro) {
                cantidades[i] = nuevaCantidad;
                return true;
            }
        }
        return false;
    }


};

class Biblioteca{
private:
    std::string nombre;
    std::string facultad;
    std::vector<Estante*>estantes; // se trata como agregacion 
public:
    //constructores
    Biblioteca(std::string facultad = "", std::string nombre = ""){
        this->facultad = facultad;
        this->nombre = nombre;
    }
    //getters
    std::string getNombre() const {
        return nombre;}
    std::string getFacultad() const {
        return facultad;
    }
    const std::vector<Estante*>& getEstantes() const { 
            return this->estantes;
        }


    // setters 
    void setNombre(std::string nuevoNombre) {
        nombre = nuevoNombre;
    }
    void setFacultad(std::string nuevaFacultad) {
        facultad = nuevaFacultad;
    }
    void setEstantes(const std::vector<Estante*>& nuevosEstantes) {
            this->estantes = nuevosEstantes;
        }
    void agregarEstante(Estante* estante) {
            if (estante != nullptr) {
                this->estantes.push_back(estante);
            }
        }

    // mostrar informacion
    void print(){
        std::cout<<"Nombre: "<<nombre<<"\n";
        std::cout<<"Facultad: "<<facultad<<"\n";
    }

    int contarTotalEjemplares() const {
        int total = 0;
        for (size_t i = 0; i < estantes.size(); ++i) {
            if (estantes[i] != nullptr) {
                total += estantes[i]->contarTotalEjemplares();
            }
        }
        return total;
    }
};

class Estudiante {
private:
    std::string codigo;
    std::string nombre;

public:
    //  Constructor de la clase Estudiante
    Estudiante(std::string codigo = "", std::string nombre = "") {
        this->codigo = codigo;
        this->nombre = nombre;
    }
    //  Getters
    std::string getCodigo() const {
        return this->codigo;
    }
    std::string getNombre() const {
        return this->nombre;
    }

    //  Setters
    void setCodigo(const std::string& nuevoCodigo) {
        this->codigo = nuevoCodigo;
    }
    void setNombre(const std::string& nuevoNombre) {
        this->nombre = nuevoNombre;
    }

    //  Metodo para mostrar la informacion del estudiante
    void print() const {
        std::cout << "Codigo: " << this->codigo << " | Nombre: " << this->nombre << std::endl;
    }
};

class Prestamo {
private:
    //  Atributos asociativos para registrar el prestamo
    Estudiante* estudiante;
    Libro* libro;
    Estante* estante;
    Biblioteca* biblioteca;

public:
    //  Constructor de la clase Prestamo
    Prestamo(Estudiante* estudiante = nullptr, Libro* libro = nullptr, Estante* estante = nullptr, Biblioteca* biblioteca = nullptr) {
        this->estudiante = estudiante;
        this->libro = libro;
        this->estante = estante;
        this->biblioteca = biblioteca;
    }

    //  Getters
    Estudiante* getEstudiante() const {
        return this->estudiante;
    }
    Libro* getLibro() const {
        return this->libro;
    }
    Estante* getEstante() const {
        return this->estante;
    }
    Biblioteca* getBiblioteca() const {
        return this->biblioteca;
    }

    //  Setters
    void setEstudiante(Estudiante* nuevoEstudiante) {
        this->estudiante = nuevoEstudiante;
    }
    void setLibro(Libro* nuevoLibro) {
        this->libro = nuevoLibro;
    }
    void setEstante(Estante* nuevoEstante) {
        this->estante = nuevoEstante;
    }
    void setBiblioteca(Biblioteca* nuevaBiblioteca) {
        this->biblioteca = nuevaBiblioteca;
    }

    //  Metodo para mostrar los detalles del prestamo
    void print() const {
        std::cout << "Estudiante: " << (this->estudiante ? this->estudiante->getNombre() : "N/A")
                  << " (Codigo: " << (this->estudiante ? this->estudiante->getCodigo() : "N/A") << ")"
                  << " | Libro: " << (this->libro ? this->libro->getTitulo() : "N/A")
                  << " | Estanteria: " << (this->estante ? this->estante->getNombre() : "N/A")
                  << " | Biblioteca: " << (this->biblioteca ? this->biblioteca->getNombre() : "N/A") << std::endl;
    }
};

class Sistema {
private:
    std::string nombreInstitucion;
    std::vector<Biblioteca*> bibliotecas;
    std::vector<Autor*> autores;
    std::vector<Libro*> libros;
    std::vector<Estante*> estantes;
    std::vector<Estudiante*> estudiantes;
    std::vector<Prestamo*> prestamos;
public:
    
// --- CONSTRUCTORES ---
    Sistema(std::string nombreInstitucion = "") {
        this->nombreInstitucion = nombreInstitucion;
    }
    // --- SETTERS ---
    void setNombreInstitucion(std::string nombreInstitucion) {
        this->nombreInstitucion = nombreInstitucion;
    }
    void setBibliotecas(const std::vector<Biblioteca*>& nuevasBibliotecas) {
        this->bibliotecas = nuevasBibliotecas;
    }
    void setAutores(const std::vector<Autor*>& nuevosAutores) {
        this->autores = nuevosAutores;
    }
    void setLibros(const std::vector<Libro*>& nuevosLibros) {
            this->libros = nuevosLibros;
        }
    void setEstantes(const std::vector<Estante*>& nuevosEstantes) {
        this->estantes = nuevosEstantes;
    }
    void setEstudiantes(const std::vector<Estudiante*>& nuevosEstudiantes) {
        this->estudiantes = nuevosEstudiantes;
    }
    void setPrestamos(const std::vector<Prestamo*>& nuevosPrestamos) {
        this->prestamos = nuevosPrestamos;
    }
    
    // --- GETTERS ---
    std::string getNombreInstitucion() const {
        return this->nombreInstitucion;
    }
    const std::vector<Biblioteca*>& getBibliotecas() const {
        return this->bibliotecas;
    }
    const std::vector<Autor*>& getAutores() const {
        return this->autores;
    }
    const std::vector<Libro*>& getLibros() const {
        return this->libros;
    }
    const std::vector<Estante*>& getEstantes() const {
        return this->estantes;
    }
    const std::vector<Estudiante*>& getEstudiantes() const {
        return this->estudiantes;
    }
    const std::vector<Prestamo*>& getPrestamos() const {
        return this->prestamos;
    }
    
    // --- REGISTRAR AUTOR ---
    void registrarAutor(std::string nombre, std::string fechaNacimiento = "No registrado", std::string nacionalidad = "No registrado") {
        Autor* nuevoAutor = new Autor(nombre, fechaNacimiento, nacionalidad);
        this->autores.push_back(nuevoAutor);
        std::cout << "-> Autor '" << nombre << "' registrado exitosamente.\n";
    }
   
    // --- MOSTRAR AUTORES ---
    void mostrarAutores() const {
        if (this->autores.empty()) {
            std::cout << "\nNo hay autores registrados en el sistema.\n";
            return;
        }
        std::cout << "\n=== LISTA DE AUTORES REGISTRADOS ===\n";
        for (size_t i = 0; i < this->autores.size(); ++i) {
            std::cout << i + 1 << ". ";
            this->autores[i]->print(); // Aprovecha el método print() existente en Autor
        }
    }

    // --- REGISTRAR LIBROS ---
    void registrarLibro(std::string titulo, int isbn, int anio = 0, Autor* autor = nullptr) {
        Libro* nuevoLibro = new Libro(titulo, isbn, anio, autor);
        this->libros.push_back(nuevoLibro);
        std::cout << "-> Libro '" << titulo << "' registrado exitosamente.\n";
    }

    // Ahora utiliza directamente la funcion print() de la clase Libro
    void mostrarLibros() const {
        if (this->libros.empty()) {
            std::cout << "\nNo hay libros registrados en el sistema.\n";
            return;
        }
        std::cout << "\n=== LISTA DE LIBROS REGISTRADOS ===\n";
        for (size_t i = 0; i < this->libros.size(); ++i) {
            std::cout << i + 1 << ". ";
            this->libros[i]->print(); // MODIFICADO: Delegacion de la impresion a la clase Libro
        }
    }
    
    // --- REGISTRAR ESTANTES ---
    void registrarEstante(std::string nombre) {
        Estante* nuevoEstante = new Estante(nombre);
        this->estantes.push_back(nuevoEstante);
        std::cout << "-> Estanteria '" << nombre << "' registrada exitosamente.\n";
    }
    void mostrarEstantes() const {
        if (this->estantes.empty()) {
            std::cout << "\nNo hay estanterias registradas en el sistema.\n";
            return;
        }
        std::cout << "\n=== LISTA DE ESTANTERIAS REGISTRADAS ===\n";
        for (size_t i = 0; i < this->estantes.size(); ++i) {
            std::cout << i + 1 << ". ";
            this->estantes[i]->print();
        }
    }
    void registrarEjemplar(Libro* libro, Estante* estante, int cantidad) {
        if (libro != nullptr && estante != nullptr && cantidad > 0) {
            estante->agregarEjemplar(libro, cantidad);
            std::cout << "-> Se han asignado " << cantidad << " ejemplar(es) del libro '" 
                      << libro->getTitulo() << "' a la estanteria '" << estante->getNombre() << "'.\n";
        } else {
            std::cout << "-> Error: Datos invalidos para registrar el ejemplar.\n";
        } 
    }
    
    
    
    // --- REGISTRAR BIBLIOTECA ---
    Biblioteca* registrarBiblioteca(std::string facultad, std::string nombre) { 
            Biblioteca* nuevaBiblioteca = new Biblioteca(facultad, nombre);
            this->bibliotecas.push_back(nuevaBiblioteca);
            std::cout << "-> Biblioteca '" << nombre << "' de " << facultad << " registrada exitosamente.\n";
            return nuevaBiblioteca;
        }
    //  Metodo para asignar una estanteria a una biblioteca
    bool asignarEstanteABiblioteca(Biblioteca* biblioteca, Estante* estante) {
        if (biblioteca == nullptr || estante == nullptr) {
            std::cout << "-> Error: Biblioteca o estanteria invalida.\n";
            return false;
        }

        if (estante->getAsignado()) { 
            std::cout << "-> Error: La estanteria '" << estante->getNombre() 
                      << "' ya pertenece a una biblioteca y no se puede volver a asignar.\n";
            return false;
        }

        biblioteca->agregarEstante(estante);
        estante->setAsignado(true); 
        std::cout << "-> Estanteria '" << estante->getNombre() 
                  << "' asignada exitosamente a la biblioteca '" << biblioteca->getNombre() << "'.\n";
        return true;
    }
    // Metodo para listar bibliotecas
    void mostrarBibliotecas() const {
        if (this->bibliotecas.empty()) {
            std::cout << "\nNo hay bibliotecas registradas en el sistema.\n";
            return;
        }
        std::cout << "\n=== LISTA DE BIBLIOTECAS REGISTRADAS ===\n";
        for (size_t i = 0; i < this->bibliotecas.size(); ++i) {
            std::cout << i + 1 << ". ";
            this->bibliotecas[i]->print();
        }
    }
    // Recorre la lista de prestamos y calcula la cantidad de ejemplares prestados
    // para un libro especifico en un estante y biblioteca determinados.
    int contarPrestamosPorLibroYEstante(Libro* libro, Estante* estante, Biblioteca* biblioteca) const {
        int contador = 0;
        for (size_t i = 0; i < this->prestamos.size(); ++i) {
            if (this->prestamos[i]->getLibro() == libro &&
                this->prestamos[i]->getEstante() == estante &&
                this->prestamos[i]->getBiblioteca() == biblioteca) {
                contador++;
            }
        }
        return contador;
    }
    
    
    // Metodo para consultar la disponibilidad de un libro por su titulo en todas las bibliotecas y sus estanterias
    void consultarDisponibilidadLibro(std::string titulo) const {
        if (this->bibliotecas.empty()) {
            std::cout << "-> No hay bibliotecas registradas en el sistema.\n";
            return;
        }

        bool encontrado = false;
        std::cout << "\n=== RESULTADOS DE DISPONIBILIDAD PARA: '" << titulo << "' ===\n";

        for (size_t i = 0; i < this->bibliotecas.size(); ++i) {
            Biblioteca* biblio = this->bibliotecas[i];
            const std::vector<Estante*>& estantesBiblio = biblio->getEstantes();

            for (size_t j = 0; j < estantesBiblio.size(); ++j) {
                Estante* estante = estantesBiblio[j];
                const std::vector<Libro*>& librosEstante = estante->getLibros();
                const std::vector<int>& cantidadesEstante = estante->getCantidades();

                for (size_t k = 0; k < librosEstante.size(); ++k) {
                    if (librosEstante[k]->getTitulo() == titulo) {
                        // AGREGADO: Calculo dinamico de prestamos
                        int cantidadPrestada = contarPrestamosPorLibroYEstante(librosEstante[k], estante, biblio);

                        if (cantidadesEstante[k] > 0 || cantidadPrestada > 0) {
                            std::cout << "-> Biblioteca: " << biblio->getNombre()
                                      << " (" << biblio->getFacultad() << ")"
                                      << " | Estanteria: " << estante->getNombre()
                                      << " | Ejemplares disponibles: " << cantidadesEstante[k]
                                      << " | Ejemplares prestados: " << cantidadPrestada << "\n"; // MODIFICADO: Muestra prestados
                            encontrado = true;
                        }
                    }
                }
            }
        }

        if (!encontrado) {
            std::cout << "-> No se encontraron ejemplares registrados del libro '" << titulo << "' en ninguna biblioteca.\n";
        }
    }

    //  Metodo para mostrar todos los libros de una biblioteca, su estanteria y cantidad de ejemplares
    void mostrarInventarioBiblioteca(int indiceBiblioteca) const {
        if (indiceBiblioteca < 0 || indiceBiblioteca >= (int)this->bibliotecas.size()) {
            std::cout << "-> Error: Indice de biblioteca invalido.\n";
            return;
        }

        Biblioteca* biblio = this->bibliotecas[indiceBiblioteca];
        const std::vector<Estante*>& estantesBiblio = biblio->getEstantes();

        std::cout << "\n=== INVENTARIO DE LA BIBLIOTECA: " << biblio->getNombre() 
                  << " (" << biblio->getFacultad() << ") ===\n";

        if (estantesBiblio.empty()) {
            std::cout << "-> La biblioteca no tiene estanterias asignadas.\n";
            return;
        }

        bool tieneLibros = false;

        for (size_t i = 0; i < estantesBiblio.size(); ++i) {
            Estante* estante = estantesBiblio[i];
            const std::vector<Libro*>& librosEstante = estante->getLibros();
            const std::vector<int>& cantidadesEstante = estante->getCantidades();

            std::cout << "\n[Estanteria: " << estante->getNombre() << "]\n";

            if (librosEstante.empty()) {
                std::cout << "  (Estanteria vacia, sin libros registrados)\n";
            } else {
                for (size_t j = 0; j < librosEstante.size(); ++j) {
                    // AGREGADO: Calculo dinamico de prestamos por libro en estante
                    int cantidadPrestada = contarPrestamosPorLibroYEstante(librosEstante[j], estante, biblio);

                    std::cout << "  - Libro: " << librosEstante[j]->getTitulo()
                              << " | ISBN: " << librosEstante[j]->getIsbn()
                              << " | Ejemplares disponibles: " << cantidadesEstante[j]
                              << " | Ejemplares prestados: " << cantidadPrestada << "\n"; // MODIFICADO: Muestra prestados
                    tieneLibros = true;
                }
            }
        }

        if (!tieneLibros) {
            std::cout << "\n-> La biblioteca no cuenta con ejemplares de libros registrados en sus estanterias.\n";
        }
    }
    //  Metodo para gestionar y mostrar el conteo total de ejemplares de una biblioteca seleccionada
    void contarInventarioBiblioteca(int indiceBiblioteca) const {
        if (indiceBiblioteca < 0 || indiceBiblioteca >= (int)this->bibliotecas.size()) {
            std::cout << "-> Error: Indice de biblioteca invalido.\n";
            return;
        }

        Biblioteca* biblio = this->bibliotecas[indiceBiblioteca];
        int totalEjemplares = biblio->contarTotalEjemplares();

        std::cout << "\n=== CONTEO DE INVENTARIO EN BIBLIOTECA ===\n";
        std::cout << "Biblioteca: " << biblio->getNombre() << " (" << biblio->getFacultad() << ")\n";
        std::cout << "Cantidad de estanterias asignadas: " << biblio->getEstantes().size() << "\n";
        std::cout << "Total de ejemplares disponibles en el inventario: " << totalEjemplares << "\n";
    }

    
    // Metodo controlador para actualizar el inventario de un ejemplar coordinando la validacion del estante y el libro.

    bool actualizarInventario(Estante* estante, Libro* libro, int nuevaCantidad) {
        if (estante != nullptr && libro != nullptr && nuevaCantidad >= 0) {
            bool exito = estante->actualizarCantidad(libro, nuevaCantidad);
            if (exito) {
                std::cout << "-> Inventario actualizado con exito. Nueva cantidad de '" 
                          << libro->getTitulo() << "': " << nuevaCantidad << ".\n";
                return true;
            }
        }
        std::cout << "-> Error: No se pudo actualizar el inventario.\n";
        return false;
    }

    // --- FUNCIONES 3ER PUNTO  ---

    //   - Registrar un estudiante
    void registrarEstudiante(std::string codigo, std::string nombre) {
        Estudiante* nuevoEstudiante = new Estudiante(codigo, nombre);
        this->estudiantes.push_back(nuevoEstudiante);
        std::cout << "-> Estudiante '" << nombre << "' con codigo '" << codigo << "' registrado exitosamente.\n";
    }
    //  - Visualizar estudiante 
    void mostrarEstudiantes() const {
        if (this->estudiantes.empty()) {
            std::cout << "\nNo hay estudiantes registrados en el sistema.\n";
            return;
        }
        std::cout << "\n=== LISTA DE ESTUDIANTES REGISTRADOS ===\n";
        for (size_t i = 0; i < this->estudiantes.size(); ++i) {
            std::cout << i + 1 << ". ";
            this->estudiantes[i]->print();
        }
    }
    //  - Registrar un prestamo 
    bool registrarPrestamo(Estudiante* estudiante, Biblioteca* biblioteca, Estante* estante, Libro* libro) {
        if (estudiante == nullptr || biblioteca == nullptr || estante == nullptr || libro == nullptr) {
            std::cout << "-> Error: Datos invalidos para realizar el prestamo.\n";
            return false;
        }

        // Verificar que el estante pertenezca a la biblioteca seleccionada
        bool estanteEnBiblioteca = false;
        const std::vector<Estante*>& estantesBiblio = biblioteca->getEstantes();
        for (size_t i = 0; i < estantesBiblio.size(); ++i) {
            if (estantesBiblio[i] == estante) {
                estanteEnBiblioteca = true;
                break;
            }
        }

        if (!estanteEnBiblioteca) {
            std::cout << "-> Error: La estanteria seleccionada no pertenece a la biblioteca especificada.\n";
            return false;
        }

        // Buscar el libro en la estanteria y verificar disponibilidad
        const std::vector<Libro*>& librosEstante = estante->getLibros();
        const std::vector<int>& cantidadesEstante = estante->getCantidades();
        int indiceLibro = -1;

        for (size_t i = 0; i < librosEstante.size(); ++i) {
            if (librosEstante[i] == libro) {
                indiceLibro = (int)i;
                break;
            }
        }

        if (indiceLibro == -1) {
            std::cout << "-> Error: El libro no se encuentra en la estanteria seleccionada.\n";
            return false;
        }

        int cantidadDisponible = cantidadesEstante[indiceLibro];
        if (cantidadDisponible <= 0) {
            std::cout << "-> Error: No hay ejemplares disponibles para prestar de este libro en esta estanteria.\n";
            return false;
        }

        // Disminuir en 1 la cantidad disponible en el estante
        estante->actualizarCantidad(libro, cantidadDisponible - 1);

        // Crear el registro de prestamo y agregarlo al vector
        Prestamo* nuevoPrestamo = new Prestamo(estudiante, libro, estante, biblioteca);
        this->prestamos.push_back(nuevoPrestamo);

        std::cout << "-> Prestamo registrado con exito para el estudiante '" << estudiante->getNombre() << "'.\n";
        return true;
    }
    //  Requerimiento 3 - Dada una biblioteca, listar los ejemplares actualmente prestados y el estudiante a quien fueron prestados
    void listarPrestamosPorBiblioteca(Biblioteca* biblioteca) const {
        if (biblioteca == nullptr) {
            std::cout << "-> Error: Biblioteca invalida.\n";
            return;
        }

        std::cout << "\n=== EJEMPLARES PRESTADOS EN LA BIBLIOTECA: " << biblioteca->getNombre() << " ===\n";
        bool encontrado = false;

        for (size_t i = 0; i < this->prestamos.size(); ++i) {
            if (this->prestamos[i]->getBiblioteca() == biblioteca) {
                encontrado = true;
                std::cout << "-> Libro: " << this->prestamos[i]->getLibro()->getTitulo()
                          << " | Estanteria: " << this->prestamos[i]->getEstante()->getNombre()
                          << " | Prestado a: " << this->prestamos[i]->getEstudiante()->getNombre()
                          << " (Codigo: " << this->prestamos[i]->getEstudiante()->getCodigo() << ")\n";
            }
        }

        if (!encontrado) {
            std::cout << "-> No hay ejemplares actualmente prestados en esta biblioteca.\n";
        }
    }  
    //  Requerimiento 4 - Dado un estudiante, listar los libros que dicho estudiante tiene actualmente en prestamo
    void listarPrestamosPorEstudiante(Estudiante* estudiante) const {
        if (estudiante == nullptr) {
            std::cout << "-> Error: Estudiante invalido.\n";
            return;
        }

        std::cout << "\n=== LIBROS EN PRESTAMO PARA EL ESTUDIANTE: " << estudiante->getNombre() 
                  << " (Codigo: " << estudiante->getCodigo() << ") ===\n";
        bool encontrado = false;

        for (size_t i = 0; i < this->prestamos.size(); ++i) {
            if (this->prestamos[i]->getEstudiante() == estudiante) {
                encontrado = true;
                std::cout << "-> Libro: " << this->prestamos[i]->getLibro()->getTitulo()
                          << " | Biblioteca: " << this->prestamos[i]->getBiblioteca()->getNombre()
                          << " | Estanteria: " << this->prestamos[i]->getEstante()->getNombre() << "\n";
            }
        }

        if (!encontrado) {
            std::cout << "-> El estudiante no tiene libros actualmente en prestamo.\n";
        }
    }


};


// definimos algunas funciones 
//Limpia los saltos de linea pendientes en el buffer cin
void limpiarBuffer() {
    std::string temp;
    std::getline(std::cin, temp);
}

//  Despliega el menu visual separando la opcion 5 en dos casos (del 1 al 10)
void mostrarMenu(const std::string& nombreInstitucion) {
    std::cout << "\n===== BIENVENIDO AL SISTEMA " << nombreInstitucion << " =====\n";
    std::cout << "MENU DE OPCIONES\n";
    std::cout << "1: Registrar un Autor\n";
    std::cout << "2: Registrar un Libro\n";
    std::cout << "3: Registrar una Estanteria nueva\n";
    std::cout << "4: Registrar un ejemplar de libro\n";
    std::cout << "5: Registrar una Biblioteca\n"; // MODIFICADO: Solo registra la biblioteca
    std::cout << "6: Asignar estanteria a una biblioteca\n"; // AGREGADO: Caso independiente
    std::cout << "7: Consultar un libro\n";
    std::cout << "8: Listado de inventario\n";
    std::cout << "9: Conteo de inventario\n";
    std::cout << "10: Actualizar el inventario\n";
    std::cout << "11: Registrar un Estudiante\n";                  
    std::cout << "12: Registrar prestamo de libro\n";               
    std::cout << "13: Listar prestamos por Biblioteca\n";          
    std::cout << "14: Listar libros prestados por Estudiante\n";    
    std::cout << "0: Finalizacion de operacion del sistema\n";
    std::cout << "Seleccione una opcion: ";
}
// Procesa el registro de un autor
void ejecutarRegistroAutor(Sistema& sistema) {
    std::cout << "\n--- Registrar Autor ---\n";
    std::string nombre, fechaNacimiento, nacionalidad;

    limpiarBuffer();
    std::cout << "Ingrese el nombre del autor (o '0' para salir): ";
    std::getline(std::cin, nombre);

    if (nombre == "0") {
        std::cout << "-> Operacion cancelada.\n";
        return;
    }

    std::cout << "Ingrese la fecha de nacimiento (o presione ENTER para omitir): ";
    std::getline(std::cin, fechaNacimiento);
    if (fechaNacimiento.empty()) fechaNacimiento = "No registrado";

    std::cout << "Ingrese la nacionalidad (o presione ENTER para omitir): ";
    std::getline(std::cin, nacionalidad);
    if (nacionalidad.empty()) nacionalidad = "No registrado";

    // Llama directamente a la funcion unificada
    sistema.registrarAutor(nombre, fechaNacimiento, nacionalidad);
}

// Procesa el registro de un libro
void ejecutarRegistroLibro(Sistema& sistema) {
    std::cout << "\n--- Registrar Libro ---\n";
    Autor* autorSeleccionado = nullptr;

    if (!sistema.getAutores().empty()) {
        int respAutor = 0;
        std::cout << "Desea asociar un autor existente? (1: Si / 2: No (Anonimo) / 0: Salir): ";
        std::cin >> respAutor;

        if (respAutor == 0) return;
        if (respAutor == 1) {
            sistema.mostrarAutores();
            int indiceAutor = 0;
            std::cout << "Seleccione el numero del autor: ";
            std::cin >> indiceAutor;
            if (indiceAutor >= 1 && indiceAutor <= (int)sistema.getAutores().size()) {
                autorSeleccionado = sistema.getAutores()[indiceAutor - 1];
            }
        }
    }

    std::string titulo;
    int isbn = 0, anio = 0;

    limpiarBuffer();
    std::cout << "Ingrese el titulo del libro: ";
    std::getline(std::cin, titulo);

    std::cout << "Ingrese el ISBN (numero entero): ";
    std::cin >> isbn;

    std::cout << "Ingrese el anio de publicacion (0 si lo desconoce): ";
    std::cin >> anio;

    // Llama directamente a la funcion unificada
    sistema.registrarLibro(titulo, isbn, anio, autorSeleccionado);
}

//  Procesa el registro de una estanteria
void ejecutarRegistroEstante(Sistema& sistema) {
    std::cout << "\n--- Registrar Estanteria ---\n";
    std::string nombreEstante;

    limpiarBuffer();

    std::cout << "Ingrese el nombre o identificador de la estanteria (o '0' para salir): ";
    std::getline(std::cin, nombreEstante);

    if (nombreEstante == "0") {
        std::cout << "-> Operacion cancelada. Volviendo al menu principal...\n";
        return;
    }

    sistema.registrarEstante(nombreEstante);
}
//  Procesa la asignacion de ejemplares de un libro a un estante
void ejecutarRegistroEjemplar(Sistema& sistema) {
    std::cout << "\n--- Registrar Ejemplar ---\n";

    if (sistema.getLibros().empty()) {
        std::cout << "-> No hay libros registrados en el sistema. Registre un libro primero (Opcion 2).\n";
        return;
    }

    if (sistema.getEstantes().empty()) {
        std::cout << "-> No hay estanterias registradas en el sistema. Registre una estanteria primero (Opcion 3).\n";
        return;
    }

    sistema.mostrarLibros();
    int indiceLibro = 0;
    std::cout << "Seleccione el numero del libro (o 0 para salir): ";
    std::cin >> indiceLibro;

    if (indiceLibro == 0) {
        std::cout << "-> Operacion cancelada. Volviendo al menu principal...\n";
        return;
    }

    if (indiceLibro < 1 || indiceLibro > (int)sistema.getLibros().size()) {
        std::cout << "-> Seleccion invalida de libro. Volviendo al menu principal...\n";
        return;
    }

    Libro* libroSeleccionado = sistema.getLibros()[indiceLibro - 1];

    sistema.mostrarEstantes();
    int indiceEstante = 0;
    std::cout << "Seleccione el numero de la estanteria (o 0 para salir): ";
    std::cin >> indiceEstante;

    if (indiceEstante == 0) {
        std::cout << "-> Operacion cancelada. Volviendo al menu principal...\n";
        return;
    }

    if (indiceEstante < 1 || indiceEstante > (int)sistema.getEstantes().size()) {
        std::cout << "-> Seleccion invalida de estanteria. Volviendo al menu principal...\n";
        return;
    }

    Estante* estanteSeleccionado = sistema.getEstantes()[indiceEstante - 1];

    int cantidad = 0;
    std::cout << "Ingrese la cantidad de ejemplares a agregar (o 0 para salir): ";
    std::cin >> cantidad;

    if (cantidad <= 0) {
        std::cout << "-> Operacion cancelada o cantidad invalida. Volviendo al menu principal...\n";
        return;
    }

    sistema.registrarEjemplar(libroSeleccionado, estanteSeleccionado, cantidad);
}
//  Procesa la creacion de una biblioteca y la asignacion de sus estantes
// FUNCION MODIFICADA: Procesa exclusivamente el registro de la biblioteca
void ejecutarRegistroBiblioteca(Sistema& sistema) {
    std::cout << "\n--- Registrar Biblioteca ---\n";
    std::string facultad, nombre;

    limpiarBuffer();

    std::cout << "Ingrese la facultad (o '0' para salir): ";
    std::getline(std::cin, facultad);

    if (facultad == "0") {
        std::cout << "-> Operacion cancelada. Volviendo al menu principal...\n";
        return;
    }

    std::cout << "Ingrese el nombre de la biblioteca (o '0' para salir): ";
    std::getline(std::cin, nombre);

    if (nombre == "0") {
        std::cout << "-> Operacion cancelada. Volviendo al menu principal...\n";
        return;
    }

    
    sistema.registrarBiblioteca(facultad, nombre);
}
//  Maneja de forma independiente la asignacion de una estanteria a una biblioteca
void ejecutarAsignacionEstanteABiblioteca(Sistema& sistema) {
    std::cout << "\n--- Asignar Estanteria a Biblioteca ---\n";

    if (sistema.getBibliotecas().empty()) {
        std::cout << "-> No hay bibliotecas registradas en el sistema. Registre una biblioteca primero (Opcion 5).\n";
        return;
    }

    if (sistema.getEstantes().empty()) {
        std::cout << "-> No hay estanterias registradas en el sistema. Registre una estanteria primero (Opcion 3).\n";
        return;
    }

    sistema.mostrarBibliotecas();
    int indiceBiblioteca = 0;
    std::cout << "Seleccione el numero de la biblioteca (o 0 para salir): ";
    std::cin >> indiceBiblioteca;

    if (indiceBiblioteca == 0) {
        std::cout << "-> Operacion cancelada. Volviendo al menu principal...\n";
        return;
    }

    if (indiceBiblioteca < 1 || indiceBiblioteca > (int)sistema.getBibliotecas().size()) {
        std::cout << "-> Seleccion invalida de biblioteca. Volviendo al menu principal...\n";
        return;
    }

    Biblioteca* bibliotecaSeleccionada = sistema.getBibliotecas()[indiceBiblioteca - 1];

    sistema.mostrarEstantes();
    int indiceEstante = 0;
    std::cout << "Seleccione el numero de la estanteria a asignar (o 0 para salir): ";
    std::cin >> indiceEstante;

    if (indiceEstante == 0) {
        std::cout << "-> Operacion cancelada. Volviendo al menu principal...\n";
        return;
    }

    if (indiceEstante < 1 || indiceEstante > (int)sistema.getEstantes().size()) {
        std::cout << "-> Seleccion invalida de estanteria. Volviendo al menu principal...\n";
        return;
    }

    Estante* estanteSeleccionado = sistema.getEstantes()[indiceEstante - 1];

    sistema.asignarEstanteABiblioteca(bibliotecaSeleccionada, estanteSeleccionado);
}
//  Consulta la disponibilidad de un libro por su titulo
void ejecutarConsultaLibro(Sistema& sistema) {
    std::cout << "\n--- Consultar Disponibilidad de Libro ---\n";

    if (sistema.getBibliotecas().empty()) {
        std::cout << "-> No hay bibliotecas registradas en el sistema para consultar.\n";
        return;
    }

    std::string tituloConsultar;
    limpiarBuffer();

    std::cout << "Ingrese el titulo del libro a consultar (o '0' para salir): ";
    std::getline(std::cin, tituloConsultar);

    if (tituloConsultar == "0") {
        std::cout << "-> Operacion cancelada. Volviendo al menu principal...\n";
        return;
    }

    sistema.consultarDisponibilidadLibro(tituloConsultar);
}
//  Muestra el listado de inventario de una biblioteca elegida
void ejecutarListadoInventario(Sistema& sistema) {
    std::cout << "\n--- Listado de Inventario ---\n";

    if (sistema.getBibliotecas().empty()) {
        std::cout << "-> No hay bibliotecas registradas en el sistema.\n";
        return;
    }

    sistema.mostrarBibliotecas();
    int indiceBiblio = 0;
    std::cout << "Seleccione el numero de la biblioteca a consultar inventario (o 0 para salir): ";
    std::cin >> indiceBiblio;

    if (indiceBiblio == 0) {
        std::cout << "-> Operacion cancelada. Volviendo al menu principal...\n";
        return;
    }

    if (indiceBiblio < 1 || indiceBiblio > (int)sistema.getBibliotecas().size()) {
        std::cout << "-> Seleccion invalida de biblioteca. Volviendo al menu principal...\n";
        return;
    }

    sistema.mostrarInventarioBiblioteca(indiceBiblio - 1);
}
//  Realiza el conteo total de ejemplares de una biblioteca
void ejecutarConteoInventario(Sistema& sistema) {
    std::cout << "\n--- Conteo de Inventario ---\n";

    if (sistema.getBibliotecas().empty()) {
        std::cout << "-> No hay bibliotecas registradas en el sistema.\n";
        return;
    }

    sistema.mostrarBibliotecas();
    int indiceBiblioteca = 0;
    std::cout << "Seleccione el numero de la biblioteca para realizar el conteo (o 0 para salir): ";
    std::cin >> indiceBiblioteca;

    if (indiceBiblioteca == 0) {
        std::cout << "-> Operacion cancelada. Volviendo al menu principal...\n";
        return;
    }

    if (indiceBiblioteca < 1 || indiceBiblioteca > (int)sistema.getBibliotecas().size()) {
        std::cout << "-> Seleccion invalida de biblioteca. Volviendo al menu principal...\n";
        return;
    }

    sistema.contarInventarioBiblioteca(indiceBiblioteca - 1);
}
//  Permite actualizar las cantidades de un libro en un estante
void ejecutarActualizacionInventario(Sistema& sistema) {
    std::cout << "\n--- Actualizar Inventario ---\n";

    if (sistema.getEstantes().empty()) {
        std::cout << "-> No hay estanterias registradas en el sistema.\n";
        return;
    }

    sistema.mostrarEstantes();
    int indiceEstante = 0;
    std::cout << "Seleccione el numero de la estanteria (o 0 para salir): ";
    std::cin >> indiceEstante;

    if (indiceEstante == 0) {
        std::cout << "-> Operacion cancelada. Volviendo al menu principal...\n";
        return;
    }

    if (indiceEstante < 1 || indiceEstante > (int)sistema.getEstantes().size()) {
        std::cout << "-> Seleccion invalida de estanteria.\n";
        return;
    }

    Estante* estanteSeleccionado = sistema.getEstantes()[indiceEstante - 1];
    const std::vector<Libro*>& librosEstante = estanteSeleccionado->getLibros();
    const std::vector<int>& cantidadesEstante = estanteSeleccionado->getCantidades();

    if (librosEstante.empty()) {
        std::cout << "-> La estanteria seleccionada no tiene libros registrados.\n";
        return;
    }

    std::cout << "\n=== LIBROS EN LA ESTANTERIA: " << estanteSeleccionado->getNombre() << " ===\n";
    for (size_t i = 0; i < librosEstante.size(); ++i) {
        std::cout << i + 1 << ". Libro: " << librosEstante[i]->getTitulo()
                  << " | Cantidad actual: " << cantidadesEstante[i] << "\n";
    }

    int indiceLibro = 0;
    std::cout << "Seleccione el numero del libro a actualizar (o 0 para salir): ";
    std::cin >> indiceLibro;

    if (indiceLibro == 0) {
        std::cout << "-> Operacion cancelada. Volviendo al menu principal...\n";
        return;
    }

    if (indiceLibro < 1 || indiceLibro > (int)librosEstante.size()) {
        std::cout << "-> Seleccion invalida de libro.\n";
        return;
    }

    Libro* libroSeleccionado = librosEstante[indiceLibro - 1];

    int nuevaCantidad = 0;
    std::cout << "Ingrese la nueva cantidad total disponible (0 o mayor): ";
    std::cin >> nuevaCantidad;

    if (nuevaCantidad < 0) {
        std::cout << "-> Cantidad invalida. Debe ser un numero mayor o igual a 0.\n";
        return;
    }

    sistema.actualizarInventario(estanteSeleccionado, libroSeleccionado, nuevaCantidad);
}

//  Ejecuta la captura interactiva para registrar un estudiante
void ejecutarRegistroEstudiante(Sistema& sistema) {
    std::cout << "\n--- Registrar Estudiante ---\n";
    std::string codigo, nombre;

    limpiarBuffer();
    std::cout << "Ingrese el codigo del estudiante (o '0' para salir): ";
    std::getline(std::cin, codigo);

    if (codigo == "0") {
        std::cout << "-> Operacion cancelada. Volviendo al menu principal...\n";
        return;
    }

    std::cout << "Ingrese el nombre completo del estudiante: ";
    std::getline(std::cin, nombre);

    sistema.registrarEstudiante(codigo, nombre);
}
// Ejecuta la captura interactiva para registrar un prestamo
void ejecutarRegistroPrestamo(Sistema& sistema) {
    std::cout << "\n--- Registrar Prestamo de Libro ---\n";

    if (sistema.getEstudiantes().empty()) {
        std::cout << "-> No hay estudiantes registrados. Registre un estudiante primero (Opcion 11).\n";
        return;
    }

    if (sistema.getBibliotecas().empty()) {
        std::cout << "-> No hay bibliotecas registradas en el sistema.\n";
        return;
    }

    // 1. Seleccionar estudiante
    sistema.mostrarEstudiantes();
    int indiceEstudiante = 0;
    std::cout << "Seleccione el numero del estudiante (o 0 para salir): ";
    std::cin >> indiceEstudiante;

    if (indiceEstudiante == 0) {
        std::cout << "-> Operacion cancelada. Volviendo al menu principal...\n";
        return;
    }

    if (indiceEstudiante < 1 || indiceEstudiante > (int)sistema.getEstudiantes().size()) {
        std::cout << "-> Seleccion invalida de estudiante. Volviendo al menu principal...\n";
        return;
    }

    Estudiante* estudianteSeleccionado = sistema.getEstudiantes()[indiceEstudiante - 1];

    // 2. Seleccionar biblioteca
    sistema.mostrarBibliotecas();
    int indiceBiblioteca = 0;
    std::cout << "Seleccione el numero de la biblioteca (o 0 para salir): ";
    std::cin >> indiceBiblioteca;

    if (indiceBiblioteca == 0) {
        std::cout << "-> Operacion cancelada. Volviendo al menu principal...\n";
        return;
    }

    if (indiceBiblioteca < 1 || indiceBiblioteca > (int)sistema.getBibliotecas().size()) {
        std::cout << "-> Seleccion invalida de biblioteca. Volviendo al menu principal...\n";
        return;
    }

    Biblioteca* bibliotecaSeleccionada = sistema.getBibliotecas()[indiceBiblioteca - 1];

    const std::vector<Estante*>& estantesBiblio = bibliotecaSeleccionada->getEstantes();
    if (estantesBiblio.empty()) {
        std::cout << "-> La biblioteca seleccionada no tiene estanterias asignadas.\n";
        return;
    }

    // 3. Seleccionar estanteria
    std::cout << "\n=== ESTANTERIAS EN LA BIBLIOTECA: " << bibliotecaSeleccionada->getNombre() << " ===\n";
    for (size_t i = 0; i < estantesBiblio.size(); ++i) {
        std::cout << i + 1 << ". ";
        estantesBiblio[i]->print();
    }

    int indiceEstante = 0;
    std::cout << "Seleccione el numero de la estanteria (o 0 para salir): ";
    std::cin >> indiceEstante;

    if (indiceEstante == 0) {
        std::cout << "-> Operacion cancelada. Volviendo al menu principal...\n";
        return;
    }

    if (indiceEstante < 1 || indiceEstante > (int)estantesBiblio.size()) {
        std::cout << "-> Seleccion invalida de estanteria. Volviendo al menu principal...\n";
        return;
    }

    Estante* estanteSeleccionado = estantesBiblio[indiceEstante - 1];

    // 4. Seleccionar libro
    const std::vector<Libro*>& librosEstante = estanteSeleccionado->getLibros();
    const std::vector<int>& cantidadesEstante = estanteSeleccionado->getCantidades();

    if (librosEstante.empty()) {
        std::cout << "-> La estanteria seleccionada no tiene libros registrados.\n";
        return;
    }

    std::cout << "\n=== LIBROS DISPONIBLES EN LA ESTANTERIA: " << estanteSeleccionado->getNombre() << " ===\n";
    for (size_t i = 0; i < librosEstante.size(); ++i) {
        std::cout << i + 1 << ". Libro: " << librosEstante[i]->getTitulo()
                  << " | Cantidad disponible: " << cantidadesEstante[i] << "\n";
    }

    int indiceLibro = 0;
    std::cout << "Seleccione el numero del libro a prestar (o 0 para salir): ";
    std::cin >> indiceLibro;

    if (indiceLibro == 0) {
        std::cout << "-> Operacion cancelada. Volviendo al menu principal...\n";
        return;
    }

    if (indiceLibro < 1 || indiceLibro > (int)librosEstante.size()) {
        std::cout << "-> Seleccion invalida de libro. Volviendo al menu principal...\n";
        return;
    }

    Libro* libroSeleccionado = librosEstante[indiceLibro - 1];

    sistema.registrarPrestamo(estudianteSeleccionado, bibliotecaSeleccionada, estanteSeleccionado, libroSeleccionado);
}
// AGREGADO: Ejecuta la consulta de ejemplares prestados dada una biblioteca
void ejecutarListarPrestamosPorBiblioteca(Sistema& sistema) {
    std::cout << "\n--- Listar Ejemplares Prestados por Biblioteca ---\n";

    if (sistema.getBibliotecas().empty()) {
        std::cout << "-> No hay bibliotecas registradas en el sistema.\n";
        return;
    }

    sistema.mostrarBibliotecas();
    int indiceBiblioteca = 0;
    std::cout << "Seleccione el numero de la biblioteca (o 0 para salir): ";
    std::cin >> indiceBiblioteca;

    if (indiceBiblioteca == 0) {
        std::cout << "-> Operacion cancelada. Volviendo al menu principal...\n";
        return;
    }

    if (indiceBiblioteca < 1 || indiceBiblioteca > (int)sistema.getBibliotecas().size()) {
        std::cout << "-> Seleccion invalida de biblioteca. Volviendo al menu principal...\n";
        return;
    }

    Biblioteca* bibliotecaSeleccionada = sistema.getBibliotecas()[indiceBiblioteca - 1];
    sistema.listarPrestamosPorBiblioteca(bibliotecaSeleccionada);
}

//  Ejecuta la consulta de libros prestados dado un estudiante
void ejecutarListarPrestamosPorEstudiante(Sistema& sistema) {
    std::cout << "\n--- Listar Libros Prestados por Estudiante ---\n";

    if (sistema.getEstudiantes().empty()) {
        std::cout << "-> No hay estudiantes registrados en el sistema.\n";
        return;
    }

    sistema.mostrarEstudiantes();
    int indiceEstudiante = 0;
    std::cout << "Seleccione el numero del estudiante (o 0 para salir): ";
    std::cin >> indiceEstudiante;

    if (indiceEstudiante == 0) {
        std::cout << "-> Operacion cancelada. Volviendo al menu principal...\n";
        return;
    }

    if (indiceEstudiante < 1 || indiceEstudiante > (int)sistema.getEstudiantes().size()) {
        std::cout << "-> Seleccion invalida de estudiante. Volviendo al menu principal...\n";
        return;
    }

    Estudiante* estudianteSeleccionado = sistema.getEstudiantes()[indiceEstudiante - 1];
    sistema.listarPrestamosPorEstudiante(estudianteSeleccionado);
}

int main() {
    Sistema sistema("UNICAUCA");
    int opcion = -1;

    do {
        mostrarMenu(sistema.getNombreInstitucion());
        std::cin >> opcion;

        switch (opcion) {
            case 1: ejecutarRegistroAutor(sistema); break;
            case 2: ejecutarRegistroLibro(sistema); break;
            case 3: ejecutarRegistroEstante(sistema); break;
            case 4: ejecutarRegistroEjemplar(sistema); break;
            case 5: ejecutarRegistroBiblioteca(sistema); break;
            case 6: ejecutarAsignacionEstanteABiblioteca(sistema); break;
            case 7: ejecutarConsultaLibro(sistema); break;
            case 8: ejecutarListadoInventario(sistema); break;
            case 9: ejecutarConteoInventario(sistema); break;
            case 10: ejecutarActualizacionInventario(sistema); break;
            case 11: ejecutarRegistroEstudiante(sistema); break;                 // AGREGADO
            case 12: ejecutarRegistroPrestamo(sistema); break;                   // AGREGADO
            case 13: ejecutarListarPrestamosPorBiblioteca(sistema); break;       // AGREGADO
            case 14: ejecutarListarPrestamosPorEstudiante(sistema); break;       // AGREGADO
            case 0: std::cout << "\nFinalizando operacion del sistema. Hasta luego!\n"; break;
            default: std::cout << "\nOpcion no valida. Por favor, intente de nuevo.\n"; break;
        }
    } while (opcion != 0);

    return 0;
}