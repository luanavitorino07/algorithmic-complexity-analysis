#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ListaComCursor.h"

double tempo_decorrido(struct timespec inicio, struct timespec fim) {
    long segundos = fim.tv_sec - inicio.tv_sec;
    long nanosegundos = fim.tv_nsec - inicio.tv_nsec;

    if (nanosegundos < 0) {
        segundos -= 1;
        nanosegundos += 1000000000;
    }
    return (double)segundos + ((double)nanosegundos / 1000000000.0);
}

void preencher_lista(ListaCursor *l, int n) {
    mover_inicio(l);
    for (int i = 0; i < n; i++) {
        inserir_depois(l, i);
    }
}

int main() {
    int tamanhos[] = {1000, 50000, 100000, 500000, 1000000};
    int num_tamanhos = 5;
    int repeticoes = 10;

    printf("=== BENCHMARK: LISTA SEQUENCIAL ===\n");
    printf("Tamanho | Caso 1: Ins. Inicio (s) | Caso 2: Acesso Indice (s) | Caso 3: Rem. Inicio (s) | Caso 4: Rem. Meio (s) | Caso 5: Percurso (s)\n");
    printf("-------------------------------------------------------------------------------------------------------------------------\n");

    for (int t = 0; t < num_tamanhos; t++) {
        int n = tamanhos[t];
        double tempos[5] = {0.0, 0.0, 0.0, 0.0, 0.0};

        int *indices_aleatorios = malloc(100 * sizeof(int));
        srand(42); 
        for (int i = 0; i < 100; i++) {
            indices_aleatorios[i] = rand() % n;
        }

        for (int r = 0; r < repeticoes; r++) {
            ListaCursor *l = criar_lista();
            preencher_lista(l, n);

            struct timespec inicio, fim;
            clock_gettime(CLOCK_MONOTONIC, &inicio);
            for (int i = 0; i < 100; i++) {
                mover_inicio(l);
                inserir_antes(l, 999);
            }
            clock_gettime(CLOCK_MONOTONIC, &fim);
            tempos[0] += tempo_decorrido(inicio, fim);

            destruir_lista(l);
        }
        tempos[0] /= repeticoes;

        for (int r = 0; r < repeticoes; r++) {
            ListaCursor *l = criar_lista();
            preencher_lista(l, n);

            int val_saida;
            struct timespec inicio, fim;
            clock_gettime(CLOCK_MONOTONIC, &inicio);
            for (int i = 0; i < 100; i++) {
                mover_para_indice(l, indices_aleatorios[i]);
                obter_atual(l, &val_saida);
            }
            clock_gettime(CLOCK_MONOTONIC, &fim);
            tempos[1] += tempo_decorrido(inicio, fim);

            destruir_lista(l);
        }
        tempos[1] /= repeticoes;

        for (int r = 0; r < repeticoes; r++) {
            ListaCursor *l = criar_lista();
            preencher_lista(l, n);

            struct timespec inicio, fim;
            clock_gettime(CLOCK_MONOTONIC, &inicio);
            mover_inicio(l);
            for (int i = 0; i < 100; i++) {
                remover_atual(l);
            }
            clock_gettime(CLOCK_MONOTONIC, &fim);
            tempos[2] += tempo_decorrido(inicio, fim);

            destruir_lista(l);
        }
        tempos[2] /= repeticoes;

        for (int r = 0; r < repeticoes; r++) {
            ListaCursor *l = criar_lista();
            preencher_lista(l, n);

            struct timespec inicio, fim;
            clock_gettime(CLOCK_MONOTONIC, &inicio);
            mover_para_indice(l, n / 2);
            for (int i = 0; i < 100; i++) {
                remover_atual(l);
            }
            clock_gettime(CLOCK_MONOTONIC, &fim);
            tempos[3] += tempo_decorrido(inicio, fim);

            destruir_lista(l);
        }
        tempos[3] /= repeticoes;

        for (int r = 0; r < repeticoes; r++) {
            ListaCursor *l = criar_lista();
            preencher_lista(l, n);

            int val_saida;
            struct timespec inicio, fim;
            clock_gettime(CLOCK_MONOTONIC, &inicio);
            mover_inicio(l);
            do {
                obter_atual(l, &val_saida);
            } while (avancar_cursor(l));
            clock_gettime(CLOCK_MONOTONIC, &fim);
            tempos[4] += tempo_decorrido(inicio, fim);

            destruir_lista(l);
        }
        tempos[4] /= repeticoes;

        printf("%-7d | %-23.9f | %-25.9f | %-23.9f | %-21.9f | %.9f\n", 
               n, tempos[0], tempos[1], tempos[2], tempos[3], tempos[4]);

        free(indices_aleatorios);
    }

    return 0;
}