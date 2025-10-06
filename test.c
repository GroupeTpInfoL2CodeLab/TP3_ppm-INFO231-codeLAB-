#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CMD 256
#define MAX_FILENAME 128

// Prototype des fonctions
void afficher_invite();
void commande_size(const char *filename);
void commande_dom(const char *color, int val, const char *filename);
void aide();

int main() {
    char commande[MAX_CMD];

    printf("Application de traitement d'images PPM réalisée par Perros.\n");

    while (1) {
        afficher_invite();
        if (!fgets(commande, sizeof(commande), stdin))
            break;

        // Supprimer le \n à la fin
        commande[strcspn(commande, "\n")] = 0;

        // Quitter
        if (strcmp(commande, "quit") == 0) {
            printf("Fermeture de ppmviewer...\n");
            break;
        }

        // Exemple : size image1.ppm
        if (strncmp(commande, "size ", 5) == 0) {
            char filename[MAX_FILENAME];
            if (sscanf(commande + 5, "%s", filename) == 1)
                commande_size(filename);
            else
                printf("Usage : size <nom_fichier.ppm>\n");
        }

        // Exemple : dom R 4 image.ppm
        else if (strncmp(commande, "dom ", 4) == 0) {
            char color;
            int val;
            char filename[MAX_FILENAME];
            if (sscanf(commande + 4, "%c %d %s", &color, &val, filename) == 3)
                commande_dom(&color, val, filename);
            else
                printf("Usage : dom <R|G|B> <valeur> <fichier.ppm>\n");
        }

        else if (strcmp(commande, "help") == 0)
            aide();

        else
            printf("Commande inconnue. Tapez 'help' pour la liste.\n");
    }

    return 0;
}

void afficher_invite() {
    printf("ppmviewer > ");
}

// Affiche la taille de l'image
void commande_size(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Fichier non trouvé : %s\n", filename);
        return;
    }

    char format[3];
    int width, height, maxval;
    fscanf(f, "%2s", format);
    if (strcmp(format, "P3") != 0) {
        printf("Format non supporté (doit être P3)\n");
        fclose(f);
        return;
    }

    fscanf(f, "%d %d %d", &width, &height, &maxval);
    printf("%d x %d\n", width, height);

    fclose(f);
}

// Fait varier la dominance de couleur (foncer / éclaircir)
void commande_dom(const char *color, int val, const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Fichier non trouvé : %s\n", filename);
        return;
    }

    char format[3];
    int width, height, maxval;
    fscanf(f, "%2s", format);
    fscanf(f, "%d %d %d", &width, &height, &maxval);

    int r, g, b;

    // Prépare le nouveau nom de fichier
    char output_name[256];
    snprintf(output_name, sizeof(output_name), "%s_dom.ppm", filename);

    FILE *out = fopen(output_name, "w");
    if (!out) {
        printf("Erreur : impossible de créer %s\n", output_name);
        fclose(f);
        return;
    }

    fprintf(out, "P3\n%d %d\n%d\n", width, height, maxval);

    // Lecture et modification pixel par pixel
    while (fscanf(f, "%d %d %d", &r, &g, &b) == 3) {
        if (*color == 'R' || *color == 'r') r += val;
        if (*color == 'G' || *color == 'g') g += val;
        if (*color == 'B' || *color == 'b') b += val;

        // Clamp entre 0 et maxval
        if (r < 0) r = 0; if (r > maxval) r = maxval;
        if (g < 0) g = 0; if (g > maxval) g = maxval;
        if (b < 0) b = 0; if (b > maxval) b = maxval;

        fprintf(out, "%d %d %d\n", r, g, b);
    }

    fclose(f);
    fclose(out);
    printf("opération effectuée ; %s créé\n", output_name);
}

void aide() {
    printf("Commandes disponibles :\n");
    printf(" size <fichier.ppm>              : affiche la taille de l'image\n");
    printf(" dom <R|G|B> <val> <fichier.ppm> : ajuste la dominance de couleur\n");
    printf(" quit                            : quitter le programme\n");
}
