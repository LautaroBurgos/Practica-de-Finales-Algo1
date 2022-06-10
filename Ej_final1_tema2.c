/*	A burbuja, los dias de tormenta la ponen muy mal,se angustia, estresa, se pasa de vueltas y muchas sensaciones mas que no
vamos a comentar porque no son el objetivo de este ejercicio.
El profesor Utonio,creo un juego para que burbuja se mantenga ocupada en estos dias grises.



El juego consiste en una matriz cargada de numeros  positivos aleatorios, y realizar tantas vueltas como sean necesarias
hasta que la matriz se "estabilice"	.
La matriz esta estabilizada cuando ningun numero de ella cambia en una vuelta.
En cada vuelta, a cada numero se le resta el que esta a su izquierda(en el caso del primero numero se le resta el que esta
en la ultima columna).Si un numero pasa a ser negativo,este se transforma automaticamente en un cero.

SE PIDE 
1.Crear una funcion que reciba una matriz cargada con numeros positivos y devuelva cuantas "vueltas" tiene que dar burbuja
hasta estabilizar la matriz.*/
#include <stdio.h>
#include <stdbool.h>
#define MAX_FILAS 30
#define MAX_COL 30
#define PRIMERA_COLUMNA 0
#define CERO 0
/*	
	Funcion booleana que compara 2 enteros, devuelve true de ser asi o false en caso contrario.
*/
bool numeros_iguales(int a,int b){
	return (a==b);
}
/*
	Funcion booleana auxiliar que revisa si una matriz es igual a otra recursivamente, devuelve false, en caso de NO 
	haber cambiado, o 	true , si encuentra diferencia
*/
bool matriz_cambio_rec(int matriz[MAX_FILAS][MAX_COL],int anterior[MAX_FILAS][MAX_COL],int fil_actual,int col_actual){
	if(fil_actual==MAX_FILAS-1 && col_actual==MAX_COL-1){
		return false;
	}
	if(numeros_iguales(matriz[fil_actual][col_actual],anterior[fil_actual][col_actual])){
		if(col_actual==MAX_COL-1){
			return (matriz_cambio_rec(matriz,anterior,fil_actual+1,0));
		}
		else{
			return(matriz_cambio_rec(matriz,anterior,fil_actual,col_actual+1));
		}
	}
	else{
		return false;
	}
}
/*
	Funcion booleana que devuelve true, si una matriz cambio respecto a su anterior o false en caso contrario.
*/
bool matriz_cambio(int matriz[MAX_FILAS][MAX_COL],int anterior[MAX_FILAS][MAX_COL]){
	return	matriz_cambio_rec(matriz,anterior,0,0);
}
/*
	Procedimiento que hace una copia de una matriz de enteros para posteriormente revisar si esta cambio.
*/
void guardar_matriz_copia(int matriz[MAX_FILAS][MAX_COL],int copia[MAX_FILAS][MAX_COL]){
	for(int fil_actual=0;fil_actual<MAX_FILAS;fil_actual++){
		for(int col_actual=0;col_actual<MAX_COL;col_actual++){
			copia[fil_actual][col_actual]=matriz[fil_actual][col_actual];
		}
	}
}
/*
	Procedimiento que recorre una matriz de enteros y en caso de haber un numero negativo lo reemplaza por cero
*/
void convertir_negativos_a_cero(int matriz[MAX_FILAS][MAX_COL]){
	for(int fil_actual=0;fil_actual<MAX_FILAS;fil_actual++){
		for(int col_actual=0;col_actual<MAX_COL;col_actual++){
			if(matriz[fil_actual][col_actual]<CERO){
				matriz[fil_actual][col_actual]=CERO;
			}
		}
	}
}
/*
	Procedimiento que se encarga de restar un numero de una matriz de una matriz de enteros con su anterior, o en caso
	de ser la primera columna, resta con el numero de la ultima columna.
*/
void restar_num_anterior(int matriz[MAX_FILAS][MAX_COL]){
	for(int fil_actual=0;fil_actual<MAX_FILAS;fil_actual++){
		for(int col_actual=0;col_actual<MAX_COL;col_actual++){
			if(col_actual==PRIMERA_COLUMNA){
				matriz[fil_actual][col_actual]-=matriz[fil_actual][MAX_COL-1];
			}
			else{
				matriz[fil_actual][col_actual]-=matriz[fil_actual][col_actual-1];
			}
		}
	}
}
/*
	Funcion que devuelve la cantidad de vueltas que tuvo que dar  la matriz de numeros aleatorios hasta estabilizarse.
*/
int vueltas_dadas(int matriz[MAX_FILAS][MAX_COL]){
	int vueltas=0;
	bool cambio=true;
	int matriz_anterior[MAX_FILAS][MAX_COL];
	while(cambio){
		guardar_matriz_copia(matriz,matriz_anterior);
		restar_num_anterior(matriz);
		if(matriz_cambio(matriz,anterior)){
			vueltas++;
		}
		else{
			cambio=false;
		}
	}
	return vueltas;
}