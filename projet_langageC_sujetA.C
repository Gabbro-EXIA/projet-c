#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void menu(){
    printf("+-----------------------------------+\n|1 : Addition                       |\n|2 : Soustraction                   |\n|3 : Multiplication                 |\n|4 : Tables des multiplications     |\n|5 : Divisions                      |\n|0 : Sortir du jeu                  |\n+-----------------------------------+\nQuel est votre choix ?\t");
}


void addition(int *score){
    int resultat;
    srand(time(NULL));
    int a = rand() % 100;
    int b = rand() % 100;

    printf("Addition \n %d + %d = ? \n Entrez le resultat \n", a, b);
    scanf("%d", &resultat);
    printf("Vous avez entre %d \n", resultat);
    if (resultat == a + b){
        printf("Bravo ! \n");
        score += 1;
    }
    else{
        printf("Trompe ! \n");
    }
}


void soustraction(int *score){
    int resultat;
    while(resultat == NULL){
    srand(time(NULL));
        int a = rand() % 100;
        int b = rand() % 100;
        if(a > b){
            printf("Soustraction \n %d - %d = ? \n Entrez le resultat \n", a, b);
            scanf("%d", &resultat);
            printf("Vous avez entre %d \n", resultat);
            if (resultat == a - b){
                printf("Bravo ! \n");
                score += 1;
            }
            else{
                printf("Trompe ! \n");
            }
        }
    }
}


void multiplication(int *score){
    int resultat;
    srand(time(NULL));
    int a = rand() % 10 + 1;
    int b = rand() % 10 + 1;

    printf("Multiplication \n %d * %d = ? \n Entrez le resultat \n", a, b);
    scanf("%d", &resultat);
    printf("Vous avez entre %d \n", resultat);
    if (resultat == a * b){
        printf("Bravo ! \n");
        score += 1;
    }
    else{
        printf("Trompe ! \n");
    }
}


void table_multi(int *score){
    int resultat;
    int taille;

    printf("Choisissez la table de multiplication\t");
    scanf("%d", &taille);

    printf("\n   ");
    for (int i = 1; i <= taille; i++)
    {
        printf("%4d", i);
    }
    printf("\n");

    for (int i = 1; i <= taille; i++)
    {
        printf("%2d ", i);
        for (int j = 1; j <= taille; j++)
        {
            printf("%4d", i * j);
        }
        printf("\n");
    }
    printf("Voulez-vous remplir une colonne par vous même ? (1=Oui,0=Non)\t");
    scanf("%d", &resultat);
    if (resultat == 1)
    {
        int colonne;
        printf("Entrez le numéro de la colonne (1 à %d)\t", taille);
        scanf("%d", &colonne);
        if (colonne < 1 || colonne > taille)
        {
            printf("Numéro de colonne invalide.\n");
            return;
        }
        for (int i = 1; i <= taille; i++)
        {
            int reponse_utilisateur;
            printf("Quel est le résultat de %d * %d ?\t", i, colonne);
            scanf("%d", &reponse_utilisateur);
            if (reponse_utilisateur == i * colonne)
            {
                printf("Bravo !\n");
                (*score)++;
            }
            else
            {
                printf("Désolé, la bonne réponse est %d.\n", i * colonne);
            }
        }
    }
}




int main(){
    char choix;
    int score = 0;

    menu();
    scanf("%s", &choix);
    while(choix != '0'){
        switch(choix){
            case '1':
                addition(&score);
                break;
            case '2':
                soustraction(&score);
                break;
            case '3':
                multiplication(&score);
                break;
            case '4':
                table_multi(&score);
                break;
            case '5':
                printf("division");
                break;
            default:
                printf("Mauvaise manipulation");
        }
        printf("%d",&score);
        menu();
        scanf("%s", &choix);
        printf("");
    }
    printf("Merci de votre visite ! \n");
    return 0;
}
