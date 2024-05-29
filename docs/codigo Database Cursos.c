#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 50

/*-----------------ESTRUCTURAS DEL PROGRAMA----------------------*/

struct Profesor {                                        //STRUCT DEL PROFESOR
	char *nombreProfesor;                                //NOMBRE DEL PROFESOR
	char *apellidoProfesor;                              //APELLIDO DEL PROFESOR
	char *rutProfesor;                                   //RUT DEL PROFESOR
	int horario[8][5];                                   //MATRIZ QUE CONTIENE EL HORARIO DEL PROFESOR
};

struct nodoProfesor {                                    //NODO PROFESOR
	struct Profesor *datosProfesor;                      //STRUCT DEL PROFESOR
	struct nodoProfesor *sig;                            //SIGUIENTE NODO PROFESOR
};

struct nodoNotas {                                       //NODO NOTAS
	float nota;                                          //NOTA DEL ESTUDIANTE
	struct nodoNotas *sig;                               //SIGUIENTE NODO/NOTA
};

struct Asignatura {                                      //STRUCT DE LA ASIGNATURA
	char *nombreAsignatura;                              //NOMBRE DE LA ASIGNATURA
	struct nodoNotas *headNotas;                         //CABECERA DE LA LISTA DE NOTAS DEL ALUMNO
};

struct nodoAsignatura {                                  //NODO ASIGNATURA
	struct Asignatura *datosAsignatura;                  //STRUCT DE LA ASIGNATURA
	struct nodoAsignatura *sig;                          //SIGUIENTE NODO/ASIGNATURA
};

struct Alumno {                                          //STRUCT ALUMNO
	char *nombreAlumno;                                  //NOMBRE DEL ALUMNO
	char *apellidoAlumno;                                //APELLIDO DEL ALUMNO
	char *rutAlumno;                                     //RUT DEL ALUMNO
	char *cursoAlumno;                                   //CURSO DEL ALUMNO
	struct nodoAsignatura *headAsignatura;              //ASIGNATURAS O RAMOS QUE TIENE EL ALUMNO
};

struct nodoAlumno {                                      //NODO ALUMNO
	struct Alumno *datosAlumno;                          //STRUCT DEL ALUMNO
	struct nodoAlumno *sig;                              //SIGUIENTE NODO/ALUMNO
};

struct Curso {                                           //STRUCT CURSO
	char *nombreCurso;                                   //NOMBRE DEL CURSO
	int cantidadAlumnos;                                 //CANTIDAD DE ALUMNO QUE HAY EN EL CURSO
	struct nodoAsignatura *AsignaturaCurso;              //LISTA DE ASIGNATURAS QUE TIENE EL CURSO
	struct nodoAlumno *headAlumno;                       //LISTA DE ALUMNOS EN EL CURSO
};

struct nodoCurso {                                       //NODO CURSO
	struct Curso *datosCurso;                            //DATOS QUE CONTIENE EL CURSO
	struct nodoCurso *sig;                               //SIGUIENTE NODO/CURSO
};

struct Establecimiento {                                 //NODO PRINCIPAL DEL PROGRAMA ESTABLECIMIENTO
	struct nodoCurso *headCurso;                         //CABECERA DE LISTA DE CURSOS
	struct nodoProfesor *headProfesor;                   //CABECERA DE LISTA DE PROFESORES
};

struct Establecimiento *e;                               //STRUCT PRINCIPAL DEL PROGRAMA
													 /*---------------DECLARACION DE FUNCIONES Y PROCEDIMIENTOS------------------*/
void cargarProfesores(struct nodoProfesor **);
void guardarProfesores(struct nodoProfesor *);
//void cargarCursos(struct nodoCurso **);
void guardarCursos(struct nodoCurso *);
int soloNumerosCmd(char *);
int leerOpcion(int);
int validarHorario(int);
void volverMenu(int *);
void mostrarProfesores(struct nodoProfesor *);
void mayusculas(char *);
int soloNumeros(char *);
void llenarHorario(struct nodoProfesor *);
void imprimirHorario(struct nodoProfesor *);
struct nodoProfesor* buscarProfesor(char *, struct nodoProfesor *);
struct nodoProfesor* crearNodoProfesor(struct nodoProfesor *);
void mostrarProfesor(struct nodoProfesor *);
void agregarProfesor(struct nodoProfesor **);
void salir();
void errorMemoria(void *);
void eliminarProfesor(struct nodoProfesor **);
void modificarNombreDocente(struct nodoProfesor *);
void modificarApellidoDocente(struct nodoProfesor *);
void modificarRutDocente(struct nodoProfesor *);
void modificarProfesor(struct nodoProfesor **);
void mostrarCurso(struct nodoCurso *);
struct nodoCurso *buscarCurso(struct nodoCurso *, char *);
struct nodoCurso* crearNodoCurso(struct nodoCurso *);
void agregarCurso(struct nodoCurso **);
void modificaNombreCurso(struct nodoCurso **);
void eliminarCurso(struct nodoCurso **);
struct nodoAlumno* buscarAlumno(struct nodoCurso *, char *);
void mostrarAlumno(struct nodoCurso *);
void agregarAlumno(struct nodoCurso **);
void eliminarAlumno(struct nodoCurso **);
void modificarNombreAlumno(struct nodoAlumno *);
void modificarApellidoAlumno(struct nodoAlumno *);
void modificarAlumno(struct nodoCurso **);
struct nodoAsignatura* buscarAsignatura(struct nodoAsignatura *, char *);
struct nodoAsignatura* crearNodoAsignatura(struct nodoAsignatura *);
void agregarAsignatura(struct nodoAsignatura **);
void eliminarAsignatura(struct nodoAsignatura **);
void agregarNotasSegundo(struct nodoNotas **);
void agregarNotasPrimero(struct nodoAsignatura *);
void eliminarNotasSegundo(struct nodoNotas **);
void eliminarNotasPrimero(struct nodoAsignatura *);
void traspasoAsignatura(struct nodoAsignatura **, struct nodoAsignatura *);

/*---------------------------PROGRAMA PRINCIPAL-----------------------------*/

int main(void) {
	int opcion;   //OPCION INGRESADA POR EL USUARIO

	e = (struct Establecimiento*)malloc(sizeof(struct Establecimiento));
	e->headProfesor = NULL;
	e->headCurso = NULL;

	cargarProfesores(&e->headProfesor);
	//cargarCursos(&e->headCurso);
	//cargarArchivoCursos();
	do {
		/*MENU PRINCIPAL*/
		printf("        ===============================================================\n");
		printf("                            BIENVENIDO A TIMEWARD\n");
		printf("                                MENU PRINCIPAL\n");
		printf("        ===============================================================\n\n\n");
		printf("                           1- USUARIO ADMINISTRADOR\n");
		printf("                           2- USUARIO INVITADO\n");
		printf("                           3- SALIR DEL PROGRAMA\n\n");
		printf("                           INGRESE UNA DE LAS OPCIONES: ");

		opcion = leerOpcion(3);

		switch (opcion) {
		case 1:
			/*MENU DEL ADMINISTRADOR*/
			system("cls");
			printf("        ===============================================================\n");
			printf("                         SISTEMA DE INFORMACION - TIMEWARD\n");
			printf("                              USUARIO ADMINISTRADOR\n");
			printf("        ===============================================================\n\n\n");
			printf("                           1- BASE DE DATOS DOCENTES\n");
			printf("                           2- BASE DE DATOS ESTUDIANTES\n");
			printf("                           3- BASE DE DATOS CURSOS\n");
			printf("                           4- VOLVER AL MENU PRINCIPAL\n\n");
			printf("                           INGRESE UNA DE LAS OPCIONES: ");

			switch (leerOpcion(4)) {
			case 1:
				system("cls");
				printf("        ===============================================================\n");
				printf("                         SISTEMA DE INFORMACION - TIMEWARD\n");
				printf("                              BASE DE DATOS DOCENTES\n");
				printf("        ===============================================================\n\n\n");
				printf("                           1- MOSTRAR LISTA DE DOCENTES\n");
				printf("                           2- AGREGAR DOCENTE\n");
				printf("                           3- MODIFICAR DOCENTE\n");
				printf("                           4- ELIMINAR DOCENTE\n");
				printf("                           5- VOLVER AL MENU PRINCIPAL\n\n");
				printf("                           INGRESE UNA DE LAS OPCIONES: ");

				switch (leerOpcion(5)) {
				case 1:
					system("cls");
					//MOSTRAR LISTA DE DOCENTES
					mostrarProfesores(e->headProfesor);
					break;
				case 2:
					system("cls");
					//AGREGAR DOCENTE
					agregarProfesor(&e->headProfesor);
					guardarProfesores(e->headProfesor);
					break;
				case 3:
					system("cls");
					//MODIFICAR DOCENTE
					modificarProfesor(&e->headProfesor);
					guardarProfesores(e->headProfesor);
					break;
				case 4:
					system("cls");
					//ELIMINAR DOCENTE
					eliminarProfesor(&e->headProfesor);
					guardarProfesores(e->headProfesor);
					break;
				case 5:
					system("cls");
					//VOLVER AL MENU PRINCIPAL
					break;
				}
				break;
			case 2:
				system("cls");
				printf("        ===============================================================\n");
				printf("                         SISTEMA DE INFORMACION - TIMEWARD\n");
				printf("                             BASE DE DATOS ESTUDIANTES\n");
				printf("        ===============================================================\n\n\n");
				printf("                           1- MOSTRAR DATOS DEL ESTUDIANTE\n");
				printf("                           2- AGREGAR UN ESTUDIANTE\n");
				printf("                           3- MODIFICAR DATOS DEL UN ESTUDIANTE\n");
				printf("                           4- ELIMINAR UN ESTUDIANTE\n");
				printf("                           5- VOLVER AL MENU PRINCIPAL\n\n");
				printf("                           INGRESE UNA DE LAS OPCIONES: ");

				switch (leerOpcion(5)) {
				case 1:
					system("cls");
					//MOSTRAR ESTUDIANTE
					mostrarAlumno(e->headCurso);
					break;
				case 2:
					system("cls");
					//AGREGAR ESTUDIANTE
					agregarAlumno(&e->headCurso);
					guardarCursos(e->headCurso);
					break;
				case 3:
					system("cls");
					//MODIFICAR ESTUDIANTE
					modificarAlumno(&e->headCurso);
					guardarCursos(e->headCurso);
					break;
				case 4:
					system("cls");
					//ELIMINAR ESTUDIANTE
					eliminarAlumno(&e->headCurso);
					guardarCursos(e->headCurso);
					break;
				case 5:
					system("cls");
					//VOLVER AL MENU PRINCIPAL
					break;
				}
				break;
			case 3:
				system("cls");
				printf("        ===============================================================\n");
				printf("                           SISTEMA DE INFORMACION - TIMEWARD\n");
				printf("                             BASE DE DATOS CURSOS\n");
				printf("        ===============================================================\n\n\n");
				printf("                           1- MOSTRAR LISTA DE CURSOS\n");
				printf("                           2- AGREGAR UN CURSO\n");
				printf("                           3- MODIFICAR NOMBRE DEL CURSO\n");
				printf("                           4- ELIMINAR UN CURSO\n");
				printf("                           5- VOLVER AL MENU PRINCIPAL\n\n");
				printf("                           INGRESE UNA DE LAS OPCIONES: ");

				switch (leerOpcion(6)) {
				case 1:
					system("cls");
					//MOSTRAR LISTA DE CURSOS
					mostrarCurso(e->headCurso);
					break;
				case 2:
					system("cls");
					//AGREGAR UN CURSO
					agregarCurso(&e->headCurso);
					guardarCursos(e->headCurso);
					break;
				case 3:
					system("cls");
					//MODIFICAR CURSO
					modificaNombreCurso(&e->headCurso);
					guardarCursos(e->headCurso);
					break;
				case 4:
					system("cls");
					//ELIMINAR CURSO
					eliminarCurso(&e->headCurso);
					guardarCursos(e->headCurso);
					break;
				case 5:
					system("cls");
					//VOLVER AL MENU PRINCIPAL
					break;
				}
				break;
			case 4:
				system("cls");
				//VUELVE AL MENU PRINCIPAL
				break;
			}
			break;

		case 2:
			/*MENU DEL INVITADO*/
			system("cls");
			printf("        ===============================================================\n");
			printf("                         SISTEMA DE INFORMACION - TIMEWARD\n");
			printf("                                USUARIO INVITADO\n");
			printf("        ===============================================================\n\n\n");
			printf("                           1- MOSTRAR LISTA DE CURSOS\n");
			printf("                           2- MOSTRAR LISTA DE DOCENTES\n");
			printf("                           3- MOSTRAR UN DOCENTE\n");
			printf("                           4- MOSTRAR UN ALUMNO\n");
			printf("                           5- VOLVER AL MENU PRINCIPAL\n\n");
			printf("                           INGRESE UNA DE LAS OPCIONES: ");

			switch (leerOpcion(5)) {
			case 1:
				system("cls");
				//MOSTRAR LISTA DE CURSOS
				mostrarCurso(e->headCurso);
				break;
			case 2:
				system("cls");
				//MOSTRAR LISTA DE PROFESORES
				mostrarProfesores(e->headProfesor);
				break;
			case 3:
				system("cls");
				//MOSTRAR UN PROFESOR POR EL RUT
				mostrarProfesor(e->headProfesor);
				break;
			case 4:
				system("cls");
				//MOSTRAR UN ALUMNO POR EL RUT
				mostrarAlumno(e->headCurso);
				break;
			case 5:
				system("cls");
				//VOLVER AL MENU PRINCIPAL
				break;
			}
			//PRODECIMIENTO
			break;

		case 3:
			/*SALIR DEL PROGRAMA*/
			system("cls");
			//guardarArchivoProfesor();
			//guardarArchivoAlumno();
			salir();
		}
		volverMenu(&opcion);
	} while (opcion != 3);

	//guardarArchivoProfesor();
	//guardarArchivoAlumno();

	return 0;
}

/*---------------DECLARACION DE FUNCIONES Y PROCEDIMIENTOS------------------*/

void errorMemoria(void *puntero) {
	if (puntero == NULL) {
		printf("============================================================\n");
		printf("OCURRIO UN ERROR EN EL GUARDADO Y ALMACENAMIENTO DE MEMORIA\n");
		printf("============================================================\n");
		system("pause");
		exit(0);
	}
}

void verificarEliminado(void *puntero) {
	if (puntero == NULL) {
		printf("		EL ELEMENTO SE ELIMINO CORRECTAMENTE");
	}
	else {
		printf("		ERROR!	EL ELEMENTO NO SE ELIMINO CORRECTAMENTE!");
		printf("		SE PROCEDERA A CERRAR EL PROGRAMA!!\n");
		system("pause");
		exit(0);
	}
	return;
}

int soloNumerosCmd(char *numero) {
	int i;
	for (i = 0; i < strlen(numero); i++) {
		if (!isdigit(numero[i])) return 0;
	}
	return 1;
}

int leerOpcion(int limiteSuperior) {
	char buffer[MAX];
	int comando;                 //OPCION QUE ESCOGIO EL USUARIO.
	do {
		scanf("%s", buffer);    //LEER OPCI�N ESCOGIDA POR EL USUARIO.
		fflush(stdin);
		printf("\n");
		if (soloNumerosCmd(buffer)) {
			comando = atoi(buffer);
			if ((comando >= 1) && (comando <= limiteSuperior)) {    //SI LA OPCI�N EST� ENTRE LAS OPCIONES DEL MEN�.
				return comando;                                     //RETORNA OPCI�N.
			}
			else {                                                                        //SI LA OPCI�N NO EST� ENTE LAS OPCIONES DEL MEN�.
				printf("        ===============================================================\n\n");
				printf("                  OPCION INVALIDA, INGRESE UNA OPCION VALIDA: ");   //RETORNA MENSAJE.
			}
		}
		else {
			printf("        ===============================================================\n\n");
			printf("                  OPCION INVALIDA, INGRESE UNA OPCION VALIDA: ");   //RETORNA MENSAJE.
		}

	} while ((comando < 1) || (comando > limiteSuperior));
}

int validarHorario(int limiteSuperior) {
	char buffer[MAX];
	int horas;                 //CLAVES ESCOGIDA POR EL USUARIO

	do {
		scanf("%s", buffer);    //LEER OPCI�N ESCOGIDA POR EL USUARIO.
		fflush(stdin);
		printf("\n");
		if (soloNumerosCmd(buffer)) {
			horas = atoi(buffer);
			if ((horas >= 0) && (horas <= limiteSuperior)) {    //SI LA CLAVE EST� ENTRE CLAVE 1-8
				return horas;                                   //RETORNA CLAVE.
			}
			else {                                                                        //SI LA CLAVE NO EST� ENTRE CLAVE 1-8.
				printf("           CLAVE INVALIDA, INGRESE UNA CLAVE VALIDA :");
			}
		}
		else {
			printf("           CLAVE INVALIDA, INGRESE UNA CLAVE VALIDA :");
		}

	} while ((horas < 0) || (horas > limiteSuperior));
}

void volverMenu(int *opcion) {
	int cmd;

	//system("cls");
	printf("        ===============================================================\n");
	printf("                                 QUE DESEA?\n");
	printf("        ===============================================================\n\n");
	printf("                           1- VOLVER AL MENU PRINCIPAL\n");
	printf("                           2- SALIR DEL PROGRAMA \n\n");
	printf("                           INGRESE UNA DE LAS OPCIONES: ");

	cmd = leerOpcion(2);
	switch (cmd) {
	case 1:
		system("cls");
		opcion = 0;
		break;
	case 2:
		salir();
	}
}

void mostrarProfesores(struct nodoProfesor *head) {
	struct nodoProfesor *rec;
	int i = 1;

	if (head == NULL) {
		printf("        ===============================================================\n");
		printf("                         SISTEMA DE INFORMACION - TIMEWARD\n");
		printf("                             MOSTRAR LISTA DE DOCENTES\n");
		printf("        ===============================================================\n\n\n");
		printf("                           NO HAY DOCENTES INSCRITOS!\n\n\n");
	}
	else {
		rec = head;
		printf("        ===============================================================\n");
		printf("                         SISTEMA DE INFORMACION - TIMEWARD\n");
		printf("                             MOSTRAR LISTA DE DOCENTES\n");
		printf("        ===============================================================\n\n\n");
		do {
			printf("          %d) %s   \t%s   \t%s\n\n", i, rec->datosProfesor->apellidoProfesor, rec->datosProfesor->nombreProfesor, rec->datosProfesor->rutProfesor);
			i++;
			rec = rec->sig;
		} while (rec != head);
	}
	return;
}

void mayusculas(char *cadena) {
	int i;
	size_t largo;
	largo = strlen(cadena);
	for (i = 0; i < largo; i++) {
		cadena[i] = toupper(cadena[i]);
	}

	return;
}

void salir() {

	system("cls");
	printf("        ===============================================================\n");
	printf("                           GRACIAS POR USAR TIMEWARD\n");
	printf("                                  HASTA LUEGO\n");
	printf("        ===============================================================\n\n");
	system("pause");
	exit(0);
}

int soloNumeros(char *dato) {
	int i;
	for (i = 0; i < strlen(dato); i++) {
		if (!isdigit(dato[i])) {
			if (dato[i] != 'K') {
				return 0;
			}
		}
	}
	return 1;
}

struct nodoProfesor* buscarProfesor(char *rutNuevo, struct nodoProfesor *head) {
	struct nodoProfesor *rec;

	if (head == NULL) {
		return NULL;
	}
	else {
		
		rec = head;
		do {
			if (strcmp(rec->datosProfesor->rutProfesor, rutNuevo) == 0) {
				return rec;
			}
			else {
				rec = rec->sig;
			}
		} while (rec != head);
	}
	return NULL;
}

void mostrarProfesor(struct nodoProfesor *headProfesor) {
	struct nodoProfesor *profesorM;
	char buffer[MAX];

	if (headProfesor == NULL) {
		printf("        ===============================================================\n");
		printf("                         SISTEMA DE INFORMACION - TIMEWARD\n");
		printf("                                 MOSTRAR DOCENTES\n");
		printf("        ===============================================================\n\n\n");
		printf("                           NO HAY DOCENTES INSCRITOS!\n\n\n");
	}
	else {
		printf("        ===============================================================\n");
		printf("                         SISTEMA DE INFORMACION - TIMEWARD\n");
		printf("                                 MOSTRAR DOCENTES\n");
		printf("        ===============================================================\n\n\n");
		printf("           INTRODUZCA EL RUT DEL DOCENTE QUE DESEA MOSTRAR : ");
		do {
			scanf("%s", buffer);
			fflush(stdin);
			if (!soloNumeros(buffer)) {
				printf("\n");
				printf("        ===============================================================\n\n");
				printf("	   El NUMERO DE RUT INGRESADO ES INVALIDO!\n");
				printf("	   POR FAVOR INGRESE UNO VALIDO : ");
			}
		} while (!soloNumeros(buffer));

		profesorM = buscarProfesor(buffer, headProfesor);
		if (profesorM) {
			printf("        ===============================================================\n\n");
			printf("           1- NOMBRE DEL DOCENTE   : %s\n", profesorM->datosProfesor->nombreProfesor);
			printf("           2- APELLIDO DEL DOCENTE : %s\n", profesorM->datosProfesor->apellidoProfesor);
			printf("           3- RUT DEL DOCENTE      : %s\n\n", profesorM->datosProfesor->rutProfesor);
			printf("           EL HORARIO DEL DOCENTE ES EL SIGUIENTE :\n\n");
			imprimirHorario(profesorM);
		}
		else {
			system("cls");
			printf("        ===============================================================\n");
			printf("                         SISTEMA DE INFORMACION - TIMEWARD\n");
			printf("                                 MOSTRAR DOCENTES\n");
			printf("        ===============================================================\n\n\n");
			printf("           NO SE ENCONTRO EL RUT QUE USTED INGRESO!\n\n\n");
		}
	}
	return;
}

void imprimirHorario(struct nodoProfesor *head) {
	int i, j;
	printf("   | LUNES     \t|| MARTES    \t|| MIERCOLES \t|| JUEVES     \t|| VIERNES   \t| \n");
	for (i = 0; i < 8; i++) {
		printf("%d  ", i + 1);
		for (j = 0; j < 5; j++) {
			if (head->datosProfesor->horario[i][j] == 1)
			{
				printf("|ocupado   \t|");
			}
			else
			{
				printf("|disponible\t|");
			}
		}
		printf("\n");
	}
	return;
}

void llenarHorario(struct nodoProfesor *nuevo) {
	int vector[9];
	int i, j;
	int opcion;
	int horas;

	for (i = 0; i < 8; i++) {
		for (j = 0; j < 5; j++) {
			nuevo->datosProfesor->horario[i][j] = 0;
		}
	}

	for (i = 0; i < 9; i++) {
		vector[i] = 0;
	}

	do {
		printf("        ===============================================================\n\n");
		printf("           EN QUE DIA DESEA LLENAR LAS CLAVES?\n");
		printf("           1)LUNES\n");
		printf("           2)MARTES\n");
		printf("           3)MIERCOLES\n");
		printf("           4)JUEVES\n");
		printf("           5)VIERNES\n");
		printf("           6)TERMINAR EL HORARIO\n\n");
		printf("           INGRESE UNA DE LAS OPCIONES: ");
		opcion = leerOpcion(6);
		printf("\n");
		switch (opcion) {

		case 1:
			printf("        ===============================================================\n\n");
			printf("           INTRODUZCA LAS CLAVES A OCUPAR\n");
			printf("           RECORDAR QUE LAS CLAVES SON ENTRE 1 y 8\n");
			printf("           INGRESE UN 0 CUANDO TERMINE DE LLENAR :\n\n");
			printf("           CLAVE : ");
			horas = validarHorario(8);
			i = 0;

			while (horas != 0) {
				vector[i] = horas;
				i++;
				printf("           CLAVE : ");
				horas = validarHorario(8);
			}
			i = 0;

			while (vector[i] != 0) {
				nuevo->datosProfesor->horario[vector[i] - 1][0] = 1;
				i++;
			}

			for (i = 0; i < 9; i++) {
				vector[i] = 0;
			}
			break;

		case 2:
			printf("        ===============================================================\n\n");
			printf("           INTRODUZCA LAS CLAVES A OCUPAR\n");
			printf("           RECORDAR QUE LAS CLAVES SON ENTRE 1 y 8\n");
			printf("           INGRESE UN 0 CUANDO TERMINE DE LLENAR :\n\n");
			printf("           CLAVE : ");
			horas = validarHorario(8);
			i = 0;

			while (horas != 0) {
				vector[i] = horas;
				i++;
				printf("           CLAVE : ");
				horas = validarHorario(8);
			}
			i = 0;

			while (vector[i] != 0) {
				nuevo->datosProfesor->horario[vector[i] - 1][1] = 1;
				i++;
			}

			for (i = 0; i < 9; i++) {
				vector[i] = 0;
			}
			break;

		case 3:
			i = 0;
			printf("        ===============================================================\n\n");
			printf("           INTRODUZCA LAS CLAVES A OCUPAR\n");
			printf("           RECORDAR QUE LAS CLAVES SON ENTRE 1 y 8\n");
			printf("           INGRESE UN 0 CUANDO TERMINE DE LLENAR :\n\n");
			printf("           CLAVE : ");
			horas = validarHorario(8);
			i = 0;

			while (horas != 0) {
				vector[i] = horas;
				i++;
				printf("           CLAVE : ");
				horas = validarHorario(8);
			}
			i = 0;

			while (vector[i] != 0) {
				nuevo->datosProfesor->horario[vector[i] - 1][2] = 1;
				i++;
			}

			for (i = 0; i < 9; i++) {
				vector[i] = 0;
			}
			break;

		case 4:
			printf("        ===============================================================\n\n");
			printf("           INTRODUZCA LAS CLAVES A OCUPAR\n");
			printf("           RECORDAR QUE LAS CLAVES SON ENTRE 1 y 8\n");
			printf("           INGRESE UN 0 CUANDO TERMINE DE LLENAR :\n\n");
			printf("           CLAVE : ");
			horas = validarHorario(8);
			i = 0;

			while (horas != 0) {
				vector[i] = horas;
				i++;
				printf("           CLAVE : ");
				horas = validarHorario(8);
			}
			i = 0;

			while (vector[i] != 0) {
				nuevo->datosProfesor->horario[vector[i] - 1][3] = 1;
				i++;
			}

			for (i = 0; i < 9; i++) {
				vector[i] = 0;
			}
			break;

		case 5:
			i = 0;
			printf("        ===============================================================\n\n");
			printf("           INTRODUZCA LAS CLAVES A OCUPAR\n");
			printf("           RECORDAR QUE LAS CLAVES SON ENTRE 1 y 8\n");
			printf("           INGRESE UN 0 CUANDO TERMINE DE LLENAR :\n\n");
			printf("           CLAVE : ");
			horas = validarHorario(8);
			i = 0;

			while (horas != 0) {
				vector[i] = horas;
				i++;
				printf("           CLAVE : ");
				horas = validarHorario(8);
			}
			i = 0;

			while (vector[i] != 0) {
				nuevo->datosProfesor->horario[vector[i] - 1][4] = 1;;
				i++;
			}

			for (i = 0; i < 9; i++) {
				vector[i] = 0;
			}
			break;

		case 6:
			printf("        ===============================================================\n\n");
			printf("           EL HORARIO QUEDA DE LA SIGUIENTE FORMA :\n\n");
			imprimirHorario(nuevo);
			break;

		default:
			printf("           INGRESE UNA OPCION VALIDA!\n");
			break;
		}
	} while (opcion != 6);

	return;
}

struct nodoProfesor* crearNodoProfesor(struct nodoProfesor *head) {
	struct nodoProfesor *nuevo;
	char *auxiliar = NULL;
	char buffer[MAX];
	int opcion;

	nuevo = (struct nodoProfesor*)malloc(sizeof(struct nodoProfesor));
	nuevo->datosProfesor = (struct Profesor *)malloc(sizeof(struct Profesor));
	errorMemoria(nuevo->datosProfesor);

	printf("        ===============================================================\n");
	printf("                       SISTEMA DE INFORMACION - TIMEWARD\n");
	printf("                               AGREGAR DOCENTE\n");
	printf("        ===============================================================\n\n\n");
	printf("           1- INTRODUZCA EL NOMBRE DEL DOCENTE   : ");

	scanf(" %[^\n]s", buffer);
	mayusculas(buffer);

	nuevo->datosProfesor->nombreProfesor = (char *)malloc(sizeof(char)*strlen(buffer));
	errorMemoria(nuevo->datosProfesor->nombreProfesor);
	strcpy(nuevo->datosProfesor->nombreProfesor, buffer);

	printf("           2- INTRODUZCA EL APELLIDO DEL DOCENTE : ");

	scanf(" %[^\n]s", buffer);
	mayusculas(buffer);

	nuevo->datosProfesor->apellidoProfesor = (char *)malloc(sizeof(char)*strlen(buffer));
	errorMemoria(nuevo->datosProfesor->apellidoProfesor);
	strcpy(nuevo->datosProfesor->apellidoProfesor, buffer);

	do {
		printf("           3- INTRODUZCA EL RUT DEL DOCENTE      : ");
		do {
			scanf("%s", buffer);
			mayusculas(buffer);
			fflush(stdin);
			if (!soloNumeros(buffer)) {
				printf("\n");
				printf("        ===============================================================\n\n");
				printf("	   El NUMERO DE RUT INGRESADO ES INVALIDO!\n");
				printf("	   POR FAVOR INGRESE UNO VALIDO : ");
			}
		} while (!soloNumeros(buffer));
		if (buscarProfesor(buffer, head)) {
			printf("\n");
			printf("        ===============================================================\n\n");
			printf("           EL NUMERO DE RUT QUE QUIERE INGRESAR YA ESTA REGISTRADO!\n");
			printf("           DESEA INGRESAR OTRO NUMERO?\n");
			printf("		1. SI\n");
			printf("		2. NO\n");
			printf("           INGRESE UNA DE LAS OPCIONES: ");
			opcion = leerOpcion(2);
			if (opcion == 2) {
				return NULL;
			}
			printf("        ===============================================================\n\n");
		}
	} while (buscarProfesor(buffer, head));

	nuevo->datosProfesor->rutProfesor = (char*)malloc(sizeof(char)*strlen(buffer));
	errorMemoria(nuevo->datosProfesor->rutProfesor);
	strcpy(nuevo->datosProfesor->rutProfesor, buffer);
	printf("           4- COMPLETE EL HORARIO DEL DOCENTE    : \n\n");
	llenarHorario(nuevo);

	nuevo->sig = NULL;

	return nuevo;
}

void agregarProfesor(struct nodoProfesor **head) {
	struct nodoProfesor *rec = NULL;
	struct nodoProfesor *auxiliar = NULL;
	int opcion;

	do {
		auxiliar = crearNodoProfesor(*head);
		if (auxiliar == NULL) {
			system("cls");
			printf("        ===============================================================\n");
			printf("                         SISTEMA DE INFORMACION - TIMEWARD\n");
			printf("                                AGREGAR DOCENTE\n");
			printf("        ===============================================================\n\n\n");
			printf("	       NO SE AGREGO EL NUEVO DOCENTE!\n\n");
			printf("        ===============================================================\n\n");
			printf("               DESEA INTENTARLO NUEVAMENTE?\n");
			printf("               1- SI\n               2- NO\n\n");
			printf("               INGRESE UNA DE LAS OPCIONES: ");
			opcion = leerOpcion(2);
			if (opcion == 2) {
				return;
			}
			system("cls");
		}
	} while (auxiliar == NULL);

	if ((*head) == NULL) {
		(*head) = (struct nodoProfesor *)malloc(sizeof(struct nodoProfesor));
		errorMemoria(*head);
		(*head) = auxiliar;
		(*head)->sig = (*head);
	}
	else {
		rec = (*head);
		while (rec->sig != *head) {
			rec = rec->sig;
		}

		rec->sig = NULL;
		rec->sig = (struct nodoProfesor*)malloc(sizeof(struct nodoProfesor));
		errorMemoria(rec->sig);
		rec->sig = auxiliar;
		rec->sig->sig = (*head);
	}
	printf("\n");
	printf("           EL DOCENTE HA SIDO AGREGADO CON EXITO! \n\n");
}

void eliminarProfesor(struct nodoProfesor **head) {
	char rut[MAX];
	struct nodoProfesor *profeEliminar = NULL;
	struct nodoProfesor *rec = NULL;
	struct nodoProfesor *primero = *head; //guardar lista
	int opcion;
	int opcionRetorno = 2;

	if (*head == NULL) {
		printf("        ===============================================================\n");
		printf("                       SISTEMA DE INFORMACION - TIMEWARD\n");
		printf("                               ELIMINAR DOCENTE\n");
		printf("        ===============================================================\n\n\n");
		printf("                           NO HAY DOCENTES INSCRITOS!\n\n\n");
	}
	else {
		do {
			system("cls");
			printf("        ===============================================================\n");
			printf("                       SISTEMA DE INFORMACION - TIMEWARD\n");
			printf("                               ELIMINAR DOCENTE\n");
			printf("        ===============================================================\n\n\n");
			printf("          INGRESE EL RUT DEL DOCENTE QUE DESEA ELIMINAR : ");
			do {
				scanf("%s", rut);
				mayusculas(rut);
				fflush(stdin);
				if (!soloNumeros(rut)) {
					printf("\n");
					printf("        ===============================================================\n\n");
					printf("	   El NUMERO DE RUT INGRESADO ES INVALIDO!\n");
					printf("	   POR FAVOR INGRESE UNO VALIDO : ");
				}
			} while (!soloNumeros(rut));
			profeEliminar = buscarProfesor(rut, *head);
			if (profeEliminar) {
				printf("\n");
				printf("        ===============================================================\n\n\n");
				printf("               NOMBRE DEL DOCENTE : %s %s\n\n", profeEliminar->datosProfesor->nombreProfesor, profeEliminar->datosProfesor->apellidoProfesor);
				printf("               DESEA ELIMINAR EL DOCENTE?\n");
				printf("	       1- SI\n	       2- NO\n\n");
				printf("               INGRESE UNA DE LAS OPCIONES: ");
				opcion = leerOpcion(2);
				switch (opcion) {
				case 1:
					if (profeEliminar == *head) {       //SI EL PROFE A ELIMINAR ES EL HEAD
						rec = *head;
						if (rec->sig == *head) {
							free(profeEliminar);
							*head = NULL;
							//verificarEliminado(profeEliminar);
							printf("	       EL PROFESOR FUE ELIMINADO CORRECTAMENTE!\n\n");
							return;
						}
						else {   //ver
							do {
								rec = rec->sig;
							} while (rec->sig != *head);
							primero = primero->sig;
							free(profeEliminar);
							*head = primero;
							rec->sig = *head;
							//verificarEliminado(profeEliminar);
							printf("	       EL PROFESOR FUE ELIMINADO CORRECTAMENTE!\n\n");
							printf("        ===============================================================\n\n");
						}
					}
					else {
						rec = *head;
						do {
							rec = rec->sig;
						} while (rec->sig != profeEliminar);
						rec->sig = profeEliminar->sig;
						free(profeEliminar);
						//verificarEliminado(profeEliminar);
						printf("	       EL PROFESOR FUE ELIMINADO CORRECTAMENTE!\n\n");
						printf("        ===============================================================\n\n");
					}
					break;

				case 2:
					printf("	       EL PROFESOR FUE NO HA SIDO ELIMINADO!\n\n");
					printf("        ===============================================================\n\n");
					opcionRetorno = 2;
					break;
				}
				printf("	       DESEA ELIMINAR OTRO PROFESOR?\n\n");
				printf("	       1- SI\n	       2- NO\n\n");
				printf("	       INGRESE UNA DE LAS OPCIONES: ");
				opcionRetorno = leerOpcion(2);
			}
			else {
				system("cls");
				printf("        ===============================================================\n");
				printf("                       SISTEMA DE INFORMACION - TIMEWARD\n");
				printf("                               ELIMINAR DOCENTE\n");
				printf("        ===============================================================\n\n\n");
				printf("	   EL DOCENTE QUE DESEA ELIMINAR NO HA SIDO ENCONTRADO!\n\n");
				printf("        ===============================================================\n\n");
				printf("	     DESEA INTENTARLO DE NUEVO?\n\n");
				printf("	     1- SI\n	     2- NO\n\n");
				printf("             INGRESE UNA DE LAS OPCIONES: ");
				opcionRetorno = leerOpcion(2);
			}
		} while (opcionRetorno == 1);
	}
	return;
}

void modificarNombreDocente(struct nodoProfesor *modificar) {
	char buffer[MAX];

	printf("        ===============================================================\n");
	printf("                       SISTEMA DE INFORMACION - TIMEWARD\n");
	printf("                               MODIFICAR DOCENTE\n");
	printf("        ===============================================================\n\n\n");
	printf("           INTRODUZCA EL NUEVO NOMBRE DEL DOCENTE : ");
	scanf(" %[^\n]s", buffer);
	mayusculas(buffer);
	printf("\n");
	modificar->datosProfesor->nombreProfesor = (char *)malloc(sizeof(char)*strlen(buffer));
	errorMemoria(modificar->datosProfesor->nombreProfesor);
	strcpy(modificar->datosProfesor->nombreProfesor, buffer);
	printf("           EL NOMBRE DEL DOCENTE SE MODIFICO EXITOSAMENTE!\n\n");

	return;
}

void modificarApellidoDocente(struct nodoProfesor *modificar) {
	char buffer[MAX];

	printf("        ===============================================================\n");
	printf("                       SISTEMA DE INFORMACION - TIMEWARD\n");
	printf("                               MODIFICAR DOCENTE\n");
	printf("        ===============================================================\n\n\n");
	printf("           INTRODUZCA EL NUEVO APELLIDO DEL DOCENTE : ");
	scanf(" %[^\n]s", buffer);
	mayusculas(buffer);
	printf("\n");
	modificar->datosProfesor->apellidoProfesor = (char *)malloc(sizeof(char)*strlen(buffer));
	errorMemoria(modificar->datosProfesor->apellidoProfesor);
	strcpy(modificar->datosProfesor->apellidoProfesor, buffer);
	printf("           EL APELLIDO DEL DOCENTE SE MODIFICO EXITOSAMENTE!\n\n");

	return;
}

void modificarRutDocente(struct nodoProfesor *modificar) {
	char buffer[MAX];
	int opcion;

	do {
		printf("        ===============================================================\n");
		printf("                       SISTEMA DE INFORMACION - TIMEWARD\n");
		printf("                               MODIFICAR DOCENTE\n");
		printf("        ===============================================================\n\n\n");
		printf("           INTRODUZCA EL NUEVO RUT DEL DOCENTE : ");
		do {
			scanf("%s", buffer);
			mayusculas(buffer);
			fflush(stdin);
			if (!soloNumeros(buffer)) {
				printf("\n");
				printf("        ===============================================================\n\n");
				printf("	   El NUMERO DE RUT INGRESADO ES INVALIDO!\n");
				printf("	   POR FAVOR INGRESE UNO VALIDO : ");
			}
		} while (!soloNumeros(buffer));
		if (buscarProfesor(buffer, e->headProfesor)) {
			printf("\n");
			printf("        ===============================================================\n\n");
			printf("           EL NUMERO DE RUT QUE QUIERE INGRESAR YA ESTA REGISTRADO!\n");
			printf("           DESEA INGRESAR OTRO NUMERO?\n");
			printf("		1. SI\n");
			printf("		2. NO\n");
			printf("           INGRESE UNA DE LAS OPCIONES: ");
			opcion = leerOpcion(2);
			if (opcion == 2) {
				printf("\n");
				printf("           EL RUT DEL DOCENTE NO SE MODIFICO!\n\n");
				return;
			}
			system("cls");
		}
	} while (buscarProfesor(buffer, e->headProfesor));

	modificar->datosProfesor->rutProfesor = (char *)malloc(sizeof(char)*strlen(buffer));
	errorMemoria(modificar->datosProfesor->rutProfesor);
	strcpy(modificar->datosProfesor->rutProfesor, buffer);
	printf("\n");
	printf("           EL RUT DEL DOCENTE SE MODIFICO EXITOSAMENTE!\n\n");

	return;
}

void modificarProfesor(struct nodoProfesor **head) {
	struct nodoProfesor *profeModificar = NULL;
	char rut[50];
	int opcion;

	if (*head == NULL) {
		printf("        ===============================================================\n");
		printf("                       SISTEMA DE INFORMACION - TIMEWARD\n");
		printf("                               MODIFICAR DOCENTE\n");
		printf("        ===============================================================\n\n\n");
		printf("                           NO HAY DOCENTES INSCRITOS!\n\n\n");
	}
	else {
		printf("        ===============================================================\n");
		printf("                       SISTEMA DE INFORMACION - TIMEWARD\n");
		printf("                               MODIFICAR DOCENTE\n");
		printf("        ===============================================================\n\n\n");
		printf("          INGRESE EL RUT DEL DOCENTE QUE DESEA MODIFICAR : ");
		do {
			scanf("%s", rut);
			fflush(stdin);
			if (!soloNumeros(rut)) {
				printf("\n");
				printf("        ===============================================================\n\n");
				printf("	   El NUMERO DE RUT INGRESADO ES INVALIDO!\n");
				printf("	   POR FAVOR INGRESE UNO VALIDO : ");
			}
		} while (!soloNumeros(rut));
		profeModificar = buscarProfesor(rut, *head);

		if (profeModificar) {
			printf("\n");
			printf("        ===============================================================\n\n\n");
			printf("                NOMBRE DEL DOCENTE : %s %s\n\n", profeModificar->datosProfesor->nombreProfesor, profeModificar->datosProfesor->apellidoProfesor);
			printf("                        1- MODIFICAR NOMBRE DEL DOCENTE\n");
			printf("                        2- MODIFICAR APELLIDO DEL DOCENTE\n");
			printf("                        3- MODIFICAR RUT DEL DOCENTE\n");
			printf("                        4- MODIFICAR HORARIO DEL DOCENTE\n");
			printf("                        5- SALIR AL MENU PRINCIPAL\n\n");
			printf("                        INGRESE UNA DE LAS OPCIONES: ");
			opcion = leerOpcion(5);

			switch (opcion) {
			case 1:
				system("cls");
				//modificar nombre
				modificarNombreDocente(profeModificar);
				break;
			case 2:
				system("cls");
				//modificar apellidos
				modificarApellidoDocente(profeModificar);
				break;
			case 3:
				system("cls");
				modificarRutDocente(profeModificar);
				//modificar rut
				break;
			case 4:
				system("cls");
				//modificar horario del docente
				printf("        ===============================================================\n");
				printf("                       SISTEMA DE INFORMACION - TIMEWARD\n");
				printf("                               MODIFICAR DOCENTE\n");
				printf("        ===============================================================\n\n\n");
				printf("           EL HORARIO DEL DOCENTE ES EL SIGUIENTE :\n\n");
				imprimirHorario(profeModificar);
				printf("        ===============================================================\n\n");
				printf("           DESEA RESETEAR EL HORARIO DEL DOCENTE?\n\n");
				printf("		   1- SI\n");
				printf("		   2- NO\n\n");
				printf("           INGRESE UNA DE LAS OPCIONES: ");
				opcion = leerOpcion(2);

				switch (opcion) {
				case 1:
					system("cls");
					printf("        ===============================================================\n");
					printf("                       SISTEMA DE INFORMACION - TIMEWARD\n");
					printf("                               MODIFICAR DOCENTE\n");
					printf("\n");
					//llenar horario
					llenarHorario(profeModificar);
					break;
				case 2:
					system("cls");
					//salir al menu principal
					break;
				}
				break;

			case 5:
				system("cls");
				//salir al menu principal
				break;
			}
		}
		else {
			printf("\n");
			printf("          EL DOCENTE QUE DESEA MODIFICAR NO ESTA INGRESADO!\n\n\n");
		}
	}
	return;
}

struct nodoCurso *buscarCurso(struct nodoCurso *head, char *nombre) {
	struct nodoCurso *rec = NULL;
	rec = head;
	while (rec != NULL) {
		if (strcmp(rec->datosCurso->nombreCurso, nombre) == 0) {
			return rec;
		}
		rec = rec->sig;
	}
	return NULL;
}

void mostrarCurso(struct nodoCurso *headCurso) {
	char buffer[MAX];
	struct nodoCurso *cursoAMostrar = NULL;
	struct nodoCurso *recCurso = NULL;
	struct nodoAlumno *recAlumno = NULL;
	int opcionRetorno = 1;
	int opcion;
	int i;

	if (headCurso == NULL) {
		printf("        ===============================================================\n");
		printf("                       SISTEMA DE INFORMACION - TIMEWARD\n");
		printf("                               MOSTRAR CURSOS\n");
		printf("        ===============================================================\n\n\n");
		printf("                          NO HAY CURSOS REGISTRADOS!\n\n\n");
	}
	else {
		system("cls");
		recCurso = headCurso;
		printf("        ===============================================================\n");
		printf("                       SISTEMA DE INFORMACION - TIMEWARD\n");
		printf("                               MOSTRAR CURSOS\n");
		printf("        ===============================================================\n\n\n");
		i = 0;

		while (recCurso != NULL) {
			printf("		%d) - %s 		CANTIDAD ALUMNOS: %d\n", i + 1, recCurso->datosCurso->nombreCurso, recCurso->datosCurso->cantidadAlumnos);
			i++;
			recCurso = recCurso->sig;
		}
		printf("\n");
		printf("        ===============================================================\n\n");
		printf("                DESEA VER LA LISTA DE ALGUN CURSO?\n");
		printf("                1- SI\n                2- NO\n\n");
		printf("                INGRESE UNA DE LAS OPCIONES: ");
		opcion = leerOpcion(2);
		switch (opcion) {
		case 1:
			do {
				printf("        ===============================================================\n");
				printf("                       SISTEMA DE INFORMACION - TIMEWARD\n");
				printf("                               MOSTRAR CURSOS\n");
				printf("        ===============================================================\n\n");
				printf("	INGRESE EL NOMBRE DEL CURSO QUE DESEA MOSTRAR : ");
				scanf(" %[^\n]s", buffer);
				mayusculas(buffer);
				printf("\n");
				cursoAMostrar = buscarCurso(headCurso, buffer);
				if (cursoAMostrar == NULL) {
					printf("	EL CURSO BUSCADO NO HA SIDO ENCONTRADO!\n\n");
				}
				else {
					printf("        ===============================================================\n\n");
					printf("		CURSO : %s\n\n", cursoAMostrar->datosCurso->nombreCurso);
					printf("		CANTIDAD DE ALUMNOS INSCRITOS : %d\n", cursoAMostrar->datosCurso->cantidadAlumnos);
					if (cursoAMostrar->datosCurso->headAlumno == NULL) {
						printf("\n");
						printf("		NO HAY ALUMNOS INSCRITOS EN ESTE CURSO!\n\n");
					}
					else {
						recAlumno = cursoAMostrar->datosCurso->headAlumno;
						i = 0;
						while (recAlumno != NULL) {
							printf("\n");
							printf("          %d) %s   \t%s   \t%s\n\n", i + 1, recAlumno->datosAlumno->apellidoAlumno, recAlumno->datosAlumno->nombreAlumno, recAlumno->datosAlumno->rutAlumno);
							recAlumno = recAlumno->sig;
						}
					}
				}
				printf("        ===============================================================\n\n");
				printf("		DESEA BUSCAR OTRO CURSO?\n\n");
				printf("		1)SI\n		2)NO\n\n");
				printf("		INGRESE UNA DE LAS OPCIONES: ");
				opcionRetorno = leerOpcion(2);
				if (opcionRetorno == 1)
					system("cls");
			} while (opcionRetorno == 1);
			break;
		case 2:
			return;
			break;
		}
	}
	return;
}

struct nodoCurso* crearNodoCurso(struct nodoCurso *headC) {
	struct nodoCurso *nuevo;
	char buffer[MAX];

	nuevo = (struct nodoCurso*)malloc(sizeof(struct nodoCurso));
	nuevo->datosCurso = (struct Curso*)malloc(sizeof(struct Curso));
	errorMemoria(nuevo->datosCurso);

	printf("        ===============================================================\n");
	printf("                       SISTEMA DE INFORMACION - TIMEWARD\n");
	printf("                                AGREGAR CURSO\n");
	printf("        ===============================================================\n\n\n");
	printf("           INTRODUZCA EL NOMBRE DEL CURSO : ");

	scanf(" %[^\n]s", buffer);
	mayusculas(buffer);
	if (buscarCurso(headC, buffer) == NULL) {
		printf("\n");
		nuevo->datosCurso->nombreCurso = (char *)malloc(sizeof(char)*strlen(buffer));
		errorMemoria(nuevo->datosCurso->nombreCurso);
		strcpy(nuevo->datosCurso->nombreCurso, buffer);

		printf("           CANTIDAD DE ALUMNOS INCRITOS EN EL CURSO : 0\n");
		nuevo->datosCurso->cantidadAlumnos = 0;
		nuevo->datosCurso->headAlumno = NULL;
		nuevo->datosCurso->AsignaturaCurso = NULL;
		printf("\n");
		agregarAsignatura(&nuevo->datosCurso->AsignaturaCurso);
		if (nuevo->datosCurso->AsignaturaCurso == NULL) {
			printf("           ERROR! TIENE QUE AGREGAR AL MENOS UNA ASIGNATURA\n");
			return NULL;
		}
	}
	else {
		return NULL;
	}
	return nuevo;
}

void agregarCurso(struct nodoCurso **headC) {
	struct nodoCurso *rec;
	struct nodoCurso *auxiliar;
	int opcion;

	do {
		auxiliar = crearNodoCurso(*headC);
		if (auxiliar == NULL) {
			system("cls");
			printf("        ===============================================================\n");
			printf("                       SISTEMA DE INFORMACION - TIMEWARD\n");
			printf("                                AGREGAR CURSO\n");
			printf("        ===============================================================\n\n");
			printf("	       NO SE AGREGO EL CURSO!\n\n");
			printf("               DESEA INTENTARLO DE NUEVO?\n\n");
			printf("               1- SI\n	       2- NO\n\n");
			printf("               INGRESE UNA DE LAS OPCIONES: ");
			opcion = leerOpcion(2);
			if (opcion == 2) {
				return;
			}
			system("cls");
		}
	} while (auxiliar == NULL);

	if ((*headC) == NULL) {  //SI NO EXISTE UNA LISTA DE CURSOS, SE CREAR� EL HEAD
		(*headC) = (struct nodoCurso *)malloc(sizeof(struct nodoCurso));
		errorMemoria(*headC);
		(*headC) = auxiliar;
		(*headC)->sig = NULL;
	}
	else { //SI EXISTE UNA LISTA DE CURSOS, SE AGREGAR� AL FINAL
		rec = (*headC);
		while (rec->sig != NULL) {
			rec = rec->sig;
		}

		rec->sig = NULL;
		rec->sig = (struct nodoCurso*)malloc(sizeof(struct nodoCurso));
		errorMemoria(rec->sig);
		rec->sig = auxiliar;
		rec->sig->sig = NULL;
	}
	printf("\n");
	printf("           SE AGREGO EL CURSO EXITOSAMENTE!\n\n");
	return;
}

void modificaNombreCurso(struct nodoCurso **head) {
	char buffer[MAX];
	struct nodoCurso *cursoModificar = NULL;
	int opcionRetorno = 1;

	if (*head == NULL) {
		printf("        ===============================================================\n");
		printf("                       SISTEMA DE INFORMACION - TIMEWARD\n");
		printf("                                MODIFICAR CURSO\n");
		printf("        ===============================================================\n\n\n");
		printf("			   NO HAY CURSOS REGISTRADOS!\n\n\n");
		return;
	}
	else {
		do {
			printf("        ===============================================================\n");
			printf("                       SISTEMA DE INFORMACION - TIMEWARD\n");
			printf("                                MODIFICAR CURSO\n");
			printf("        ===============================================================\n\n\n");
			printf("           INTRODUZCA EL NOMBRE DEL CURSO A MODIFICAR : ");
			scanf(" %[^\n]s", buffer);
			mayusculas(buffer);
			cursoModificar = buscarCurso(*head, buffer);
			if (cursoModificar) {
				printf("\n");
				printf("        ===============================================================\n\n");
				printf("			       CURSO : %s\n\n", cursoModificar->datosCurso->nombreCurso);
				printf("           INTRODUZCA EL NUEVO NOMBRE DEL CURSO : ");
				scanf(" %[^\n]s", buffer);
				mayusculas(buffer);
				if (buscarCurso(*head, buffer) == NULL) {
					cursoModificar->datosCurso->nombreCurso = NULL;
					cursoModificar->datosCurso->nombreCurso = (char*)malloc(sizeof(char)*strlen(buffer));
					errorMemoria(cursoModificar->datosCurso->nombreCurso);
					strcpy(cursoModificar->datosCurso->nombreCurso, buffer);
					printf("\n");
					printf("           EL CURSO SE HA MODIFICADO EXITOSAMENTE!\n\n");
				}
				else {
					printf("\n");
					printf("           EL NOMBRE DEL CURSO QUE INGRESO YA EXISTE!\n\n");
				}
			}
			else {
				printf("\n");
				printf("           EL CURSO INGRESADO NO HA SIDO ENCONTRADO!! \n\n");
			}
			printf("        ===============================================================\n\n");
			printf("			DESEA MODIFICAR OTRO CURSO?\n");
			printf("			1- SI\n			2- NO\n\n");
			printf("			INGRESE UNA DE LAS OPCIONES : ");
			opcionRetorno = leerOpcion(2);
			system("cls");

		} while (opcionRetorno == 1);
	}
	return;
}

void eliminarCurso(struct nodoCurso **head) {
	char buffer[MAX];
	int opcion;
	int opcionRetorno;
	struct nodoCurso *primero = *head;
	struct nodoCurso *rec = NULL;
	struct nodoCurso *cursoEliminar = NULL;

	if ((*head) == NULL) {
		printf("        ===============================================================\n");
		printf("                       SISTEMA DE INFORMACION - TIMEWARD\n");
		printf("                                ELIMINAR CURSO\n");
		printf("        ===============================================================\n\n\n");
		printf("			   NO HAY CURSOS REGISTRADOS!\n\n");
		return;
	}
	else {
		do {
			printf("        ===============================================================\n");
			printf("                       SISTEMA DE INFORMACION - TIMEWARD\n");
			printf("                                ELIMINAR CURSO\n");
			printf("        ===============================================================\n\n\n");
			printf("	  INGRESE EL NOMBRE DEL CURSO QUE DESEA ELIMINAR : ");
			scanf(" %[^\n]s", buffer);
			mayusculas(buffer);
			cursoEliminar = buscarCurso(*head, buffer);
			if (cursoEliminar) {
				printf("\n");
				printf("        ===============================================================\n\n");
				printf("               NOMBRE DEL CURSO : %s\n", cursoEliminar->datosCurso->nombreCurso);
				printf("	       EL CURSO CUENTA CON %d ALUMNOS INSCRITOS.\n\n", cursoEliminar->datosCurso->cantidadAlumnos);
				printf("	       ESTA SEGURO QUE DESEA ELIMINAR EL CURSO? : \n");
				printf("	       1- SI\n	       2- NO\n\n");
				printf("               INGRESE UNA DE LAS OPCIONES: ");
				opcion = leerOpcion(2);
				switch (opcion) {
				case 1:
					if (cursoEliminar == *head) {
						if (cursoEliminar->sig == NULL) {
							free(cursoEliminar);
							printf("               EL CURSO HA SIDO ELIMINADO EXISTOSAMENTE!\n\n");
							*head = NULL;
							return;
						}
						else {
							primero = primero->sig;
							free(cursoEliminar);
							*head = primero;
							printf("               EL CURSO HA SIDO ELIMINADO EXISTOSAMENTE!\n\n");
						}
					}
					else {
						rec = *head;
						while (rec->sig != cursoEliminar) {
							rec = rec->sig;
						}
						rec->sig = rec->sig->sig;
						free(cursoEliminar);
						printf("               EL CURSO HA SIDO ELIMINADO EXISTOSAMENTE!\n\n");
					}
					break;
				case 2:
					printf("               EL CURSO NO HA SIDO ELIMINADO! \n\n");
					break;
				}
			}
			else {
				system("cls");
				printf("        ===============================================================\n");
				printf("                       SISTEMA DE INFORMACION - TIMEWARD\n");
				printf("                               ELIMINAR CURSO\n");
				printf("        ===============================================================\n\n\n");
				printf("	   EL CURSO QUE DESEA ELIMINAR NO HA SIDO ENCONTRADO!\n\n");
			}
			printf("        ===============================================================\n\n");
			printf("	     DESEA ELIMINAR OTRO CURSO?\n\n");
			printf("	     1- SI\n	     2- NO\n\n");
			printf("             INGRESE UNA DE LAS OPCIONES: ");
			opcionRetorno = leerOpcion(2);
			system("cls");
		} while (opcionRetorno == 1);
	}
	return;
}

struct nodoAlumno* buscarAlumno(struct nodoCurso *headCurso, char *rut) {
	struct nodoCurso *recCurso;
	struct nodoAlumno *recAlumno;

	recCurso = headCurso;
	while (recCurso != NULL) {
		recAlumno = recCurso->datosCurso->headAlumno;
		while (recAlumno != NULL) {
			if (strcmp(recAlumno->datosAlumno->rutAlumno, rut) == 0) {
				return recAlumno;
			}
			recAlumno = recAlumno->sig;
		}
		recCurso = recCurso->sig;
	}
	return NULL;
}

void mostrarAlumno(struct nodoCurso *headC) {
	char buffer[MAX];
	int i = 1;
	struct nodoAlumno *mosAlumno;
	struct nodoAsignatura *recRamo;
	struct nodoNotas *recNota;

	if (headC == NULL) {
		printf("        ===============================================================\n");
		printf("                         SISTEMA DE INFORMACION - TIMEWARD\n");
		printf("                                 MOSTRAR ESTUDIANTE\n");
		printf("        ===============================================================\n\n\n");
		printf("                           NO HAY CURSOS REGISTRADOS!\n\n\n");
	}
	else {
		printf("        ===============================================================\n");
		printf("                         SISTEMA DE INFORMACION - TIMEWARD\n");
		printf("                                 MOSTRAR ESTUDIANTE\n");
		printf("        ===============================================================\n\n\n");
		printf("	  INGRESE EL RUT DEL ESTUDIANTE QUE DESEA MOSTRAR : ");

		scanf(" %[^\n]s", buffer);
		mayusculas(buffer);
		mosAlumno = buscarAlumno(headC, buffer);
		printf("\n");
		if (mosAlumno == NULL) {
			printf("        ===============================================================\n");
			printf("                         SISTEMA DE INFORMACION - TIMEWARD\n");
			printf("                                 MOSTRAR ESTUDIANTE\n");
			printf("        ===============================================================\n\n\n");
			printf("                        EL RUT NO SE ENCUENTRA REGISTRADO!\n\n\n");
		}
		else {
			printf("        ===============================================================\n\n");
			printf("                 1- NOMBRE DEL ESTUDIANTE   : %s\n", mosAlumno->datosAlumno->nombreAlumno);
			printf("                 2- APELLIDO DEL ESTUDIANTE : %s\n", mosAlumno->datosAlumno->apellidoAlumno);
			printf("                 3- RUT DEL ESTUDIANTE      : %s\n", mosAlumno->datosAlumno->rutAlumno);
			printf("                 4- CURSO DEL ESTUDIANTE    : %s\n", mosAlumno->datosAlumno->cursoAlumno);
			printf("\n");
			printf("                 LAS ASIGNATURAS DEL ESTUDIANTE SON : \n");

			recRamo = mosAlumno->datosAlumno->headAsignatura;
			if (recRamo != NULL) {
				i = 1;
				printf("\n");
				while (recRamo != NULL) {
					printf("                 %d- %s\n", i, recRamo->datosAsignatura->nombreAsignatura);
					recNota = recRamo->datosAsignatura->headNotas;
					while (recNota != NULL) {
						printf("                    %0.1f\n", recNota->nota);
						recNota = recNota->sig;
					}
					i++;
					recRamo = recRamo->sig;
				}
				printf("\n");
			}
			else {
				printf("\n");
				printf("                 EL ALUMNO NO TIENE ASIGNATURAS INSCRITAS!\n");
				printf("\n");
			}
		}
	}
	return;
}

void traspasoAsignatura(struct nodoAsignatura **headAsignaturaAlumno, struct nodoAsignatura *headAsignaturaCurso) {
	struct nodoAsignatura *recCurso = NULL;
	struct nodoAsignatura *recAlumno = NULL;
	
	recCurso = headAsignaturaCurso;

	while (recCurso != NULL) {
		if (*headAsignaturaAlumno == NULL) {
			(*headAsignaturaAlumno) = (struct nodoAsignatura *)malloc(sizeof(struct nodoAsignatura));
			(*headAsignaturaAlumno)->datosAsignatura = (struct Asignatura *)malloc(sizeof(struct Asignatura));
			(*headAsignaturaAlumno)->datosAsignatura->nombreAsignatura = (char *)malloc(sizeof(char)*strlen(headAsignaturaCurso->datosAsignatura->nombreAsignatura));
			strcpy((*headAsignaturaAlumno)->datosAsignatura->nombreAsignatura, headAsignaturaCurso->datosAsignatura->nombreAsignatura);
			(*headAsignaturaAlumno)->datosAsignatura->headNotas = NULL;
			(*headAsignaturaAlumno)->sig = NULL;
		}
		else {
			recAlumno = *headAsignaturaAlumno;
			while (recAlumno->sig != NULL) {
				recAlumno = recAlumno->sig;
			}
			recAlumno->sig = (struct nodoAsignatura *)malloc(sizeof(struct nodoAsignatura));
			recAlumno->sig->datosAsignatura = (struct Asignatura *)malloc(sizeof(struct Asignatura));
			recAlumno->sig->datosAsignatura->nombreAsignatura = (char*)malloc(sizeof(char)*strlen(recCurso->datosAsignatura->nombreAsignatura));
			strcpy(recAlumno->sig->datosAsignatura->nombreAsignatura, recCurso->datosAsignatura->nombreAsignatura);
			recAlumno->sig->datosAsignatura->headNotas = NULL;
			recAlumno->sig->sig = NULL;

		}
		recCurso = recCurso->sig;
	}
	return;
}

struct nodoAlumno* crearNodoAlumno(struct nodoCurso *headCurso) {
	struct nodoAlumno *nuevo;
	char buffer[MAX];
	int opcion;

	nuevo = (struct nodoAlumno *)malloc(sizeof(struct nodoAlumno));
	errorMemoria(nuevo);
	nuevo->datosAlumno = (struct Alumno *)malloc(sizeof(struct Alumno));
	errorMemoria(nuevo->datosAlumno);

	printf("        ===============================================================\n");
	printf("                         SISTEMA DE INFORMACION - TIMEWARD\n");
	printf("                                AGREGAR ESTUDIANTE\n");
	printf("        ===============================================================\n\n\n");
	printf("           1- INTRODUZCA EL NOMBRE DEL ALUMNO    : ");
	scanf(" %[^\n]s", buffer);
	mayusculas(buffer);
	nuevo->datosAlumno->nombreAlumno = (char *)malloc(sizeof(char)*strlen(buffer));
	errorMemoria(nuevo->datosAlumno->nombreAlumno);
	strcpy(nuevo->datosAlumno->nombreAlumno, buffer);

	printf("           2- INTRODUZCA EL APELLIDO DEL ALUMNO  : ");
	scanf(" %[^\n]s", buffer);
	mayusculas(buffer);
	nuevo->datosAlumno->apellidoAlumno = (char *)malloc(sizeof(char)*strlen(buffer));
	errorMemoria(nuevo->datosAlumno->apellidoAlumno);
	strcpy(nuevo->datosAlumno->apellidoAlumno, buffer);

	do {
		printf("           3- INTRODUZCA EL RUT DEL ALUMNO       : ");
		do {
			scanf("%s", buffer);
			mayusculas(buffer);
			fflush(stdin);
			if (!soloNumeros(buffer)) {
				printf("\n");
				printf("        ===============================================================\n\n");
				printf("	   El NUMERO DE RUT INGRESADO ES INVALIDO!\n");
				printf("	   POR FAVOR INGRESE UNO VALIDO : ");
			}
		} while (!soloNumeros(buffer));
		if (buscarAlumno(headCurso, buffer)) {
			printf("\n");
			printf("        ===============================================================\n\n");
			printf("           EL NUMERO DE RUT QUE QUIERE INGRESAR YA ESTA REGISTRADO!\n");
			printf("           DESEA INGRESAR OTRO NUMERO?\n");
			printf("		1- SI\n");
			printf("		2- NO\n\n");
			printf("           INGRESE UNA DE LAS OPCIONES: ");
			opcion = leerOpcion(2);
			if (opcion == 2) {
				return NULL;
			}
			printf("        ===============================================================\n\n");
		}
	} while (buscarAlumno(headCurso, buffer));

	nuevo->datosAlumno->rutAlumno = (char *)malloc(sizeof(char)*strlen(buffer));
	errorMemoria(nuevo->datosAlumno->rutAlumno);
	strcpy(nuevo->datosAlumno->rutAlumno, buffer);
	nuevo->datosAlumno->headAsignatura = NULL;
	traspasoAsignatura(&nuevo->datosAlumno->headAsignatura, headCurso->datosCurso->AsignaturaCurso);

	printf("\n");
	printf("        ===============================================================\n\n");
	printf("           DESEA INGRESAR LAS ASIGNATURAS ADICIONALES?\n");
	printf("		1- SI\n");
	printf("		2- NO\n\n");
	printf("           INGRESE UNA DE LAS OPCIONES: ");
	opcion = leerOpcion(2);

	switch (opcion) {
	case 1:
		agregarAsignatura(&nuevo->datosAlumno->headAsignatura);
		break;
	case 2:
		printf("\n");
		printf("           NO SE AGREGARON ASIGNATURAS ADICIONALES\n");
		printf("           PUEDE REALIZARLO DESPUES EN LA OPCION DE MODIFICAR ESTUDIANTE\n");
		break;
	}
	return nuevo;
}

void agregarAlumno(struct nodoCurso **headCurso) {
	char buffer[MAX];
	int opcion;
	struct nodoCurso *cursoModificar = NULL;
	struct nodoAlumno *auxiliar = NULL;
	struct nodoAlumno *rec = NULL;
	int opcionRetorno = 1;


	if (*headCurso == NULL) {
		printf("        ===============================================================\n");
		printf("                         SISTEMA DE INFORMACION - TIMEWARD\n");
		printf("                                AGREGAR ESTUDIANTE\n");
		printf("        ===============================================================\n\n\n");
		printf("                           NO HAY CURSOS REGISTRADOS!\n\n\n");
		return;
	}
	else {
		do {
			printf("        ===============================================================\n");
			printf("                         SISTEMA DE INFORMACION - TIMEWARD\n");
			printf("                                AGREGAR ESTUDIANTE\n");
			printf("        ===============================================================\n\n\n");
			printf("	INGRESE EL CURSO AL CUAL DESEA AGREGAR AL ALUMNO : ");
			scanf(" %[^\n]s", buffer);
			mayusculas(buffer);
			printf("\n");
			cursoModificar = buscarCurso(*headCurso, buffer);

			if (cursoModificar) {
				do {
					auxiliar = crearNodoAlumno(*headCurso);
					if (auxiliar == NULL) {
						system("cls");
						printf("        ===============================================================\n");
						printf("                         SISTEMA DE INFORMACION - TIMEWARD\n");
						printf("                                AGREGAR ESTUDIANTE\n");
						printf("        ===============================================================\n\n\n");
						printf("	       NO SE AGREGO EL NUEVO ALUMNO!\n\n");
						printf("        ===============================================================\n\n");
						printf("               DESEA INTENTARLO NUEVAMENTE?\n");
						printf("               1- SI\n               2- NO\n\n");
						printf("               INGRESE UNA DE LAS OPCIONES: ");
						opcion = leerOpcion(2);
						if (opcion == 2) {
							return;
						}
						system("cls");
					}
				} while (auxiliar == NULL);

				auxiliar->datosAlumno->cursoAlumno = (char *)malloc(sizeof(char)*strlen(cursoModificar->datosCurso->nombreCurso));
				errorMemoria(auxiliar->datosAlumno->cursoAlumno);
				strcpy(auxiliar->datosAlumno->cursoAlumno, cursoModificar->datosCurso->nombreCurso);

				if (cursoModificar->datosCurso->headAlumno == NULL) {
					cursoModificar->datosCurso->headAlumno = (struct nodoAlumno*)malloc(sizeof(struct nodoAlumno));
					errorMemoria(cursoModificar->datosCurso->headAlumno);
					cursoModificar->datosCurso->headAlumno = auxiliar;
					cursoModificar->datosCurso->headAlumno->sig = NULL;
				}
				else {
					rec = cursoModificar->datosCurso->headAlumno;
					while (rec->sig != NULL) {
						rec = rec->sig;
					}
					rec->sig = (struct nodoAlumno *)malloc(sizeof(struct nodoAlumno));
					errorMemoria(rec->sig);
					rec->sig = auxiliar;
					rec->sig->sig = NULL;
				}
				cursoModificar->datosCurso->cantidadAlumnos++;
			}
			else {
				printf("	EL CURSO INGRESADO NO HA SIDO ENCONTRADO!\n");
			}
			printf("\n");
			printf("        ===============================================================\n\n");
			printf("           DESEA AGREGAR ALGUN ALUMNO A OTRO CURSO?\n");
			printf("		1- SI\n");
			printf("		2- NO\n\n");
			printf("           INGRESE UNA DE LAS OPCIONES: ");
			opcionRetorno = leerOpcion(2);
			system("cls");
		} while (opcionRetorno == 1);
	}
	return;
}

void eliminarAlumno(struct nodoCurso **headCurso) {
	struct nodoAlumno *alumnoEliminar = NULL;
	struct nodoAlumno *rec = NULL;
	struct nodoAlumno *primero = NULL;
	struct nodoCurso *cursoModificar = NULL;
	char buffer[MAX];
	int opcionRetorno = 1;
	int opcion = 1;

	if (*headCurso == NULL) {
		printf("        ===============================================================\n");
		printf("                         SISTEMA DE INFORMACION - TIMEWARD\n");
		printf("                               ELIMINAR ESTUDIANTE\n");
		printf("        ===============================================================\n\n\n");
		printf("                           NO HAY CURSOS REGISTRADOS!\n\n\n");
	}
	else {
		do {
			do {
				system("cls");
				printf("        ===============================================================\n");
				printf("                         SISTEMA DE INFORMACION - TIMEWARD\n");
				printf("                              ELIMINAR ESTUDIANTE\n");
				printf("        ===============================================================\n\n\n");
				printf("           INTRODUZCA EL RUT DEL ALUMNO QUE DESEA ELIMINAR : ");
				do {
					scanf("%s", buffer);
					mayusculas(buffer);
					fflush(stdin);
					if (!soloNumeros(buffer)) {
						printf("\n");
						printf("        ===============================================================\n\n");
						printf("	   El NUMERO DE RUT INGRESADO ES INVALIDO!\n");
						printf("	   POR FAVOR INGRESE UNO VALIDO : ");
					}
				} while (!soloNumeros(buffer));

				alumnoEliminar = buscarAlumno(*headCurso, buffer);
				if (!alumnoEliminar) {
					printf("\n");
					printf("        ===============================================================\n\n");
					printf("           EL NUMERO DE RUT QUE INGRESO NO HA SIDO ENCONTRADO!\n");
					printf("           DESEA INGRESAR OTRO NUMERO?\n");
					printf("		1. SI\n");
					printf("		2. NO\n\n");
					printf("           INGRESE UNA DE LAS OPCIONES: ");
					opcion = leerOpcion(2);
					if (opcion == 2) {
						return;
					}
				}
			} while (!alumnoEliminar);

			cursoModificar = buscarCurso(*headCurso, alumnoEliminar->datosAlumno->cursoAlumno);
			primero = cursoModificar->datosCurso->headAlumno;

			if (alumnoEliminar == cursoModificar->datosCurso->headAlumno) {
				primero = primero->sig;
				free(alumnoEliminar);
				alumnoEliminar = NULL;
				cursoModificar->datosCurso->headAlumno = NULL;
				cursoModificar->datosCurso->headAlumno = primero;
			}
			else {
				rec = cursoModificar->datosCurso->headAlumno;
				while (rec->sig != alumnoEliminar) {
					rec = rec->sig;
				}
				rec->sig = rec->sig->sig;
				free(alumnoEliminar);
				alumnoEliminar = NULL;
			}
			cursoModificar->datosCurso->cantidadAlumnos--;
			printf("           EL ESTUDIANTE SE ELIMINO EXISTOSAMENTE!\n\n");
			printf("           DESEA ELIMINAR OTRO ALUMNO?\n");
			printf("		1. SI\n");
			printf("		2. NO\n\n");
			printf("           INGRESE UNA DE LAS OPCIONES: ");
			opcionRetorno = leerOpcion(2);
		} while (opcionRetorno == 1);
	}
	return;
}

void modificarNombreAlumno(struct nodoAlumno *modificar) {
	char buffer[MAX];

	printf("        ===============================================================\n");
	printf("                       SISTEMA DE INFORMACION - TIMEWARD\n");
	printf("                               MODIFICAR ESTUDIANTE\n");
	printf("        ===============================================================\n\n\n");
	printf("           INTRODUZCA EL NUEVO NOMBRE DEL ESTUDIANTE : ");
	scanf(" %[^\n]s", buffer);
	mayusculas(buffer);
	printf("\n");
	modificar->datosAlumno->nombreAlumno = (char *)malloc(sizeof(char)*strlen(buffer));
	errorMemoria(modificar->datosAlumno->nombreAlumno);
	strcpy(modificar->datosAlumno->nombreAlumno, buffer);
	printf("           EL NOMBRE DEL ESTUDIANTE SE MODIFICO EXITOSAMENTE!\n\n");
	return;
}

void modificarApellidoAlumno(struct nodoAlumno *modificar) {
	char buffer[MAX];

	printf("        ===============================================================\n");
	printf("                       SISTEMA DE INFORMACION - TIMEWARD\n");
	printf("                               MODIFICAR ESTUDIANTE\n");
	printf("        ===============================================================\n\n\n");
	printf("           INTRODUZCA EL NUEVO APELLIDO DEL ESTUDIANTE : ");
	scanf(" %[^\n]s", buffer);
	mayusculas(buffer);
	printf("\n");
	modificar->datosAlumno->apellidoAlumno = (char *)malloc(sizeof(char)*strlen(buffer));
	errorMemoria(modificar->datosAlumno->apellidoAlumno);
	strcpy(modificar->datosAlumno->apellidoAlumno, buffer);
	printf("           EL APELLIDO DEL ESTUDIANTE SE MODIFICO EXITOSAMENTE!\n\n");
	return;
}

void modificarRutAlumno(struct nodoAlumno *modificar) {
	char buffer[MAX];
	int opcion;

	do {
		printf("        ===============================================================\n");
		printf("                       SISTEMA DE INFORMACION - TIMEWARD\n");
		printf("                               MODIFICAR ESTUDIANTE\n");
		printf("        ===============================================================\n\n\n");
		printf("           INTRODUZCA EL NUEVO RUT DEL ESTUDIANTE : ");
		do {
			scanf("%s", buffer);
			mayusculas(buffer);
			fflush(stdin);
			if (!soloNumeros(buffer)) {
				printf("\n");
				printf("        ===============================================================\n\n");
				printf("	   El NUMERO DE RUT INGRESADO ES INVALIDO!\n");
				printf("	   POR FAVOR INGRESE UNO VALIDO : ");
			}
		} while (!soloNumeros(buffer));
		if (buscarProfesor(buffer, e->headProfesor)) {
			printf("\n");
			printf("        ===============================================================\n\n");
			printf("           EL NUMERO DE RUT QUE QUIERE INGRESAR YA ESTA REGISTRADO!\n");
			printf("           DESEA INGRESAR OTRO NUMERO?\n");
			printf("		1. SI\n");
			printf("		2. NO\n");
			printf("           INGRESE UNA DE LAS OPCIONES: ");
			opcion = leerOpcion(2);
			if (opcion == 2) {
				printf("\n");
				printf("           EL RUT DEL ESTUDIANTE NO SE MODIFICO!\n\n");
				return;
			}
			system("cls");
		}
	} while (buscarProfesor(buffer, e->headProfesor));

	modificar->datosAlumno->rutAlumno = (char *)malloc(sizeof(char)*strlen(buffer));
	errorMemoria(modificar->datosAlumno->rutAlumno);
	strcpy(modificar->datosAlumno->rutAlumno, buffer);
	printf("\n");
	printf("           EL RUT DEL ESTUDIANTE SE MODIFICO EXITOSAMENTE!\n\n");

	return;
}

void modificarAlumno(struct nodoCurso **headC) {
	char buffer[MAX];
	struct nodoAlumno *modAlumno;
	int opcionRetorno = 0;

	do {
		if (*headC == NULL) {
			printf("        ===============================================================\n");
			printf("                       SISTEMA DE INFORMACION - TIMEWARD\n");
			printf("                               MODIFICAR ESTUDIANTE\n");
			printf("        ===============================================================\n\n\n");
			printf("                          NO HAY CURSOS REGISTRADOS!\n\n\n");
			opcionRetorno = 2;
		}
		else {
			printf("        ===============================================================\n");
			printf("                       SISTEMA DE INFORMACION - TIMEWARD\n");
			printf("                               MODIFICAR ESTUDIANTE\n");
			printf("        ===============================================================\n\n\n");
			printf("	  INGRESE EL RUT DEL ESTUDIANTE QUE DESEA MODIFICAR : ");
			scanf(" %[^\n]s", buffer);
			modAlumno = buscarAlumno(*headC, buffer);
			printf("\n");
			if (modAlumno == NULL) {
				printf("	  EL RUT NO SE ENCUENTRA REGISTRADO!\n\n\n");
			}
			else {
				printf("        ===============================================================\n\n");
				printf("	  ESTUDIANTE POR MODIFICAR : %s %s\n\n", modAlumno->datosAlumno->nombreAlumno, modAlumno->datosAlumno->apellidoAlumno);
				printf("	  QUE DESEA MODIFICAR?\n");
				printf("	  1- NOMBRE DEL ESTUDIANTE\n");
				printf("	  2- APELLIDO DEL ESTUDIANTE\n");
				printf("	  3- RUT DEL ESTUDIANTE\n");
				printf("	  4- ASIGNATURAS DEL ESTUDIANTE\n");
				printf("	  5- NOTAS DEL ESTUDIANTE\n");
				printf("	  6- SALIR\n\n");
				printf("	  INGRESE UNA DE LAS OPCIONES: ");

				switch (leerOpcion(6)) {
				case 1:
					system("cls");
					//MODIFICAR NOMBRE DEL ESTUDIANTE
					modificarNombreAlumno(modAlumno);
					break;
				case 2:
					system("cls");
					//MODIFICAR APELLIDO DEL ESTUDIANTE
					modificarApellidoAlumno(modAlumno);
					break;
				case 3:
					system("cls");
					//MODIFICAR RUT DEL ESTUDIANTE
					modificarRutAlumno(modAlumno);
					break;
				case 4:
					system("cls");
					//MODIFICAR ASIGNATURAS (AGREGAR/ELIMINAR)
					printf("        ===============================================================\n");
					printf("                       SISTEMA DE INFORMACION - TIMEWARD\n");
					printf("                              MODIFICAR ASIGNATURA\n");
					printf("        ===============================================================\n\n\n");
					printf("	  1- AGREGAR ASIGNATURA\n");
					printf("	  2- ELIMINAR ASIGNATURA\n\n");
					printf("	  INGRESE UNA DE LAS OPCIONES: ");
					opcionRetorno = leerOpcion(2);
					switch (opcionRetorno) {
					case 1:
						agregarAsignatura(&modAlumno->datosAlumno->headAsignatura);
						break;
					case 2:
						eliminarAsignatura(&modAlumno->datosAlumno->headAsignatura);
						break;
					}
					break;
				case 5:
					system("cls");
					//MODIFICAR NOTAS (AGREGAR/ELIMINAR)
					printf("        ===============================================================\n");
					printf("                       SISTEMA DE INFORMACION - TIMEWARD\n");
					printf("                              MODIFICAR NOTAS\n");
					printf("        ===============================================================\n\n\n");
					printf("	  1- AGREGAR NOTAS\n");
					printf("	  2- ELIMINAR NOTAS\n\n");
					printf("	  INGRESE UNA DE LAS OPCIONES: ");
					opcionRetorno = leerOpcion(2);
					switch (opcionRetorno) {
					case 1:
						agregarNotasPrimero(modAlumno->datosAlumno->headAsignatura);
						break;
					case 2:
						eliminarNotasPrimero(modAlumno->datosAlumno->headAsignatura);
						break;
					}
					break;
				case 6:
					//SALIR AL MENU PRINCIPAL
					opcionRetorno = 2;
					break;
				}
				printf("        ===============================================================\n\n");
				printf("           DESEA MODIFICAR OTRO ESTUDIANTE?\n");
				printf("           1- SI\n");
				printf("           2- NO\n\n");
				printf("           INGRESE UNAS DE LAS OPCIONES: ");
				opcionRetorno = leerOpcion(2);
				if (opcionRetorno == 1) {
					system("cls");
				}
			}
		}
	} while (opcionRetorno == 1);
	return;
}

struct nodoAsignatura* buscarAsignatura(struct nodoAsignatura *head, char *buffer) {
	struct nodoAsignatura *rec = NULL;

	if (head != NULL) {
		rec = head;
		while (rec != NULL) {
			if (strcmp(rec->datosAsignatura->nombreAsignatura, buffer) == 0) {
				return rec;
			}
			rec = rec->sig;
		}
	}
	return NULL;
}

struct nodoAsignatura* crearNodoAsignatura(struct nodoAsignatura *head) {
	struct nodoAsignatura *nuevo = NULL;
	char buffer[MAX];
	int opcion;

	nuevo = (struct nodoAsignatura*)malloc(sizeof(struct nodoAsignatura));
	errorMemoria(nuevo);
	nuevo->datosAsignatura = (struct Asignatura *)malloc(sizeof(struct Asignatura));
	errorMemoria(nuevo->datosAsignatura);
	do {
		printf("        ===============================================================\n");
		printf("                       SISTEMA DE INFORMACION - TIMEWARD\n");
		printf("                               AGREGAR ASIGNATURA\n");
		printf("        ===============================================================\n\n\n");
		printf("	   INTRODUZCA LA NUEVA ASIGNATURA : ");
		scanf(" %[^\n]s", buffer);
		mayusculas(buffer);
		printf("\n");
		if (buscarAsignatura(head, buffer)) {
			printf("\n");
			printf("        ===============================================================\n\n");
			printf("           LA ASIGNATURA QUE DESEA AGREGAR YA ESTA REGISTRADA!\n");
			printf("           DESEA AGREGAR OTRA ASIGNATURA?\n");
			printf("		1. SI\n");
			printf("		2. NO\n\n");
			printf("           INGRESE UNA DE LAS OPCIONES: ");
			opcion = leerOpcion(2);
			if (opcion == 2) {
				return NULL;
			}
			else {
				system("cls");
			}
		}
	} while (buscarAsignatura(head, buffer));

	nuevo->datosAsignatura->nombreAsignatura = (char*)malloc(sizeof(char)*strlen(buffer));
	errorMemoria(nuevo->datosAsignatura->nombreAsignatura);
	strcpy(nuevo->datosAsignatura->nombreAsignatura, buffer);
	nuevo->datosAsignatura->headNotas = NULL;
	nuevo->sig = NULL;

	return nuevo;
}

void agregarAsignatura(struct nodoAsignatura **headAsignatura) {
	struct nodoAsignatura *rec = NULL;
	struct nodoAsignatura *auxiliar = NULL;
	int opcion;

	do {
		do {
			auxiliar = crearNodoAsignatura(*headAsignatura);
			if (auxiliar == NULL) {
				system("cls");
				printf("        ===============================================================\n");
				printf("                       SISTEMA DE INFORMACION - TIMEWARD\n");
				printf("                               AGREGAR ASIGNATURA\n");
				printf("        ===============================================================\n\n\n");
				printf("           NO SE AGREGO LA ASIGNATURA!\n");
				printf("		1. SI\n");
				printf("		2. NO\n\n");
				printf("           INGRESE UNA DE LAS OPCIONES: ");
				opcion = leerOpcion(2);
				if (opcion == 2) {
					return;
				}
				system("cls");
			}
		} while (auxiliar == NULL);

		if (*headAsignatura == NULL) {
			*headAsignatura = (struct nodoAsignatura *)malloc(sizeof(struct nodoAsignatura));
			errorMemoria(*headAsignatura);
			*headAsignatura = auxiliar;
		}
		else {
			rec = *headAsignatura;
			while (rec->sig != NULL) {
				rec = rec->sig;
			}
			rec->sig = (struct nodoAsignatura *)malloc(sizeof(struct nodoAsignatura));
			rec->sig = auxiliar;
		}

		printf("        ===============================================================\n\n");
		printf("           DESEA AGREGAR OTRA ASIGNATURA?\n");
		printf("		1. SI\n");
		printf("		2. NO\n\n");
		printf("           INGRESE UNA DE LAS OPCIONES: ");
		opcion = leerOpcion(2);
		if (opcion == 1) {
			system("cls");
		}
	} while (opcion == 1);

	return;
}

void eliminarAsignatura(struct nodoAsignatura **headAsignatura) {
	char buffer[MAX];
	int opcion;
	int opcionRetorno;
	struct nodoAsignatura *primero = *headAsignatura;
	struct nodoAsignatura *rec = NULL;
	struct nodoAsignatura *asignaturaEliminar = NULL;

	if ((*headAsignatura) == NULL) {
		printf("        ===============================================================\n");
		printf("                       SISTEMA DE INFORMACION - TIMEWARD\n");
		printf("                              ELIMINAR ASIGNATURA\n");
		printf("        ===============================================================\n\n\n");
		printf("			   NO HAY ASIGNATURAS POR ELIMINAR!\n\n");
		return;
	}
	else {
		do {
			printf("        ===============================================================\n");
			printf("                       SISTEMA DE INFORMACION - TIMEWARD\n");
			printf("                              ELIMINAR ASIGNATURA\n");
			printf("        ===============================================================\n\n\n");
			printf("	  INGRESE EL NOMBRE DE LA ASIGNATURA QUE DESEA ELIMINAR : ");
			scanf(" %[^\n]s", buffer);
			mayusculas(buffer);
			asignaturaEliminar = buscarAsignatura(*headAsignatura, buffer);
			if (asignaturaEliminar) {
				printf("\n");
				printf("        ===============================================================\n\n");
				printf("               NOMBRE DE LA ASIGNATURA : %s\n", asignaturaEliminar->datosAsignatura->nombreAsignatura);
				printf("	       ESTA SEGURO QUE DESEA ELIMINAR LA ASIGNATURA? : \n");
				printf("	       1- SI\n	       2- NO\n\n");
				printf("               INGRESE UNA DE LAS OPCIONES: ");
				opcion = leerOpcion(2);
				switch (opcion) {
				case 1:
					if (asignaturaEliminar == *headAsignatura) {
						if (asignaturaEliminar->sig == NULL) {
							free(asignaturaEliminar);
							printf("               LA ASIGNATURA HA SIDO ELIMINADA EXISTOSAMENTE!\n\n");
							*headAsignatura = NULL;
							return;
						}
						else {
							primero = primero->sig;
							free(asignaturaEliminar);
							*headAsignatura = primero;
							printf("               LA ASIGNATURA HA SIDO ELIMINADA EXISTOSAMENTE!\n\n");
						}
					}
					else {
						rec = *headAsignatura;
						while (rec->sig != asignaturaEliminar) {
							rec = rec->sig;
						}
						rec->sig = rec->sig->sig;
						free(asignaturaEliminar);
						printf("               LA ASIGNATURA HA SIDO ELIMINADA EXISTOSAMENTE!\n\n");
					}
					break;
				case 2:
					printf("               LA ASIGNATURA NO HA SIDO ELIMINADA! \n\n");
					break;
				}
			}
			else {
				system("cls");
				printf("        ===============================================================\n");
				printf("                       SISTEMA DE INFORMACION - TIMEWARD\n");
				printf("                              ELIMINAR ASIGNATURA\n");
				printf("        ===============================================================\n\n\n");
				printf("	   LA ASIGNATURA QUE DESEA ELIMINAR NO HA SIDO ENCONTRADA!\n\n");
			}
			printf("        ===============================================================\n\n");
			printf("	     DESEA ELIMINAR OTRA ASIGNATURA?\n\n");
			printf("	     1- SI\n	     2- NO\n\n");
			printf("             INGRESE UNA DE LAS OPCIONES: ");
			opcionRetorno = leerOpcion(2);
			if (opcionRetorno == 1) {
				system("cls");
			}
		} while (opcionRetorno == 1);
	}
	return;
}

void agregarNotasSegundo(struct nodoNotas **headN) {
	struct nodoNotas *recN;
	float notaAlumno;

	printf("\n");
	printf("        ===============================================================\n\n");
	printf("           INGRESE LA NOTA DEL ESTUDIANTE : ");
	scanf("%f", &notaAlumno);

	if ((*headN) == NULL) {
		(*headN) = (struct nodoNotas*)malloc(sizeof(struct nodoNotas));
		(*headN)->nota = notaAlumno;
		(*headN)->sig = NULL;
	}
	else {
		recN = *headN;
		while (recN->sig != NULL) {
			recN = recN->sig;
		}
		
		recN->sig = (struct nodoNotas*)malloc(sizeof(struct nodoNotas));
		recN->sig->nota = notaAlumno;
		recN->sig->sig = NULL;
	}
	printf("\n");
	printf("           LA NOTA DEL ESTUDIANTE SE INGRESO EXITOSAMENTE!\n\n");

	return;
}

void agregarNotasPrimero(struct nodoAsignatura *headAsignatura) {
	struct nodoAsignatura *asignaturaMod = NULL; 				//Asignatura a Modificar
	char buffer[MAX];											//Cadena para leer
	int opcion;													//Opcion

	do {
		system("cls");
		printf("        ===============================================================\n");
		printf("                       SISTEMA DE INFORMACION - TIMEWARD\n");
		printf("                               AGREGAR NOTAS\n");
		printf("        ===============================================================\n\n\n");
		printf("           INGRESE EL NOMBRE DE LA ASIGNATURA : ");
		scanf(" %[^\n]s", buffer);
		mayusculas(buffer);
		asignaturaMod = buscarAsignatura(headAsignatura, buffer);

		if (asignaturaMod != NULL) {
			agregarNotasSegundo(&asignaturaMod->datosAsignatura->headNotas);
		}
		else {
			system("cls");
			printf("        ===============================================================\n");
			printf("                       SISTEMA DE INFORMACION - TIMEWARD\n");
			printf("                               AGREGAR NOTAS\n");
			printf("        ===============================================================\n\n\n");
			printf("           NO SE ENCONTRO LA ASIGNATURA QUE USTED INGRESO!\n\n");
			opcion = 2;
		}
		printf("        ===============================================================\n\n");
		printf("           DESEA AGREGAR OTRA NOTA?\n");
		printf("		1. SI\n");
		printf("		2. NO\n\n");
		printf("           INGRESE UNA DE LAS OPCIONES: ");
		opcion = leerOpcion(2);
		if (opcion == 1) {
			system("cls");
		}
	} while (opcion == 1);

	return;
}

void eliminarNotasSegundo(struct nodoNotas **headN) {
	struct nodoNotas *recN = NULL;
	int opcion;

	if ((*headN) == NULL) {
		system("cls");
		printf("        ===============================================================\n");
		printf("                       SISTEMA DE INFORMACION - TIMEWARD\n");
		printf("                               ELIMINAR NOTAS\n");
		printf("        ===============================================================\n\n\n");
		printf("           NO HAY NOTAS POR ELIMINAR EN ESTA ASIGNATURA!\n\n");
		return;
	}
	else {
		system("cls");
		printf("        ===============================================================\n");
		printf("                       SISTEMA DE INFORMACION - TIMEWARD\n");
		printf("                               ELIMINAR NOTAS\n");
		printf("        ===============================================================\n\n\n");
		printf("           DESEA ELIMINAR LAS NOTAS DE LA ASIGNATURA?\n");
		printf("           1- SI\n");
		printf("           2- NO\n\n");
		printf("           INGRESE UNAS DE LAS OPCIONES: ");
		opcion = leerOpcion(2);
		switch (opcion) {
		case 1:
			free(*headN);
			*headN = NULL;
			break;
		case 2:
			return;
			break;
		}
	}
}

void eliminarNotasPrimero(struct nodoAsignatura *headAsignatura) {
	struct nodoAsignatura *asignaturaMod = NULL;
	char buffer[MAX];
	int opcion;

	do {
		system("cls");
		printf("        ===============================================================\n");
		printf("                       SISTEMA DE INFORMACION - TIMEWARD\n");
		printf("                               ELIMINAR NOTAS\n");
		printf("        ===============================================================\n\n\n");
		printf("           INGRESE EL NOMBRE DE LA ASIGNATURA : ");
		scanf(" %[^\n]s", buffer);
		mayusculas(buffer);
		asignaturaMod = buscarAsignatura(headAsignatura, buffer);

		if (asignaturaMod) {
			eliminarNotasSegundo(&asignaturaMod->datosAsignatura->headNotas);
		}
		else {
			system("cls");
			printf("        ===============================================================\n");
			printf("                       SISTEMA DE INFORMACION - TIMEWARD\n");
			printf("                               ELIMINAR NOTAS\n");
			printf("        ===============================================================\n\n\n");
			printf("           NO SE ENCONTRO LA ASIGNATURA QUE USTED INGRESO!\n\n");
			opcion = 2;
		}
		printf("        ===============================================================\n\n");
		printf("           DESEA ELIMINAR OTRA NOTA?\n");
		printf("		1. SI\n");
		printf("		2. NO\n\n");
		printf("           INGRESE UNA DE LAS OPCIONES: ");
		opcion = leerOpcion(2);
		if (opcion == 1) {
			system("cls");
		}
	} while (opcion == 1);

	return;
}

void cargarProfesores(struct nodoProfesor **head) {
	FILE *DBProfesores;
	struct nodoProfesor *rec = NULL;
	char buffer[MAX];
	int control, i, j;
	int numeroHorario;
	
	DBProfesores = fopen("profesores.txt", "r");				//ABRE EL ARCHIVO
	if (DBProfesores == NULL) {									//SI OCURRE UN ERROR AL ABRIR
		printf("ERROR ARCHIVO VACIO\n");
		exit(1);
	}
	else {
		control = fscanf(DBProfesores, " %[^\n]s", buffer);			//A LA VARIABLE DE CONTROL SE LE ASIGNA LA PRIMERA LECTURA (LEE EL NOMBRE)
 
		while (control != EOF) {									//INICIA EL RECORRIDO DEL ARCHIVO
			if (*head == NULL) {									//SI NO EXISTE HEAD DE PROFESORES, SE CREA EL PRIMER ELEMENTO DE LA LISTA
				*head = (struct nodoProfesor *)malloc(sizeof(struct nodoProfesor));
				(*head)->datosProfesor = (struct Profesor *)malloc(sizeof(struct Profesor));			//SE ASIGNA LA MEMORIA DEL NODO

				(*head)->datosProfesor->nombreProfesor = (char *)malloc(sizeof(char)*strlen(buffer));	//SE ASIGNA LA MEMORIA DE NOMBRE Y SE COPIA DEL ARCHIVO
				strcpy((*head)->datosProfesor->nombreProfesor, buffer);

				fscanf(DBProfesores, " %[^\n]s", buffer);													//SE LEE EL APELLIDO
				(*head)->datosProfesor->apellidoProfesor = (char *)malloc(sizeof(char)*strlen(buffer));		//SE ASIGNA LA MEMORIA DE APELLIDO Y SE COPIA DEL ARCHIVO
				strcpy((*head)->datosProfesor->apellidoProfesor, buffer);

				fscanf(DBProfesores, " %[^\n]s", buffer);		//SE LEE EL RUT
				
				fgetc(DBProfesores);							//ELIMINA EL SALTO DE LINEA SIGUIENTE AL RUT
				(*head)->datosProfesor->rutProfesor = (char *)malloc(sizeof(char)*strlen(buffer));			//SE LE ASIGNA MEMORIA AL RUT Y LUEGO SE COPIA DEL ARCHIVO
				strcpy((*head)->datosProfesor->rutProfesor, buffer);

				for (i = 0; i < 8; i++) {
					for (j = 0; j < 5; j++) {
						numeroHorario = fgetc(DBProfesores) - 48;
						(*head)->datosProfesor->horario[i][j] = numeroHorario;
					}
					fgetc(DBProfesores);					//ELIMINA EL SALTO DE LINEA PARA LEER CORRECTAMENTE LA MATRIZ
				}
				(*head)->sig = (*head);
			}
			else {							//SI ENTRA ACA, SIGNIFICA QUE YA CREO LA CABEZA DE LA LISTA
				rec = *head;	
				do {						//RECORRE LA LISTA CIRCULAR HASTA EL ULTIMO ELEMENTO (EL QUE ESTA ENLAZADO CON EL HEAD)
					rec = rec->sig;
				} while (rec->sig != *head);

				rec->sig = (struct nodoProfesor *)malloc(sizeof(struct nodoProfesor));			//SE LE ASIGNA MEMORIA A ESE PUNTERO
				rec->sig->datosProfesor = (struct Profesor *)malloc(sizeof(struct Profesor));	//SE ASIGNA MEMORIA AL STRUCT DEL PUNTERO

				rec->sig->datosProfesor->nombreProfesor = (char *)malloc(sizeof(char)*strlen(buffer));	//SE ASIGNA MEMORIA AL NOMBRE Y SE COPIA DEL ARCHIVO
				strcpy(rec->sig->datosProfesor->nombreProfesor, buffer);


				fscanf(DBProfesores, " %[^\n]s", buffer);						//SE LEE EL APELLIDO
				rec->sig->datosProfesor->apellidoProfesor = (char *)malloc(sizeof(char)*strlen(buffer));	//SE LE ASIGNA MEMORIA AL APELLIDO Y SE COPIA DEL ARCHIVO
				strcpy(rec->sig->datosProfesor->apellidoProfesor, buffer);

				fscanf(DBProfesores, " %[^\n]s", buffer);						//LEE EL RUT DEL PROFESOR
				fgetc(DBProfesores);											//ELIMINA EL SALTO DE LINEA
				rec->sig->datosProfesor->rutProfesor = (char *)malloc(sizeof(char)*strlen(buffer));			//SE LE ASIGNA MEMORIA AL RUT Y SE COPIA DEL ARCHIVO
				strcpy(rec->sig->datosProfesor->rutProfesor, buffer);

				for (i = 0; i < 8; i++) {
					for (j = 0; j < 5; j++) {
						numeroHorario = fgetc(DBProfesores) - 48;
						rec->sig->datosProfesor->horario[i][j] = numeroHorario;
					}
					fgetc(DBProfesores);
				}
				rec->sig->sig = (*head);
			}
			control = fscanf(DBProfesores, " %[^\n]s", buffer);			//REALIZA LA MISMA LECTURA QUE ANTES DE ENTRAR AL CICLO (LEE EL NOMBRE)
		}
	}
	fclose(DBProfesores);							//SE CIERRA EL ARCHIVO
}

void guardarProfesores(struct nodoProfesor *head) {
	FILE *DBProfesores;
	struct nodoProfesor *rec = NULL;
	int i, j;
	DBProfesores = fopen("profesores.txt", "w+");
	rec = head;
	do {
		fprintf(DBProfesores, "%s\n", rec->datosProfesor->nombreProfesor);
		fprintf(DBProfesores, "%s\n", rec->datosProfesor->apellidoProfesor);
		fprintf(DBProfesores, "%s\n", rec->datosProfesor->rutProfesor);
		for (i = 0; i < 8; i++){
			for (j = 0; j <5; j++){
				fprintf(DBProfesores, "%d", rec->datosProfesor->horario[i][j]);
			}
			fprintf(DBProfesores, "\n");
		}
		rec = rec->sig;
	} while (rec != head);
}

void cargarCursos(struct nodoCurso **headCurso)
{
	FILE *DBCursos;
	struct nodoCurso *rec = NULL;
	struct nodoAsignatura *recAsig = NULL;
	struct nodoAsignatura *headAsig = NULL;
	struct nodoAlumno *headAlumno = NULL;
	struct nodoAlumno *recAlumno = NULL;
	struct nodoNotas *recNotas = NULL;
	char separador[6] = "~ * ~";
	char finalDeCurso[6] = "/////";
	char finalMaterias[6] = "_____";
	char buffer[MAX];
	int control, aux;

	//ESTE ES UN CODIGO EXPERIMENTAL, NO HA SIDO COMPROBADO CON TODOS LOS CASOS Y PUEDE QUE FALLE
	//ESTE CODIGO ES BASICAMENTE UNA IMPLEMENTACION DE TODO EL CODIGO DEL PROGRAMA, PERO SIN MODULARIZACION, YA QUE LA ENTRADA DE DATOS NO SERA DEL TECLADO
	//SI NO QUE SERA DE UN ARCHIVO

	DBCursos = fopen("cursos.txt", "r");
	if (DBCursos == NULL) {
		printf("ERROR AL ABRIR EL ARCHIVO \n");
		exit(1);
	}
	else {
		control = fscanf(DBCursos, " %[^\n]s", buffer);
		while (control != EOF) {
			if (*headCurso == NULL) {
				*headCurso = (struct nodoCurso *)malloc(sizeof(struct nodoCurso));
				(*headCurso)->datosCurso = (struct Curso *)malloc(sizeof(struct Curso));
				(*headCurso)->datosCurso->nombreCurso = (char *)malloc(sizeof(char)*strlen(buffer));
				strcpy((*headCurso)->datosCurso->nombreCurso, buffer);
				(*headCurso)->datosCurso->AsignaturaCurso = NULL;
				headAsig = (*headCurso)->datosCurso->AsignaturaCurso;
				headAlumno = (*headCurso)->datosCurso->headAlumno;

				fscanf(DBCursos, " %[^\n]s", buffer);
				while (strcmp(buffer, separador) != 0) {
					if (headAsig == NULL) {
						headAsig = (struct nodoAsignatura *)malloc(sizeof(struct nodoAsignatura));
						headAsig->datosAsignatura = (struct Asignatura *)malloc(sizeof(struct Asignatura));
						headAsig->datosAsignatura->nombreAsignatura = (char *)malloc(sizeof(char)*strlen(buffer));
						strcpy(headAsig->datosAsignatura->nombreAsignatura, buffer);
						headAsig->datosAsignatura->headNotas = NULL;
						headAsig->sig = NULL;
					}
					else {
						recAsig = headAsig;
						while (recAsig->sig != NULL) {
							recAsig = recAsig->sig;
						}
						recAsig->sig = (struct nodoAsignatura *)malloc(sizeof(struct nodoAsignatura));
						recAsig->sig->datosAsignatura = (struct Asignatura *)malloc(sizeof(struct Asignatura));
						recAsig->sig->datosAsignatura->nombreAsignatura = (char *)malloc(sizeof(char)*strlen(buffer));
						strcpy(recAsig->sig->datosAsignatura->nombreAsignatura, buffer);
						recAsig->sig->datosAsignatura->headNotas = NULL;
						recAsig->sig->sig = NULL;
					}
					fscanf(DBCursos, " %[^\n]s", buffer);
				}
				fscanf(DBCursos, "%d\n", (*headCurso)->datosCurso->cantidadAlumnos);

				fscanf(DBCursos, " %[^\n]s", buffer);
				while (strcmp(buffer, finalDeCurso) != 0) {
					if (headAlumno == NULL) {
						headAlumno = (struct nodoAlumno *)malloc(sizeof(struct nodoAlumno));
						headAlumno->datosAlumno = (struct Alumno *)malloc(sizeof(Alumno));
						headAlumno->datosAlumno->nombreAlumno = (char *)malloc(sizeof(char)*strlen(buffer));
						strcpy(headAlumno->datosAlumno->nombreAlumno, buffer);
						fscanf(DBCursos, " %[^\n]s", buffer);
						headAlumno->datosAlumno->apellidoAlumno= (char *)malloc(sizeof(char)*strlen(buffer));
						strcpy(headAlumno->datosAlumno->apellidoAlumno, buffer);
						fscanf(DBCursos, " %[^\n]s", buffer);
						headAlumno->datosAlumno->rutAlumno = (char *)malloc(sizeof(char)*strlen(buffer));

						fscanf(DBCursos, " %[^\n]s", buffer);
						headAsig = headAlumno->datosAlumno->headAsignatura;
						while (strcmp(buffer, separador) != 0) {
							if (headAsig == NULL) {
								headAsig = (struct nodoAsignatura *)malloc(sizeof(struct nodoAsignatura));
								headAsig->datosAsignatura = (struct Asignatura *)malloc(sizeof(struct Asignatura));
								headAsig->datosAsignatura->nombreAsignatura = (char *)malloc(sizeof(char)*strlen(buffer));
								headAsig->datosAsignatura->headNotas == NULL;
								strcpy(headAsig->datosAsignatura->nombreAsignatura, buffer);
								fscanf(DBCursos, " %[^\n]s", buffer);
								while (strcmp(buffer,separador)== 0) {
									if (headAsig->datosAsignatura->headNotas == NULL) {
										headAsig->datosAsignatura->headNotas = (struct nodoNotas *)malloc(sizeof(struct nodoNotas));
										headAsig->datosAsignatura->headNotas->nota = atof(buffer);
										headAsig->datosAsignatura->headNotas->sig = NULL;
									}
									else {
										recNotas = headAsig->datosAsignatura->headNotas;
										while (recNotas->sig != NULL) {
											recNotas = recNotas->sig;
										}
										recNotas->sig = (struct nodoNotas *)malloc(sizeof(struct nodoNotas));
										recNotas->sig->nota = atof(buffer);
										recNotas->sig->sig = NULL;
									}
								}
								headAsig->sig = NULL;
							}
							else {
								recAsig = headAsig;
								while (recAsig->sig != NULL) {
									recAsig = recAsig->sig;
								}
								recAsig->sig = (struct nodoAsignatura *)malloc(sizeof(struct nodoAsignatura));
								recAsig->sig->datosAsignatura = (struct Asignatura *)malloc(sizeof(struct Asignatura));
								recAsig->sig->datosAsignatura->nombreAsignatura = (char *)malloc(sizeof(char)*strlen(buffer));
								strcpy(recAsig->sig->datosAsignatura->nombreAsignatura, buffer);
								headAsig = recAsig->
								while(strcmp(buffer, separador) == 0) {
									if (headAsig->datosAsignatura->headNotas == NULL) {
										headAsig->datosAsignatura->headNotas = (struct nodoNotas *)malloc(sizeof(struct nodoNotas));
										headAsig->datosAsignatura->headNotas->nota = atof(buffer);
										headAsig->datosAsignatura->headNotas->sig = NULL;
									}
									else {
										recNotas = headAsig->datosAsignatura->headNotas;
										while (recNotas->sig != NULL) {
											recNotas = recNotas->sig;
										}
										recNotas->sig = (struct nodoNotas *)malloc(sizeof(struct nodoNotas));
										recNotas->sig->nota = atof(buffer);
										recNotas->sig->sig = NULL;
									}
								}
								headAsig->sig = NULL;
								recAsig->sig->sig = NULL;


							}
							fscanf(DBCursos, " %[^\n]s", buffer);
						}
					}
					else {

					}
					fscanf(DBCursos, " %[^\n]s", buffer);
				}

				(*headCurso)->sig = NULL;
			}
			else {
				while (rec->sig != NULL) {
					rec = rec->sig;
				}
				*headCurso = (struct nodoCurso *)malloc(sizeof(struct nodoCurso));
				(*headCurso)->datosCurso = (struct Curso *)malloc(sizeof(struct Curso));
				(*headCurso)->datosCurso->nombreCurso = (char *)malloc(sizeof(char)*strlen(buffer));
				strcpy((*headCurso)->datosCurso->nombreCurso, buffer);
				(*headCurso)->datosCurso->AsignaturaCurso = NULL;
				headAsig = (*headCurso)->datosCurso->AsignaturaCurso;
				fscanf(DBCursos, " %[^\n]s", buffer);
				while (strcmp(buffer, separador) != 0) {
					if (headAsig == NULL) {
						headAsig = (struct nodoAsignatura *)malloc(sizeof(struct nodoAsignatura));
						headAsig->datosAsignatura = (struct Asignatura *)malloc(sizeof(struct Asignatura));
						headAsig->datosAsignatura->nombreAsignatura = (char *)malloc(sizeof(char)*strlen(buffer));
						strcpy(headAsig->datosAsignatura->nombreAsignatura, buffer);
						headAsig->datosAsignatura->headNotas = NULL;
						headAsig->sig = NULL;
					}
					else {
						recAsig = headAsig;
						while (recAsig->sig != NULL) {
							recAsig = recAsig->sig;
						}
						recAsig->sig = (struct nodoAsignatura *)malloc(sizeof(struct nodoAsignatura));
						recAsig->sig->datosAsignatura = (struct Asignatura *)malloc(sizeof(struct Asignatura));
						recAsig->sig->datosAsignatura->nombreAsignatura = (char *)malloc(sizeof(char)*strlen(buffer));
						strcpy(recAsig->sig->datosAsignatura->nombreAsignatura, buffer);
						recAsig->sig->datosAsignatura->headNotas = NULL;
						recAsig->sig->sig = NULL;
					}
					fscanf(DBCursos, " %[^\n]s", buffer);
				}

				(*headCurso)->sig = NULL;

			}
			control = fscanf(DBCursos, " %[^\n]s", buffer);
		}
	}
}

void guardarCursos(struct nodoCurso *head) {
	FILE *DBCursos;
	struct nodoCurso *recCurso = NULL;
	struct nodoAsignatura *recAsig = NULL;
	struct nodoAlumno *recAlumno = NULL;
	struct nodoNotas *recNotas = NULL;
	

	DBCursos = fopen("cursos.txt","w+");
	recCurso = head;
	while (recCurso != NULL) {
		fprintf(DBCursos, "%s\n", recCurso->datosCurso->nombreCurso);
		recAsig = recCurso->datosCurso->AsignaturaCurso;
		while (recAsig != NULL) {
			fprintf(DBCursos, "%s\n", recAsig->datosAsignatura->nombreAsignatura);
			recAsig = recAsig->sig;
		}
		printf("~ * ~");

		fprintf(DBCursos, "%d\n", recCurso->datosCurso->cantidadAlumnos);
		recAlumno = recCurso->datosCurso->headAlumno;
		if (recAlumno) {
			while (recAlumno != NULL) {
				fprintf(DBCursos, "%s\n", recAlumno->datosAlumno->nombreAlumno);
				fprintf(DBCursos, "%s\n", recAlumno->datosAlumno->apellidoAlumno);
				fprintf(DBCursos, "%s\n", recAlumno->datosAlumno->rutAlumno);

				recAsig = NULL;
				recAsig = recAlumno->datosAlumno->headAsignatura;
				while (recAsig != NULL) {
					fprintf(DBCursos, "%s\n", recAsig->datosAsignatura->nombreAsignatura);
					recNotas = recAsig->datosAsignatura->headNotas;
					if (recNotas) {
						while (recNotas != NULL) {
							fprintf(DBCursos, "%0.1f\n", recNotas->nota);
							recNotas = recNotas->sig;
						}
						fprintf(DBCursos,"~ * ~");
					}
					recAsig = recAsig->sig;
				}
				fprintf(DBCursos,"_____");
				recAlumno = recAlumno->sig;
			}
			fprintf(DBCursos,"~ * ~");
		}
		recCurso = recCurso->sig;
	}
	fprintf(DBCursos,"/////");
}
