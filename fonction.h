#ifndef FONCTION_H
#define FONCTION_H

void afficherInvite();

void sizeImage(const char* nomFichier);

void foncer_ou_eclaircir(const char *nom_fichier, char couleur, int val);

void gris(const char *nomFichier);

void negatif(const char *nomFichier);

void couper(const char *nomFichier, int l1, int l2, int c1, int c2, const char *nomSortie);

void filtreMedian(const char *nomFichier);

void help();

void clear();

#endif
