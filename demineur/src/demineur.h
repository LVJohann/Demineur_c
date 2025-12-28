#ifndef __DEMINEUR_H_
#define __DEMINEUR_H_

// Inclusion des entetes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <string.h>

// Definition des constantes symboliques
/**
 * \def ERREUR_ALLOC
 * code d'erreur lié a une allocation de mémoire
 */
#define ERREUR_ALLOC -2

/**
 * \def ERREUR_STR
 * Code d'erreur lié a la lecture d'une chaine de caractères
 */
#define ERREUR_STR -1

/**
 * 
 */
#define ERREUR_ARG -3

/**
 * \enum etat
 * Enumeration des différents états que peut prendre une case de démineur
 */
enum etat {
    MASQUEE, /**< La case est masquee */
    DEVOILEE, /**< La case est dévoilée */
    DRAPEAU /**< La case a un drapeau */
};


/**
 * \struct carreau
 * Structure définissant une case de démineur
 */
typedef struct {
    enum etat etat_case; /**< Etat de la case de démineur */
    int int_etatMine; /**< Entier permettant de voir si la case possède une mine */
    int int_nbMine; /**< Nombre de mines autour de la case */
} carreau;


/**
 * \struct plateau
 * Structure définissant le plateau de jeu
 */
typedef struct {
    carreau** grille; /**< Pointeur de case */
    int int_hauteur; /**< Hauteur du plateau */
    int int_largeur; /**< Largeur du plateau */
    int int_nbMine; /**< Nombre de mines sur le plateau */
} plateau;


/**
 * \fn plateau creerPlateau(int int_nbColonne, int int_nbLigne, int int_nbMine)
 * \brief Initialise le plateau de démineur
 * 
 * \param int int_nbColonne, nombre de colonnes du plateau
 * \param int int_nbLigne, nombre de lignes du plateau
 * \param int int_nbMine, nombre de mines sur le plateau
 * \return plateau, plateau de jeu
 */
plateau creerPlateau(int int_nbColonne, int int_nbLigne, int int_nbMine);


/**
 * \fn void initPlateau(plateau table)
 * \brief initialise le plateau de jeu
 * 
 * \param plateau table, plateau de jeu
 */
void initPlateau(plateau table);


/**
 * \fn void interface(plateau table)
 * \brief affiche le plateau
 * 
 * \param plateau table, pleateau de jeu a afficher
 */
void interface(plateau table);


/**
 * \fn devoiler(plateau table, int int_x, int int_y)
 * \brief Dévoile la case [int_x][int_y] du plateau ainsi que les cases adjacentes si la case n'a aucune bombe sur les cases adjacentes
 * 
 * \param plateau table, plateau de jeu
 * \param int int_x, numero de ligne
 * \param int int_y, numéro de colonne
 * \param int* pint_etatJeu, etat de jeu. L'entier associé vaut 0 si le joueur quitte, 1 sinon
 */
void devoiler(plateau table, int int_x, int int_y, int* pint_etatJeu);


/**
 * \fn placerDrapeau(plateau table, int int_x, int int_y)
 * \brief Permet a l'utilisateur de placer un drapeau sur la case [int_x][int_y] ou d'enlever un drapeau de la case
 * 
 * \param plateau table, plateau de jeu
 * \param int int_x, numéro de ligne
 * \param int int_y, numéro de colonne
 */
void placerDrapeau(plateau table, int int_x, int int_y);


/**
 * \fn int nbDrapeau(plateau table)
 * \brief Renvoie le nombre de drapeaux placés sur le plateau
 * 
 * \param plateau table, plateau de jeu
 * \return int, nombre de drapeaux placés sur le plateau
*/
int nbDrapeau(plateau table);


/**
 * \fn void tourDeJeu(plateau table)
 * \brief Permet au joueur de jouer un tour
 * 
 * \param plateau table, plateau de jeu
 * \param int* pint_etatJeu, etat de jeu. L'entier associé vaut 0 si le joueur quitte, 1 sinon
 * \param int* pint_nbTour, adresse du nombre de tours qui vaut 0 lors du premier tour, 1 sinon
 * \param int* pint_tempsInit, adresse du temps initial
 * \param int* pint_tempsFinal, adresse du temps final
 * \param int* pint_tempsPrec, temps précédent si la partie est chargée
 */
void tourDeJeu(plateau table, int* pint_etatJeu, int* pint_nbTour, int* pint_tempsInit, int* pint_tempsFinal, int* pint_tempsPrec);


/**
 * \fn void partiePerdue(plateau table)
 * \brief Montre l'emplacement de toutes les bombes et met fin a la partie
 * 
 * \param plateau table, plateau de jeu
 * \param int* pint_etatJeu, etat de jeu. L'entier associé vaut 0 si le joueur quitte, 1 sinon
 */
void partiePerdue(plateau table, int* pint_etatJeu);


/**
 * \fn int partieGagnee(plateau table, int* pint_etatJeu)
 * \brief Verifie si la partie est gagnée
 * 
 * \param plateau table, plateau de jeu
 * \return int, 1 si la partie est gagnée, 0 si la partie est toujours en cours 
 */
int partieGagnee(plateau table);


/**
 * \fn void nbMines(plateau table)
 * \brief Compte le nombre de mines autour de chaque case du plateau de jeu
 * 
 * \param plateau table, plateau de jeu
 */
void nbMines(plateau table);


// Inclusion de l'entete lié à la sauvegarde
#include "save.h"

#endif