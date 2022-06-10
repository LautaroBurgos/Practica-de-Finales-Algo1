#include <stdio.h>
#include<stdlib.h>
#define MAX_CARACTERES 100
#define MAX_ZONAS 20
#define MAX_FECHAS 20
#define LECTURA_ZONA_FECHA "%[^\n]\n\t%[^/]/%[^/]/[^\n]\n"
#define LECTURA_HUESOS "\t\t%[^\n]"
typedef struct hueso{
	char tipo[MAX_CARACTERES];
}hueso_t;

typedef struct fecha{
	int dia;
	int mes;
	int año;
	hueso_t huesos[MAX_CARACTERES];
}fecha_t;

typedef struct zona{
	char nombre_zona[MAX_CARACTERES]; 
	fecha_t fechas[MAX_FECHAS];
}zona_t;

typedef struct dato{
	zona_t zonas[MAX_ZONAS];
}dato_t;

int main(){
	FILE* huesos= fopen("huesitos.csv","r");
	if(!huesos){
		perror("No se pudo abrir el archivo");
		return -1;
	}
	FILE* aux=fopen("aux.csv","w");
	if(!aux){
		perror("No se pudo abrir el archivo1");
		return -1;
	}
	dato_t datos;
	int tope_zonas=0;
	int tope_fechas=0;
	int tope_huesitos=0;
	while(!feof(huesitos)){
		int cant_datos = fscanf(huesitos,LECTURA_ZONA_FECHA,datos.zona[tope_zonas].nombre_zona,datos.zona[tope_zonas].fecha[tope_fechas].dia,
		datos.zona[tope_zonas].fecha[tope_fechas].mes,datos.zona[tope_zonas].fecha[tope_fechas].año);
		if(cant_datos!=4){
			tope_zonas++;
			tope_fechas++;
			
			while
		}
		int leidos= fscanf(huesitos,,);	
	}
	fclose(huesos);
	fclose(aux);
	rename("aux.csv","huesitos.csv");
	return 0;
}