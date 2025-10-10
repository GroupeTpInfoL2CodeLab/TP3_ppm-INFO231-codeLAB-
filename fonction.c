#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"

void sizeImage(const char *nomFichier) {
    FILE *fic = fopen(nomFichier, "r");
    if (!fic) {
        printf("Erreur : impossible d'ouvrir %s\n", nomFichier);
        return;
    }

    char format[3];
    int largeur, hauteur, max;
    fscanf(fic, "%2s", format);
    if (strcmp(format, "P3") != 0) {
        printf("Erreur : format non supporté (doit être P3)\n");
        fclose(fic);
        return;
    }

    fscanf(fic, "%d %d %d", &largeur, &hauteur, &max);
    printf("Taille de %s : %d x %d\n", nomFichier, largeur, hauteur);
    fclose(fic);
}

void foncer_ou_eclaircir(const char *nomFichier, char couleur, int valeur) {
    FILE *entree = fopen(nomFichier, "r");
    if (!entree) {
        printf("Erreur : impossible d'ouvrir %s\n", nomFichier);
        return;
    }

    char nomSortie[256];
    snprintf(nomSortie, sizeof(nomSortie), "%s_dom.ppm", nomFichier);

    FILE *sortie = fopen(nomSortie, "w");
    if (!sortie) {
        printf("Erreur : impossible de créer %s\n", nomSortie);
        fclose(entree);
        return;
    }

    char format[3];
    int largeur, hauteur, max;
    fscanf(entree, "%2s", format);
    if (strcmp(format, "P3") != 0) {
        printf("Erreur : format non supporté.\n");
        fclose(entree);
        fclose(sortie);
        return;
    }

    fscanf(entree, "%d %d %d", &largeur, &hauteur, &max);
    fprintf(sortie, "P3\n%d %d\n%d\n", largeur, hauteur, max);

    int r, g, b;
    while (fscanf(entree, "%d %d %d", &r, &g, &b) == 3) {
        if (couleur == 'R') r += valeur;
        else if (couleur == 'G') g += valeur;
        else if (couleur == 'B') b += valeur;

        if (r < 0) r = 0; if (r > max) r = max;
        if (g < 0) g = 0; if (g > max) g = max;
        if (b < 0) b = 0; if (b > max) b = max;

        fprintf(sortie, "%d %d %d\n", r, g, b);
    }

    fclose(entree);
    fclose(sortie);

    printf("✅ %s généré avec succès !\n", nomSortie);
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void help() {
    printf("\nCommandes disponibles :\n");
    printf("  dom R|G|B valeur fichier.ppm  - Fonce ou éclaircit les pixels dominants d'une couleur.\n");
    printf("  gris fichier.ppm              - Convertit l'image en niveaux de gris.\n");
    printf("  size fichier.ppm              - Affiche la taille de l'image (largeur x hauteur).\n");
    printf("  cut fichier.ppm l1 l2 c1 c2 fichier_resultat.ppm           - Découpe une portion de l'image.\n");
    printf("  neg fichier.ppm fichier_resultat.ppm                       - Crée le négatif de l'image.\n");
    printf("  fil fichier.ppm               - Applique un filtre médian 3x3 sur l'image.\n");
    printf("  clear                         - Nettoie l'écran.\n");
    printf("  man                           - Affiche ce manuel.\n");
    printf("  quit                          - Quitte l'application.\n");
}


void gris(const char *nomFichier) {
    FILE *entree = fopen(nomFichier, "r");
    if (!entree) {
        printf("Erreur : impossible d'ouvrir %s\n", nomFichier);
        return;
    }

    char nomSortie[256];
    snprintf(nomSortie, sizeof(nomSortie), "%s_gris.ppm", nomFichier);

    FILE *sortie = fopen(nomSortie, "w");
    if (!sortie) {
        printf("Erreur : impossible de créer %s\n", nomSortie);
        fclose(entree);
        return;
    }

    char format[3];
    int largeur, hauteur, max;
    fscanf(entree, "%2s", format);
    if (strcmp(format, "P3") != 0) {
        printf("Erreur : format non supporté.\n");
        fclose(entree);
        fclose(sortie);
        return;
    }

    fscanf(entree, "%d %d %d", &largeur, &hauteur, &max);
    fprintf(sortie, "P3\n%d %d\n%d\n", largeur, hauteur, max);

    int r, g, b;
    while (fscanf(entree, "%d %d %d", &r, &g, &b) == 3) {
        int gris = (r + g + b) / 3;  // moyenne simple
        fprintf(sortie, "%d %d %d\n", gris, gris, gris);
    }

    fclose(entree);
    fclose(sortie);

    printf("✅ Image convertie en niveaux de gris : %s\n", nomSortie);
}


void negatif(const char *nomFichier) {
    FILE *entree = fopen(nomFichier, "r");
    if (!entree) {
        printf("Erreur : impossible d'ouvrir %s\n", nomFichier);
        return;
    }

    char nomSortie[256];
    snprintf(nomSortie, sizeof(nomSortie), "%s_neg.ppm", nomFichier);

    FILE *sortie = fopen(nomSortie, "w");
    if (!sortie) {
        printf("Erreur : impossible de créer %s\n", nomSortie);
        fclose(entree);
        return;
    }

    char format[3];
    int largeur, hauteur, max;
    fscanf(entree, "%2s", format);
    if (strcmp(format, "P3") != 0) {
        printf("Erreur : format non supporté.\n");
        fclose(entree);
        fclose(sortie);
        return;
    }

    fscanf(entree, "%d %d %d", &largeur, &hauteur, &max);
    fprintf(sortie, "P3\n%d %d\n%d\n", largeur, hauteur, max);

    int r, g, b;
    while (fscanf(entree, "%d %d %d", &r, &g, &b) == 3) {
        fprintf(sortie, "%d %d %d\n", max - r, max - g, max - b);
    }

    fclose(entree);
    fclose(sortie);

    printf("✅ Négatif créé avec succès : %s\n", nomSortie);
}


void couper(const char *nomFichier, int l1, int l2, int c1, int c2, const char *nomSortie) {
    FILE *f = fopen(nomFichier, "r");
    if (!f) {
        printf("Erreur : impossible d'ouvrir %s\n", nomFichier);
        return;
    }

    char format[3];
    int largeur, hauteur, max;
    fscanf(f, "%2s", format);
    if (strcmp(format, "P3") != 0) {
        printf("Erreur : format non supporté (doit être P3)\n");
        fclose(f);
        return;
    }

    // Lire les dimensions et la valeur max
    fscanf(f, "%d %d %d", &largeur, &hauteur, &max);

    if (l1 < 1 || l2 > hauteur || c1 < 1 || c2 > largeur || l1 >= l2 || c1 >= c2) {
        printf("Erreur : coordonnées invalides.\n");
        fclose(f);
        return;
    }

    // Allocation mémoire
    int **R = malloc(hauteur * sizeof(int *));
    int **G = malloc(hauteur * sizeof(int *));
    int **B = malloc(hauteur * sizeof(int *));
    for (int i = 0; i < hauteur; i++) {
        R[i] = malloc(largeur * sizeof(int));
        G[i] = malloc(largeur * sizeof(int));
        B[i] = malloc(largeur * sizeof(int));
    }

    // Lecture des pixels
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            fscanf(f, "%d %d %d", &R[i][j], &G[i][j], &B[i][j]);
        }
    }
    fclose(f);

    int nouvH = l2 - l1 + 1;
    int nouvL = c2 - c1 + 1;

    FILE *out = fopen(nomSortie, "w");
    if (!out) {
        printf("Erreur : impossible de créer %s\n", nomSortie);
        return;
    }

    fprintf(out, "P3\n%d %d\n%d\n", nouvL, nouvH, max);

    for (int i = l1 - 1; i < l2; i++) {
        for (int j = c1 - 1; j < c2; j++) {
            fprintf(out, "%d %d %d\n", R[i][j], G[i][j], B[i][j]);
        }
    }

    fclose(out);

    // Libération mémoire
    for (int i = 0; i < hauteur; i++) {
        free(R[i]);
        free(G[i]);
        free(B[i]);
    }
    free(R);
    free(G);
    free(B);

    printf("✅ Découpage réussi : %s créé.\n", nomSortie);
}


void filtreMedian(const char *nomFichier) {
    FILE *f = fopen(nomFichier, "r");
    if (!f) {
        printf("Erreur : impossible d'ouvrir %s\n", nomFichier);
        return;
    }

    char format[3];
    int largeur, hauteur, max;
    fscanf(f, "%2s", format);
    if (strcmp(format, "P3") != 0) {
        printf("Erreur : format non supporté (doit être P3)\n");
        fclose(f);
        return;
    }

    fscanf(f, "%d %d %d", &largeur, &hauteur, &max);

    int **R = malloc(hauteur * sizeof(int *));
    int **G = malloc(hauteur * sizeof(int *));
    int **B = malloc(hauteur * sizeof(int *));
    int **Rout = malloc(hauteur * sizeof(int *));
    int **Gout = malloc(hauteur * sizeof(int *));
    int **Bout = malloc(hauteur * sizeof(int *));
    for (int i = 0; i < hauteur; i++) {
        R[i] = malloc(largeur * sizeof(int));
        G[i] = malloc(largeur * sizeof(int));
        B[i] = malloc(largeur * sizeof(int));
        Rout[i] = malloc(largeur * sizeof(int));
        Gout[i] = malloc(largeur * sizeof(int));
        Bout[i] = malloc(largeur * sizeof(int));
    }

    for (int i = 0; i < hauteur; i++)
        for (int j = 0; j < largeur; j++)
            fscanf(f, "%d %d %d", &R[i][j], &G[i][j], &B[i][j]);
    fclose(f);

    int voisinsR[9], voisinsG[9], voisinsB[9];
    int k;

    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            k = 0;
            for (int dy = -1; dy <= 1; dy++) {
                int y = i + dy;
                if (y < 0) y = 0;
                if (y >= hauteur) y = hauteur - 1;
                for (int dx = -1; dx <= 1; dx++) {
                    int x = j + dx;
                    if (x < 0) x = 0;
                    if (x >= largeur) x = largeur - 1;
                    voisinsR[k] = R[y][x];
                    voisinsG[k] = G[y][x];
                    voisinsB[k] = B[y][x];
                    k++;
                }
            }
            // Tri bubble sort pour la médiane
            for (int a = 0; a < 8; a++)
                for (int b = 0; b < 8 - a; b++) {
                    if (voisinsR[b] > voisinsR[b + 1]) { int t=voisinsR[b]; voisinsR[b]=voisinsR[b+1]; voisinsR[b+1]=t; }
                    if (voisinsG[b] > voisinsG[b + 1]) { int t=voisinsG[b]; voisinsG[b]=voisinsG[b+1]; voisinsG[b+1]=t; }
                    if (voisinsB[b] > voisinsB[b + 1]) { int t=voisinsB[b]; voisinsB[b]=voisinsB[b+1]; voisinsB[b+1]=t; }
                }
            Rout[i][j] = voisinsR[4];
            Gout[i][j] = voisinsG[4];
            Bout[i][j] = voisinsB[4];
        }
    }

    char sortie[120];
    sprintf(sortie, "%s_fil.ppm", nomFichier);
    FILE *out = fopen(sortie, "w");
    if (!out) {
        printf("Erreur : impossible de créer %s\n", sortie);
        return;
    }

    fprintf(out, "P3\n%d %d\n%d\n", largeur, hauteur, max);
    for (int i = 0; i < hauteur; i++)
        for (int j = 0; j < largeur; j++)
            fprintf(out, "%d %d %d\n", Rout[i][j], Gout[i][j], Bout[i][j]);
    fclose(out);

    for (int i = 0; i < hauteur; i++) {
        free(R[i]); free(G[i]); free(B[i]);
        free(Rout[i]); free(Gout[i]); free(Bout[i]);
    }
    free(R); free(G); free(B);
    free(Rout); free(Gout); free(Bout);

    printf("✅ Filtre médian appliqué sur tous les pixels : %s créé.\n", sortie);
}
