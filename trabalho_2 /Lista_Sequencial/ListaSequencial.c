/*
    Emerson Camilo Pizarro Laquise
    Luana Assunção Vitorino
    Pedro de Freitas Sena
    Sarah Mendes Gurgel
*/


#include "ListaComCursor.h"
#include <stdlib.h>

struct lista_cursor {
    int qtd;
    int *dados;
    int cap;
    int cursor;
};

//criação e destruição
static int garante_cap(ListaCursor *l){
    if (!l) return 0;

    //tem espaço
    if (l->qtd < l->cap) return 1;

    if (l->cap == 0){
        l->dados = malloc(10*sizeof(int)); //criando com cap 10
        if (!l->dados) return 0; //erro de alocação
        l->cap = 10;
    }
    else {
        //dobrando a capacidade
        int nova_cap = l->cap*2;
        int *novo = realloc(l->dados, nova_cap*sizeof(int));

        if (!novo) return -1;

        l->dados = novo;
        l->cap = nova_cap;
    }

    return 1;
}


ListaCursor* criar_lista(void){
    ListaCursor *l = malloc(sizeof(ListaCursor));

    if (!l) return NULL;

    l->cap = 0;
    l->cursor = -1;
    l->qtd = 0;
    l->dados = NULL;

    return l;
} 

void destruir_lista(ListaCursor* l){
    if (!l){
        return;
    }

    free(l->dados);
    free(l);
}

//navegação do cursor
void mover_inicio(ListaCursor* l){
    if (!l) return;
    if (l->qtd > 0) l->cursor = 0;
}

void mover_fim(ListaCursor* l) {
    if (!l) return;
    if (l->qtd > 0) l->cursor = l->qtd-1;
}

int avancar_cursor(ListaCursor* l){
    if (!l) return 0;
    if (l->qtd == 0 || l->cursor >= l->qtd-1) return 0;

    l->cursor++;
    return 1;
}

int retroceder_cursor(ListaCursor* l){
    if (!l) return 0;
    if (l->qtd == 0 || l->cursor <= 0) return 0;

    l->cursor--;
    return 1;
}

int mover_para_indice(ListaCursor* l, int indice){
    if (!l) return 0;
    if (indice < 0 || indice >= l->qtd) return 0;

    l->cursor = indice;
    return 1;
}



//consulta
int obter_atual(ListaCursor* l, int* valor_saida){
    if (!l || !valor_saida) return 0;
    if (l->qtd == 0) return 0;
    if (l->cursor < 0 || l->cursor >= l->qtd) return 0;

    *valor_saida = l->dados[l->cursor];
    return 1;
}



//modificação
int inserir_antes(ListaCursor* l, int valor){
    if (!l) return 0;
    if (garante_cap(l) != 1) return 0;

    if (l->qtd == 0){
        l->dados[0] = valor;
        l->cursor = 0;
    }
    else{
        for (int i = l->qtd; i > l->cursor; i--){
            l->dados[i] = l->dados[i-1];
        }
        l->dados[l->cursor] = valor;
        l->cursor++;
    }

    l->qtd++;
    return 1;
}

int inserir_depois(ListaCursor* l, int valor){
    if (!l) return 0;
    if (garante_cap(l) != 1) return 0;

    if (l->qtd == 0){
        l->dados[0] = valor;
        l->cursor = 0;
    }
    else{
        for (int i = l->qtd; i > l->cursor+1; i--){
            l->dados[i] = l->dados[i-1];
        }
        l->dados[l->cursor+1] = valor;
    }

    l->qtd++;
    return 1;
}

int remover_atual(ListaCursor*l){
    if (!l) return 0;
    if (l->qtd == 0) return 0;

    if (l->qtd == 1) l->cursor = -1; //ficou vazia
    else if (l->cursor == l->qtd-1) l->cursor--; //n tem sucessor
    else { 
        for (int i = l->cursor; i < l->qtd-1; i++){
            l->dados[i] = l->dados[i+1];
        }
    }
    l->qtd--;
    return 1;
}


//informação
int tamanho_lista(ListaCursor *l){
    if (!l) return 0;
    return l->qtd;
}