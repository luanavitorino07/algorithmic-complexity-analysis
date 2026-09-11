#include <stdio.h>


void inversao(int v[], int n){
    int temp;

    //for (int i = 0; i < n/2; i++){
    //    temp = v[i];
    //    v[i] = v[n-1-i];
    //    v[n-1-i] = temp;
    //}

    for(int i = 0; i < n; i++){
        printf("%d ", v[n-1-i]);
    }

    printf("\n");
}


void busca_sequencial(int v[], int n){
    int busca;

    scanf("%d", &busca);

    for (int i = 0; i < n; i++){
        if (v[i] == busca){
            printf("SIM\n");
            return;
        }
    }

    printf("NAO\n");
}

void busca_binaria_it(int v[], int n){
    int busca, l = 0, r = n-1;

    scanf("%d", &busca);

    while(l <= r){
        int m = l + (r - l) /2;

        if (v[m] == busca) {
            printf("SIM\n");
            return;
        }

        if (v[m] < busca){
            l = m + 1;
        }
        else {
            r = m - 1;
        }
    }

    printf("NAO\n");

}

void busca_binaria_rec(int v[], int l, int r, int busca){
    if (l>r) {
        printf("NAO\n");
        return;
    }    
    

    int m = l + (r - l) / 2;

    if (v[m] == busca) {
        printf("SIM\n");
        return;
    }

    if (v[m] < busca){
        busca_binaria_rec(v, m + 1, r, busca);
        return;
    }

    busca_binaria_rec(v, l, m-1, busca);

}


int main(){
    int n, op = 0;

    scanf("%d", &n);

    int v[n];

   for (int i = 0; i < n; i++){
        scanf("%d", &v[i]);
    }

    while(op != 5){
        scanf("%d", &op);

        switch(op){
            case 1:  
                inversao(v, n);    
            break;

            case 2:  
                busca_sequencial(v, n);
            break;

            case 3:  
                busca_binaria_it(v, n);
            break;

            case 4:
                int x;
                scanf("%d", &x);
                busca_binaria_rec(v, 0, n-1, x);
            break;

            case 5: 
                return 0;
            break;
        }

    }

    return 0;
}