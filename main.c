#include "main.h"
// No hagas #include aquí, hazlos en main.h

int main(int argc, char const *argv[])
{
    // Verifica si hay al menos de 3 parametros
    // sino entonces se imprimen las instrucciones
    // y se para la ejecución del programa
    if (argc < 3)
    {
        imprime_instrucciones();
        return 0;
    }else{
	    FILE *file = fopen( argv[argc-1], "r" );
	    
	    //sino entonces calcula la palabra con mayor repeticion por documento.
	    printf( "Nombre del archivo\t\tPalabra más repetida\t\tNúmero de repeticiones\n");
	    fprintf( file, "Nombre del archivo\t\tPalabra más repetida\t\tNúmero de repeticiones\n");
	    //itera por archivo
	    for( int i = 1; i < argc-1; i++ ){
	    	printf("%s\t\t\t",argv[i]);
	    	fprintf( file, "%s\t\t\t",argv[i]);
	    	calcula_repeticiones( argv[i],file );
	    }
	    printf("Se guardó el resultado en el archivo %s\n", argv[argc-1] );
	    fclose(file);
	}
   	return 0;
}

/* ------ Aquí va la implementación de tus funciones ------ */

void imprime_instrucciones(){

	printf("Error: El formato de entrada es incorrecto\n");
	printf("Uso: nombre_archivo <archivo> [<archivo> [<archivo> ...]] <archivo>\n");

}

void calcula_repeticiones( char const * arch, FILE *destino ){

	FILE *file;
	file = fopen( arch, "r" );
	char cadena[100];
	Lista lista = crea_lista();

	while( !feof(file) ){
		fscanf( file, "%s ,.-", cadena );
		Palabra *nueva = malloc( sizeof( Palabra ) );
		nueva -> palabra = cadena;
		nueva -> c = 1;
		inserta_elemento(lista,nueva);
	}

	ordena_lista(lista,&cmp);
	imprime_lista(lista);
	
	Elemento *cabeza = *lista;

	printf("%s\t\t\t", (cabeza -> valor -> palabra) );
	fprintf( destino, "%s\t\t\t", (cabeza -> valor -> palabra) );

	printf("%d\n", cabeza-> valor -> c );
	fprintf(destino, "%d\n", cabeza-> valor -> c );

	fclose(file);
	borra_lista(lista);
}


//LISTAS
/***********************************************************************************/
/*Libera(free) la memoria ocupada por la lista, sus elementos y valores*/
//No se te olvide liberar la memoria de cada elemento y su valor.
void borra_lista(Lista lista){
	
	//creamos un iterador
	Elemento* iterador = *lista;

	//si la lista esta vacía solo borra la memoria ocupada por la lista
	if( *lista == NULL ){
		free( lista );
		return;
	}
	//recorremos la lista
	while( iterador != NULL ){
		//quitamos el elemento de la lista
		iterador = quita_elemento( lista, 0 );
		//liberamos ambos campos de ese nodo de la lista
		free( iterador -> valor );
		free( iterador );
		//retomamos el inicio de la lista
		iterador = *lista;
	}
	//liberamos el espacio ocupado por la lista
	free(lista);

}

/*Remueve un elemento de una lista en una posición dada*/
//Si la posición no coincide con ningún elemento se regresa NULL
Elemento *quita_elemento(Lista lista, size_t posicion){

	//creamos un iterador
	Elemento* iterador;
	//auxiliar para mantener el control de la lista al eliminar
	Elemento* auxiliar;
	//En caso de eliminar la cola guardamos el penultimo
	Elemento* auxPenultimo;
	//nos sirve para saber en donde eliminar
	size_t indice = 0;

	//si la lista esta vacía o el apuntador no entra en la longitud regresamos NULL
	if( *lista == NULL || posicion >= longitud(lista) || posicion < 0 )
		return NULL;
	//en caso de que quitemos la cabeza de la lista:
	if( posicion == 0 ){

		//apuntamos al primer elemento de la lista
		iterador = *lista;
		//guardamos el segundo elemento
		auxiliar = iterador -> siguiente;
		//igualamos la referencia del segundo elemento al del primer elemento de la lista
		*lista = auxiliar;
		//regresamos la cabeza
		return iterador;

	}
	//sino nos situamos en el primer elemento.
	iterador = *lista;
	//recorremos la lista
	while( iterador != NULL ){
		//si encontramos la posicion eliminamos el elemento
		if( indice == posicion-1 ){
			//en caso de que sea la cola
			if( posicion == longitud(lista)-1 ){
				auxiliar = iterador;
				//ahora el penultimo es la cola
				auxPenultimo -> siguiente = NULL;
			}else{
				auxiliar = iterador -> siguiente;
				//retomamos el control de la lista
				iterador -> siguiente = auxiliar -> siguiente;
			}
			//regresamos el elemento eliminado
			return auxiliar;

		}
		auxPenultimo = iterador;
		//pasamos al siguiente
		iterador = iterador -> siguiente;
		//aumentamos la posición
		indice ++;
	}

}


/*Crea una lista vacía*/
Lista crea_lista(){

	//reservamos espacio en memoria para la lista
	Lista lista = malloc( sizeof( Lista ) );
	return lista;

}

/*Inserta un elemento en la lista y se regresa el nuevo tamanio de la lista*/
void inserta_elemento(Lista lista, Palabra * valor){
	//creamos un iterador para recorrer la lista
	Elemento* iterador;
	//nos situamos en el primer elemento.
	iterador = *lista;
	//recorremos la lista
	while( iterador != NULL ){
		if( strcmp( iterador -> valor -> palabra, valor -> palabra ) == 0 ){
			iterador -> valor -> c++;
			return;
		}
		iterador = iterador -> siguiente;
	}
	//creamos un puntero que apuntará al nuevo elemento
	Elemento* nuevo = malloc( sizeof( Elemento ) );
	//asignamos el nuevo valor
	//apuntamos el elemento a la cabeza de la lista
	nuevo -> siguiente = *lista;
	nuevo -> valor = valor;
	//apuntamos la lista al nuevo elemento
	*lista = nuevo;
	
}

/*Imprime los elementos de la lista*/
void imprime_lista(Lista lista){

	//creamos un iterador para recorrer la lista
	Elemento* iterador;
	//nos situamos en el primer elemento.
	iterador = *lista;

	//recorremos la lista
	while( iterador != NULL ){
		//imprimimos el elemento
		printf("(%s,%d)", (iterador -> valor->palabra), iterador->valor-> c );

		iterador = iterador -> siguiente;
	}
	printf("\n");

}

/*Función que ordena una lista usando una función comparadora*/
//Recomiendo apoyarte de tu función 'cmp_int', qsort y un arreglo
void ordena_lista(Lista lista, int(*cmp)(const void*, const void*)){

	//creamos un iterador
	Elemento* iterador = *lista;
	//guardamos la longitud de la lista
	size_t len = longitud(lista);
	
	//creamos un arreglo de elementos para guardar los elementos de la lista
	Elemento* elementos = malloc( sizeof( Elemento )*len );

	//llenamos el arreglo
	for( int i = 0; i < len; i++ ){
		elementos[i] = *iterador;
		iterador = iterador -> siguiente;
	}

	//llamamos a la funcion qsort()
	qsort( elementos, len, sizeof(Elemento), *cmp );

	//apuntamos a la cabeza de la lista
	iterador = *lista;

	//llenamos la lista con los valores ordenados
	for( int i = 0; i < len; i++ ){
		iterador -> valor = elementos[i].valor;
		iterador = iterador -> siguiente;
	}


}

/*Regresa el número de elementos en la lista*/
size_t longitud(Lista lista){
	
	//creamos un iterador para recorrer la lista
	Elemento* iterador;
	//creamos un contador
	size_t len = 0;

	//nos situamos en el primer elemento.
	iterador = *lista;
	//recorremos la lista
	while( iterador != NULL ){
		iterador = iterador -> siguiente;
		len++;
	}

	return len;

}

int cmp( const void* a, const void* b){
	//cast a tipo ELEMENTO
	Elemento* x = ( Elemento* )a;
	Elemento* y = ( Elemento* )b;
	//cast de los valores a INT
	int v1 = x -> valor -> c;
	int v2 = y -> valor -> c;
	
	return v2-v1;
	
}