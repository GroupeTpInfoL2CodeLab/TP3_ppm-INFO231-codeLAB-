#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"

int main() {
    char commande[10];
    char couleur;
    int valeur;
    char nomFichier[100];

    printf("\n\t***********************************************\n");
    printf("\t| Application de manipulation d'image PPM !!  |\n");
    printf("\t***********************************************\n\n");
    printf("Tape 'man' pour afficher le manuel des commandes.\n\n");

    while (1) {
        printf("\nppmviewer> ");
        int nbLus = scanf("%9s", commande);
        if (nbLus != 1)
            continue;

        if (strcmp(commande, "size") == 0) {
            scanf("%99s", nomFichier);
            sizeImage(nomFichier);
        }

        else if (strcmp(commande, "gris") == 0) {
            scanf("%99s", nomFichier);
            gris(nomFichier);
        }

        else if (strcmp(commande, "dom") == 0) {
            scanf(" %c %d %99s", &couleur, &valeur, nomFichier);
            foncer_ou_eclaircir(nomFichier, couleur, valeur);
        }
        else if (strcmp(commande, "man") == 0) {
            help();
        }
        else if (strcmp(commande, "neg") == 0) {
            scanf("%49s", nomFichier);
            negatif(nomFichier);
        }

        else if (strcmp(commande, "cut") == 0) {
            int l1, l2, c1, c2;
            char fichier[50], resultat[50];

        if (scanf("%49s %d %d %d %d %49s", fichier, &l1, &l2, &c1, &c2, resultat) == 6)
            couper(fichier, l1, l2, c1, c2, resultat);
        else
            printf("Usage : cut fichier.ppm l1 l2 c1 c2 resultat.ppm\n");
        }
        else if (strcmp(commande, "fil") == 0) {
            if (scanf("%49s", nomFichier) == 1)
                filtreMedian(nomFichier);
            else
            printf("Usage : fil fichier.ppm\n");
        }


        else if (strcmp(commande, "clear") == 0) {
            system("clear");
        }
        else if (strcmp(commande, "quit") == 0) {
            printf("Fermeture de l'application...\n");
            break;
        }
        else {
            printf("Commande invalide, essaye encore.\n");
        }
    }

    return 0;
}
