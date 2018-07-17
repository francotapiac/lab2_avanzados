#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_
#include "estructura.h"

lista *pop(lista *p);
lista *anularPiLa(lista *p);
int **topeTablero(lista *p);
int topePosX(lista *p);
int topePosY(lista *p);
int topeProfundidad(lista *p);
lista *push(lista *p, int **tablero, int posX, int posY, int profundidad);
lista *crearNodo(int **tablero,int i,int j,int ref);
lista *InsertarNodo(lista *q,int **tablero,int x,int y,int estado);

FILE *abrirArchivo(char *nombre_archivo);
lista *crearLista(FILE *archivo);
boolean posicionesPertenecenTablero(int posX,int posY);
boolean tableroSeEncuentraGuardado(lista *recorridoTotal,int **tablero);
int **intercambiarCasillas(int **tableroAuxiliar,int **tablero,int posXActual,int posYActual,int posXAnterior,int posYAnterior);
int **crearTablero(int cantidadFilas,int cantidadColumnas);
boolean tableroRecorridoIgualTableroFinal( int **tablero);
int moverFicha(lista *recorridoTotal,lista *p, int  profundidadFinal);

#endif