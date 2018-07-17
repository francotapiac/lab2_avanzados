#ifndef _FUNCIONES_C_
#define _FUNCIONES_C_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "estructura.h"
#include "funciones.h"


//Función que borra tope de lista
//Entrada: pila
//salida: pila sin tope
lista *pop(lista *p){

	if(p != NULL){
		lista *auxiliar = p->sig;
		free(p);
		return auxiliar;
	}
	return p;
}

//Función encargada de anular lista
//Entrada: pila
//Salida: Nulo
lista *anularPiLa(lista *p){
	while(p != NULL)
		p = pop(p);
	return NULL;
}

//Función que encuentra tablero en tope de pila
//Entrada: pila
//salida: tablero de enteros
int **topeTablero(lista *p){
	if(p != NULL)
		return p->tablero;
	return NULL;
}

//Función que encuentra posición fila de celda vacía en tope de pila
//Entrada: pila
//salida: entero
int topePosX(lista *p){
	if(p != NULL)
		return p->posX;
	return -1;
}

//Función que encuentra posición columna de celda vacía en tope de pila
//Entrada: pila
//salida: entero
int topePosY(lista *p){
	if(p != NULL)
		return p->posY;
	return -1;
}

//Función que encuentra profundidad tope de pila
//Entrada: pila
//Salida: entero
int topeProfundidad(lista *p){
	if(p != NULL)
		return p->profundidad;
	return -1;
}

//Función que inserta un nodo en pila
//Entradas: pila, tablero, fila de celda vacía, columna de celda vacía, profundidad tablero
//salida: pila con nuevo nodo
lista *push(lista *p, int **tablero, int posX, int posY, int profundidad){

	lista *nuevoNodo = crearNodo(tablero,posX,posY,profundidad);
	nuevoNodo->sig = p;
	return nuevoNodo;
}

//Función que crea nodo del tipo lista
//Entrada: tablero de enteros, fila i, columna j, profundidad ref
lista *crearNodo(int **tablero,int i,int j,int ref){

	lista *nodo = (lista*)malloc(sizeof(lista));
	nodo->tablero = crearTablero(3,3);
	int p;
	for(p = 0; p < 3;p++){
		int w;
		for(w = 0; w < 3; w++)
			nodo->tablero[p][w] = tablero[p][w];
	}
	nodo->posX = i;
	nodo->posY = j;
	nodo->profundidad = ref;
	nodo->sig = NULL;
	return nodo;
}


//Funciones de Puzzle 8


//Función encargada de abrir el archivo entrada.in
//Entrada: nombre archivo
//Salida: archivo
FILE *abrirArchivo(char *nombre_archivo){

	FILE* archivo = NULL;
	archivo = fopen(nombre_archivo,"r");
	if(archivo == NULL){
        printf(" Error: no se ha podido abrir el archivo correctamente \n Verifique si el archivo se encuentra en la misma carpeta de su programa");
        exit(-1);
	}
	return archivo;
}

//Función que crea pila con datos de archivo
//Entrada: archivo con puzzle 8
//Salida: pila del tipo lista
lista *crearLista(FILE *archivo){

	lista *listaTablero = NULL;
	char lista_temporal[500];
	int posX;
	int posY;
	int **tablero  = (int**)malloc(3*sizeof(int*));
	int i;
	for(i = 0;i < 3; i++)
		tablero[i] = (int*)malloc(3*sizeof(int));
	//almacenar datos del archivo en la lista
	for(i = 0; i < 3; i++){
		fscanf(archivo,"%s",&lista_temporal);
		int j;
		for(j = 0; j < 3; j++){
			if(lista_temporal[j] == 'X'){
				posX = i;
				posY = j;
				tablero[i][j] = 0;
			}
			else{
				tablero[i][j] = (int)(lista_temporal[j] - 48);
			}
		}
	}
	listaTablero = push(listaTablero,tablero,posX,posY,0);
	fclose(archivo);
	return listaTablero;
}

//Se verifica si posiciones de entradas pueden estar en tablero
//Entrada: fila posX  y columna posY
//Salida: booleano
boolean posicionesPertenecenTablero(int posX,int posY){

	if(posX < 0 || posY < 0)
		return false;
	if(posX >= 3 || posY >= 3)
		return false;
	return true;
}

//Verifica si tablero ya se encuentra en recorrido total
//Entrada: recorrido total y tablero a verificar
//Salida: booleano
boolean tableroSeEncuentraGuardado(lista *recorridoTotal,int **tablero){

	if(recorridoTotal == NULL)
		return false;
	lista *indice = recorridoTotal;
	boolean comparadorTablero = false;
	while(indice != NULL && comparadorTablero == true){
		int i;
		for(i = 0; i < 3;i++){
			int j;
			for(j = 0; j < 3;j++){
				if(indice->tablero[i][j] != tablero[i][j])
					comparadorTablero = false;
			}
		}
		indice = indice->sig;
	}
	return comparadorTablero;

}

//Función encargada de trasladar celda vacía
//Entradas: tablero auxiliar, tablero, fila y columnas actuales a mover, filas y columnas anteriores
int **intercambiarCasillas(int **tableroAuxiliar,int **tablero,int posXActual,int posYActual,int posXAnterior,int posYAnterior){

	int p;
	for(p = 0; p < 3; p++){
		int w;
		for(w = 0; w < 3; w++){
			tableroAuxiliar[p][w] = tablero[p][w];
		}
	}

	int elemento = tableroAuxiliar[posXActual][posYActual];
	tableroAuxiliar[posXActual][posYActual] = tableroAuxiliar[posXAnterior][posYAnterior];
	tableroAuxiliar[posXAnterior][posYAnterior] = elemento;

	return tableroAuxiliar;
}

//función que inicializa tablero
//Entrada: cantidad de filas y columnas
//Salida: tablero
int **crearTablero(int cantidadFilas,int cantidadColumnas){

	int **tablero  = (int**)malloc(3*sizeof(int*));
	int i;
	for(i = 0;i < 3; i++)
		tablero[i] = (int*)malloc(3*sizeof(int));
	return tablero;
}

//Función que verifica si tablero corresponde al tablero final
//Entrada: tablero
//Salida: boobleano
boolean tableroRecorridoIgualTableroFinal( int **tablero){
 
	if(tablero[0][0] == 1 && tablero[0][1] == 2 && tablero[0][2] == 3 && 
		tablero[1][0] == 4 && tablero[1][1] == 5 && tablero[1][2] == 6 && 
		tablero[2][0] == 7 && tablero[2][1] == 8 && tablero[2][2] == 0)
		return true;
	return false;
}


//Función que muestra tablero
//Entrada: tablero de enteros
//Salida:
void mostrarTablero(int **tablero){
	int w;
	int k;

	for(k = 0; k < 3; k++){
		for (int w = 0; w < 3; ++w)
			printf("%d", tablero[k][w]);
			printf("\n");
		}
		printf("\n");
}

//Función que realiza backtracking, buscando todos los tableros solución que sean 
//de menor profundidad que el tablero solución anterior
//Entrada: recorrido total, pila p del tipo lista, profundiad final o tope
//Salida: profundidad final (cantidad de movimiento menor)
int moverFicha(lista *recorridoTotal,lista *p, int  profundidadFinal){

	int dx[4] = {0,0,1,-1};
	int dy[4] = {1,-1,0,0};

	while(p != NULL){

		//Se sacan datos del tope de la pila
		int **tablero = topeTablero(p);
		int posX = topePosX(p);
		int posY = topePosY(p);
		int profundidad = topeProfundidad(p);
		p = pop(p);
		mostrarTablero(tablero);

		//Se analiza si posible tablero solucion tiene una profundidad menor a la profundidad final
		if(tableroRecorridoIgualTableroFinal(tablero) == true && profundidad <= profundidadFinal){
			recorridoTotal = push(recorridoTotal,tablero,posX,posY,profundidad);
			profundidadFinal = profundidad;
		}

		//Cada tablero que no esté guardado en recorrido, se almacena en esa lista y en pila p.
		else if(tableroSeEncuentraGuardado(recorridoTotal,tablero) == false && profundidad < profundidadFinal){
			recorridoTotal = push(recorridoTotal,tablero,posX,posY,profundidad);
			int i;
			for(i = 0; i < 4; i++){
				if(posicionesPertenecenTablero(posX + dx[i],posY + dy[i]) == true){
					int **tableroAuxiliar = crearTablero(3,3);
					tableroAuxiliar = intercambiarCasillas(tableroAuxiliar,tablero,posX + dx[i],posY+ dy[i],posX,posY);
					p = push(p,tableroAuxiliar,posX + dx[i],posY + dy[i],profundidad + 1);
					//printf("%d\n",profundidad + 1 );
				}
			}
		}
	}
	return profundidadFinal;
}


//Función encargada de mostrar en un archivo la salida
//Entrada: menor camino como profundidad final
//Salida:
void escribirSalida(int profundidadFinal){

	int i;
	FILE* archivo = NULL;
	char* nombre = "salida.out";
	archivo = fopen(nombre,"w");
 	if(archivo == NULL)
    	printf("error \n");	
    
	if(profundidadFinal == 10)
		fprintf(archivo, "No existe solucion para el puzzle");
	else
		fprintf(archivo,"Se requiere %d movimientos\n",profundidadFinal );
	}

int main(int argc, char const *argv[])
{
	FILE *archivo = abrirArchivo("entrada.in");
	lista *tableroIncial = crearLista(archivo);
	lista *recorridoTotal = NULL;
	int menorCamino = moverFicha(recorridoTotal,tableroIncial, 10);
	escribirSalida(menorCamino);
	/*if(menorCamino == 10)
		printf( "No existe solucion para el puzzle");
	else
		printf("Se requiere %d movimientos\n",menorCamino );*/
	
	anularPiLa(recorridoTotal);
	anularPiLa(tableroIncial);
	return 0;
}

#endif