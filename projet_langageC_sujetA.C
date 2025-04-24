#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void menu(){
    printf("+-----------------------------------+\n|1 : Addition                       |\n|2 : Soustraction                   |\n|3 : Multiplication                 |\n|4 : Tables des multiplications     |\n|5 : Divisions                      |\n|0 : Sortir du jeu                  |\n+-----------------------------------+\nQuel est votre choix ?\t");
}


void gestionReponse(int resultat, int *score)
{
    int essaie = 3; 
    int reponse; 

    while (essaie > 0)
    {
        scanf("%d", &reponse);
        printf("Vous avez entre : %d\n", reponse);
        if (reponse == resultat)
        {
            switch (essaie)
            {
                case 3:
                    printf("Bravo, vous gagnez 10 points!\n\n");
                    *score += 10; 
                    return;
                case 2:
                    printf("Bravo ! Vous avez utilise 2 essais. Vous gagnez donc 5 points.\n\n");
                    *score += 5; 
                    return;
                case 1:
                    printf("Bravo ! Vous avez utilise 3 essai. Vous ne gagnez donc qu'un point.\n\n");
                    *score += 1; 
                    return;
            }
        }
        else
        {
            essaie--;
            if (essaie == 0){
                printf("Désole, la bonne réponse est %d.\n\n", resultat);
            }
            else{
                printf("Désole, ce n'est pas la bonne réponse. Il vous reste %d essais.\n\n", essaie);
            }
        }
    }
}


void addition(int *score){
    int resultat;
    srand(time(NULL));
    int a = rand() % 100;
    int b = rand() % 100;

    printf("Addition \n %d + %d = ? \n Entrez le resultat \n", a, b);
    resultat = a + b;
    gestionReponse(resultat, score);   
}


void soustraction(int *score){
    int resultat;
    while(resultat == NULL){
        srand(time(NULL));
        int a = rand() % 100;
        int b = rand() % 100;
        if(a > b){
            printf("Soustraction \n %d - %d = ? \n Entrez le resultat \n", a, b);
            resultat = a - b;
            gestionReponse(resultat, score);
        }
    }
}


void multiplication(int *score){
    int resultat;
    srand(time(NULL));
    int a = rand() % 10 + 1;
    int b = rand() % 10 + 1;

    printf("Multiplication \n %d * %d = ? \n Entrez le resultat \n", a, b);
    printf("Vous avez entre %d \n", resultat);
    resultat = a * b;
    gestionReponse(resultat, score);
}


void table_multi(int *score){
    int resultat;
    int taille;

    printf("Choisissez la taille de la table de multiplication\t");
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
    printf("Voulez-vous remplir une colonne par vous meme ? (1=Oui,0=Non)\t");
    scanf("%d", &resultat);
    if (resultat == 1)
    {
        int colonne;
        printf("Entrez le numero de la colonne (1 à %d)\t", taille);
        scanf("%d", &colonne);
        if (colonne < 1 || colonne > taille)
        {
            printf("Numero de colonne invalide.\n");
            return;
        }
        for (int i = 1; i <= taille; i++)
        {
            int reponse_utilisateur;
            printf("Quel est le resultat de %d * %d ?\t", i, colonne);
            scanf("%d", &reponse_utilisateur);
            if (reponse_utilisateur == i * colonne)
            {
                printf("Bravo !\n");
                (*score)++;
            }
            else
            {
                printf("Désole, la bonne réponse est %d.\n", i * colonne);
            }
        }
    }
}


void enregistrerScore(const char *nom, int score) {
    FILE *fichier = fopen("score/scores.csv", "a"); 
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier des scores.\n");
        return;
    }



}

int enregistrerScore() {
    FILE *fichier = fopen("score.txt","a");
    if (fichier == NULL){
        printf("Erreur d'ouverture du fichier.\n");
        return 0;
    }


}


int main(){
    char nom[25];
    char choix;
    int score = 0;
    int terminer = 0;

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
            case '0':
                printf("Merci d'avoir joué ! Votre score final est : %d\n", score);
                terminer = enregistrerScore();
                if (terminer == 1){ 
                    printf("%d",&score);
                    return 0;
                }
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
