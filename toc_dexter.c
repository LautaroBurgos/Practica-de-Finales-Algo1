/*
	Dexter tiene un par (varios) de tocs. Uno de ellos, es que le molesta ver que el volumen de la television en numero
	impar(a menos que sea 5).Dee dee, siempre dispuesta a molestarlo, se gasto en poner todos los televisores de su 
	laboratorio en numeros aleatorios. 
	Se pide
	Teniendo un archivo donde cada linea representa el volumen de cada televisor,modificarlos de la siguiente manera.
	Si es impar menor  a 5, cambiarlo por el numero par mas cercano yendo para abajo.Si es impar mayor a 5, cambiarlo
	por el numero par mas cercano yendo para arriba.
*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define ERROR -1
#define MAX_NOMBRE 30
#define MODO_LECTURA "r"
#define CINCO 5
#define MODO_ESCRITURA "w"
#define FORMATO_LECTURA "%i\n"
#define FORMATO_ESCRITURA "%i\n"
/*
	Funcion booleana que devuelve true si un entero es impar o false en caso de ser par.
*/
bool es_impar(int valor){
	return((valor%2)!=0);
}
/*
	PRE:Recibe un puntero al archivo de volumenes en modo lectura y un entero por referencia.
	POST:El auxiliar queda con el valor leido.
	Funcion que lee una linea del archivo volumenes, y guarda lo leido en el auxiliar, devuelve la cantidad de enteros leidos.
*/
int leer_una_linea(FILE* volumenes,int* auxiliar){
	return (fscanf(volumenes,FORMATO_LECTURA,&(*auxiliar)));
}
/*
	PRE:Recibe un puntero a un archivo en modo escritura y un entero.
	POST:El valor entero queda escrito en el archivo.
	Procedimiento que escribe el valor dado por parametro en el archivo del cual se recibe el puntero por parametro.
*/
void escribir_una_linea(FILE* valores_corregidos,int auxiliar){
	fprintf(valores_corregidos,FORMATO_ESCRITURA,auxiliar );
}
/*
	PRE:Recibe un entero, y un puntero  a un archivo en modo escritura.
	POST:El archivo valores corregidos queda con el valor auxiliar escrito, si es necesario, corregido.
	Procedimiento que segun el valor que recibe en el auxiliar, escribe o un valor u otro segun, las elecciones de dexter
	en el archivo  valores_corregidos.
*/
void escribir_valor_correspondiente(int auxiliar,FILE* valores_corregidos){
	if((es_impar(auxiliar))&&(auxiliar>CINCO)){
		escribir_una_linea(valores_corregidos,auxiliar+1);
	}
	else if((es_impar(auxiliar))&&(auxiliar<CINCO)){
		escribir_una_linea(valores_corregidos,auxiliar-1);
	}
	else{
		escribir_una_linea(valores_corregidos,auxiliar);
	}
}
/*
	PRE:Recibe 2 punteros a archivos, el de volumenes en modo lectura, y el de valores_corregidos en modo escritura.
	POST:El archivo auxiliar queda con los valores del volumenes , pero corregidos segun las preferencias de dexter.
	Procedimiento que recorre todo el archivo de volumenes, a la vez que compara ,y escribe el valor corregido en el auxiliar.
*/
void arreglar_cada_linea(FILE* volumenes,FILE* valores_corregidos){
	int auxiliar;
	int leidos=leer_una_linea(volumenes,&auxiliar);
	while(leidos==CANT_LEIDOS){
		escribir_valor_correspondiente(auxiliar,valores_corregidos);
		leidos=leer_una_linea(volumenes,&auxiliar);
	}
}
/*

	PRE:Recibe el nombre del archivo de volumenes
	POST:El archivo queda con los valores corregidos que son mas a gusto de dexter.
	Funcion que lee un archivo de volumenes, y lo corrige a un valor deseado en caso de que no sea del agrado de dexter, 
	devuelve  0 si pudo abrir bien los archivos o -1 si no pudo abrir alguno de ellos.

*/
int corregir_volumenes(char nombre_archivo_volumenes[MAX_NOMBRE]){
	FILE* volumenes=fopen(nombre_archivo_volumenes,MODO_LECTURA);
	if(!volumenes){
		perror("No se pudo abrir el archivo de volumenes");
		return	ERROR;
	}
	FILE* valores_corregidos=fopen("aux.csv",MODO_ESCRITURA);
	if(!valores_corregidos){
		perror("No se pudo crear el archivo valores_corregidos");
		return ERROR;
	}
	arreglar_cada_linea(volumenes,valores_corregidos);
	fclose(valores_corregidos);
	fclose(volumenes);
	rename(valores_corregidos,volumenes);
	return 0;
}