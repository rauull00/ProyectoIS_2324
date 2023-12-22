#include <iostream>
#include <string>
#include "gestion_actividades.h"
#include "inscripcion.h"
#include <regex> //Expresiones regulares para verificar el formato del mail


void menu_inicio_sesion();
void menu_admin();
void menu_director();
void menu_usuario();
void menu_visitante();
void inscripcion();
void gestion();
void visualizar();
void asignarDirector();
void limpiarPantalla();
using namespace std;
/*
Privilegios

	0 = Administrador
	3 = Director academico
	5 = Usuario

*/

int main(){

	menu_inicio_sesion();

}

void menu_inicio_sesion(){
	int op;
	std::cout << "|======================================================|";
		std::cout << "\n|******** Bienvenidos a Gestion ActividadesRCM ********|";
		std::cout << "\n|======================================================|";
		std::cout << "\n| Por favor, seleccione el numero de la opcion deseada:|\n";
		std::cout << "| 1. Iniciar sesion                                    |\n";
		std::cout << "| 2. Entrar como visitante                             |\n";
		std::cout << "| 3. Crear cuenta de usuario                           |\n";
		std::cout << "| 0. Salir                                             |\n";
		std::cout << "|======================================================|\n\n";
		std::cout << "Opcion: ";
	std::cin >> op;
	std::cin.ignore(1000, '\n');
	limpiarPantalla();
	std::string email;
	std::string contrasena;
	int priv;
	int count = 0;

	switch(op){
		case 0:
			exit(EXIT_SUCCESS);
		break;
		case 1:

			while(count < 3){
				std::cout << "|=========================================|";
				std::cout << "\nEscriba su email\n";
				std::getline(std::cin, email);
				std::cout << "Escriba su contrasena\n";
				std::getline(std::cin, contrasena);
				priv = inicio_sesion(email, contrasena);
				if(priv == 1){
					std::cout << "Su email o contrasena no son correctos\n";
					count++;
					std::cout << "Le quedan " << 3-count << " intentos\n";
				}else {
					count=3;
				}
			}
			limpiarPantalla();
			if(priv == 0){
				menu_admin();
			}else if(priv == 3){
				menu_director();
			}else if(priv == 5){
				menu_usuario();
			}else if(priv == 1){
				std::cout << "Se ha quedado sin intentos de inicio de sesion, vuelva mas tarde\n";
				exit(EXIT_FAILURE);
			}

		break;
		case 2:
			menu_visitante();
		break;
		case 3:
			std::string nombre;
			int id=0;
			std::string email;
			std::string contrasena;
			std::cout << "|=============================================|\n";
						std::cout << "|====           REGISTRAR USUARIO          ===|\n";
						std::cout << "|=============================================|\n";
						std::cout << "| Introduzca su nombre: ";
			std::cin >> nombre;

			while(existe_id(id)){
				std::cout << "Introduzca su id\n" << std::endl;
				std::cin >> id;
				std::cin.ignore();
				if(existe_id(id)){
					std::cout << "Escriba otro id, el id escogido ya esta en uso\n";
				}
			}

			std::regex formato("^\\w+@uco\\.es$");
			do {
        		std::cout << "| Introduzca su email: ";
        		std::getline(std::cin, email);
        		if (!std::regex_match(email, formato)) {
            	std::cout << "Correo electrónico no válido" << std::endl;
            	std::cout << "Debe seguir el formato <CadenaCaracteres@uco.es>" << std::endl;
        		}
    		} while (!std::regex_match(email, formato));

			std::cout << "Introduzca su contrasena\n" << std::endl;
			std::getline(std::cin, contrasena);

			crear_usuario(nombre, id, email, contrasena, 5);

			priv = inicio_sesion(email, contrasena);
			menu_usuario();
		break;
	}

}


void menu_admin(){

	int opc=0;

	std::cout << "|=======================================================|\n";
		std::cout << "|====            SESION INICIADA CON EXITO           ===|\n";
		std::cout << "|=======================================================|\n";
		std::cout << "|====************** MENU ADMINISTRADOR **************===|\n";
		std::cout << "|=======================================================|\n";
		std::cout << "| Por favor, seleccione el numero de la opcion deseada: |\n";
		std::cout << "| 1. Asignar Administrador                              |\n";
		std::cout << "| 2. Gestion de actividades                             |\n";
		std::cout << "| 3. Visualizar actividades                             |\n";
		std::cout << "| 0. Salir del programa                                 |\n";
		std::cout << "|=======================================================|\n\n";
	std::cin >> opc;
	std::cin.ignore(1000, '\n');
	limpiarPantalla();
	while(opc != 4){
		switch(opc){
			case 1:
				asignarDirector();
				exit(EXIT_SUCCESS);
			break;
			case 2:
				gestion();
			break;
			case 3:
				visualizar();
			break;
			case 4:
				exit(EXIT_SUCCESS);
			break;
		}
	}
}

void menu_director(){

	int opc=0;

		std::cout << "|=======================================================|\n";
		std::cout << "|====            SESION INICIADA CON EXITO           ===|\n";
		std::cout << "|=======================================================|\n";
		std::cout << "|====*********** MENU DIRECTOR ACADEMICO ************===|\n";
		std::cout << "|=======================================================|\n";
		std::cout << "| Por favor, seleccione el numero de la opcion deseada: |\n";
		std::cout << "| 1. Gestion de actividades                             |\n";
		std::cout << "| 2. Visualizar actividades                             |\n";
		std::cout << "| 0. Salir del programa                                 |\n";
		std::cout << "|=======================================================|\n\n";
	std::cin >> opc;
	std::cin.ignore(1000, '\n');
	limpiarPantalla();
	while(opc != 3){
		switch(opc){
			case 1:
				gestion();
			break;
			case 2:
				visualizar();
			break;
			case 3:
				exit(EXIT_SUCCESS);
			break;
		}
	}
}

void menu_usuario(){

	int opc=0;
	std::cout << "|=======================================================|\n";
		std::cout << "|====            SESION INICIADA CON EXITO           ===|\n";
		std::cout << "|=======================================================|\n";
		std::cout <<"| Por favor, seleccione el numero de la opcion deseada: |\n";
		std::cout << "| 1. Preinscribirse en una actividad                    |\n";
		std::cout << "| 2. Visualizar actividades                             |\n";
		std::cout << "| 0. Salir del programa                                 |\n";
		std::cout << "|=======================================================|\n";
	std::cin >> opc;
	std::cin.ignore(1000, '\n');
	limpiarPantalla();
	while(opc != 0){
		switch(opc){
			case 0:
				exit(EXIT_SUCCESS);
			break;
			case 1:
				inscripcion();
			break;
			case 2:
				visualizar();
			break;
		}
	}
}

void menu_visitante(){

	int opc=0;
	std::cout << "|=======================================================|\n";
		std::cout << "| Por favor, seleccione el numero de la opcion deseada: |\n";
		std::cout << "| 1. Visualizar Actividades Academicas                  |\n";
		std::cout << "| 0. Salir del programa                                 |\n";
		std::cout << "|=======================================================|\n\n";
	std::cin >> opc;
	std::cin.ignore(1000, '\n');
	limpiarPantalla();
	while(opc != 0){
		switch(opc){
			case 0:
				exit(EXIT_SUCCESS);
			break;
			case 1:
				visualizar();
			break;
		}
	}
}


void inscripcion(){

	int opc1=0;

	std::cout << "|=======================================================|\n";
		std::cout << "| Por favor, seleccione el numero de la opcion deseada: |\n";
		std::cout << "| 1. Comenzar la preinscripcion                         |\n";
		std::cout << "| 0. Salir                                              |\n";
		std::cout << "|=======================================================|\n";

	std::cin >> opc1;
	std::cin.ignore(1000, '\n');
	limpiarPantalla();
	switch(opc1){

		case 0:
			exit(EXIT_SUCCESS);
		break;

		case 1:
			std::string actividad;
			std::cout << "|===========================================================|\n";
						std::cout << "| Escriba el nombre de alguno de las siguientes actividades |\n\n";
			get_lista_actividades();
			std::getline(std::cin, actividad);
			if(!existe_actividad(actividad)){
				std::cout << "La actividad introducido no existe";
				exit(EXIT_FAILURE);
			}

			std::string nombre;
			std::string id;
			int id1;
			std::string privilegio;
			std::string email;
			std::string contrasena;

			std::ifstream lista("data/Inicio_sesion.txt");

			while(!lista.eof()){
				getline(lista, nombre);
				getline(lista, id);
				getline(lista, privilegio);
				getline(lista, email);
				getline(lista, contrasena);
				id1 = stoi(id);
				if(idg == id1){
					inscribir_alumno(actividad, nombre, id1, email, contrasena, 5);
					std::cout << "\n|===================================================|\n";
										std::cout << "| Se ha preinscrito con exito al curso seleccionado |\n";
										std::cout << "|===================================================|\n";
					lista.close();
					exit(EXIT_SUCCESS);
				}
			}
			lista.close();

		break;

		}
}

void gestion(){

	int opc2=0;
	std::list<Actividad> C;
	C = cargar_actividades();
		std::cout << "|=======================================================|\n";
			std::cout << "| Por favor, seleccione el numero de la opcion deseada: |\n";
			std::cout << "| 1. Anadir un actividad                                |\n";
			std::cout << "| 2. Borrar una actividad                               |\n";
			std::cout << "| 3. Listar alumnos de una actividad                    |\n";
			std::cout << "| 0. Salir del programa                                 |\n";
			std::cout << "|=======================================================|\n\n";
		std::cout << "\nOpcion: ";
	std::cin >> opc2;
	limpiarPantalla();
	std::cin.ignore(1000, '\n');

	switch(opc2){

		case 0:
			exit(EXIT_SUCCESS);
			break;

		case 1:
			add_actividad();
			std::cout << "Se ha anadido el actividad \n\n";
			break;

		case 2:
			delete_actividad();
			std::cout << "Se ha borrado el actividad \n\n";
		break;
		case 3:
			get_lista_users();
			std::cout << '\n';
		break;
	}
}

void visualizar(){

	int opc;
	std::string actividad;
	std::list<Actividad> C;
	C = cargar_actividades();

	std::cout << "|===============================================================|\n";
		std::cout << "|ACTIVIDADES :                                                  |\n";
		get_lista_actividades();
		std::cout << "|===============================================================|\n";
		std::cout << "| 1. Visualizar la descripcion de una actividad                 |\n";
		std::cout << "| 0. Salir                                                      |\n";
		std::cout << "|===============================================================|\n";

	std::cin >> opc;
	std::cin.ignore(1000, '\n');
	switch(opc){

		case 0:
			exit(EXIT_SUCCESS);
		break;

		case 1:
			std::cout << "Escriba el nombre de la actividad del que desea visualizar la descripcion\n";
			std::getline(std::cin, actividad);
			if(!existe_actividad(actividad)){
				std::cout << "La actividad introducida no existe\n";
				exit(EXIT_FAILURE);
			}
			for (auto it1 = C.begin(); it1 != C.end(); it1++){
				if ((*it1).get_nombre()== actividad){
					std::cout << (*it1).get_descripcion() << std::endl;
					std::cout << (*it1).get_aforo() << std::endl;
				}
			}
			std::cout << "\n";
		break;

	}
}
void asignarDirector(){

			std::string nombre;
			int id=0;
			std::string email;
			std::string contrasena;

			std::cout << "Introduzca el nombre\n" << std::endl;
			std::cin >> nombre;

			while(existe_id(id)){
				std::cout << "Introduzca su id\n" << std::endl;
				std::cin >> id;
				std::cin.ignore();
				if(existe_id(id)){
					std::cout << "Escriba otro id, el id escogido ya esta en uso\n";
				}
			}

			std::cout << "Introduzca el email\n" << std::endl;
			std::getline(std::cin, email);

			std::cout << "Introduzca la contrasena\n" << std::endl;
			std::getline(std::cin, contrasena);

			crear_usuario(nombre, id, email, contrasena, 3);
			std::cout<<"Se ha creado correctamente\n";
			menu_director();
}

void limpiarPantalla() {
    // Función para limpiar la pantalla en sistemas Windows
    #ifdef _WIN32
        system("cls");
    #else
    // Función para limpiar la pantalla en sistemas Unix/Linux
        system("clear");
    #endif
}

