/*	Puro hueso ultimamente estuvo indagando en el folklore argetino y se volvio muy fanatico de este genero nuevo para el
Le empezo agarrar curiosidad sobre las letras de las canciones y por eso nos pidio ayuda para que le saciemos esta curiosidad
	SE PIDE
1.Dado un archivo de texto que contiene la letra de una  cancion, se pide que se devuelva la cantidad de letras que hay de
cada una, es decir,cuantas a , cuantas b, cuantas c,etc
Se debe pensar en una estructura para la solucion del problema y justificar la eleccion*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_NOMBRE 20
#define ERROR -1
#define MAX_ABECEDARIO 54
#define MAX_CARACTERES 27
#define FIN_ABECEDARIO_MIN 122
#define FIN_ABECEDARIO_MAYUS 90
#define INICIO_ABECEDARIO_ASCII_MIN 96
#define INICIO_ABECEDARIO_ASCII_MAYUS 65
#define FORMATO_LECTURA "%c"
typedef struct caracteres{
	char letra;
	int cantidad;
}caracteres_t;
/*	
	Procedimiento que lee del stream cancion todos los caracteres de la cancion y al final quedan con sus cantidades.
*/
void escanear_caracteres(FILE* cancion,caracteres_t abc[MAX_ABECEDARIO],int tope_abc){
	char auxiliar;
	bool encontro;
	int i;
	while(!feof(cancion)){
		i=0;
		encontro=false;
		fscanf(cancion,"%c",&auxiliar);
		while((!encontro)&&(i<tope_abc)){
			if(auxiliar==abc[i].letra){
				(abc[i].cantidad)++;
				encontro=true;
			}
			i++;
		}
	}
}
/*	
	Funcion que lee el archivo de la cancion de puro hueso
*/
int leer_archivo_cancion(char nombre_archivo_cancion[MAX_NOMBRE],caracteres_t abc[MAX_ABECEDARIO],int tope_abc){
	FILE* cancion=fopen(nombre_archivo_cancion,"r");
	if(!cancion){
		perror("No se pudo abrir el archivo de cancion");
		return ERROR;
	}
	escanear_caracteres(cancion,abc,tope_abc);
	fclose(cancion);
	return 0;
}
/*
	Procedimiento que a un vector de tipo caracteres_t le pone en su campo letra, todas las letras del abecedario,primero en
mayuscula y luego en minuscula	
*/
void asignar_letras_a_vector(caracteres_t abc[MAX_ABECEDARIO],int* tope_abc){
	int j=0;
	for(int i=INICIO_ABECEDARIO_ASCII_MAYUS;i<FIN_ABECEDARIO_MIN;i++){
		if((i<FIN_ABECEDARIO_MAYUS)||(i>INICIO_ABECEDARIO_ASCII_MIN)){
			abc[j].letra=i;
			abc[j].cantidad=0;
			j++;
			(*tope_abc)++;
		}
	}
}
/*	Procedimiento que */
void contar_cantidades_letras(caracteres_t abc[MAX_ABECEDARIO],int* tope_abc){
	asignar_letras_a_vector(abc,tope_abc);
	leer_archivo_cancion("cancion.txt",abc,(*tope_abc));
}

int main(){
	caracteres_t abc[MAX_ABECEDARIO];
	int tope_abc=0;
	contar_cantidades_letras(abc,&tope_abc);
	for(int i=0;i<tope_abc;i++){
		printf("Caracter %c - cantidad %i \n",abc[i].letra,abc[i].cantidad );
	}
	printf("\n");
	return 0;
}

