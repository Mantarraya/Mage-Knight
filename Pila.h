#ifndef PILA_H
#define	PILA_H

typedef struct Card{
    char* nombre;
    int pMove;
    int pAttack;
    int pDefend;
    int pHeal;
    int pBuy;
}TCard;

typedef struct nodo {
        TCard info;
        struct nodo *sig;
} TNodo;

typedef struct {
        TNodo *top;
} TPila;


void inicializar_Baraja(TPila*);
void insertar_Carta_Baraja(TPila*, TCard);
TCard sacar_Carta_Baraja(TPila*);
int esta_Baraja_Vacia(TPila *);
void finalizar_Baraja(TPila *);


#endif

