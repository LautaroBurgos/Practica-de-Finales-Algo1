/*		Hacer una funcion que dados dos strings,uno que representa una oracion y el otro una palabra devuelva la posicion 
	de la primer aparicion de la palabra en la oracion. *SE DEBE CONSIDERAR EL CASO QUE NO SE ENCUENTRE*. Por ejemplo: Si la
	oracion es "Oye tablon tu mama te llama",y la palabra es "Tablon", se deberia devolver 4. Ya que la 'T' , es la quinta
	letra que aparece en la oracion.
	EXPLICACION: (suponiendo que la palabra es "tablon"),arranca comparando la palabra con los primeros 6 caracteres de 
	la oracion, si la palabra no se encuentra ahi, repite el proceso pero empieza a comparar ahora desde el segundo caracter
	de la oracion, se repite hasta llegar al final

	OYE TABLON TE LLAMA TU MAMA
	------
	 ------
	  ------
	   -------
	   Asi sucesivamente
	*/
/*	Funcion que devuelve la posicion de una palabra en una oracion, devuelve -1 en caso de no haberla encontrado
*/
#include <stdio.h>
#include <string.h>
#define MAX_ORACION 30
#define MAX_PALABRA 50
#define NO_ENCONTRADO -1
int posicion_palabra(char oracion[MAX_ORACION],char palabra[MAX_PALABRA]){
	char oracion_aux[MAX_ORACION];
	int posicion=NO_ENCONTRADO;
	for(int i=0;i<strlen(oracion);i++){
		for(int j=0;j<strlen(palabra);j++){
			oracion_aux[j]=oracion[i+j];
		}
		if(strncmp(oracion_aux,palabra,strlen(palabra))==0){
			posicion=i;
		}
	}
	return posicion;
}