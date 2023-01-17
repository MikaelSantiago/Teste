#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct vertice {
    int chave;
    struct vertice *pai;
    struct vertice *esq;
    struct vertice *dir;
}VERTICE;

VERTICE *raiz = NULL;

VERTICE *buscar (int x, VERTICE *aux){
    if (aux == NULL){ //vazio
        return NULL;
    }else if (x == aux -> chave){ //achei o vertice
        return aux;
    }else if (x < aux -> chave){ // caminha para esquerda
        if (aux -> esq != NULL){
            return buscar (x, aux -> esq);
        }else{
            return aux;
        }
    }else{
        if (aux -> dir != NULL){ // caminha para direita
            return buscar (x, aux -> dir);
        }else{
            return aux;
        }
    }
}

void add (int x){
    VERTICE *result = buscar (x, raiz);

    if (result == NULL || result -> chave != x){
        VERTICE *novo = (VERTICE*) malloc (sizeof (VERTICE));
        novo -> chave = x;
        novo -> pai = result;
        novo -> esq = NULL;
        novo -> dir = NULL;

        if (result == NULL){
            raiz = novo;
        }else{
            if (x < result -> chave){
                result -> esq = novo;
            }else{
                result -> dir = novo;
            }
        }
    }
}

VERTICE *rem (int x, VERTICE *aux){
    VERTICE *result = buscar (x, aux);

    if (result == NULL){
        return NULL;
    }

    if (result -> esq == NULL && result -> dir == NULL){ //folha
        if (result -> chave < result -> pai -> chave){
            result -> pai -> esq = NULL;
            free (result);
        }else{
            result -> pai -> dir = NULL;
            free (result);
        }
    }else if (result -> esq != NULL && result -> dir == NULL){ //pai com 1 filho esq
        if (result -> esq -> chave < result -> pai -> chave){
            result -> pai -> esq = result -> esq;
            result -> esq -> pai = result -> pai;
            free (result);
        }else{
            result -> pai -> dir = result -> esq;
            result -> esq -> pai = result -> pai;
            free (result);
        }
    }else if (result -> esq == NULL && result -> dir != NULL){ //pai com 1 filho dir
        if (result -> dir -> chave < result -> pai -> chave){
            result -> pai -> esq = result -> dir;
            result -> dir -> pai = result -> pai;
            free (result);
        }else{
            result -> pai -> dir = result -> dir;
            result -> dir -> pai = result -> pai;
            free (result);
        }
    }else{
        aux = result -> dir;  //menor dos maiores
        while (aux -> esq != NULL){
            aux = aux -> esq;
        }

        result -> chave = aux -> chave;  //substituição dos dados

        if (aux -> dir == NULL){  //caso seja folha
            aux -> pai -> esq = NULL;
            free (aux);
        }else{   //caso seja pai com 1 filho na direita
            aux -> pai -> esq = aux -> dir;
            aux -> dir -> pai = aux -> pai;
            free (aux);
        }         
    }
}

void imprimir (VERTICE *aux){
    if (aux -> esq != NULL){
        imprimir (aux -> esq);
    }
    printf ("%d ", aux -> chave);
    if (aux -> dir != NULL){
        imprimir (aux ->dir);
    }
}




int main (){
    add (15);
    add (10);
    add (5);
    add (8);
    add (12);
    add (11);
    add (20);
    add (18);
    add (16);
    add (25);
    add (24);

    imprimir (raiz);

    rem (20, raiz);

    printf ("\n");

    imprimir (raiz);

}