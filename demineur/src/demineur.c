/**
 * \file demineur.c
 * \date 10/12/2025
 * \brief Fichier contenant les fonctions liées au démineur
 * \author Johann Levi-Valensi
 */

// Inclusion des entetes
#include "demineur.h"


// creerPlateau
plateau creerPlateau(int int_nbColonne, int int_nbLigne, int int_nbMine) {   
    plateau table; // Plateau de jeu
    int i; // Variable d'incrementation

    if (int_nbMine > int_nbColonne*int_nbLigne) {
        fprintf(stderr, "\nErreur, il y a plus de mines que de cases !");
        exit(-3);
    }

    // Definition de la taille du plateau
    table.int_hauteur = int_nbLigne;
    table.int_largeur = int_nbColonne;

    // Definition du nombre de mines
    table.int_nbMine = int_nbMine;

    // Allocation de l'espace mémoire pour le plateau
    // D'abord les lignes
    table.grille = malloc(table.int_hauteur*sizeof(carreau*));
    if (table.grille == NULL) {
        fprintf(stderr, "Erreur d'allocation !\n");
        exit(ERREUR_ALLOC);
    }

    // Puis les colonnes
    for (i=0; i<table.int_hauteur; i++) {
        table.grille[i] = malloc(table.int_largeur*sizeof(carreau));
        if (table.grille[i] == NULL) {
            fprintf(stderr, "Erreur d'allocation !\n");
            exit(ERREUR_ALLOC);
        }
    }

    return table;
}


// nbMines
void nbMines(plateau table) {
    int i; // Variable d'incrementation
    int j; // Variable d'incrementation
    int int_nbMine; // Nombre de mines autour d'une case

    // Recherche pour chaque case du nombre de mines autour
    /*
        Pour le cas des coins, on regarde les 3 cases autour
        Pour le cas des bords hors coin, on regarde les 5 autour
        Pour le cas central, on regarde les 8 cases autour
    */
    for (i=0; i<table.int_hauteur; i++) {
        for (j=0; j<table.int_largeur; j++) {
            int_nbMine = 0; // Nombre de mines autour de la case [i][j]



            // Cas si la case [i][j] est une bombe
            if (table.grille[i][j].int_etatMine == 1) {
                table.grille[i][j].int_nbMine == -1;
            } else {

                // Cas de la bordure superieure
                if (i == 0) {
                    if (j == 0) { // Cas du coin superieur gauche
                        if (table.grille[i][j+1].int_etatMine == 1) {
                            int_nbMine++;
                        }
                        if (table.grille[i+1][j].int_etatMine == 1) {
                            int_nbMine++;
                        }
                        if (table.grille[i+1][j+1].int_etatMine == 1) {
                            int_nbMine++;
                        }

                    } else if (j == table.int_largeur-1) {  // Cas du coin superieur droit
                        if (table.grille[i][j-1].int_etatMine == 1) {
                            int_nbMine++;
                        }
                        if (table.grille[i+1][j].int_etatMine == 1) {
                            int_nbMine++;
                        }
                        if (table.grille[i+1][j-1].int_etatMine == 1) {
                            int_nbMine++;
                        }

                    } else { // Le reste
                        if (table.grille[i][j-1].int_etatMine == 1) {
                            int_nbMine++;
                        }
                        if (table.grille[i][j+1].int_etatMine == 1) {
                            int_nbMine++;
                        }
                        if (table.grille[i+1][j-1].int_etatMine == 1) {
                            int_nbMine++;
                        }
                        if (table.grille[i+1][j].int_etatMine == 1) {
                            int_nbMine++;
                        }
                        if (table.grille[i+1][j+1].int_etatMine == 1) {
                            int_nbMine++;
                        }
                    }
                }


                // Cas de la bordure inferieure
                if (i == table.int_hauteur-1) {
                    if (j == 0) { // Cas du coin inferieur gauche
                        if (table.grille[i][j+1].int_etatMine == 1) {
                            int_nbMine++;
                        }
                        if (table.grille[i-1][j].int_etatMine == 1) {
                            int_nbMine++;
                        }
                        if (table.grille[i-1][j+1].int_etatMine == 1) {
                            int_nbMine++;
                        }

                    } else if (j == table.int_largeur-1) { // Cas du coin inferieur droit 
                        if (table.grille[i][j-1].int_etatMine == 1) {
                            int_nbMine++;
                        }
                        if (table.grille[i-1][j].int_etatMine == 1) {
                            int_nbMine++;
                        }
                        if (table.grille[i-1][j-1].int_etatMine == 1) {
                            int_nbMine++;
                        }

                    } else { // Le reste
                        if (table.grille[i][j-1].int_etatMine == 1) {
                            int_nbMine++;
                        }
                        if (table.grille[i][j+1].int_etatMine == 1) {
                            int_nbMine++;
                        }
                        if (table.grille[i-1][j-1].int_etatMine == 1) {
                            int_nbMine++;
                        }
                        if (table.grille[i-1][j].int_etatMine == 1) {
                            int_nbMine++;
                        }
                        if (table.grille[i-1][j+1].int_etatMine == 1) {
                            int_nbMine++;
                        }
                    }
                }

                /*
                    Les cas des 4 coins ont étés vérifiés
                    Il faut maintenant vérifier les bordures de gauche et de droite, coins exclus
                */
                
                // Bordure de gauche
                if (j == 0 && i > 0 && i < table.int_hauteur-1) {
                    if (table.grille[i-1][j].int_etatMine == 1) {
                        int_nbMine++;
                    }
                    if (table.grille[i+1][j].int_etatMine == 1) {
                        int_nbMine++;
                    }
                    if (table.grille[i-1][j+1].int_etatMine == 1) {
                        int_nbMine++;
                    }
                    if (table.grille[i+1][j+1].int_etatMine == 1) {
                        int_nbMine++;
                    }
                    if (table.grille[i][j+1].int_etatMine == 1) {
                        int_nbMine++;
                    }

                // Bordure de droite
                } else if (j == table.int_largeur-1 && i > 0 && i < table.int_hauteur-1) {
                    if (table.grille[i-1][j].int_etatMine == 1) {
                        int_nbMine++;
                    }
                    if (table.grille[i+1][j].int_etatMine == 1) {
                        int_nbMine++;
                    }
                    if (table.grille[i-1][j-1].int_etatMine == 1) {
                        int_nbMine++;
                    }
                    if (table.grille[i+1][j-1].int_etatMine == 1) {
                        int_nbMine++;
                    }
                    if (table.grille[i][j-1].int_etatMine == 1) {
                        int_nbMine++;
                    }
                }

                // Cas central
                if ((i > 0 && i < table.int_hauteur-1) && (j > 0 && j < table.int_largeur-1)) {
                    if (table.grille[i-1][j-1].int_etatMine == 1) {
                        int_nbMine++;
                    }
                    if (table.grille[i-1][j].int_etatMine == 1) {   
                        int_nbMine++;
                    }
                    if (table.grille[i-1][j+1].int_etatMine == 1) {
                        int_nbMine++;
                    }
                    if (table.grille[i][j-1].int_etatMine == 1) {
                        int_nbMine++;
                    }
                    if (table.grille[i][j+1].int_etatMine == 1) {
                        int_nbMine++;
                    }
                    if (table.grille[i+1][j-1].int_etatMine == 1) {
                        int_nbMine++;
                    }
                    if (table.grille[i+1][j].int_etatMine == 1) {
                        int_nbMine++;
                    }
                    if (table.grille[i+1][j+1].int_etatMine == 1) {
                        int_nbMine++;
                    }
                }



                // Affectation du nombre de bombes
                table.grille[i][j].int_nbMine = int_nbMine;

            }
        }
    }
}

// initPlateau
void initPlateau(plateau table) {
    int i; // Variable d'incrementation
    int j; // Variable d'incrementation
    int int_x; // Position en x (largeur)
    int int_y; // Position en y (hauteur)
    int int_nbMine; // Nombre de mines


    // Initialisation de l'etat de la case et de l'etat de la mine sur la case
    for (i=0; i<table.int_hauteur; i++) {
        for (j=0; j<table.int_largeur; j++) {
            table.grille[i][j].etat_case = MASQUEE;
            table.grille[i][j].int_etatMine = 0;
        }
    }


    // Assignation des mines aux cases
    int_nbMine = 0; // Nombre de mines placées sur le plateau
    while (int_nbMine < table.int_nbMine) {
        int_x = rand() % table.int_largeur;
        int_y = rand() % table.int_hauteur;
        
        if (table.grille[int_y][int_x].int_etatMine == 0) {
            table.grille[int_y][int_x].int_etatMine = 1;
            int_nbMine++;
        }
    }

    // Affectation du nombre de mines autour de la case
    nbMines(table);
}


// interface
void interface(plateau table) {
    int i;
    int j;
    int int_nbDrapeau;

    printf("\n  ");
    for (j=0; j<table.int_largeur; j++) {
        if (j < 9) {
            printf("  %d ", j+1);
        } else {
            printf(" %d ", j+1);
        }
    }
    
    for (i=0; i<table.int_hauteur; i++) {
        printf("\n  ");

        for (int k=0; k<table.int_largeur; k++) {
            printf("|---");
        }
        if (i < 9) {
            printf("|\n%d |", i+1);        
        } else {
            printf("|\n%d|", i+1);
        }
        
        for (j=0; j<table.int_largeur; j++) {
            if (table.grille[i][j].etat_case == MASQUEE) {
                printf(" # |"); 
            
            } else if (table.grille[i][j].etat_case == DEVOILEE) {
                if (table.grille[i][j].int_etatMine == 1) { // Affichage des mines dévoilées
                    printf("💥 |");
                } else {
                    switch (table.grille[i][j].int_nbMine) { // Affichage du nombre de mines aux alentours, changement de couleurs selon le nombre de mines
                    case 0:
                        printf(" %d |", table.grille[i][j].int_nbMine);
                        break;

                    case 1:
                        printf("\x1b[1;34m");
                        printf(" %d", table.grille[i][j].int_nbMine);
                        printf("\x1b[0m");
                        printf(" |");
                        break;

                    case 2:
                        printf("\x1b[1;32m");
                        printf(" %d", table.grille[i][j].int_nbMine);
                        printf("\x1b[0m");
                        printf(" |");
                        break;

                    case 3:
                        printf("\x1b[1;31m");
                        printf(" %d", table.grille[i][j].int_nbMine);
                        printf("\x1b[0m");
                        printf(" |");
                        break;

                    case 4:
                        printf("\x1b[1;35m");
                        printf(" %d", table.grille[i][j].int_nbMine);
                        printf("\x1b[0m");
                        printf(" |");
                        break;

                    case 5:
                        printf("\x1b[1;33m");
                        printf(" %d", table.grille[i][j].int_nbMine);
                        printf("\x1b[0m");
                        printf(" |");
                        break;

                    case 6:
                        printf("\x1b[1;36m");
                        printf(" %d", table.grille[i][j].int_nbMine);
                        printf("\x1b[0m");
                        printf(" |");
                        break;

                    case 7:
                        printf("\x1b[1;37m");
                        printf(" %d", table.grille[i][j].int_nbMine);
                        printf("\x1b[0m");
                        printf(" |");
                        break;

                    case 8:
                        printf("\x1b[1;27m");
                        printf(" %d", table.grille[i][j].int_nbMine);
                        printf("\x1b[0m");
                        printf(" |");
                        break;

                    default:
                        break;
                    }
                }
            } else if (table.grille[i][j].etat_case == DRAPEAU) { // Affichage des drapeaux
                printf("🚩 |");
            }    
        }
    }

    printf("\n  ");
    for (i=0; i<table.int_largeur; i++) {
        printf("|---");
    }
    printf("|");

    // Affichage du nombre de drapeaux placés
    int_nbDrapeau = nbDrapeau(table);
    printf("\n\n🚩 placés: %d/%d\n", int_nbDrapeau, table.int_nbMine);
}


// devoiler
void devoiler(plateau table, int int_x, int int_y, int* pint_etatJeu) {
    table.grille[int_x][int_y].etat_case = DEVOILEE;

    // Si la case est une bombe
    if (table.grille[int_x][int_y].int_etatMine == 1) {
        partiePerdue(table, pint_etatJeu);
        
    // Sinon on regarde pour chaque direction (NSEW) pour chaque case adjacente seulement si la case n'a pas de bombes sur les cases adjacentes
    } else {
        if (table.grille[int_x][int_y].int_nbMine == 0 && int_x != table.int_hauteur-1) {
            if (table.grille[int_x+1][int_y].etat_case == MASQUEE) {
                devoiler(table, int_x+1, int_y, pint_etatJeu);
            }
        }
        if (table.grille[int_x][int_y].int_nbMine == 0 && int_x != 0) {
            if (table.grille[int_x-1][int_y].etat_case == MASQUEE) {
                devoiler(table, int_x-1, int_y, pint_etatJeu);
            }
        }
        if (table.grille[int_x][int_y].int_nbMine == 0 && int_y != table.int_largeur-1) {
            if (table.grille[int_x][int_y+1].etat_case == MASQUEE) {
                devoiler(table, int_x, int_y+1, pint_etatJeu);
            }
        }
        if (table.grille[int_x][int_y].int_nbMine == 0 && int_y != 0) {
            if (table.grille[int_x][int_y-1].etat_case == MASQUEE) {
                devoiler(table, int_x, int_y-1, pint_etatJeu);
            }
        }
    }
    
}


// placerDrapeau
void placerDrapeau(plateau table, int int_x, int int_y) {
    if (table.grille[int_x][int_y].etat_case == MASQUEE) {
        table.grille[int_x][int_y].etat_case = DRAPEAU;

    } else if (table.grille[int_x][int_y].etat_case == DRAPEAU) {
        table.grille[int_x][int_y].etat_case = MASQUEE;
    }
}


// nbDrapeau
int nbDrapeau(plateau table) {
    int int_nbDrapeau;
    int i;
    int j;

    // Comptage du nombre de drapeaux placés
    int_nbDrapeau = 0;
    for (i=0; i<table.int_hauteur; i++) {
        for (j=0; j<table.int_largeur; j++) {
            if (table.grille[i][j].etat_case == DRAPEAU) {
                int_nbDrapeau++;
            }
        }
    }

    return int_nbDrapeau;
}


// tourDeJeu
void tourDeJeu(plateau table, int* pint_etatJeu, int* pint_nbTour, int* pint_tempsInit, int* pint_tempsFinal, int* pint_tempsPrec) {
    char* str_prompt; // Ligne a lire
    size_t nb1; // Nombre de caractères alloués
    int nb2; // Taille réelle de la chaine de caractères

    int i;
    char* str_token;
    int int_x;
    int int_y;

    int int_retour; // Valeur de retour

    char* str_nomSauv; // Nom de la sauvegarde
    size_t int_sauv1; // Nombre de caractères alloués
    int int_sauv2; // Taille réelle du nom de la sauvegarde

    int int_diffTemps; // Différence de temps

    char* str_pseudo; // Pseudo du joueur
    size_t int_pseudo1; // Nombre de caractères alloués
    int int_pseudo2; // Taille réelle du pseudo

    // Au premier tour, initialisation du timer
    if (*pint_nbTour == 0) {
        *pint_tempsInit = time(NULL);
        *pint_nbTour = 1;
    }

    // Demande de saisie de l'utilisateur
    str_prompt = NULL;
    interface(table);
    printf("\nEntrez l'action que vous voulez faire (h pour de l'aide):\t");
    nb2 = getline(&str_prompt, &nb1, stdin);
    if (nb2 == -1) {
        fprintf(stderr, "Erreur !");
        exit(ERREUR_STR);
    }

    if (str_prompt[0] == 'h') { // Demande de l'aide
        printf("\n====================Aide====================");
        printf("\nPour jouer, voici les différentes commandes à entrer:");
        printf("\nPour dévoiler une case, écrire \"d [ligne] [colonne]\"");
        printf("\nPour placer un drapeau 🚩 sur une case, écrire \"f [ligne] [colonne]\"");
        printf("\nPour sauvegarder, écrire \"save\"");
        printf("\nPour quitter, écrire \"quit\"\n");

    } else if (str_prompt[0] == 'd') { // Dévoiler une case
        if (!(nb2 < 6 || nb2 > 8) && str_prompt[1] == ' ') {
            str_token = strtok(str_prompt, " ");

            str_token = strtok(NULL, " ");
            int_x = strtol(str_token, NULL, 10);

            str_token = strtok(NULL, " ");
            int_y = strtol(str_token, NULL, 10);

            free(str_prompt);

            if (int_x < table.int_hauteur+1 && int_y < table.int_largeur+1) {
                devoiler(table, int_x-1, int_y-1, pint_etatJeu);
            } else {
                printf("\nErreur, la case choisie n'existe pas.");
            }


        } else {
            printf("\nFormat d'écriture non respécté");
        }

    } else if (str_prompt[0] == 'f') { // Placer un drapeau (flag)
        if (!(nb2 < 6 || nb2 > 8) && str_prompt[1] == ' ') {
            str_token = strtok(str_prompt, " ");

            str_token = strtok(NULL, " ");
            int_x = strtol(str_token, NULL, 10);

            str_token = strtok(NULL, " ");
            int_y = strtol(str_token, NULL, 10);

            free(str_prompt);

            if (int_x < table.int_hauteur+1 && int_y < table.int_largeur+1) {
                placerDrapeau(table, int_x-1, int_y-1);
            } else {
                printf("\nErreur, la case choisie n'existe pas.");
            }

        } else {
            printf("\nFormat d'écriture non respécté");
        }
    
    } else if (strcmp(str_prompt, "quit\n") == 0) { // Quitter le jeu
        printf("quit");
        *pint_etatJeu = 0;

    } else if (strcmp(str_prompt, "save\n") == 0) { // Sauvegarder le jeu
        str_nomSauv = NULL;
        printf("\nEntrez le nom de la sauvegarde:\t");
        int_sauv2 = getline(&str_nomSauv, &int_sauv1, stdin);
        if (int_sauv2 == -1) {
            fprintf(stderr, "Erreur !\n");
            exit(ERREUR_STR);
        }

        *pint_tempsFinal = time(NULL);

        int_diffTemps = (int)difftime(*pint_tempsFinal, *pint_tempsInit) + *pint_tempsPrec;

        int_retour = sauvegarder(table, str_nomSauv, &int_diffTemps);

        if (int_retour != 0) {
            printf("\nErreur de sauvegarde (%d)", int_retour);
        }
        
    } else {
        printf("\nFormat d'écriture non respécté");
    }


    // Si le jeu est gagné
    if (partieGagnee(table) == 1) {
        *pint_tempsFinal = time(NULL);

        int_diffTemps = (int)difftime(*pint_tempsFinal, *pint_tempsInit) + *pint_tempsPrec;
        
        printf("\nGagné ! Score: %d", int_diffTemps);

        printf("\nEntrez votre pseudo (max 80 caractères):\t");
        str_pseudo = NULL;
        int_pseudo2 = getline(&str_pseudo, &int_pseudo1, stdin);        
        if (int_sauv2 == -1) {
            fprintf(stderr, "Erreur !\n");
            exit(ERREUR_STR);
        }

        interface(table);
        
        enregistrerScore(table, str_pseudo, int_diffTemps);

        afficherTop(table.int_hauteur, table.int_largeur, table.int_nbMine);

        *pint_etatJeu = 0;
    }
}


// partiePerdue
void partiePerdue(plateau table, int* pint_etatJeu) {
    int i;
    int j;

    // Affichage de toutes les bombes
    for (i=0; i<table.int_hauteur; i++) {
        for (j=0; j<table.int_largeur; j++) {
            if (table.grille[i][j].int_etatMine == 1) {
                table.grille[i][j].etat_case = DEVOILEE;
            }
        }
    }

    // Fin de la partie
    printf("\nPerdu !");
    interface(table);
    *pint_etatJeu = 0;
}


// partieGagnee
int partieGagnee(plateau table) {
    int i; // Variable d'incrementation
    int j; // Variable d'incrementation
    int int_nbMine; // Nombre de mines avec un drapeau

    int_nbMine = 0;
    for (i=0; i<table.int_hauteur; i++) {
        for (j=0; j<table.int_largeur; j++) {
            if (table.grille[i][j].etat_case == MASQUEE || (table.grille[i][j].etat_case == DRAPEAU && table.grille[i][j].int_etatMine == 0)) {
                // Si toutes les cases ne sont pas dévoilées ou si une case avec un drapeau n'a pas de bombes
                return 0;
            }

            if (table.grille[i][j].etat_case == DRAPEAU && table.grille[i][j].int_etatMine == 1) {
                // Si la case a un drapeau et une bombe
                int_nbMine++;
            }
        }
    }

    if (table.int_nbMine == int_nbMine) { // S'il y a le bon nombre de bombes
        return 1;
    } else {
        return 0;
    }
}
