/*
    Emerson Camilo Pizarro Laquise
    Luana Assunção Vitorino
    Pedro de Freitas Sena
    Sarah Mendes Gurgel
*/


#include <stdlib.h>
#include "ListaComCursor.h"

typedef struct node {
    int data;
    struct node *next;
    struct node *prev;
} Node;

struct lista_cursor{
    int qtd;
    Node *cursor;
    Node *head;
    Node *tail;
};



//criação e destruição
ListaCursor *criar_lista(void){
    ListaCursor *l = malloc(sizeof(ListaCursor));
    if (!l) return NULL;

    l->head = NULL;
    l->tail = NULL;
    l->qtd = 0;
    l->cursor = NULL;

    return l;
}

void destruir_lista(ListaCursor *l){
	if (!l) return;

    Node *temp = l->head;
    while(temp != NULL){
        Node *rem = temp;
        temp = temp->next;
        free(rem);
    }

    free(l);
}


//navegação
void mover_inicio(ListaCursor *l){
    if (!l) return;
    if (l->qtd > 0) l->cursor = l->head;
}

void mover_fim(ListaCursor *l){
    if (!l) return;
    if (l->qtd > 0) l->cursor = l->tail;
}

int avancar_cursor(ListaCursor *l){
    if (!l || !l->cursor) return 0;
    if (l->cursor->next == NULL) return 0;
    
    l->cursor = l->cursor->next;
    return 1;
}

int retroceder_cursor(ListaCursor *l){
    if (!l || !l->cursor) return 0;
    if (l->cursor->prev == NULL || l->qtd <=0) return 0;

    l->cursor = l->cursor->prev;
    return 1;
}

int mover_para_indice(ListaCursor *l, int indice){
    if (!l) return 0;
    if (indice < 0 || indice >= l->qtd) return 0;

    Node *temp = l->head;
    for (int i = 0; i < indice; i++){
        temp = temp->next;
    }

    l->cursor = temp;
    return 1;
}



//consulta
int obter_atual(ListaCursor *l, int *valor_saida){
    if (!l || !valor_saida) return 0;
    if (l->qtd <= 0 || !l->cursor) return 0;

    *valor_saida = l->cursor->data;
    return 1;
}




//modificação
int inserir_antes(ListaCursor *l, int valor){
    if (!l) return 0;

	Node *novo = malloc(sizeof(Node));
	if (!novo) return 0;

	novo->data = valor;
	
    if (l->qtd == 0){
        novo->prev = NULL;
        novo->next = NULL;

        l->head = novo;
        l->tail = novo;
        l->cursor = novo;
    }
    else {
        novo->next = l->cursor;
        novo->prev = l->cursor->prev;


        if (l->cursor->prev != NULL) {
            l->cursor->prev->next = novo;
        } else {
            l->head = novo;
        }

        l->cursor->prev = novo;
    }

	l->qtd++;
	return 1; 
}

int inserir_depois(ListaCursor *l, int valor){
    if (!l) return 0;

    Node *novo = malloc(sizeof(Node));
    if (!novo) return 0;

    novo->data = valor;

    if (l->qtd == 0){
        novo->prev = NULL;
        novo->next = NULL;

        l->head = novo;
        l->tail = novo;
        l->cursor = novo;
    }
    else {
        novo->next = l->cursor->next;
        novo->prev = l->cursor;

        if (l->cursor->next != NULL) {
            l->cursor->next->prev = novo;
        } else {
            l->tail = novo;
        }

        l->cursor->next = novo;
    }

    l->qtd++;
    return 1;
}

int remover_atual(ListaCursor *l){
	if (!l) return 0;
	if (l->qtd <= 0) return 0;

    Node *rem = l->cursor;

    if (l->qtd == 1){ //lista vai ficar vazia
        l->head = NULL;
        l->tail = NULL;
        l->cursor = NULL;
    }
    else if (rem->next == NULL) { //se for o ultimo
        l->tail = rem->prev;
        l->tail->next = NULL;
        l->cursor = l->tail;
    }
    else if (rem->prev == NULL){  //se for o primeiro
        l->head = rem->next;
        l->head->prev = NULL;
        l->cursor = l->head;
    }
    else { //removendo no meio
        rem->prev->next = rem->next;
        rem->next->prev = rem->prev;
        l->cursor = rem->next;
    }
	
    free(rem);
	l->qtd--;
	return 1;
}



//informação
int tamanho_lista(ListaCursor *l){
    if (!l) return 0;
    return l->qtd;
}