/*
    Crear un programa que lea una cancion

*/#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_CANCION 500
#define MAX_PALABRA 20
#define MAX_NOMBRE 20
#define ERROR -1
#define FORMATO "%c"
#define ESPACIO ' '
#define CARACTER_NULO '\0'
#define COMA ','
#define PUNTO '.'

typedef struct cancion{
	char palabra[MAX_PALABRA];
}cancion_t;
/*
    Recibe un caracter y devuelve true si es una letra  o false si es un espacio,un punto o una coma
*/
bool es_caracter_valido(char caracter){
	return((caracter!=ESPACIO)&&(caracter!=COMA)&&(caracter!=PUNTO));
}
/*
    Funcion auxiliar que realiza el proceso de contar las palabras
*/
void contar_palabras(cancion_t palabras_sin_repetir[MAX_CANCION],int* tope_palabras,FILE* cancion){
	char auxiliar;
	int caracter_actual=0;
	int leidos=fscanf(cancion,FORMATO,&auxiliar);
	while(leidos!=0){
		while(es_caracter_valido(auxiliar)){
			palabras_sin_repetir[*tope_palabras].palabra[caracter_actual]=auxiliar;
			caracter_actual_palabra++;
		}
		palabras_sin_repetir[*tope_palabras].palabra[caracter_actual]=CARACTER_NULO;
	}
}
/*
	PRECONDICION: Recibe el nombre del archivo cancion por parametro 
	POSTCONDICION: Devuelve la cantidad total de palabras en la cancion que no se repiten ,o -1 si no  se pudo abrir el archivo

*/
int cantidad_palabras_sin_repetir(char nombre_archivo_cancion[MAX_NOMBRE]){
	cancion_t palabras_sin_repetir[MAX_CANCION];
	int tope_palabras;
	FILE* cancion =fopen(nombre_archivo_cancion,"r");
	if(!cancion){
		perror("No se pudo abrir el archivo");
		return ERROR;
	}
	contar_palabras(palabras,&tope_palabras,cancion);


	fclose(cancion);
	return tope_palabras;
}
