/* A burbuja, los dias de tormenta la ponen muy mal, se angustia, se estresa se pasa de vuelta y muchas sensaciones mas q.
El profesor utonio , creo  un juego para que burbuja se mantenga ocupada ene esos dias grises.
El juego consiste en una matriz cargada con numero positivos aleatorios y menores  a 10, y realiza tantas vueltas como
sean necesarias hasta que la matriz se "estabilice".
La matriz esta estabilizada cuando ningun numero de ella cambia en una vuelta.
En cada vuelta, a cada numero se le suma el que esta a su izquierda y a su derecha(en el caso de estar en un borde , solo
se le suma el costado que existe).Si un numero llega a 100 (o se pasa) debe quedar en 100.
SE PIDE
1.Crear una funcion ue reciba una matriz cargada con numeros positivos y devuelva cuantas "vueltas" tiene que dar Burbuja hasta
estabilizar la matriz.
*/
#include <stdio.h>
#include <stdbool.h>
#define MAX_FIL 20
#define MAX_COL 20
#define MAX_VALOR 100
#define PRIMERA_COL 0
/*
	Funcion booleana que devuelve true si dos enteros son iguales o false en caso contrario
*/
bool son_iguales(int a,int b){
	return(a==b);
}
/*
	Funcion booleana que recorre una matriz recursivamente y devuelve false si encuentra diferencia entre el contenido
	de las dos matrices o true si son iguales
*/
bool se_estabilizo_rec(int matriz[MAX_FIL][MAX_COL],int matriz_auxiliar[MAX_FIL][MAX_COL],int fila_actual,int col_actual){
	if((fila_actual>=MAX_FIL)||(col_actual>=MAX_COL)){
		return true;
	}
	if(!son_iguales(matriz[fila_actual][col_actual],matriz_auxiliar[fila_actual][col_actual])){
		return false;
	}
	else{
		if(col_actual==MAX_COL-1){
			if(fila_actual==MAX_FIL-1){
				return true;
			}
			else{
				return(se_estabilizo(matriz,matriz_auxiliar,fila_actual+1,0));
			}
		}
		else{
			return (se_estabilizo(matriz,matriz_auxiliar,fila_actual,col_actual+1));
		}
	}
}
/*
	Funcion auxiliar de se_estabilizo_rec
*/
bool se_estabilizo(int matriz[MAX_FIL][MAX_COL],int matriz_auxiliar[MAX_FIL][MAX_COL]){
	return(se_estabilizo_rec(matriz,matriz_auxiliar,0,0));
}
/*
	Procedimiento que suma a una posicion de una matriz de enteros, el valor de su anterior en columnas
*/
void sumar_izquierda(int matriz,int fila_actual,int col_actual){
	matriz[fila_actual][col_actual]+=matriz[fila_actual][col_actual-1];
}
/*
	Procedimiento que suma a una posicion de una matriz de enteros, el valor de su posterior en columnas
*/
void sumar_derecha(int matriz,int fila_actual,int col_actual){
	matriz[fila_actual][col_actual]+=matriz[fila_actual][col_actual+1];
}
/*
	Funcion booleana que devuelve true si un entero es menor a 100 o false en caso contrario
*/
bool se_puede_sumar(int valor){
	return(valor<MAX_VALOR);
}
/*
	Procedimiento que "gurda una copia" de la matriz actual en un auxiliar
*/
void guardar_matriz_en_aux(int matriz[MAX_FIL][MAX_COL],int auxiliar[MAX_FIL][MAX_COL]){
	for(int i=0;i<MAX_FIL;i++){
		for(int j=0;j<MAX_COL;j++){
			auxiliar[i][j]=matriz[i][j];
		}
	}
}
/*
	Procedimiento recursivo que va recorriendo una matriz de enteros y sumando en cada posicion el anterior y el siguiente,
	 si es posible, sino solo el que sea posible
*/
void dar_vuelta_rec(int matriz[MAX_FIL][MAX_COL],int fila_actual,int col_actual){
	if((fila_actual>=MAX_FIL)||(col_actual>=MAX_COL)){
		return;
	}
	if((col_actual==PRIMERA_COL)||(col_actual==MAX_COL-1)){
		if(col_actual==PRIMERA_COL){
			if(se_puede_sumar(matriz[fila_actual][col_actual])){
				sumar_derecha(matriz[fila_actual][col_actual],fila_actual,col_actual);
			}
			return (dar_vuelta_rec(matriz,fila_actual,col_actual+1));
		}
		else{
			if(fila_actual!=MAX_FIL-1){
				if(se_puede_sumar(matriz[fila_actual][col_actual])){
					sumar_izquierda(matriz,fila_actual,col_actual);	
				}
				return(dar_vuelta_rec(matriz,fila_actual+1,0));
			}
			else{
				return;
			}
		}
	}
	else{
		if(se_puede_sumar(matriz[fila_actual][col_actual])){
			sumar_izquierda(matriz,fila_actual,col_actual);
			sumar_derecha(matriz,fila_actual,col_actual);
		}
		return(dar_vuelta_rec(matriz,fila_actual,col_actual+1));
	}
}
/*
	Funcion auxiliar de la funcion recursiva que recorre la matriz y hace las sumas
*/
void dar_vuelta(int matriz[MAX_FIL][MAX_COL]){
	dar_vuelta_rec(matriz,0,0);
}
/*
	PRECONDICION: Recibe una matriz de numeros positivoos menores a 10
	POSTCONDICION:Devuelve la cantidad de vueltas que tuvo que dar la matriz hasta estabilizarse
*/
int cuantas_vueltas_dio(int matriz[MAX_FIL][MAX_COL]){
	int matriz_auxiliar[MAX_FIL][MAX_COL];
	int vueltas=0;
	bool termino=false;
	while(!termino){
		dar_vuelta(matriz);
		vueltas++;
		guardar_matriz_en_aux(matriz,matriz_auxiliar);	
		if(se_estabilizo(matriz,matriz_auxiliar)){
			termino=true;
		}
	}
	return vueltas;
}
int main(){
	int matriz[MAX_FIL][MAX_COL];
	cuantas_vueltas_dio(matriz);

	return 0;
}