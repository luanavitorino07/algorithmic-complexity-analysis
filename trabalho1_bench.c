#include <stdio.h>
#include <time.h>

int atribuicoes = 0;
int comparacoes = 0;

double tempo_decorrido(struct timespec inicio, struct timespec fim) {
    long segundos = fim.tv_sec - inicio.tv_sec;
    long nanosegundos = fim.tv_nsec - inicio.tv_nsec;

    if (nanosegundos < 0) {
        segundos -= 1;
        nanosegundos += 1000000000;
    }
    return (double)segundos + ((double)nanosegundos / 1000000000.0);
}

void inversao(int v[], int n) {
    int temp;
    atribuicoes++; // int i = 0
    for (int i = 0; i < n/2; i++) {        
        comparacoes++; // i<n/2
        
        temp = v[i];
        v[i] = v[n-1-i];
        v[n-1-i] = temp;
        atribuicoes += 3;
    }
    comparacoes++; // i=n/2 ao acabar o for 
}

int busca_sequencial(int v[], int n, int busca) {
    atribuicoes++; // int i = 0
    for (int i = 0; i < n; i++) {
        comparacoes++; // i<n

        comparacoes++;
        if (v[i] == busca) return 1;
        
    }
    comparacoes++; // i=n ao acabar o for 
    return 0;
}

int busca_binaria_it(int v[], int n, int busca) {

    int l = 0, r = n-1;
    atribuicoes += 2;
    
    comparacoes++; 
    int crescente = v[0] < v[n - 1];
    atribuicoes++;

    while(1) {   

        comparacoes++;    
        if (!(l <= r)) break;
        
        int m = l + (r - l) / 2;
        atribuicoes++;

        comparacoes++;
        if (v[m] == busca) return 1;
        

        comparacoes++;
        if (crescente) {
            comparacoes++;
            if (v[m] < busca) {              
                l = m + 1;
                atribuicoes++;
            } else {
                r = m - 1;
                atribuicoes++;
            }
        } else {
            comparacoes++;
            if (v[m] > busca) {
                l = m + 1;
                atribuicoes++;
            } else {
                r = m - 1;
                atribuicoes++;
            }
        }
        
    }
    return 0;
}

int busca_binaria_rec(int v[], int l, int r, int busca, int n) {
    comparacoes++;
    if (l > r) return 0;

    comparacoes++;
    int crescente = v[0] < v[n - 1];
    atribuicoes++;

    int m = l + (r - l) / 2;
    atribuicoes++;

    comparacoes++;
    if (v[m] == busca) return 1;

    comparacoes++;
    if (crescente) {
        comparacoes++;
        if (v[m] < busca) return busca_binaria_rec(v, m + 1, r, busca, n);
        return busca_binaria_rec(v, l, m - 1, busca, n);
    } else {
        comparacoes++;
        if (v[m] > busca) return busca_binaria_rec(v, m + 1, r, busca, n);
        return busca_binaria_rec(v, l, m - 1, busca, n);
    }
}

int main() {
    int n, op = 0;

    scanf("%d", &n);

    int v[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }

    struct timespec inicio, fim;

    while (op != 5) {
        scanf("%d", &op);
        int x;
        
        atribuicoes = 0;
        comparacoes = 0;

        switch(op) {
            case 1:
                clock_gettime(CLOCK_MONOTONIC, &inicio);
                inversao(v, n);
                clock_gettime(CLOCK_MONOTONIC, &fim);
                printf("%.9f | %d | %d\n", tempo_decorrido(inicio, fim), atribuicoes, comparacoes);
                break;

            case 2:
                scanf("%d", &x);
                clock_gettime(CLOCK_MONOTONIC, &inicio);
                busca_sequencial(v, n, x);
                clock_gettime(CLOCK_MONOTONIC, &fim);
                printf("%.9f | %d | %d\n", tempo_decorrido(inicio, fim), atribuicoes, comparacoes); 
                break;

            case 3:
                scanf("%d", &x);
                clock_gettime(CLOCK_MONOTONIC, &inicio);
                busca_binaria_it(v, n, x);
                clock_gettime(CLOCK_MONOTONIC, &fim);
                printf("%.9f | %d | %d\n", tempo_decorrido(inicio, fim), atribuicoes, comparacoes);
                break;

            case 4:
                scanf("%d", &x);
                clock_gettime(CLOCK_MONOTONIC, &inicio);
                busca_binaria_rec(v, 0, n - 1, x, n);
                clock_gettime(CLOCK_MONOTONIC, &fim);
                printf("%.9f | %d | %d\n", tempo_decorrido(inicio, fim), atribuicoes, comparacoes);
                break;

            case 5:
                return 0;
        }
    }

    return 0;
}