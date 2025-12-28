/**
 * \file save.c
 * \date 17/12/2025
 * \brief Contenu des méthodes concernant la sauvegardes des parties ainsi que la sauvegarde des différents classements
 * \author Johann Levi-Valensi
 */

// Inclusion des entetes
#include "save.h"


// sauvegarder
int sauvegarder(plateau table, char* str_pseudo, int* pint_temps) {
    FILE* pfil_fic; // Descripteur de fichier
    size_t int_nb; // Nombre pour le getline
    char* str_nomSauv; // Nom de la sauvegarde + chemin
    char* tmp; // Chaine temporaire
    int i; // Variable d'incrémentation
    int j; // Variable d'incrémentation
    int int_retour; // Valeur de retour des fonctions utilisées
    int* pint_donneesPlat; // Tableau contenant les données du plateau de jeu

    // Création d'une chaine temporaire pour corriger les défauts du getline de demineur.c
    tmp = malloc(strlen(str_pseudo)*sizeof(char) - sizeof(char));
    if (tmp == NULL) {
        fprintf(stderr, "Erreur d'allocation !\n");
        return ERREUR_ALLOC;
    }

    i = 0;
    while (str_pseudo[i] != '\n') {
        tmp[i] = str_pseudo[i];
        i++;
    }
    tmp[i] = '\0';

    str_nomSauv = malloc(strlen(tmp)*sizeof(char) + 14*sizeof(char));
    if (str_nomSauv == NULL) {
        fprintf(stderr, "Erreur d'allocation !\n");
        return ERREUR_ALLOC;
    }

    strcpy(str_nomSauv, "./usrsave/");
    strcat(str_nomSauv, tmp);
    strcat(str_nomSauv, ".dmn");


    // Ouverture du fichier
    pfil_fic = fopen(str_nomSauv, "w+");
    if (pfil_fic == NULL) {
        fprintf(stderr, "Erreur d'ouverture du fichier\n");
        return ERREUR_OUVERTURE;
    }

    // Donnees du plateau
    pint_donneesPlat = malloc(3*sizeof(int));
    if (pint_donneesPlat == NULL) {
        fprintf(stderr, "Erreur d'allocqtion.\n");
        return ERREUR_ALLOC;
    }

    pint_donneesPlat[0] = table.int_hauteur;
    pint_donneesPlat[1] = table.int_largeur;
    pint_donneesPlat[2] = table.int_nbMine;

    // Ecriture dans le fichier
    // Paramètres du plateau
    int_retour = fwrite(pint_donneesPlat, sizeof(int), 3, pfil_fic);
    if (int_retour != 3) {
        fprintf(stderr, "Erreur d'écriture.\n");
        // Fermeture du fichier
        int_retour = fclose(pfil_fic);
        if (int_retour == EOF) {
            fprintf(stderr, "Erreur de fermeture.\n");
            return ERREUR_FERMETURE;
        }
        return ERREUR_ECRITURE;
    }

    // Etat de chaque cases du plateau
    for (i=0; i<table.int_hauteur; i++) {
        int_retour = fwrite(table.grille[i], sizeof(carreau), table.int_largeur, pfil_fic);
        if (int_retour != table.int_largeur) {
            fprintf(stderr, "Erreur d'écriture.\n");
            // Fermeture du fichier
            int_retour = fclose(pfil_fic);
            if (int_retour == EOF) {
                fprintf(stderr, "Erreur de fermeture.\n");                    
                return ERREUR_FERMETURE;
            }
                return ERREUR_ECRITURE;
        }
    }

    // Temps écoulé
    int_retour = fwrite(pint_temps, sizeof(int), 1, pfil_fic);
    if (int_retour != 1) {
        fprintf(stderr, "Erreur d'écriture.\n");
        // Fermeture du fichier
        int_retour = fclose(pfil_fic);
        if (int_retour == EOF) {
            fprintf(stderr, "Erreur de fermeture.\n");
            return ERREUR_FERMETURE;
        }
        return ERREUR_ECRITURE;
    }

    // Fermeture du fichier
    int_retour = fclose(pfil_fic);
    if (int_retour == EOF) {
        fprintf(stderr, "Erreur de fermeture.\n");
        return ERREUR_FERMETURE;
    }

    return 0;

}


// charger
plateau charger(char* str_pseudo, int* pint_temps) {
    plateau table; // Plateau a renvoyer
    FILE* pfil_fic; // Descripteur de fichier
    size_t int_nb; // Nombre pour le getline
    char* str_nomSauv; // Nom de la sauvegarde + chemin
    int i; // Variable d'incrémentation
    int j; // Variable d'incrémentation
    int int_retour; // Valeur de retour des fonctions utilisées
    int* pint_donneesPlat; // Tableau contenant les données du plateau de jeu

    
    str_nomSauv = malloc(strlen(str_pseudo)*sizeof(char) + 14*sizeof(char));
    if (str_nomSauv == NULL) {
        fprintf(stderr, "Erreur d'allocation (%d)\n", ERREUR_ALLOC);
    }

    strcpy(str_nomSauv, "./usrsave/");
    strcat(str_nomSauv, str_pseudo);
    strcat(str_nomSauv, ".dmn");
    

    // Ouverture du fichier
    pfil_fic = fopen(str_nomSauv, "r+");
    if (pfil_fic == NULL) {
        fprintf(stderr, "Erreur d'ouverture du fichier (%d)\n", ERREUR_OUVERTURE);
    }


    // Donnees du plateau
    pint_donneesPlat = malloc(3*sizeof(int));
    if (pint_donneesPlat == NULL) {
        fprintf(stderr, "Erreur d'allocation (%d)\n", ERREUR_ALLOC);
        // Fermeture du fichier
        int_retour = fclose(pfil_fic);
        if (int_retour == EOF) {
            fprintf(stderr, "Erreur de fermeture (%d)\n", ERREUR_FERMETURE);
        }
    }


    // Récupération des données de sauvegarde
    int_retour = fread(pint_donneesPlat, sizeof(int), 3, pfil_fic);
    if (int_retour != 3) {
        fprintf(stderr, "Erreur de lecture (%d)\n", ERREUR_LECTURE);
        // Fermeture du fichier
        int_retour = fclose(pfil_fic);
        if (int_retour == EOF) {
            fprintf(stderr, "Erreur de fermeture (%d)\n", ERREUR_FERMETURE);
        }
    }
    


    table = creerPlateau(pint_donneesPlat[1], pint_donneesPlat[0], pint_donneesPlat[2]);


    for (i=0; i<table.int_hauteur; i++) {
        int_retour = fread(table.grille[i], sizeof(carreau), table.int_largeur, pfil_fic);
        if (int_retour != table.int_largeur) {
            fprintf(stderr, "Erreur de lecture (%d)\n", ERREUR_LECTURE);
            // Fermeture du fichier
            int_retour = fclose(pfil_fic);
            if (int_retour == EOF) {
                fprintf(stderr, "Erreur de fermeture (%d)\n", ERREUR_FERMETURE);
            }
        }
    }

    int_retour = fread(pint_temps, sizeof(int), 1, pfil_fic);
    if (int_retour != 1) {
        fprintf(stderr, "Erreur de lecture (%d)\n", ERREUR_LECTURE);
        // Fermeture du fichier
        int_retour = fclose(pfil_fic);
        if (int_retour == EOF) {
            fprintf(stderr, "Erreur de fermeture (%d)\n", ERREUR_FERMETURE);
        }

    }

    printf("\nScore actuel:%d", *pint_temps);

    // Fermeture du fichier
    int_retour = fclose(pfil_fic);
    if (int_retour == EOF) {
        fprintf(stderr, "Erreur de fermeture (%d)\n", ERREUR_FERMETURE);
    }


    free(str_nomSauv);
    return table;
}


// enregistrerScore
int enregistrerScore(plateau table, char* str_pseudo, int int_temps) {
    FILE* pfil_fic; // Descripteur de fichier
    char* str_nom; // Nom du fichier
    char str_h[3]; // Hauteur du plateau
    char str_l[3]; // Largeur du plateau
    char str_m[3]; // Nombre de mines sur le plateau
    char str_temps[10]; // Score de partie
    int int_retour; // Valeur de retour


    // Creation du nom
    int_retour = sprintf(str_h, "%d", table.int_hauteur);
    if (int_retour != 2 && int_retour != 1) {
        fprintf(stderr, "Erreur\n");
        return int_retour;
    }

    int_retour = sprintf(str_l, "%d", table.int_largeur);
    if (int_retour != 2 && int_retour != 1) {
        fprintf(stderr, "Erreur\n");
        return int_retour;
    }

    int_retour = sprintf(str_m, "%d", table.int_nbMine);
    if (int_retour != 2 && int_retour != 1) {
        fprintf(stderr, "Erreur\n");
        return int_retour;
    }

    str_nom = malloc((strlen(str_h) + strlen(str_l) + strlen(str_m) + strlen("./ldb/") + strlen(".ldb") + 2) * sizeof(char));
    if (str_nom == NULL) {
        fprintf(stderr, "Erreur d'allocation\n");
        return ERREUR_ALLOC;
    }
    strcpy(str_nom, "./ldb/");
    strcat(str_nom, str_h);
    strcat(str_nom, "_");
    strcat(str_nom, str_l);
    strcat(str_nom, "_");
    strcat(str_nom, str_m);
    strcat(str_nom, ".ldb");    
    

    // Ouverture du fichier
    pfil_fic = fopen(str_nom, "a");
    if (pfil_fic == NULL) {
        fprintf(stderr, "Erreur d'ouverture\n");
        return ERREUR_OUVERTURE;
    }


    // Ecriture du score
    int_retour = fwrite(str_pseudo, sizeof(char), strlen(str_pseudo), pfil_fic);
    if (int_retour != strlen(str_pseudo)) {
        fprintf(stderr, "Erreur d'écriture\n");
        // Fermeture du fichier
        int_retour = fclose(pfil_fic);
        if (int_retour == EOF) {
            fprintf(stderr, "Erreur de fermeture\n");
            return ERREUR_FERMETURE;
        }
        return ERREUR_ECRITURE;
    }
    
    int_retour = sprintf(str_temps, "%d\n", int_temps);
    if (int_retour < 0) {
        fprintf(stderr, "Erreur\n");
        return int_retour;
    }

    int_retour = fwrite(str_temps, sizeof(char), strlen(str_temps), pfil_fic);
    if (int_retour != strlen(str_temps)) {
        fprintf(stderr, "Erreur d'écriture\n");
        // Fermeture du fichier
        int_retour = fclose(pfil_fic);
        if (int_retour == EOF) {
            fprintf(stderr, "Erreur de fermeture\n");
            return ERREUR_FERMETURE;
        }
        return ERREUR_ECRITURE;
    }
    
    free(str_nom);

    // Fermeture du fichier
    int_retour = fclose(pfil_fic);
    if (int_retour == EOF) {
        fprintf(stderr, "Erreur de fermeture.\n");
        return ERREUR_FERMETURE;
    }


    return 0;
}



// afficherTop
int afficherTop(int int_h, int int_l, int int_m) {
    joueur* TOP; // Liste de joueurs
    joueur* TOP_tmp; // Liste temporaire
    FILE* pfil_fic; // Descripteur de fichier
    char ligne[80];
    char* str_nom;
    char str_h[3]; // Hauteur du plateau
    char str_l[3]; // Largeur du plateau
    char str_m[3]; // Nombre de mines sur le plateau
    int i; // Variable d'incrémentation
    int j; // Variable d'incrémentation
    int k; // Variable d'incrémentation
    int compteur; // Compteur
    int int_nbJoueur; // nombre de joueurs
    int int_retour; // Valeur de retour
    int int_nbJoueur_reel;
    int int_doublon;

    int int_tmp;
    char str_tmp[80];
    

    // Creation du nom
    int_retour = sprintf(str_h, "%d", int_h);
    if (int_retour != 2 && int_retour != 1) {
        fprintf(stderr, "Erreur\n");
        return int_retour;
    }

    int_retour = sprintf(str_l, "%d", int_l);
    if (int_retour != 2 && int_retour != 1) {
        fprintf(stderr, "Erreur\n");
        return int_retour;
    }

    int_retour = sprintf(str_m, "%d", int_m);
    if (int_retour != 2 && int_retour != 1) {
        fprintf(stderr, "Erreur\n");
        return int_retour;
    }

    str_nom = malloc((strlen(str_h) + strlen(str_l) + strlen(str_m) + strlen("./ldb/") + strlen(".ldb") + 2) * sizeof(char));
    if (str_nom == NULL) {
        fprintf(stderr, "Erreur d'allocation\n");
        return ERREUR_ALLOC;
    }
    strcpy(str_nom, "./ldb/");
    strcat(str_nom, str_h);
    strcat(str_nom, "_");
    strcat(str_nom, str_l);
    strcat(str_nom, "_");
    strcat(str_nom, str_m);
    strcat(str_nom, ".ldb");    

    
    /* Compter le nombre de lignes du fichier */
    // Ouverture du fichier
    pfil_fic = fopen(str_nom, "r");
    if (pfil_fic == NULL) {
        fprintf(stderr, "Erreur d'ouverture\n");
        return ERREUR_OUVERTURE;
    }

    compteur = 0;
    while (fgets(ligne, 80, pfil_fic) != NULL) {
        compteur++;
    }
    int_nbJoueur = compteur/2;
    // Fermeture du fichier
    int_retour = fclose(pfil_fic);
    if (int_retour == EOF) {
        fprintf(stderr, "Erreur de fermeture.\n");
        return ERREUR_FERMETURE;
    }


    /* Récuperer les données */
    TOP = malloc(int_nbJoueur * sizeof(joueur));
    if (TOP == NULL) {
        fprintf(stderr, "Erreur d'allocation\n");
        return ERREUR_ALLOC;
    }

    // Ouverture du fichier
    pfil_fic = fopen(str_nom, "r");
    if (pfil_fic == NULL) {
        fprintf(stderr, "Erreur d'ouverture\n");
        return ERREUR_OUVERTURE;
    }

    // Recupération des données
    i=0;
    while (fgets(TOP[i].str_pseudo, 80, pfil_fic) != NULL && i < int_nbJoueur+1) {
        fgets(ligne, 80, pfil_fic);
        TOP[i].int_score = strtol(ligne, NULL, 10);
        i++;
    }

    /* Tri des joueurs par ordre croissant des scores */
    for (i=0; i<int_nbJoueur; i++) {
        for (j=i; j<int_nbJoueur; j++) {
            if (TOP[i].int_score > TOP[j].int_score) {

                strcpy(str_tmp, TOP[i].str_pseudo);
                int_tmp = TOP[i].int_score;

                strcpy(TOP[i].str_pseudo, TOP[j].str_pseudo);
                TOP[i].int_score = TOP[j].int_score;

                strcpy(TOP[j].str_pseudo, str_tmp);
                TOP[j].int_score = int_tmp;

            }
        }
    }


    /* Suppression des doubles */
    int_nbJoueur_reel = 0;
    for (i=0; i<int_nbJoueur; i++) {
        int_doublon = 0;
        for (j=0; j<int_nbJoueur_reel; j++) {
            if (strcmp(TOP[i].str_pseudo, TOP[j].str_pseudo) == 0) {
                int_doublon = 1;
                break;
            }
        }

        if (int_doublon == 0) {
            TOP[int_nbJoueur_reel] = TOP[i];
            int_nbJoueur_reel++;
        }
    }


    /* Affichage du classement */
    printf("\n=====Classement pour les dimensions %d %d %d=====", int_h, int_l, int_m);
    if (int_nbJoueur < 10) {
        for (i=0; i<int_nbJoueur_reel; i++) {
            printf("\n%de. Pseudo: %s Score: %d", i+1, TOP[i].str_pseudo, TOP[i].int_score);
        }

    } else {
        for (i=0; i<10; i++) {
            printf("\n%de. Pseudo: %s Score: %d", i+1, TOP[i].str_pseudo, TOP[i].int_score);
        }
    }

    // Fermeture du fichier
    free(TOP);
    free(str_nom);
    int_retour = fclose(pfil_fic);
    if (int_retour == EOF) {
        fprintf(stderr, "Erreur de fermeture\n");
        return ERREUR_FERMETURE;
    }
}
