/*
    Crear un programa que invierta el orden de las letras de una frase.
    EJ;
    El cielo es azul
    luza se oleic lE
*/

#include <stdio.h>
#include <stdbool.h>
#define MAX_FRASE 100
#define MAX_PALABRA 30
#define ESPACIO ' '
#define STRING_ESPACIO " "
#define MAX_PALABRAS 50
#define CARACTER_NULO '\0'
#define NUEVA_PALABRA 0
typedef struct palabra_t{
	char palabra[MAX_PALABRA];
	int orden;
}palabra_t;
/*
	PRE:Recibe 2 strings
	POST:El primero queda con el segundo concatenado.
	Procedimiento que concatena el segundo string recibido en el primero.
*/
void concatenar_palabras(char auxiliar[MAX_FRASE],char palabra[MAX_PALABRA]){
	strcat(auxiliar,palabra);
}
/*
	Procedimiento que pasa las palabras de un vector de palabra_t a un string frase, colocando los respectivos espacios en el
	medio.
*/
void pasar_vector_a_frase(palabra_t palabras[MAX_PALABRAS],int tope_palabras,char frase[MAX_FRASE]){
	char auxiliar[MAX_FRASE];
	for(int i=0;i<tope_palabras;i++){
		concatenar_palabras(auxiliar,palabras[i].palabra);
		if(i<tope_palabras-1){
			concatenar_palabras(auxiliar,STRING_ESPACIO);
		}
	}
	strcpy(frase,auxiliar);
}
/*	
	PRE:Recibe un vector de palabras y su tope.
	POST:El vector de palabras queda ordenado segun lo especificado.
	Procedimiento que ordena un vector de palabras, descendentemente por orden.
*/
void ordenar_vector_descendentemente(palabra_t vector_palabras[MAX_PALABRAS],int tope_palabras){
	palabra_t auxiliar;
	for(int i=1;i<tope_palabras;i++){
		for(j=0;j<tope_palabras-1;j++){
			if(vector_palabras[j+1].orden<vector_palabras[j].orden){
				auxiliar=vector_palabras[j];
				vector_palabras[j]=vector_palabras[j+1];
				vector_palabras[j+1]=auxiliar;
			}
		}
	}
}
/*
	Procedimiento que agrega una palabra y su orden a un vector de tipo palabra_t
*/
void agregar_palabra(palabra_t vector_palabras[MAX_PALABRAS],int* tope_palabras,char auxiliar[MAX_PALABRA],int* palabra_actual){
	strcpy(vector_palabras[(*tope_palabras)].palabra,auxiliar);
	vector_palabras[*tope_palabras].orden=(*palabra_actual);
	(*tope_palabras)++;
	(*palabra_actual)++;
}
/*
	PRE:Recibe un string y el caracter donde va  a ir Caracter nulo.
	POST:El string queda con el \0 puesto al final.
	Procedimiento que finaliza una palabra en un string con el caracter nulo. Y pone la variable para leer palabras en cero
	lista para leer otra palabra.
*/
void finalizar_palabra(char auxiliar[MAX_PALABRA],int* caracter_actual_aux){
	auxiliar[(*caracter_actual_aux)]=CARACTER_NULO;
	(*caracter_actual_aux)=NUEVA_PALABRA;
}
/*
	PRE:Recibe el string frase, un vector de palabras, y su tope por referencia en cero.
	POST:El vector de palabras queda con las palabras pasadas y su respectivo orden cada uno. Su tope queda con el valor
	correspondiente.
	Procedimiento que lee un string frase, palabra por palabra, en un vector de tipo palabra_t , junto con el orden en el
	que se encuentra en la frase.
*/
void pasar_palabras_a_vector(char frase[MAX_FRASE],palabra_t vector_palabras[MAX_PALABRAS],int* tope_palabras){
	int caracter_actual_frase=0;
	char auxiliar[MAX_PALABRA];
	int caracter_actual_aux=0;
	int palabra_actual=0;
	while(!(termino_de_leer(frase[caracter_actual_frase]))){
		if(es_caracter_valido(frase[caracter_actual_frase])){
			auxiliar[caracter_actual_aux]=frase[caracter_actual_frase];
			caracter_actual_aux++;
		}
		finalizar_palabra(auxiliar,&caracter_actual_aux);
		agregar_palabra(palabras,tope_palabras,auxiliar,&palabra_actual);
		caracter_actual_frase++;
	}
}
/*
	PRE:Recibe un string frase.r
	POST:La frase queda con sus palabras en el orden inverso.
	Procedimiento que da vuelta el orden de las palabras de una frase.
*/
void dar_vuelta_frase(char frase[MAX_FRASE]){
	palabra_t vector_palabras[MAX_PALABRAS];
	int tope_palabras=0;
	pasar_palabra_a_vector(frase,vector_palabras,&tope_palabras);
	ordenar_vector_descendentemente(vector_palabras,tope_palabras);
	pasar_vector_a_frase(vector_palabras,tope_palabras,frase);
}
