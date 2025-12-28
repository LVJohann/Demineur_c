#ifndef __SAVE_H_
#define __SAVE_H_

// Inclusion des entetes
#include "demineur.h"


// Definition de constantes
/**
 * \def ERREUR_OUVERTURE
 * Code d'erreur lié à l'ouverture d'un fichier
 */
#define ERREUR_OUVERTURE 1

/**
 * \def ERREUR_FERMETURE
 * Code d'erreur lié à la fermeture d'un fichier
 */
#define ERREUR_FERMETURE 2

/**
 * \def ERREUR_ECRITURE
 * Code d'erreur lié à l'écriture dans un fichier
 */
#define ERREUR_ECRITURE 3

/**
 * \def ERREUR_LECTURE
 * Code d'erreur lié à la lecture d'un fichier
 */
#define ERREUR_LECTURE 4

// Definition des methodes
/**
 * \fn int sauvegarder(plateau table, char* str_pseudo)
 * \brief Sauvegarde la partie en cours du joueur sous le nom str_pseudo
 * 
 * \param plateau table, plateau de jeu à sauvegarder
 * \param char* str_pseudo, nom de la sauvegarde
 * \param int* pint_temps, temps écoulé depuis le début de la partie
 * \return int, 0 si tout c'est bien passé.
 */
int sauvegarder(plateau table, char* str_pseudo, int* pint_temps);


/**
 * \fn plateau charger(plateau table, char* str_pseudo)
 * \brief Charge la sauvegarde str_pseudo dans le plateau de jeu
 * 
 * \param char* str_pseudo, nom de la sauvegarde
 * \param int* pint_temps, temps a la fin de la partie (sauvegarde)
 * \return plateau, Le plateau de jeu chargé.
 */
plateau charger(char* str_pseudo, int* pint_temps);


/**
 * \fn int enregistrerScore(plateau table, char* str_pseudo, int int_temps)
 * \brief Permet d'enregistrer le score de str_pseudo dans un fichier selon les parametres du plateau
 * 
 * \param plateau table, plateau de jeu
 * \param char* str_pseudo, pseudo du joueur
 * \param int int_temps, score du joueur
 * \return int, 0 si tout s'est bien passé
 */
int enregistrerScore(plateau table, char* str_pseudo, int int_temps);


/**
 * \struct joueur
 * Structure définissant un joueur
 */
typedef struct {
    char str_pseudo[80]; /**< Pseudo du joueur */
    int int_score; /**< Score min du joueur */
} joueur;


/**
 * \fn int afficherTop(int int_h, int int_l, int int_m)
 * \brief Affiche le classement des 10 meilleurs scores pour un plateau de dimension donnée
 * 
 * \param int int_h, hauteur du plateau
 * \param int int_l, largeur du plateau
 * \param int int_m, nombre de mines sur le plateau 
 * \return int, 0 si tout s'est bien passé
 */
int afficherTop(int int_h, int int_l, int int_m);


#endif