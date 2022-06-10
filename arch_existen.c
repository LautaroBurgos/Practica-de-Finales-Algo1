/*
    Crear un programa que reciba un archivo que contiene directorios de carpetas, y compruebe cuales de esos directorios existen en la pc y guardarlos.
    
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_NOMBRE 20
#define MAX_DIRECCION 50
#define MAX_DIRECTORIOS 100
#define MODO_LECTURA "r"
#define ERROR -1
#define CANT_LEIDOS 1
#define FORMATO_LECTURA "%s\n"
#define FORMATO_ESCRITURA "%s\n"

typedef struct directorio{
	char direccion[MAX_DIRECCION];
}directorio_t;
/*
	Procedimiento que guarda un directorio pasado en un string, en un vector de directorios y aumenta en uno el tope.
*/
void guardar_directorio(char auxiliar[MAX_DIRECCION],directorio_t directorios_existen[MAX_DIRECTORIOS],int* tope_directorios){
	strcpy(directorios_existen[*tope_directorios],auxiliar);
	(*tope_directorios)++;
}
/*
	Funcion booleana que devuelve true si en el directorio pasado por parametro, existe un archivo,o false en caso de que no
*/
bool existe_archivo(char auxiliar[MAX_DIRECCION]){
	FILE*arch=fopen(auxiliar,MODO_LECTURA);
	if(!arch){
		return false;
	}
	else{
		fclose(arch);
		return true;
	}
}
/*
	Funcion que lee un directorio de un archivo de direcciones, y lo guarda en un auxiliar
*/
int leer_directorio(FILE* arch_direcciones,char auxiliar[MAX_DIRECCION]){
	return fscanf(arch_direcciones,FORMATO_LECTURA,auxiliar);
}
/*
	PRE:Recibe un puntero a un archivo de direcciones en modo lectura, el vector de directorios y el tope de directorios por
	referencia.
	POST:El vector de directorios queda solo con los directorios donde haya arrchivos que existan y el tope en el valor
	correspondiente.
	Procedimiento que lee un archivo de direcciones, revisa que estas mismas existan, y de ser asi las agrega al vector de 
	direcciones que existen.	
*/
void seleccionar_directorios_que_existen(FILE* arch_direcciones,directorio_t directorios_existen,int* tope_directorios){
	char auxiliar[MAX_DIRECCION];
	int leidos=leer_directorio(arch_direcciones,auxiliar);
	if(existe_archivo(auxiliar)){
		guardar_directorio(auxiliar,directorios_existen,tope_directorios);
	}
	while(leidos==CANT_LEIDOS){
		leidos=leer_directorio(arch_direcciones,auxiliar);
		if(existe_archivo(auxiliar)){
			guardar_directorio(auxiliar,directorios_existen,tope_directorios);
		}
	}
}
/*
	PRE:Recibe el nombre del archivo de direcciones, el vector de directorios vacio y su tope por referencia en cero.SE
	considera que los archivos entran en memoria. Se utilizo un vector de tipo directorio_t para guardar la informacion
	 porque lo considero mas facil de trabajar que un vector de strings.
	POST:El vector de directorios queda solo con las direcciones donde existen archivos. Devuelve 0 si todo salio bien o
	-1 si hubo error al abrir el archivo de direcciones.
	Procedimiento que abre un archivo de directorios de archivos en la computadora,lee y compara si estos archivos existen, y de 
	ser asi guarda el directorio en un vector de directorios pasado por parametro ,esto a traves de otras funciones.
*/
int guardar_directorios_archivos_que_existen(char nombre_archivo_directorios[MAX_NOMBRE],
	directorio_t directorios_existen[MAX_DIRECTORIOS],int* tope_directorios){

	FILE* arch_direcciones=fopen(nombre_archivo_directorios,MODO_LECTURA);
	if(!arch_direcciones){
		perror("No se pudo abrir el archivo de directorios");
		return ERROR;
	}
	seleccionar_directorios_que_existen(arch_direcciones,directorios_existen,tope_directorios);
	flose(arch_direcciones);
	return 0;
}	
