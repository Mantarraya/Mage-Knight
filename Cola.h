#ifndef COLA_H
#define	COLA_H

/* UTILIZAREMOS UNA COLA PARA COLOCAR A NUESTROS ENEMIGOS */

typedef struct Enemigo{
    char nombre[20];
    int pAttack;
    int pDefend;
    int pExperience;
}TEnemigo;


typedef struct nodoCola {
        TEnemigo info;
        struct nodoCola *sig;
} TNodoCola;

typedef struct {
        TNodoCola *inicio;
        TNodoCola *fin;
} TCola;

void inicializar_Cola_Enemigos(TCola*);
void insertar_Enemigo(TCola*, TEnemigo);
TEnemigo sacar_Enemigo(TCola*);
int esta_Cola_Enemigos_Vacio(TCola *);
void finalizar_Cola_Enemigos(TCola *);


#endif

