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


char menuEnregistrement(int *nom,int *score, int lignejoeur) 
{
    char choix;

    while (1==1)
    {
        printf("Bienvenue dans le jeu Champion des Maths !\n");
        printf("+-----------------------------------+\n|1 : Se connecter                   |\n|   (avec un nom d'utilisateur)     |\n|2 : ne pas se connecter            |\n+-----------------------------------+\nQuel est votre choix ?  ");
        scanf(" %c", &choix);

        while (getchar() != '\n');

        switch (choix)
        {
            case '1':
                printf("Entrez votre nom d'utilisateur :  ");
                scanf("%s", nom); 
                
                if (lectureScore(nom,score,lignejoeur) == 0) 
                {
                    printf("Erreur, le score n'a pas pu être trouvé (verifiez bien que le nom d'utilisateur soit le meme).\n\n");
                    break;                     
                }
                return; 
            case '2':
                do {
                    printf("Entrez votre nom d'utilisateur : (ce nom doit être unique)  ");
                    scanf("%s", nom); 
                    if (verifJoueur(nom) == 1) {
                        printf("Ce nom d'utilisateur existe deja. Veuillez en choisir un autre.\n");
                    }
                } while (verifJoueur(nom) == 1);
                
                *score = 0; 
                return choix; 
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
        }
        
    }
}


int verifJoueur(char *nom_joueur) {    
    FILE *fichier = fopen("score/score.txt", "r");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return 1;
    }

    char ligne[256];
    int nom_trouve = 0;

    while (fgets(ligne, sizeof(ligne), fichier)) {
        
        char ligne_copy[256];
        strcpy(ligne_copy, ligne);
        
        
        char *nom = strtok(ligne_copy, ",");

        if (strcmp(nom, nom_joueur) == 0) {
            nom_trouve = 1;
            break;
        }
    }

    fclose(fichier);
    return nom_trouve; 
}


int lectureScore(char *nom_joueur, int *score_joueur, int *lignejoueur) {    
    FILE *fichier = fopen("score/score.txt", "r");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    char ligne[256];
    int score_trouve = 0;
    int ligne_courante = 0;  

    while (fgets(ligne, sizeof(ligne), fichier)) {
        
        char ligne_copy[256];
        strcpy(ligne_copy, ligne);
        
        
        char *nom = strtok(ligne_copy, ",");
        char *score_str = strtok(NULL, ",");
        char *date = strtok(NULL, "\n");

        if (nom && score_str && date) {
            if (strcmp(nom, nom_joueur) == 0) {
                *score_joueur = atoi(score_str);
                printf("Score trouvé pour %s le %s : %d\n", nom_joueur, date, *score_joueur);
                score_trouve = 1;
                break;
            }
        }
        ligne_courante++; 
    }
    *lignejoueur = ligne_courante;  

    fclose(fichier);
    return score_trouve; 
}


int enregistrerScore(char *nom_joueur, int score,int lignejoueur) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    if (lignejoueur == -1) 
    {
        FILE *fichier = fopen("score/score.txt", "a"); 
        if (fichier == NULL) {
            printf("Erreur d'ouverture du fichier.\n");
            return 0;
        }
        
        fprintf(fichier,"%s,%d,%02d/%02d/%04d à %02dh%02d\n",nom_joueur, score,tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,tm.tm_hour, tm.tm_min);
        fclose(fichier);
    }
    else 
    {
        FILE *fichier = fopen("score/score.txt", "r+"); 
        if (fichier == NULL) {
            printf("Erreur d'ouverture du fichier.\n");
            return 0;
        }
        
        char ligne[256];
        int ligne_courante = 0;  

        while (fgets(ligne, sizeof(ligne), fichier)) {
            if (ligne_courante == lignejoueur) { 
                fseek(fichier, -strlen(ligne)-1, SEEK_CUR);
                fprintf(fichier,"%s,%d,%02d/%02d/%04d à %02dh%02d\n",nom_joueur,score,tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,tm.tm_hour, tm.tm_min);
                fclose(fichier);
                return 1; 
            }
            ligne_courante++; 
        }

        fclose(fichier);
    }
}


int main(){
    char nom[25];
    char choix;
    int score = 0;
    int terminer = 0;
    int lignejoueur = -1;

    menuEnregistrement(nom,&score,&lignejoueur);
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
                if (enregistrerScore(nom, score,lignejoueur)){ 
                    printf("Score enregistré");
                    return 0;
                }
                else {
                    printf("Erreur\n");
                    return 1;
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
