/*
	Ed y edd quieren molestar a eddy porque saben que tiene un diario donde guarda sus sentimientos
	SE PIDE
	Dados dos strings, uno que representeuna hoja del diario de Eddy y otro que represente  una palabra cualquiera, se
	reemplaze cada caracter de esa palabra pasada por x, en todas las apariciones del string que representa la hoja del diario.
	Por ejemplo si se tiene el string:

	Oye tablon te llama tu mama.Tablon...

	DEBERIA QUEDAR

	Oye xxxxx te llama tu mama.xxxxx...
*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX_PAGINA 300
#define MAX_PALABRA 20
#define ESPACIO ' '
#define CARACTER_NULO '\0'
#define CENSURA 'x'
/*
	Procedimiento que reemplaza la palabra de un string que empieza en la posicion pasada, por el caracter xxxx.
*/
void reemplazar_palabra(char pagina[MAX_PAGINA],int pos_palabra,int largo_palabra){
	int caracter_actual=pos_palabra;
	int fin=pos_palabra+largo_palabra;
	while(caracter_actual<fin){
		pagina[caracter_actual]=CENSURA;
		caracter_actual++;
	}
}
/*
	Funcion que compara dos palabras y devuelve true si lo son o false en caso contrario.
*/
bool es_la_palabra_buscada(char palabra[MAX_PALABRA],char buscada[MAX_PALABRA]){
	return(strcmp(palabra,buscada)==0);
}
/*
	Procedimiento que compara palabra por palabra ,si es la buscada , de ser asi la reemplaza , caracter a caracter por xxxx.
*/
void separar_palabras_comparar_y_reemplazar(char palabra[MAX_PALABRA],char pagina[MAX_PAGINA]){
	int caracter_actual_texto=0;
	int caracter_actual_palabra;
	int pos_palabra;
	char auxiliar[MAX_PALABRA];

	while(pagina[caracter_actual_texto]!=CARACTER_NULO){
		caracter_actual_palabra=0;
		pos_palabra=caracter_actual_texto;

		while(pagina[caracter_actual_texto]!=ESPACIO && pagina[caracter_actual_texto]!=CARACTER_NULO){
			auxiliar[caracter_actual_palabra]=pagina[caracter_actual_texto];
			caracter_actual_texto++;
			caracter_actual_palabra++;
		}
		auxiliar[caracter_actual_palabra]=CARACTER_NULO;

		if(es_la_palabra_buscada(auxiliar,palabra)){
			reemplazar_palabra(pagina,pos_palabra,strlen(palabra));
		}
		caracter_actual_texto++;
	}
}
/*
	Procedimiento que recibe un texto y una palabra por parametro,y reemplaza por x todos los caracteres de la palabra ,todas
	las veces que aparezca en el texto.
*/
void censurar_palabra(char palabra[MAX_PALABRA],char pagina[MAX_PAGINA]){
	separar_palabras_comparar_y_reemplazar(palabra,pagina);
}

int main(){
	char string[MAX_PALABRA];
	char frase[MAX_PAGINA];
	strcpy(frase,"Ankara messi ankara messi invente messi invente");
	printf("%s\n",frase );
	strcpy(string,"messi");
	censurar_palabra(string,frase);
	printf("%s\n",frase );
	return 0;
}