#include <stdio.h>
#define MAX_BANANAS 100
#define NO_ENCONTRADO -1
#define MADUREZ_IDEAL 7
#define CANTIDAD_DESEADA 3
//RACIMO 3|2|7|7|5|6|7|8|8
/* Se pide hacer una funcion recursiva que devuelva la posicion de la tercer banana con estado de madurez <7*/
/*	Funcion que busca la tercera banana apta segun madurez, en un vector de bananas y devuelve su poscion, o -1 en caso de 
 	no llegar a 3 aptas.
	PRE:
	El contador de bananas aptas , y la variable pos_actual que se usa para recorrer el vector,deben estar inicializados en cero.
	Madurez viene con el valor por parametro.
	POST:
	*/
int obtener_pos_rec(int contador_aptas,int pos_actual,int bananas[MAX_BANANAS],int tope,int madurez){
	if(i>=tope){
		return NO_ENCONTRADO;
	}
	if(bananas[pos_actual]<=madurez){
		if(contador_aptas==CANTIDAD_DESEADA){
			return pos_actual;
		}
		else{
			obtener_pos_rec(contador_aptas+1,pos_actual+1,bananas,tope,madurez);

		}
	}
	else{
		obtener_pos_rec(contador_aptas,pos_actual+1,bananas,tope,madurez);
	}

}
int obtener_pos_banana(int bananas[MAX_BANANAS],int tope,int madurez){
	madurez=MADUREZ_IDEAL;
	obtener_pos_rec(0,0,bananas,tope,madurez);
}