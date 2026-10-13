/*
    Emerson Camilo Pizarro Laquise
    Luana Assunção Vitorino
    Pedro de Freitas Sena
    Sarah Mendes Gurgel
*/


#include <stdlib.h>
#include<stdio.h>
#include "ListaComCursor.h"

int main(){

    ListaCursor *l;
    l = criar_lista();

    if (!l) return 0;

    int op, valor, res;

    while(1){
        scanf("%d", &op);

        switch(op){
            case 1:
                scanf("%d", &valor);
                inserir_antes(l, valor);
            break;

            case 2:
                scanf("%d", &valor);
                inserir_depois(l, valor);
            break;

            case 3:
                remover_atual(l);
            break;

            case 4: 
                res = obter_atual(l, &valor);
                if (res == 1) printf("%d\n", valor);
                else printf("ERRO\n");
            break;  

            case 5:
                mover_inicio(l);
            break;

            case 6:
                mover_fim(l);
            break;

            case 7:
                res = avancar_cursor(l);
                printf("%d\n", res);
            break;

            case 8:
                res = retroceder_cursor(l);
                printf("%d\n", res);
            break;

            case 9:
                scanf("%d", &valor);
                res = mover_para_indice(l, valor);
                printf("%d\n", res);
            break;

            case 10:
                res = tamanho_lista(l);
                printf("%d\n", res);
            break;

            case 0:
                destruir_lista(l);
                return 0;
        }
    }

    return 0;
}