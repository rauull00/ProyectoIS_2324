#ifndef GESTION_ACTIVIDADES_H
#define GESTION_ACTIVIDADES_H

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <cstdlib>

#define MAX_LINEA 256

void get_lista_actividades();
void add_actividad();
void delete_actividad();

class Actividad {

private:
    int idc_;
    std::string nombre_actividad_;
    std::string descripcion_actividad_;
    int aforo_; 

public:
    Actividad(int idc, std::string nombre_actividad, std::string descripcion_actividad, int aforo);

    inline int get_idc() { return idc_; }
    inline std::string get_nombre() { return nombre_actividad_; }
    inline void set_nombre(std::string nombre) { nombre_actividad_ = nombre; }
    inline std::string get_descripcion() { return descripcion_actividad_; }
    inline void set_description(std::string descripcion) { descripcion_actividad_ = descripcion; }
    inline int get_aforo() { return aforo_; } 
    inline void set_aforo(int aforo) { aforo_ = aforo; } 

    bool set_descripcion();

};

std::list<Actividad> cargar_actividades();

Actividad::Actividad(int idc, std::string nombre_actividad, std::string descripcion_actividad, int aforo) {
    idc_ = idc;
    nombre_actividad_ = nombre_actividad;
    descripcion_actividad_ = descripcion_actividad;
    aforo_ = aforo;
}

void get_lista_actividades() {
    std::ifstream lista;
    lista.open("data/Lista_actividades.txt");
    std::string linea;

    while (getline(lista, linea)) { // Coge el nombre del actividad
        std::cout << linea;         // Imprime por pantalla el nombre del actividad
        std::cout << '\n';
        getline(lista, linea); // Linea del id del actividad
        getline(lista, linea); // Linea de la descripcion
        getline(lista, linea); // Linea para el aforo
    }

    lista.close();
}

void add_actividad() {
    std::ofstream lista("data/Lista_actividades.txt", std::ios::app);

    std::string linea;
    std::string nombre;
    std::string descripcion;
    int idc;
    int aforo; 

    std::cout << "Introduzca el nombre de la actividad\n";
    std::getline(std::cin, nombre);

    std::cout << "Introduzca el id de la actividad\n";
    std::cin >> idc;
    std::cin.ignore(100, '\n');

    std::cout << "Introduzca la nueva descripción\n";
    std::getline(std::cin, descripcion);

    std::cout << "Introduzca el aforo\n";
    std::cin >> aforo;
    std::cin.ignore(100, '\n');

    Actividad c(idc, nombre, descripcion, aforo);

    lista << c.get_nombre() << std::endl;
    lista << c.get_idc() << std::endl;
    lista << c.get_descripcion() << std::endl;
    lista << c.get_aforo() << std::endl; // Nueva línea para el aforo

    lista.close();
}

void delete_actividad(){

	std::list<Actividad> lactividades;
	lactividades = cargar_actividades();
	int idc;

	std::cout << "Intoduzca el id de la actividad a eliminar\n";
	std::cin >> idc;
	std::cin.ignore(100, '\n');

	for(auto it=lactividades.begin(); it != lactividades.end(); it++){
		if((*it).get_idc() == idc){
			(*it).set_nombre("-1");
		}
	}
	std::ofstream lista2;
	lista2.open("data/Lista_actividades_aux.txt");
	for (auto it= lactividades.begin(); it != lactividades.end(); it++){
		if((*it).get_nombre() != "-1"){
			lista2 << (*it).get_nombre() << std::endl;
			lista2 << (*it).get_idc() << std::endl;
			lista2 << (*it).get_descripcion() << std::endl;
		}
	}
	lista2.close();

	remove("data/Lista_actividades.txt");
	rename("data/Lista_actividades_aux.txt", "data/Lista_actividades.txt");

}
void limpiarPantalla2() {
    // Función para limpiar la pantalla en sistemas Windows
    #ifdef _WIN32
        system("cls");
    #else
    // Función para limpiar la pantalla en sistemas Unix/Linux
        system("clear");
    #endif
}

bool set_descripcion(){
	std::string descripcion;
	std::string nombre;
	std::list<Actividad> lactividades;
	lactividades = cargar_actividades();

	std::cout << "Introduzca el nombre de la actividad\n";
	std::getline(std::cin, nombre);


	std::cout << "Intoduzca la nueva descripción\n";
	std::getline(std::cin, descripcion);


	for(auto it=lactividades.begin(); it != lactividades.end(); it++){
		if((*it).get_nombre()== nombre){
			(*it).set_description(descripcion);

			std::ofstream lista2;
			lista2.open("data/Lista_actividades_aux.txt");
			for (auto it1= lactividades.begin(); it1 != lactividades.end(); it1++){

				lista2 << (*it1).get_idc() << std::endl;
				lista2 << (*it1).get_nombre() << std::endl;
				lista2 << (*it1).get_descripcion() << std::endl;

			}
			lista2.close();

			remove("data/Lista_actividades.txt");
			rename("data/Lista_actividades_aux.txt", "data/Lista_actividades.txt");

			return true;
		}
	}

	return false;

}

std::list<Actividad> cargar_actividades() {
    std::list<Actividad> listac;
    std::string id;
    int id1;
    std::string nombre;
    std::string descripcion;
    std::string aforo; // Cambiado a string

    std::ifstream lista;
    lista.open("data/Lista_actividades.txt");

    while (!lista.eof()) {
        getline(lista, nombre);
        getline(lista, id);
        id1 = stoi(id);
        getline(lista, descripcion);
        getline(lista, aforo); // Lee el aforo como string
        Actividad c(id1, nombre, descripcion, stoi(aforo)); // Convierte aforo a entero aquí
        listac.push_back(c);
    }

    return listac;
}

#endif
