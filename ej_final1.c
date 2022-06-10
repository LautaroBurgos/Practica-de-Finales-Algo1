/*Dexter esta implementando una nueva forma de ingresar a sus sistemas,ya que cuando uso contraseñas, su hermana DeeDee las
adivino todas e hizo desastres dentro del laboratorio.
 El nuevo proceso consiste por un lado de un texto con muchas palabras y por otro lado una frase dicha por quien quiere 
ingresar.
 Si la frase dicha contiene 12 palabras y ademas esas 12 palabras se encuentran en el texto siguiendo el mismo orden(no 
 necesariamente contiguas) el ingreso es exitoso. Sabiendo que cuenta con una funcion que dados 2 strings, devueelve la 
 posicion  del primero en el segundo(contando palabras) 

 	SE PIDE: DADA UNA FRASE DICHA POR ALGUIEN QUE QUIERE INGESAR A LOS SISTEMAS DE DEXTER Y UN  TEXTO,DETERMINAR (Devolver
 	true o false), SI LA FRASE CUMPLE LAS CONDICIONES IMPUESTAS POR DEXTER*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX_FRASE 100
#define MAX_NOMBRE 20
#define MAX_PALABRA 20
#define MAX_TEXTO 300
#define MAX_CONTRASENIA 20
#define ERROR -1
#define NO_ENCONTRADO -1
#define CARACTER_NULO '\0'
#define ESPACIO ' '
#define NOMBRE_TEXTO "texto.txt"
#define FORMATO_LECTURA "%[^.]."
typedef struct frase{
	char palabra[MAX_PALABRA];
	int orden_en_frase;
	int orden_en_texto;
}frase_t;
int posicion_real(int posicion,char oracion[MAX_TEXTO]){
	int contador_palabras=0;
	int i=0;
	while(i<posicion){
		if(oracion[i]==ESPACIO){
			contador_palabras++;
		}
		i++;
	}
	return contador_palabras+1;

}
/*	Devuelve el orden de la palabra en el texto,o -1 si la palabra no esta en el texto.
 Ejemplo:
 Palabra="gato"
 texto= "si se cruza un gato negro hay que dar trece pasos hacia atras"
 La funcion devolvera 5 porque gato es la 5ta palabra.	
*/
int posicion_palabra_en_texto(char palabra[MAX_PALABRA],char oracion[MAX_TEXTO]){
	char oracion_aux[MAX_TEXTO];
	int posicion=NO_ENCONTRADO;
	for(int i=0;i<strlen(oracion);i++){
		for(int j=0;j<strlen(palabra);j++){
			oracion_aux[j]=oracion[i+j];
		}
		if(strncmp(oracion_aux,palabra,strlen(palabra))==0){
			posicion=i;
		}
	}
	return (posicion_real(posicion,oracion));
}

/*	
	Procedimiento que lee un archivo de texto y lo vuelca a un string
*/
void volcar_texto_en_string(FILE* archivo_texto,char texto_guardado[MAX_TEXTO]){
	fscanf(archivo_texto,FORMATO_LECTURA,texto_guardado);
}
/*	Procedimiento que lee una frase pasada por parametro y la vuelca en un vector de tipo frase_t y le pone su respectivo
orden 
	PRE:El tope debe estar en cero.*/
void volcar_frase_en_vector(char frase[MAX_FRASE],frase_t contrasenia[MAX_CONTRASENIA],int* tope_palabras){
	int i=0;
	int j=0;
	int palabra_actual=0;
	bool termino=false;
	while(!termino){
		while((frase[i]!=ESPACIO)&&(frase[i]!=CARACTER_NULO)){
			contrasenia[palabra_actual].palabra[j]=frase[i];
			i++;
			j++;
		}
		contrasenia[palabra_actual].palabra[j]=CARACTER_NULO;
		if(frase[i]==CARACTER_NULO){
			termino=true;
		}
		contrasenia[palabra_actual].orden_en_frase=palabra_actual+1;
		palabra_actual++;
		(*tope_palabras)++;
		j=0;
		i++;	
	}
}

/*	Funcion que se encarga de abrir el archivo de texto para su posterior uso, devuelve -1 en caso de no haber podido abrirlo
*/
int leer_archivo_y_guardar_frase(char nombre_archivo_texto[MAX_NOMBRE],char frase[MAX_FRASE],
	frase_t contrasenia[MAX_CONTRASENIA],int* tope_palabras,char texto_guardado[MAX_TEXTO]){

	FILE* archivo_texto=fopen(nombre_archivo_texto,"r");
	if(!archivo_texto){
		perror("No se pudo abrir el archivo de texto");
		return ERROR;
	}
	volcar_frase_en_vector(frase,contrasenia,tope_palabras);
	volcar_texto_en_string(archivo_texto,texto_guardado);
	fclose(archivo_texto);
	return 0;
}
/*
	Funcion booleana que devuelve true si
*/
bool tienen_mismo_orden(char texto_guardado[MAX_FRASE],frase_t contrasenia[MAX_CONTRASENIA],int tope_palabras){
	bool mismo_orden=true;
	bool termino=false;
	int i;
//	printf("%i\n",tope_palabras );
	for(i=0;i<tope_palabras;i++){
		contrasenia[i].orden_en_texto=posicion_palabra_en_texto(contrasenia[i].palabra,texto_guardado);
	//	printf("%s %i %i\n",contrasenia[i].palabra,contrasenia[i].orden_en_frase,contrasenia[i].orden_en_texto );
	}
	for(i=0;i<tope_palabras-1;i++){
		if(contrasenia[i].orden_en_texto<contrasenia[i+1].orden_en_texto){
	//		printf("%i<%i\n",contrasenia[i].orden_en_texto,contrasenia[i+1].orden_en_texto );
			if(i>=tope_palabras){
				termino=true;
			}
		}
		else{
			mismo_orden=false;
		}
	}
	return mismo_orden;
}
/*
	Funcion que revisa que la frase dada, cumpla con las condiciones para entrar al laboratorio, devuelve true de ser asi
	o false en caso contrario.
*/
bool la_frase_cumple(char nombre_archivo_texto[MAX_NOMBRE],char frase[MAX_FRASE]){
	frase_t contrasenia[MAX_CONTRASENIA];
	int tope_palabras=0;
	char texto_guardado[MAX_TEXTO];
	leer_archivo_y_guardar_frase(nombre_archivo_texto,frase,contrasenia,&tope_palabras,texto_guardado);
	if(tienen_mismo_orden(texto_guardado,contrasenia,tope_palabras)){
		return true;
	}
	else{
		return false;
	}
}
int main(){
	if(la_frase_cumple("texto.txt","La puerca esta en la pocilga")){
		printf("La frase ingresada es correcta\n");
	}
	else{
		printf("A casa campeon\n" );
	}
	return 0;
}