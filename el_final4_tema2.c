#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX_CHICOS 20
#define MAX_NOMBRE 30
#define MAX_MISIONES 200
#define ERROR -1
#define FORMATO_LECTURA "%[^;];%[^;];%i\n"
#define CANT_LEIDOS 3
typedef struct chico{
	char nombre[MAX_NOMBRE];
	mision_t misiones[MAX_MISIONES];
	int tope_misiones;
}chico_t;

typedef	struct mision{
	char nombre_mision[MAX_NOMBRE];
	int dificultad;
}mision_t;

typedef struct auxiliar{
	char nombre_chico[MAX_NOMBRE];
	char nombre_mision[MAX_NOMBRE];
	int dificultad;
}auxiliar_t;
/*
	Procedimiento que ordena un vector de chicos_t en descendentemente , por cantidad de misiones 
*/
void ordenar_por_experiencia(chicos_t chicos[MAX_CHICOS],int tope_chicos){
	chico_t auxiliar;
	for(int i=1;i<tope_chicos;i++){
		if(int j=0;j<tope_chicos-1;j++){
			if(chicos[j].tope_misiones>chicos[j+1].tope_misiones){
				auxiliar=chicos[j];
				chicos[j]=chicos[j+1];
				chicos[j+1]=auxiliar;
			}
		}
	}
}
/*
	Funcion que devuelve la posicion de un chico_t en el vector 
*/
int posicion_chico(char nombre_chico[MAX_NOMBRE],chico_t chicos[MAX_CHICOS],int tope_chicos){
	int pos_actual=0;
	bool encontro=false;
	while(!encontro){
		if(strcmp(nombre_chico,chicos[pos_actual].nombre_chico)==0){
			encontro=true;
		}
		else{
			pos_actual++;
		}
	}
	return pos_actual;
}
/*
	Funcion booleana que revisa si un nombre ya se encuentra en un vector de chicos
*/
bool esta_en_el_vector(char nombre_chico[MAX_NOMBRE],chico_t chicos[MAX_CHICOS],int tope_chicos){
	int pos_actual=0;
	bool esta=false;
	while(!esta){
		if(strcmp(nombre_chico,chicos[pos_actual].nombre_chico)==0){
			esta=true;
		}
		pos_actual++;
	}
	return esta;
}
/*
	Procedimiento que pasa correctamente la informacion de un chico y mision de un auxiliar_t a un vector
*/
void guardar_info_en_vector(auxiliar_t aux,chico_t chicos[MAX_CHICOS],int* tope_chicos){
	int posicion;
	if(!esta_en_el_vector(aux.nombre_chico,chicos,(*tope_chicos))){
		strcpy(aux.nombre,chicos[(*tope_chicos)].nombre_chico);
		strcpy(aux.nombre_mision,chicos[*tope_chicos].nombre_mision);
		chicos[*tope_chicos].dificultad=aux.dificultad;
		(*tope_chicos)++;
	}
	else{
		posicion=posicion_chico(aux.nombre_chico,chicos,(*tope_chicos));
		strcpy(chicos[posicion].misiones[chicos[posicion].tope_misiones],aux.nombre_mision);
		(chicos[posicion].tope_misiones)++;
	}
}
/*
	Funcion que lee un archivo.csv de chicos y los pasa a un vector
*/
int guardar_chicos(chico_t chicos[MAX_CHICOS],int* tope_chicos,char nombre_archivo_chicos[MAX_NOMBRE]){
	FILE* lista_chicos=fopen(nombre_archivo_chicos,"r");
	auxiliar_t aux;
	if(!lista_chicos){
		perror("No se pudo abrir el csv de chicos");
		return ERROR;
	}
	int chico_actual=0;
	int leidos=fscanf(FORMATO_LECTURA,lista_chicos,chicos[chico_actual].nombre,);
	while(leidos==CANT_LEIDOS){
		int leidos=fscanf(FORMATO_LECTURA,lista_chicos,auxiliar.nombre_chico,auxiliar.nombre_mision,auxiliar.dificultad);
		guardar_info_en_vector(auxiliar,chicos,tope_chicos);
	}
}
/*
	Procedimiento que lee un archivo csv con nombres de chicos, misiones y dificultad, y guarda los nombres y cantidad de 
	misiones que hizo cada  uno para luego guardarlo de forma descendente por cantidad de misiones en el vector de
	postulantes.

*/
void devolver_postulantes_con_mayor_experiencia(chico_t chicos[MAX_CHICOS],int* tope_chicos
	int* tope_postulantes,char nombre_archivo_chicos[MAX_NOMBRE]){
	guardar_chicos(chicos,tope_chicos,nombre_archivo_chicos);
	ordenar_por_experiencia(chicos,(*tope_chicos));
}
int main(){
	chico_t chicos[MAX_CHICOS];
	int tope_chicos=0;
	chico_t postulantes[MAX_CHICOS];
	int tope_postulantes=0;
	devolver_postulantes_con_mayor_experiencia(chicos,&tope_chicos,postulantes,&tope_postulantes);
	for(int i=0;i<tope_postulantes;i++){
		printf("%s\n",postulantes[i].nombre );
	}
	return 0;
}