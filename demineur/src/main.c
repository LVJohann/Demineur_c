/**
 * \file main.c
 * \brief Fichier main du démineur
 * \date 10/12/2025
 * \author Johann Levi-Valensi
 */

//Importation des entetes
#include "demineur.h"


/**
 * \fn int main (int argc, char** argv )
 *
 * \version 0.1 Première version
 *  
 * \param argc :nombre d'arguments en entree
 * \param argv :valeur des arguments en entree
 * \return 0   : le programme se termine normalement
 */

int main(int argc, char** argv) {
    plateau grille;
    int int_etatJeu;
    int int_nbTour;
    int* pint_nbTour;
    int int_tempsInit;
    int int_tempsFinal;
    int int_tempsPrec;
    int int_retour;


    pint_nbTour = &int_nbTour;
    int_nbTour = 0;

    // Initialisation de la suite aleatoire
    srand(time(NULL));


    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        printf("\n====================Aide====================");
        printf("\nAvant la partie:");
        printf("\nExecuter le programme sans argument permet de jouer au démineur avec les paramètres de base:");
        printf("\n\tTaille: 8x8, nombre de mines: 10");
        printf("\n\nPour créer une partie avec une taille personalisée, éxecuter le programme de la manière suivante (max 45x45):");
        printf("\n\t\"./TP10 -c [hauteur] [largeur] [nombre de mines]\"");
        printf("\n\nPour charger une partie: éxecuter le programme de la manière suivante:");
        printf("\n\t\"./TP10 -s [nom de la sauvegarde]\"");
        printf("\n\nPour afficher le tableau des scores pour une taille donnée, éxecuter le programme de la manière suivante:");
        printf("\n\t\"./TP10 -l [hauteur] [largeur] [nombre de mines]\"");

        printf("\n\n\nDans une partie:");
        printf("\nPour jouer, voici les différentes commandes à entrer:");
        printf("\nPour dévoiler une case, écrire: \n\t\"d [ligne] [colonne]\"");
        printf("\nPour placer un drapeau 🚩 sur une case, écrire: \n\t\"f [ligne] [colonne]\"");
        printf("\nPour sauvegarder, écrire: \n\t\"save\"");
        printf("\nPour quitter, écrire: \n\t\"quit\"\n");

    } else if (argc == 1) {
        grille = creerPlateau(8, 8, 10);
        initPlateau(grille);
        int_etatJeu = 1;
        int_tempsPrec = 0;

        while (int_etatJeu != 0) {
            tourDeJeu(grille, &int_etatJeu, pint_nbTour, &int_tempsInit, &int_tempsFinal, &int_tempsPrec);
        }

    } else if (argc == 5 && strcmp(argv[1], "-c") == 0) {
        grille = creerPlateau(strtol(argv[3], NULL, 10), strtol(argv[2], NULL, 10), strtol(argv[4], NULL, 10));
        initPlateau(grille);
        int_etatJeu = 1;
        int_tempsPrec = 0;

        while (int_etatJeu != 0) {
            tourDeJeu(grille, &int_etatJeu, pint_nbTour, &int_tempsInit, &int_tempsFinal, &int_tempsPrec);
        }


    } else if (argc == 3 && strcmp(argv[1], "-s") == 0) {
        grille = charger(argv[2], &int_tempsPrec);
        if (int_retour != 0) {
            printf("Erreur de chargement de la sauvegarde (%d)", int_retour);
            return int_retour;
        }
    
        int_etatJeu = 1;
        while (int_etatJeu != 0) {
            tourDeJeu(grille, &int_etatJeu, pint_nbTour, &int_tempsInit, &int_tempsFinal, &int_tempsPrec);
        }


    } else if (argc == 5 && strcmp(argv[1], "-l") == 0) {
        printf("\nLeaderboard");
        int_retour = afficherTop(strtol(argv[2], NULL, 10), strtol(argv[3], NULL, 10), strtol(argv[4], NULL, 10));
        if (int_retour != 0) {
            fprintf(stderr, "Erreur d'affichage du classement");
            return -5;
        }

    } else {
        printf("\nErreur d'argument ! Entrez \"./TP10 --help\" pour plus d'inforations.\n");
        return ERREUR_ARG;

    }

    // Le programme s'est exécuté correctement
    printf("\nFermeture du programme...\n");
    return (0);
}
