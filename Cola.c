#include <stdio.h>
#include <stdlib.h>
#include "Cola.h"


void inicializar_Cola_Enemigos(TCola *C){
    C->inicio = NULL;
    C->fin = NULL;
}

void insertar_Enemigo(TCola *C, TEnemigo nuevoElem){
    TNodoCola *ptr_nuevoNodo;
    
    ptr_nuevoNodo = (TNodoCola*)malloc(sizeof(TNodoCola));
    
    if (ptr_nuevoNodo != NULL){
        ptr_nuevoNodo->info = nuevoElem;
        ptr_nuevoNodo->sig = NULL;
        if (C->inicio == NULL)
            C->inicio = ptr_nuevoNodo;
        else 
            C->fin->sig = ptr_nuevoNodo;

        C->fin = ptr_nuevoNodo;
    }
}

TEnemigo sacar_Enemigo(TCola *C){
    if (!esta_Cola_Enemigos_Vacio(C)){
        TEnemigo head_info; TNodoCola *ptr_head;
        ptr_head = C->inicio;
        head_info = ptr_head->info;
        C->inicio = C->inicio->sig;
        free(ptr_head);
        return head_info;
    }
    return C->inicio->info;
}

int esta_Cola_Enemigos_Vacio(TCola *C){
    return (C->inicio == NULL);
}

void finalizar_Cola_Enemigos(TCola *C){
    while (!esta_Cola_Enemigos_Vacio(C))
        sacar_Enemigo(C);
}

