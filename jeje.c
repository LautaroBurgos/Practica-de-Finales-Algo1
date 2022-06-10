/*
	Faramir dejo un testamento, porque sabia, que con la personalidad que tiene, algun dia no volveria a casa.
	Tuvo la precaucion de encrpitarlo,para que solo los herederos puedan descifrarlo ya que incluye indicaciones para llegar
	una fortuna oculta.
	Siendo un merecido heredero de la herencia de Faramir se cuenta con el atchivo de texto testamento.txt y se quiere
	desencriptar para acceder a la fortuna. Se sabe que - LAS a fueron cambiadas por s- LAS s fueron cambiada por n- LAs
	n fueron cambiadas por r- Las r fueron cambiadas por a.
	A su vez,por cada e que aparecia en el testamento, se agrego una risa socarrona jeje.
	Se pide:
	1.Crear un programa que desencrpite el testamento de Faramir.
	*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define LETRA_A_MAYUSCULA 'A'
#define LETRA_A_MINUSCULA 'a'
#define LETRA_S_MAYUSCULA 'S'
#define LETRA_S_MINUSCULA 's'
#define LETRA_N_MAYUSCULA 'N'
#define LETRA_N_MINUSCULA 'n'
#define LETRA_R_MAYUSCULA 'R'
#define LETRA_R_MINUSCULA 'r'
#define LETRA_E_MAYUSCULA 'E'
#define LETRA_E_MINUSCULA 'e'
#define RISA_SOCARRONA "jeje"
#define NOMBRE_AUXILIAR "aux.txt"
#define FORMATO_ESCRITURA "%c"
#define FORMATO_LECTURA "%c"
#define LARGO_JEJE 4
#define MAX_NOMBRE 20
#define CANT_LEIDOS 1
#define FIN -1
bool termino(int leidos){
	return (leidos==FIN);
}
/*
	Funcion booleana que recibe un caracter por parametro y devuelve true  en caso de ser una letra e ya sea mayuscula o minuscula;
*/
bool es_letra_e(char caracter){
	return(caracter==LETRA_E_MAYUSCULA || caracter==LETRA_E_MINUSCULA);
}
/*
	Funcion  que recibe un caracter distinto de 'e' y devuelve el correcto en caso de ser alguno de los cambiados
*/
char devuelve_caracter_correcto(char caracter_a_comparar){
	char auxiliar=caracter_a_comparar;
	switch(caracter_a_comparar){
		case LETRA_A_MINUSCULA:
			auxiliar=LETRA_R_MINUSCULA;
			break;
		case LETRA_A_MAYUSCULA:
			auxiliar=LETRA_R_MAYUSCULA;
			break;
		case LETRA_S_MAYUSCULA:
		 	auxiliar=LETRA_A_MAYUSCULA;
		 	break;
		case LETRA_S_MINUSCULA:
			auxiliar=LETRA_A_MINUSCULA;
			break;
		case LETRA_N_MINUSCULA:
			auxiliar=LETRA_S_MINUSCULA;
			break;
		case LETRA_N_MAYUSCULA:
			auxiliar=LETRA_S_MAYUSCULA;
			break;
		case LETRA_R_MAYUSCULA:
			auxiliar=LETRA_N_MAYUSCULA;
			break;
		case LETRA_R_MINUSCULA:
			auxiliar=LETRA_N_MINUSCULA;
			break;
	}
	return auxiliar;
}
/*
	Procedimiento que revisa caracter por caracter el archivo .txt y lo reemplaza en caso de ser necesario
*/
void reescribir_texto(FILE* testamento,FILE* auxiliar){
	char caracter_auxiliar;
	int contador=0;
	bool hay_risa_socarrona=false;
	int leidos=fscanf(testamento,FORMATO_LECTURA,&caracter_auxiliar);
	fprintf(auxiliar,FORMATO_ESCRITURA,devuelve_caracter_correcto(caracter_auxiliar));
	if(es_letra_e(caracter_auxiliar)){
		hay_risa_socarrona=true;
	}
	while(leidos==CANT_LEIDOS){
		 leidos=fscanf(testamento,FORMATO_LECTURA,&caracter_auxiliar);
		 if(!termino(leidos)){
		 	if(!hay_risa_socarrona){
				if(!es_letra_e(caracter_auxiliar)){
					fprintf(auxiliar,FORMATO_ESCRITURA,devuelve_caracter_correcto(caracter_auxiliar));
				}
				else{
					fprintf(auxiliar,FORMATO_ESCRITURA,caracter_auxiliar );
					hay_risa_socarrona=true;
				}
			}
			else{
				contador++;
				if(contador==LARGO_JEJE){
					hay_risa_socarrona=false;
					contador=0;
				}
			}
		}
	}
}
/*
	Procedimiento que desencrpita un archivo txt, recibe el nombre del archivo a leer por parametro
*/
void desencriptar_testamento_faramir(char nombre_archivo[MAX_NOMBRE]){
	FILE* testamento=fopen(nombre_archivo,"r");
	if(!testamento){
		perror("No se pudo abrir");
		return;
	}
	FILE* auxiliar=fopen(NOMBRE_AUXILIAR,"w");
	if(!auxiliar){
		perror("No se pudo crear el auxiliar");
		return;
	}
	reescribir_texto(testamento,auxiliar);
	fclose(testamento);
	fclose(auxiliar);
	rename(NOMBRE_AUXILIAR,nombre_archivo);
}
int main(){
	desencriptar_testamento_faramir("testamento.txt");
	return 0;
}