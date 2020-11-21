#include <stdlib.h>
#include <ctime>
#include <stdio.h>

#define N 6

unsigned int old_arr[N][N];
unsigned int amount_arr[N][N];
unsigned int new_arr[N][N];

void Flandria_init() {
    int i, j;
    srand(unsigned(time(NULL)));
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            old_arr[i][j] = rand()%2;
}

void Flandria_print() {
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++)
            printf("%d ", old_arr[i][j]);
        printf("\n");
    }
}

int neighbor_counter(int fst, int sec) {
    int count = 0;
    int i, j;

    // Центральная сетка
    if(((fst > 0) && (fst < (N - 1))) && ((sec > 0) && (sec < (N - 1)))) {
        for(i = fst - 1; i < fst + 2; i++)
            for(j = sec - 1; j < sec + 2; j++)
                if((i != fst) || (j != sec))
                    if(old_arr[i][j] == 1)
                        count += 1;
    }
    else {
        // Полоска слева
        if(sec == 0) {
            if((fst != 0) && (fst != N - 1)) {
                for(i = fst - 1; i < fst + 2; i++)
                    for(j = sec; j < sec + 2; j++)
                        if((i != fst) || (j != sec)) {
                            if(old_arr[i][j] == 1) {
                                count += 1;
                            }
                        }
            }
            else {
                //Левые угловые клетки
                switch(fst) {
                    // Левая верхняя
                    case 0: {
                        for(i = fst; i < fst + 2; i++)
                            for(j = sec; j < sec + 2; j++)
                                if((i != fst) || (j != sec)) {
                                    if(old_arr[i][j] == 1) {
                                        count += 1;
                                    }
                                }
                        break;
                    }
                    // Левая нижняя
                    case N - 1: {
                        for(i = fst - 1; i < fst + 1; i++)
                            for(j = sec; j < sec + 2; j++)
                                if((i != fst) || (j != sec)) {
                                    if(old_arr[i][j] == 1) {
                                        count += 1;
                                    }
                                }
                        break;
                    }
                }
            }
        }
        // Полоска справа
        if(sec == N - 1){
            if((fst != 0) && (fst != N - 1)) {
                for(i = fst - 1; i < fst + 2; i++)
                    for(j = sec - 1; j < sec + 1; j++)
                        if((i != fst) || (j != sec)) {
                            if(old_arr[i][j] == 1) {
                                count += 1;
                            }
                        }
            }
            else {
                // Правые угловые клетки
                switch(fst) {
                    // Правая верхняя
                    case 0: {
                        for(i = fst; i < fst + 2; i++)
                            for(j = sec - 1; j < sec + 1; j++)
                                if((i != fst) || (j != sec)) {
                                    if(old_arr[i][j] == 1) {
                                        count += 1;
                                    }
                                }
                        break;
                    }
                    // Правая нижняя
                    case N-1: {
                        for(i = fst - 1; i < fst + 1; i++)
                            for(j = sec - 1; j < sec + 1; j++)
                                if((i != fst) || (j != sec)) {
                                    if(old_arr[i][j] == 1) {
                                        count += 1;
                                    }
                                }
                        break; 
                    }
                }
            }
        }
        // Полоска сверху
        if(fst == 0) {
            if((sec != 0) && (sec != N - 1))
                for(i = fst; i < fst + 2; i++)
                    for(j = sec - 1; j < sec + 2; j++)
                        if((i != fst) || (j != sec))
                            if(old_arr[i][j] == 1)
                                count += 1;
        }
        // Полоска снизу
        if(fst == N - 1) {
            if((sec != 0) && (sec != N - 1))
                for(i = fst - 1; i < fst + 1; i++)
                    for(j = sec - 1; j < sec + 2; j++)
                        if((i != fst) || (j != sec))
                            if(old_arr[i][j] == 1)
                                count += 1;
        }
    }
    return count;
}

void Flandria_iteration() {
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++) {
            int neighbor_amount = neighbor_counter(i, j);
            if(old_arr[i][j] != 0) {
                if((neighbor_amount < 3) || (neighbor_amount > 4))
                    new_arr[i][j] = 0;
                else
                    new_arr[i][j] = 1;
            }
            else {
                if((neighbor_amount == 3) || (neighbor_amount == 4))
                    new_arr[i][j] = 1;
            }
        }
}

void Flandria_copy() {
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            old_arr[i][j] = new_arr[i][j];
}

void Flandria_live() {
    Flandria_print();
    puts("*****************************");
    Flandria_iteration();
    Flandria_copy();
}

int Flandria_alive() {
    int count = 0;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            count += old_arr[i][j];
    return count;
}

int main() {
    Flandria_init();
    while(Flandria_alive()) {
        Flandria_live();
        getchar();
    }
    puts("All the Flanders died");
    return 0;
}
