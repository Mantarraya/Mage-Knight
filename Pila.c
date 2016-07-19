#include <stdio.h>
#include <stdlib.h>
#include "Pila.h"

void inicializar_Baraja(TPila *P){
    P->top = NULL;
}

void insertar_Carta_Baraja(TPila *P, TCard nuevoElem){
    TNodo *ptr_nuevoElem;
    
    ptr_nuevoElem = (TNodo*)malloc(sizeof(TNodo));
    
    if (ptr_nuevoElem){
        ptr_nuevoElem->info = nuevoElem;
        ptr_nuevoElem->sig = P->top;
        P->top = ptr_nuevoElem;
    }
}


int esta_Baraja_Vacia(TPila *P){
    return (P->top == NULL);
}

TCard sacar_Carta_Baraja(TPila *P){
    TCard top_info; TNodo *ptr_top;
    if (!esta_Baraja_Vacia(P)){
        ptr_top = P->top;
        top_info = ptr_top->info;
        P->top = P->top->sig;
        free(ptr_top);
        return top_info;
    }
    return P->top->info;
} 

void finalizar_Baraja(TPila *P){
    while (!esta_Baraja_Vacia(P))
        sacar_Carta_Baraja(P);
}  



