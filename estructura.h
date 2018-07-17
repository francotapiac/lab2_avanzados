#ifndef _ESTRUCTURAS_H
#define _ESTRUCTURAS_H

typedef struct lista lista;
typedef int boolean;
#define true 1
#define false 0



typedef struct lista{

	int posX;
	int posY;
	int profundidad;
	int **tablero;
	struct lista *sig;
}lista;

#endif