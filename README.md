# TP3_ppm-INFO231-codeLAB-
code de manipulation des images ppm


/*
Organisation du travail

main.c :  PERROS

a) affiche le menu d'interpretation des commandes a utiliser dans le ppmviewer avec le 'help' pour la legende du menu 
b)  une boucle infini sur le ppmviewer>
c)Afficher la taille d’une image : size fichier.ppm
d) La commande quit permet de quitter l’application

NB : server du fichier test.c present dans le dossier pour realiser votre travail
 

fonction.c 1 :  ANTA 

 Foncer ou éclaircir toutes les pixels ayant une dominante rouge, bleu ou verte :
 dom c val fichier.ppm où dom est le nom de la commande, c est la couleur (elle a pour valeurs R, G ou B) 
 et val est l’entier à ajouter ou à retrancher. Si val< 0 alors il s’agira d’éclaircir l’image sinon il s’agira plutôt de la foncer.
 fichier.ppm est le nom du fichier à traiter.

 NB : server du fichier test.c present dans le dossier pour realiser votre travail
 

fonction.c 2 : ARTHUR

 Passer en noir et blanc : gris fichier.ppm

 NB : server du fichier test.c present dans le dossier pour realiser votre travail
 

fonction.c 3 : ELVIRA

 Découper une partie de l’image :
 cut fichier.ppm l1 l2 c1 c2 fichier_resultat.ppm
 Le traitement n’est exécuté que si les valeurs de l1, l2 , c1 et c2 sont bonnes ;   c’est-à-dire l1 < l2 ≤ hauteur et c1 < c2 ≤ largeur. 
 fichier_resultat.ppm    est le nom du fichier dans lequel sera sauvegardé l’image découpée.

 NB : server du fichier test.c present dans le dossier pour realiser votre travail
 

fonction.c 4 : REINE MERCIEL

 Créer le négatif d’une image : neg fichier.ppm fichier_resultat.ppm.

 NB : server du fichier test.c present dans le dossier pour realiser votre travail
 

fonction.c 5 : PERROS

 Appliquer à une image le filtre médian : fil fichier.ppm fichier_resultat.ppm.

NB : server du fichier test.c present dans le dossier pour realiser votre travail
 
*/
