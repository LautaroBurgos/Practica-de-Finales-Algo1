/*
	Dexter esta aislado por segunda vez durante toda la pandemia, la primera fue por ir  una pool party, y esta ultima
	por compartir unos mates,todo mal. Fruto de su aburrimiento, en ambos aislamientos le paso lo mismo, gran parte de sus
	ahorros en comprar cosas por LercadoMibre.
	Tiene 2 archivos csv, uno por cada aislamiento,con la informacion de las cosas que compro en cada uno de ellos.
	Cada linea del archivo tiene la siguiente informacion:

	descripcion;precio;categoria

	SE PIDE

	1. Dado los archivos de Dexter, crear un algoritmo que genere un 3er archivo con todas las cosas que compro durante sus
	aislamientos.
	Aclaraciones:
	-Los 2 archivos de entrada estan ordenados por precio, el arhivo generado debe mantener ese  orden
	-El hecho de estar ordenados, permite trabajarlos de una manera particular, NO se deben pasar a un vector y NO se debe
	reordenar el resultado.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_DESCRIPCION 30
#define MAX_CATEGORIA 20
#define MAX_NOMBRE 30
#define MAX_STRING 40
#define FORMATO_LECTURA_COMPRA  "%[^;];%i;%[^\n]\n"
#define FORMATO_ESCRITURA_COMPRAS "%s;%i;%s\n"
#define CANT_LEIDOS 3
#define ERROR -1

typedef struct compra{
	char descripcion[MAX_DESCRIPCION];
	int precio;
	char categoria[MAX_CATEGORIA];
}compra_t;
/*
	PRECONDICION: Recibe un puntero FILE en formato escritura y un compra_t
	POSTCONDICION: El archivo es devuelto con la compra escrita, en el formato correspondiente
	Procedimiento que escribe una compra pasada por parametro en el archivo pasado por parametro en el formato pre establecido
*/
void guardar_compra(FILE* mezcla_de_archivos,compra_t compra){
	fprintf(mezcla_de_archivos,FORMATO_ESCRITURA_COMPRAS,compra.descripcion,compra.precio,compra.categoria );
}
int escanear_compra(FILE* archivo,compra_t* compra){
	return fscanf(archivo,FORMATO_LECTURA_COMPRA,(*compra).descripcion,&(*compra).precio,(*compra).categoria);
}
/*
	Funcion booleana que compara dos strings y devuelve true si son iguales  o false en caso contrario 
*/
bool son_iguales(char string1[MAX_STRING],char string2[MAX_STRING]){
	return (strcmp(string1,string2)==0);
}
void realizar_interseccion(FILE* archivo1,FILE* archivo2,FILE* interseccion_de_archivos){
	compra_t auxiliar1,auxiliar2;
	int leidos1=escanear_compra(archivo1,&auxiliar1);
	int leidos2=escanear_compra(archivo2,&auxiliar2);
	while((leidos1==CANT_LEIDOS)&&(leidos2==CANT_LEIDOS)){
		if(auxiliar1.precio==auxiliar2.precio){
			guardar_compra(interseccion_de_archivos,auxiliar1);
			leidos1=escanear_compra(archivo1,&auxiliar1);
			leidos2=escanear_compra(archivo2,&auxiliar2);
		}
		else if(auxiliar1.precio<auxiliar2.precio){
			leidos1=escanear_compra(archivo1,&auxiliar1);
		}
		else{
			leidos2=escanear_compra(archivo2,&auxiliar2);
		}
	}
}
/*
	Procedimiento que hace la diferencia entre dos archivos csv de listas de compras, pone en un archivo los elementos
	que esten en el primero pero no en el segundo archivo.
*/
void realizar_diferencia(FILE* archivo1,FILE* archivo2,FILE* diferencia_de_archivos){
	compra_t auxiliar1,auxiliar2;
	int leidos1=escanear_compra(archivo1,&auxiliar1);
	int leidos2=escanear_compra(archivo2,&auxiliar2);
	while((leidos1==CANT_LEIDOS)&&(leidos2==CANT_LEIDOS)){
		if(auxiliar1.precio==auxiliar2.precio){
			leidos1=escanear_compra(archivo1,&auxiliar1);
			leidos2=escanear_compra(archivo2,&auxiliar2);
		}
		else if(auxiliar1.precio<auxiliar2.precio){
			guardar_compra(diferencia_de_archivos,auxiliar1);
			leidos1=escanear_compra(archivo1,&auxiliar1);
		}
		else{
			leidos2=escanear_compra(archivo2,&auxiliar2);
		}
	}
	while(leidos1==CANT_LEIDOS){
		guardar_compra(diferencia_de_archivos,auxiliar1);
		leidos1=escanear_compra(archivo1,&auxiliar1);
	}
}
/*
	Procedimiento que realiza la union entre dos archivos de compras en csv, en un tercer archivo. Como es la union, no
	hay elementos repetidos en el archivo resultante.

*/
void realizar_union(FILE* archivo1,FILE* archivo2,FILE* union_de_archivos){
	compra_t auxiliar1,auxiliar2;
	int leidos1=escanear_compra(archivo1,&auxiliar1);
	int leidos2=escanear_compra(archivo2,&auxiliar2);
	while((leidos1==CANT_LEIDOS)&&(leidos2==CANT_LEIDOS)){
		if(auxiliar1.precio==auxiliar2.precio){
			guardar_compra(union_de_archivos,auxiliar1);
			leidos1=escanear_compra(archivo1,&auxiliar1);
			leidos2=escanear_compra(archivo2,&auxiliar2);
		}
		else if(auxiliar1.precio<auxiliar2.precio){
			guardar_compra(union_de_archivos,auxiliar1);
			leidos1=escanear_compra(archivo1,&auxiliar1);
		}
		else{
			guardar_compra(union_de_archivos,auxiliar2);
			leidos2=escanear_compra(archivo2,&auxiliar2);
		}
	}
	while(leidos1==CANT_LEIDOS){
		guardar_compra(union_de_archivos,auxiliar1);
		leidos1=escanear_compra(archivo1,&auxiliar1);
	}
	while(leidos2==CANT_LEIDOS){
		guardar_compra(union_de_archivos,auxiliar2);
		leidos2=escanear_compra(archivo2,&auxiliar2);
				printf("%i\n",leidos2);
	}
}
/*
	Procedimiento que realiza la mezcla de las listas
*/
void realizar_mezcla(FILE* archivo1,FILE* archivo2,FILE* mezcla_de_archivos){
	compra_t auxiliar1,auxiliar2;
	int leidos1=escanear_compra(archivo1,&auxiliar1);
	int leidos2=escanear_compra(archivo2,&auxiliar2);

	while((leidos1==CANT_LEIDOS)&&(leidos2==CANT_LEIDOS)){
		if(auxiliar1.precio<=auxiliar2.precio){
			guardar_compra(mezcla_de_archivos,auxiliar1);
			leidos1=escanear_compra(archivo1,&auxiliar1);
		}
		else{
			guardar_compra(mezcla_de_archivos,auxiliar2);
			leidos2=escanear_compra(archivo2,&auxiliar2);
		}
	}
	while(leidos1==CANT_LEIDOS){
		guardar_compra(mezcla_de_archivos,auxiliar1);
		leidos1=escanear_compra(archivo1,&auxiliar1);
	}
	while(leidos2==CANT_LEIDOS){
		guardar_compra(mezcla_de_archivos,auxiliar2);
		leidos2=escanear_compra(archivo2,&auxiliar2);	
	}
}
/*
	PRECONDICION:Recibe los nombres de ambos archivos a mezclar
	POSTCONDICION:Se crea un tercer archivo con las compras de ambos archivos manteniendo el orden por precio,devuelve 0
	si todo funciono perfectamente o -1 si hubo problema con cualquiera de los archivos
	Procedimiento que une dos listas csv de compras que estan ordenadas por precio, a una tercera con los elementos de ambos
	manteniendo el orden, 
*/
int  mezclar_lista_compras(char nombre_archivo1[MAX_NOMBRE],char nombre_archivo2[MAX_NOMBRE]){
	FILE* archivo1 = fopen(nombre_archivo1,"r");
	if(!archivo1){
		perror("No se pudo abrir un archivo de compras");
		return ERROR;
	}
	FILE* archivo2 = fopen(nombre_archivo2,"r");
	if(!archivo2){
		perror("No se pudo abrir un archivo de compras");
		fclose(archivo1);
		return ERROR;
	}
	FILE* mezcla_de_archivos=fopen("mezcla.csv","w");
	if(!mezcla_de_archivos){
		perror("No se pudo crear  el archivo mezcla");
		fclose(archivo1);
		fclose(archivo2);
		return ERROR;
	}
	realizar_union(archivo1,archivo2,mezcla_de_archivos);
	fclose(archivo1);
	fclose(archivo2);
	fclose (mezcla_de_archivos);
	return 0;
}
int main(){
	mezclar_lista_compras("compra1.csv","compra2.csv");
	return 0;
}