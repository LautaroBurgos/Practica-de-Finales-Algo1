/*
	Bombon,burbuja y bellota estaban jugando al TEG(juego que se basa en conquistar paises),cuando a Bellota le dieron ganas
	de ir al baño.Al volver , se dio cuenta que no todo estaba como lo habia dejado, habia fichas cambiadas.Pero por suerte,fue
	mas viva que las hermanas y saco una foto al tablero antes de irse.
	Se cuentan con dos matrices de pais_T ,una con el tablero antes y otro con el actual.
	SE PIDE
	1.Crear una funcion que deje a la matriz actual como antes y que devuelva la cantidad total de fichas que se tuvieron
	que sacar/poner en el cambio.
*/
#include <stdio.h>
#include <stdbool.h>
#define MAX_FILAS 30
#define MAX_COL 30
#define CERO 0
typedef struct pais{
	int cantidad_fichas;
	char color_fichas;
}pais_t;
/*
	Codigo que calcula cuantda diferencia hay entre 2 enteros, en caso de ser negativa calcula su modulo.
*/
int diferencia_de_fichas(int a,int b){
	int aux;
	aux=a-b;
	if(aux<CERO){
		aux= aux*(-1);
	}
	return aux;
}
/*
	Funcion booleana que devuelve true si hay diferencia de fichas entre 2 pais_t
*/
bool ficha_fue_cambiada(pais_t a,pais_t b){
	return ((a.cantidad_fichas)!=(b.cantidad_fichas));
}
/*
	Funcion auxiliar recursiva que devuelve la cantidad de fichas fueron cambiadas del tablero.
*/
int cant_fichas_rec(pais_t tablero[MAX_FILAS][MAX_COL],pais_t anterior[MAX_FILAS][MAX_COL],int fila_actual,int col_actual,
	int fichas_cambiadas){
	if(fila_actual==MAX_FILAS && col_actual && MAX_COL){
		return fichas_cambiadas;
	}
	if(ficha_fue_cambiada(tablero[fila_actual][col_actual],anterior[fila_actual][col_actual])){
		fichas_cambiadas+=diferencia_de_fichas((tablero[fila_actual][col_actual]).cantidad_fichas,
			(anterior[fila_actual][col_actual]).cantidad_fichas);
	}
	if(col_actual==MAX_COL-1){
		return cant_fichas_rec(tablero,anterior,fila_actual+1,0,fichas_cambiadas);
	}
	else{
		return cant_fichas_rec(tablero,anterior,fila_actual,col_actual+1,fichas_cambiadas);
	}
}
/*
Funcion que devuelve la cantidad total de fichas que fueron cambiadas de un tablero
*/
int cant_fichas(int tablero[MAX_FILAS][MAX_COL],int anterior[MAX_FILAS][MAX_COL]){
	return cant_fichas_rec(tablero,anterior,0,0,0);
}