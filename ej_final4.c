/*Dexter ama las tuercas, nombra a cada una por su diametro y las guarda en una caja muy especial.
En cada celda de a caja pone varias tuercas de modo de cuando las guarda, la suma de los diametros de todas las tuercas de esa
celda debe ser mayor al dimetro de las celdas en cruz pero menor que las que estan en diagonal
SE PIDE
Dada la caja de tuercas de dexter y una nueva tuerca a guardar, crear una funcion que devuelva la coordenada donde se puede 
insertar la tuerca.
EL EJ ESTA MAL , LOS VECTORES DE TUERCAS NO TIENEN TOPE, SE USA EL MAX TUERCAS*/
#include <stdio.h>
#include <stdbool.h>
#define MAX_CELDAS 30
#define MAX_TUERCAS 20
#define NO_ENCONTRADO -1
typedef struct coordenada{
	int fila;
	int col;
}coordenada_t;
/*	
	Funcion que devuelve la suma total de los diametros de cada tuerca  de un vector de tuercas
*/
int diametro_total_celda(int tuercas[MAX_TUERCAS]){
	int diametro_total=0;
	for(int i=0;i<MAX_TUERCAS;i++){
		diametro_total+=tuercas[i];
	}
	return diametro_total;
}
/*
	Funcion booleana auxiliar de la funcion cumple_en_cruz, que dependiendo de en que posicio  quiera revisar solo llame
	a la auxiliar posible, en caso de estar en un borde,la funcion cumple_en_cruz revisa a cual puede llamar y la llama.
*/
bool diagonal_abajo_derecha(int caja[MAX_CELDAS][MAX_CELDAS][MAX_TUERCAS],int fila_actual,int col_actual){
	return((diametro_total_celda(caja,fila_actual,col_actual))<(diametro_total_celda(caja,fila_actual+1,col_actual+1)));
}
/*
	Funcion booleana auxiliar de la funcion cumple_en_cruz, que dependiendo de en que posicio  quiera revisar solo llame
	a la auxiliar posible, en caso de estar en un borde,la funcion cumple_en_cruz revisa a cual puede llamar y la llama.
*/
bool diagonal_abajo_izquierda(int caja[MAX_CELDAS][MAX_CELDAS][MAX_TUERCAS],int fila_actual,int col_actual){
	return((diametro_total_celda(caja,fila_actual,col_actual))<(diametro_total_celda(caja,fila_actual+1,col_actual-1)));
}
/*
	Funcion booleana auxiliar de la funcion cumple_en_cruz, que dependiendo de en que posicio  quiera revisar solo llame
	a la auxiliar posible, en caso de estar en un borde,la funcion cumple_en_cruz revisa a cual puede llamar y la llama.
*/
bool diagonal_arriba_derecha(int caja[MAX_CELDAS][MAX_CELDAS][MAX_TUERCAS],int fila_actual,int col_actual){
	return((diametro_total_celda(caja,fila_actual,col_actual))<(diametro_total_celda(caja,fila_actual-1,col_actual+1)));
}
/*
	Funcion booleana auxiliar de la funcion cumple_en_cruz, que dependiendo de en que posicio  quiera revisar solo llame
	a la auxiliar posible, en caso de estar en un borde,la funcion cumple_en_cruz revisa a cual puede llamar y la llama.
*/
bool diagonal_arriba_izquierda(int caja[MAX_CELDAS][MAX_CELDAS][MAX_TUERCAS],int fila_actual,int col_actual){
	return((diametro_total_celda(caja,fila_actual,col_actual))<(diametro_total_celda(caja,fila_actual-1,col_actual-1)));
}
/*
	Funcion booleana auxiliar de la funcion cumple_en_cruz, que dependiendo de en que posicio  quiera revisar solo llame
	a la auxiliar posible, en caso de estar en un borde,la funcion cumple_en_cruz revisa a cual puede llamar y la llama.
*/
bool en_cruz_abajo(int caja[MAX_CELDAS][MAX_CELDAS][MAX_TUERCAS],int fila_actual,int col_actual){
	return((diametro_total_celda(caja,fila_actual,col_actual))>(diametro_total_celda(caja,fila_actual+1,col_actual)));
}
/*
	Funcion booleana auxiliar de la funcion cumple_en_cruz, que dependiendo de en que posicio  quiera revisar solo llame
	a la auxiliar posible, en caso de estar en un borde,la funcion cumple_en_cruz revisa a cual puede llamar y la llama.
*/
bool en_cruz_derecha(int caja[MAX_CELDAS][MAX_CELDAS][MAX_TUERCAS],int fila_actual,int col_actual){
	return((diametro_total_celda(caja,fila_actual,col_actual))>(diametro_total_celda(caja,fila_actual,col_actual+1)));
}
/*
	Funcion booleana auxiliar de la funcion cumple_en_cruz, que dependiendo de en que posicio  quiera revisar solo llame
	a la auxiliar posible, en caso de estar en un borde,la funcion cumple_en_cruz revisa a cual puede llamar y la llama.
*/
bool en_cruz_izquierda(int caja[MAX_CELDAS][MAX_CELDAS][MAX_TUERCAS],int fila_actual,int col_actual){
	return((diametro_total_celda(caja,fila_actual,col_actual))>(diametro_total_celda(caja,fila_actual,col_actual-1)));
}
/*
	Funcion booleana auxiliar de la funcion cumple_en_cruz, que dependiendo de en que posicio  quiera revisar solo llame
	a la auxiliar posible, en caso de estar en un borde,la funcion cumple_en_cruz revisa a cual puede llamar y la llama.
*/
bool en_cruz_arriba(int caja[MAX_CELDAS][MAX_CELDAS][MAX_TUERCAS],int fila_actual,int col_actual){
	return((diametro_total_celda(caja,fila_actual,col_actual))>(diametro_total_celda(caja,fila_actual-1,col_actual)));
}
/*
	Funcion booleana que devuelve true si el diametro total de la celda buscada es mayor que todas las celdas arriba,abajo,
	por izquierda y por derecha ,a una celda de distancia, o false en caso contrario.
*/
bool cumple_en_cruz(int caja[MAX_CELDAS][MAX_CELDAS][MAX_TUERCAS],int fila_actual,int col_actual){
	if(fila_actual==MAX_CELDAS-1){
		if(col_actual=MAX_CELDAS-1){
			return((en_cruz_arriba(caja,fila_actual,col_actual))&&(en_cruz_izquierda(caja,fila_actual,col_actual)));
		}
		else if(col_actual==0){
			return((en_cruz_arriba(caja,fila_actual,col_actual))&&(en_cruz_derecha(caja,fila_actual,col_actual)));
		}
		else{
			return ((en_cruz_arriba(caja,fila_actual,col_actual))&&(en_cruz_derecha(caja,fila_actual,col_actual))&&
				(en_cruz_izquierda(caja,fila_actual,col_actual)));
		}
	}
	else if(fila_actual==0){
		if(col_actual==MAX_CELDAS-1){
			return ((en_cruz_abajo(caja,fila_actual,col_actual))&&(en_cruz_izquierda(caja,fila_actual,col_actual)));
		}
		else if(col_actual==0){
			return((en_cruz_derecha(caja,fila_actual,col_actual))&&(en_cruz_abajo(caja,fila_actual,col_actual)));
		}
		else{
			return((en_cruz_izquierda(caja,fila_actual,col_actual))&&(en_cruz_derecha(caja,fila_actual,col_actual))&&
				en_cruz_abajo(caja,fila_actual,col_actual));
		}
	}
	else{
		if(col_actual==MAX_CELDAS-1){
			return((en_cruz_arriba(caja,fila_actual,col_actual))&&(en_cruz_abajo(caja,fila_actual,col_actual))&&
				en_cruz_izquierda(caja,fila_actual,col_actual));
		}
		else if(col_actual==0){
			return((en_cruz_arriba(caja,fila_actual,col_actual))&&(en_cruz_abajo(caja,fila_actual,col_actual))&&
				en_cruz_derecha(caja,fila_actual,col_actual));
		}
		else{
			return((en_cruz_arriba(caja,fila_actual,col_actual))&&(en_cruz_abajo(caja,fila_actual,col_actual))&&
				en_cruz_izquierda(caja,fila_actual,col_actual)&&(en_cruz_derecha(caja,fila_actual,col_actual)));
		}
	}
}
/*
	Funcion booleana que devuelve true si  el diametro total de la celda buscada es menor que todas las celdas diagonales a
	una celda de distancia o false en caso contrario.
*/
bool cumple_diagonales(int caja[MAX_CELDAS][MAX_CELDAS][MAX_TUERCAS],int fila_actual,int col_actual){
	if(fila_actual==MAX_CELDAS-1){
		if(col_actual==MAX_CELDAS-1){
			return(diagonal_arriba_izquierda(caja,fila_actual,col_actual));
		}
		else if(col_actual==0){
			return(diagonal_arriba_derecha(caja,fila_actual,col_actual));
		}
		else{
			return(diagonal_arriba_derecha(caja,fila_actual,col_actual)&& diagonal_arriba_izquierda(caja,fila_actual,col_actual));
		}
	}
	else if(fila_actual==0){
		if(col_actual==0){
			return(diagonal_abajo_derecha(caja,fila_actual,col_actual));
		}
		else if(col_actual==MAX_CELDAS-1){
			return(diagonal_abajo_izquierda(caja,fila_actual,col_actual));
		}
		else{
			return(diagonal_abajo_derecha(caja,fila_actual,col_actual)&&(diagonal_abajo_izquierda(caja,fila_actual,col_actual)));		
		}
	}
	else{
		if(col_actual==0){
			return(diagonal_abajo_derecha(caja,fila_actual,col_actual)&&(diagonal_arriba_derecha(caja,fila_actual,col_actual)));
		}
		else if(col_actual==MAX_CELDAS-1){
			return (diagonal_abajo_izquierda(caja,fila_actual,col_actual)&&(diagonal_arriba_izquierda(caja,fila_actual,col_actual)));
		}
		else{
			return(diagonal_arriba_izquierda(caja,fila_actual,col_actual)&&(diagonal_abajo_izquierda(caja,fila_actual,col_actual))&&
				diagonal_abajo_derecha(caja,fila_actual,col_actual)&&diagonal_arriba_derecha(caja,fila_actual,col_actual));
		}
	}
}
/*
	Funcion booleana que chequea que una celda de la matriz cumpla con las condiciones especificadas
*/
bool cumple_condiciones(int caja[MAX_CELDAS][MAX_CELDAS][MAX_TUERCAS],int fila_actual,int col_actual){
	return(cumple_diagonales(caja,fila_actual,col_actual)&& cumple_en_cruz(caja,fila_actual,col_actual));
}
/*	
	Funcion de tipo coordenada_t que devuelve la posicion de una celda donde puede ser introducida la nueva tuerca.O -1 en
	en ambos campos de la coordenada si no encontro una celda adecuada.
*/
coordenada_t buscar_celda_adecuada(int caja[MAX_CELDAS][MAX_CELDAS][MAX_TUERCAS]){
	coordenada_t aux;
	aux.fila=NO_ENCONTRADO;
	aux.col=NO_ENCONTRADO;
	for(int i=0;i<MAX_CELDAS;i++){
		for(int j=0;j<MAX_CELDAS;j++){
			if(cumple_condiciones(caja,i,j)){
				aux.fila=i;
				aux.col=j;
			}
		}
	}
	return aux;
}