/*
	Scooby doo y sus amigos,se dedican a capturar monstruos y villanos de todo tipo, y siempre llevaron 
	registro de sus victorias y , para las ultimas , le delegaron la responsabilidad a shaggy de actualizar
	este registro.
	Se dieron cuenta que en vez de hacer llo que le pidieron,varias veces armao un buen sandwaich y ahora
	quedaron algunas victorias sin pasar
	SE PIDE
	1.Dado el vector de victorias original y un vector que representa las victorias que shaggy "olvido" de pasar
	las agregue al vector original manteniendo el orden. Ambos vectores estan ordenados alfabeticamente
	segun el nombre del monstruo o villano.
*/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define MAX_NOMBRE 20
#define MAX_VICTORIAS 100
typedef struct{
	char nombre_enemigo[MAX_NOMBRE];
	bool es_monstruo;
	int dificultad;
}victoria_t;
/*
	Procedimiento que inserta una victoria_t en un vector de victoria_t de forma ordenada por el campo nombre_enemigo
*/
void insertar_victoria(victoria_t victorias[MAX_VICTORIAS],int* tope_victorias,victoria_t olvidada){
	bool inserto=false;
	int pos_actual;
	victoria_t auxiliar;
	for(pos_actual=0;pos_actual<(*tope_victorias);pos_actual++){
		if(strcmp(olvidada.nombre_enemigo,victorias[pos_actual].nombre_enemigo)<0){
			auxiliar=victorias[pos_actual];
			olvidada=auxiliar;
			inserto=true;
		}
	}
	if(inserto){
		victorias[(*tope_victorias)]=auxiliar;
		(*tope_victorias)++;
	}
}
/*
	Procedimiento que agrega al vector de victorias,las victorias olvidadas por scooby, de manera ordenada.
	PRE:ambos vectores de victorias vienen ordenados alfabeticamente por nombre de villano
*/
void agregar_victorias_olvidadas(victoria_t victorias[MAX_VICTORIAS],int* tope_victorias,victoria_t olvidadas[MAX_VICTORIAS],
	int tope_olvidadas){
	for(int victoria_actual=0;victoria_actual<tope_olvidadas;victoria_actual++){
		insertar_victoria(victorias,tope_victorias,olvidadas[victoria_actual]);
	}
}