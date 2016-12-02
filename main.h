#ifndef MAIN_H // Guarda para evitar include circulares
#define MAIN_H
/* ------ Se hacen todos los includes necesarios ------ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ------ Definición de tus estructuras ------ */

typedef struct{ 
	char *palabra;
	int c;
}Palabra; 

struct elemento
{
	struct elemento *siguiente;
	Palabra *valor;
};

// defino alias para los datos (struct elemento) y (Elemento**)
typedef struct elemento Elemento; /*No cambies esta línea*/
typedef Elemento** Lista; /*No cambies esta línea*/


/* ------ Definición de tus funciones ------ */

/*Imprime las instrucciones de uso del programa*/
void imprime_instrucciones();

/*Calcula que palabra se repitió más en un archivo y el número de veces que aparece*/
void calcula_repeticiones( char const * arch, FILE *destino );

/*Guarda el resultado de cada archivo en el archivo final*/
void guarda_en_archivo( char const * arch, char linea[] );



/*Libera(free) la memoria ocupada por la lista, sus elementos y valores*/
//No se te olvide liberar la memoria de cada elemento y su valor.
void borra_lista(Lista);

/*Crea una lista vacía*/
Lista crea_lista();

/*Inserta un elemento en la lista y se regresa el nuevo tamanio de la lista*/
void inserta_elemento(Lista lista, Palabra *valor );


/*Remueve un elemento de una lista en una posición dada*/
//Si la posición no coincide con ningún elemento se regresa NULL
Elemento *quita_elemento(Lista lista, size_t posicion);


/*Regresa el número de elementos en la lista*/
size_t longitud(Lista lista);


/*Función que ordena una lista usando una función comparadora*/
//Recomiendo apoyarte de tu función 'cmp_int', qsort y un arreglo
void ordena_lista(Lista lista, int(*cmp)(const void*, const void*));

int cmp( const void* a, const void* b);


/*Imprime los elementos de la lista*/
void imprime_lista(Lista lista);

#endif //MAIN_H