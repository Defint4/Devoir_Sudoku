#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HORIZ 0
#define VERT 1

void generer(int solution[9][9], int nb_zeros) {
    int i, j, k;

    int generated[9][9];
    for(i = 0; i < 9; ++i) {
        for(j = 0; j < 9; ++j) {
            generated[i][j] = solution[i][j];
        }
    }

    int zero_indices[nb_zeros][2];
    for(k = 0; k < nb_zeros; ++k) {
        i = rand() % 9;
        j = rand() % 9;

        int already_chosen = 0;
        for(int l = 0; l < k; ++l) {
            if(i == zero_indices[l][0] && j == zero_indices[l][1]) {
                already_chosen = 1;
                break;
            }
        }
        if(already_chosen) {
            k--;
        } else {
            zero_indices[k][0] = i;
            zero_indices[k][1] = j;
            generated[i][j] = 0;
        }
    }

    for(i = 0; i < 9; ++i) {
        for(j = 0; j < 9; ++j) {
            solution[i][j] = generated[i][j];
        }
    }
}


int saisir(int grid[9][9]) {
    int i, j, v;
    do {
        printf("Saisir les indices i(grille) et j(case), entre 1 et 9 séparer par des espaces : ");
        scanf("%d %d", &i, &j);
        printf("saisir la valeur de la case (entre 1 et 9): ");
        scanf("%d", &v);
    } while (i < 0 || i > 8 || j < 0 || j > 8 || v < 1 || v > 9);

    if (grid[i-1][j-1] == 0) {
        grid[i-1][j-1] = v;
    }

    int num_non_zeros = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (grid[i][j] != 0) {
                num_non_zeros++;
            }
        }
    }
    return num_non_zeros;
}


int verifierLigneColonne(int grille[9][9], int num, int sens) {
    int elements[9] = {0};
    for (int i = 0; i < 9; i++) {
        if (sens == HORIZ && grille[num][i] != 0) {
            elements[grille[num][i] - 1]++;
        } else if (sens == VERT && grille[i][num] != 0) {
            elements[grille[i][num] - 1]++;
        }
    }
    for (int i = 0; i < 9; i++) {
        if (elements[i] > 1) {
            return 0;
        }
    }
    return 1;
}

int verifierRegion(int k, int l, int grille[][9]) {
    int tab[9] = {0};
    for (int i = k*3; i < k*3+3; i++) {
        for (int j = l*3; j < l*3+3; j++) {
            if (grille[i][j] != 0 && tab[grille[i][j]-1] == 0) {
                tab[grille[i][j]-1] = 1;
            } else if (grille[i][j] != 0) {
                return 0;
            }
        }
    }
    return 1;
}

int verifierGrille(int grille[9][9]) {

    for (int i = 0; i < 9; i++) {
        if (!verifierLigneColonne(grille, i, HORIZ)) {
            return 0;
        }
    }

    for (int j = 0; j < 9; j++) {
        if (!verifierLigneColonne(grille, j, VERT)) {
            return 0;
        }
    }

    for (int k = 0; k < 3; k++) {
        for (int l = 0; l < 3; l++) {
            if (!verifierRegion(k, l, grille)) {
                return 0;
            }
        }
    }
    return 1;
}


int main(){
    // Ne pas toucher le code entre les commentaires
    srand( time( NULL ) );


    int i, j, k;
    int solution[9][9];
    printf("SOLUTION");  
    printf("\n");  
    printf("---------------------------------");  
    printf("\n");  
    for(j=0;j<9; ++j) 
    {
    for(i=0; i<9; ++i)
        solution[j][i] = (i + j*3 +j /3) %9 +1 ; 
    }
    
    for(i=0;i<9; ++i) 
    {
    for(j=0; j<9; ++j)
        printf("%d ", solution[i][j]);
    printf("\n");  
    }
    printf("---------------------------------");  
    printf("\n");  
    //toucher le code entre les commentaires
    int grille[9][9];
    int nb_zeros = 35;
    generer(solution, nb_zeros);

    for(int i=0; i<9; ++i) {
        for(int j=0; j<9; ++j) {
            grille[i][j] = solution[i][j];
        }
    }

    for(i=0; i<9; ++i) {
        for(j=0; j<9; ++j) {
            printf("%d ", grille[i][j]);
        }
        printf("\n");
    }

    int remplissage = 40;
    while (remplissage < 81) {

        remplissage = saisir(grille);
        for(i=0; i<9; ++i) {
            for(j=0; j<9; ++j) {
                printf("%d ", grille[i][j]);
            }
            printf("\n");
        }
        if (remplissage == 81) {
            if(verifierGrille(grille)) {
                printf("Bravo, la grille est correcte !\n");
            } else {
                printf("La grille est incorrecte, réessayez.\n");
            }
        }
    }
    //Ne pas toucher au code ci dessous
    system("pause");
    return 0;
}

