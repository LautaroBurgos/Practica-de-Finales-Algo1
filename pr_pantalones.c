/*
	Johnny Bravo es un hombre que siempre viste de la misma forma, no le gusta salirse de su zona de confort, pero a 
	pesar de eso es muy exigente con la calidad de las prendas que compra, en este caso vamos a ayudarle con los pantalones.
	Tiene un archivo csv en donde guardar registros de todos los pantalones que fue viendo en internet, tiene el formato
	marca;color;numero_talle;tela_calidad
	Se pide 
	Dado el archivo de pantalones, hacer un algoritmo que dado un cierto talle, elimine del archivo a todos los pantalones
	que tengan talle menor al talle especificado.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_MARCA 30
#define MAX_CALIDAD 20
#define MAX_NOMBRE 20
#define MODO_LECTURA "r"
#define MODO_ESCRITURA "w"
#define FORMATO_ESCRITURA "%s;%i;%s\n"
#define FORMATO_LECTURA "%[^;];%i;%[^\n]\n"
#define CANT_LEIDOS 3
#define ERROR -1

typedef struct pantalon{
	char marca[MAX_MARCA];
	int numero_talle;
	char tela_calidad[MAX_CALIDAD];
}pantalon_t;
/*
	Procedimiento que escribe en un archivo auxiliar, el pantalon pasado por parametro.
*/
void escribir_pantalon_en_auxiliar(FILE* auxiliar,pantalon_t pantalon_aux){
	fprintf(auxiliar,FORMATO_ESCRITURA,pantalon_aux.marca,pantalon_aux.numero_talle,pantalon_aux.tela_calidad);
}
/*
	Funcion booleana que devuelve true si el talle del pantalon dado es mayor o igual que el talle buscado
*/
bool pantalon_cumple(int talle_pantalon,int talle_buscado){
	return (talle_pantalon>=talle_buscado);
}
/*
	Funcion que lee una linea del archivo csv de pantalones y guarda su contenido en una estructura auxiliar.
*/
int leer_un_pantalon(FILE* pantalones,pantalon_t* pantalon_aux){
	return(fscanf(pantalones,FORMATO_LECTURA,(*pantalon_aux).marca,&(*pantalon_aux).numero_talle,(*pantalon_aux).tela_calidad));
}
/*
	Procedimiento que escribe lee un archivo de pantalones, compara y guarda en un auxiliar,si cumple la condicion de ser
	mayor al talle buscado.
*/
void guardar_pantalones_cumplen(FILE* pantalones,FILE* auxiliar,int talle_buscado){
	pantalon_t pantalon_aux;
	int leidos=leer_un_pantalon(pantalones,&pantalon_aux);
	while(leidos==CANT_LEIDOS){
		if(pantalon_cumple(pantalon_aux.numero_talle,talle_buscado)){
			escribir_pantalon_en_auxiliar(auxiliar,pantalon_aux);
		}
		leidos=leer_un_pantalon(pantalones,&pantalon_aux);
	}
}
/*
	Funcion que abre un archivo csv de pantalones, lo lee y elimina de este a todos  los pantalones con talle menor al talle
	pasado por parametro.
*/
int eliminar_pantalones_talle_mas_chico(char nombre_archivo_pantalones[MAX_NOMBRE],int talle_buscado){
	FILE* pantalones =fopen(nombre_archivo_pantalones,MODO_LECTURA);
	if(!pantalones){
		perror("No se pudo abrir el archivo de pantalones");
		return ERROR;
	}
	FILE* auxiliar=fopen("aux.csv",MODO_ESCRITURA);
	if(!auxiliar){
		perror("No se pudo crear el archivo auxiliar");
		fclose(pantalones);
		return ERROR;	
	}
	guardar_pantalones_cumplen(pantalones,auxiliar,talle_buscado);
	flcose(auxiliar);
	fclose(pantalones);
	rename(pantalones,auxiliar);
	return 0;
}