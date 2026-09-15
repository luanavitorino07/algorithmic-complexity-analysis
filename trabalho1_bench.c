#include <stdio.h>
#include <time.h>

long tempo_decorrido(struct timespec inicio, struct timespec fim) {
    long segundos = fim.tv_sec - inicio.tv_sec;
    long nanosegundos = fim.tv_nsec - inicio.tv_nsec;

    if (nanosegundos < 0) {
        segundos -= 1;
        nanosegundos += 1000000000;
    }

    return (segundos * 1000000000L) + nanosegundos;
}

void inversao(int v[], int n){
    int temp;
    for (int i = 0; i < n/2; i++){
        temp = v[i];
        v[i] = v[n-1-i];
        v[n-1-i] = temp;
    }
}

int busca_sequencial(int v[], int n, int busca){
    for (int i = 0; i < n; i++){
        if (v[i] == busca) return 1;
    }
    return 0;
}

int busca_binaria_it(int v[], int n, int busca){
    int l = 0, r = n-1;
    int crescente = v[0] < v[n - 1];

    while(l <= r){
        int m = l + (r - l) / 2;

        if (v[m] == busca) return 1;

        if (crescente){
            if (v[m] < busca) l = m + 1;
            else r = m - 1;
        } else {
            if (v[m] > busca) l = m + 1;
            else r = m - 1;
        }
    }
    return 0;
}

int busca_binaria_rec(int v[], int l, int r, int busca, int n){
    if (l > r) return 0;

    int crescente = v[0] < v[n - 1];
    int m = l + (r - l) / 2;

    if (v[m] == busca) return 1;

    if (crescente){
        if (v[m] < busca) return busca_binaria_rec(v, m + 1, r, busca, n);
        return busca_binaria_rec(v, l, m - 1, busca, n);
    } else {
        if (v[m] > busca) return busca_binaria_rec(v, m + 1, r, busca, n);
        return busca_binaria_rec(v, l, m - 1, busca, n);
    }
}

int main(){
    int n, op = 0;

    scanf("%d", &n);

    int v[n];
    for (int i = 0; i < n; i++){
        scanf("%d", &v[i]);
    }

    struct timespec inicio, fim;

    while(op != 5){
        scanf("%d", &op);
        int x;

        switch(op){
            case 1:
                clock_gettime(CLOCK_MONOTONIC, &inicio);
                inversao(v, n);
                clock_gettime(CLOCK_MONOTONIC, &fim);
                printf("%ld\n", tempo_decorrido(inicio, fim)); 
                break;

            case 2:
                scanf("%d", &x);
                clock_gettime(CLOCK_MONOTONIC, &inicio);
                busca_sequencial(v, n, x);
                clock_gettime(CLOCK_MONOTONIC, &fim);
                printf("%ld\n", tempo_decorrido(inicio, fim)); 
                break;

            case 3:
                scanf("%d", &x);
                clock_gettime(CLOCK_MONOTONIC, &inicio);
                busca_binaria_it(v, n, x);
                clock_gettime(CLOCK_MONOTONIC, &fim);
                printf("%ld\n", tempo_decorrido(inicio, fim)); 
                break;

            case 4:
                scanf("%d", &x);
                clock_gettime(CLOCK_MONOTONIC, &inicio);
                busca_binaria_rec(v, 0, n - 1, x, n);
                clock_gettime(CLOCK_MONOTONIC, &fim);
                printf("%ld\n", tempo_decorrido(inicio, fim)); 
                break;

            case 5:
                return 0;
        }
    }

    return 0;
}