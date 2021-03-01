/** 
 * \file io.h 
 * header pour le io
 * \author Marlind Tahiri
 */

#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"

// affichage d'un trait horizontal
/**
 * affiche un trait
 * \param c numero de colonnes
 * \returns \c void
 */
void affiche_trait (int c);

// affichage d'une ligne de la grille
/**
 * affiche une ligne verticale
 * \param c numero de colonnes
 * \param ligne tableau ligne
 * \returns \c void
 */
void affiche_ligne (int c, int* ligne);

// affichage d'une grille
/**
 * affiche une grille
 * \relatesalso grille
 * \param g grille g
 * \param v toggle vieillisement
 * \returns \c void
 */
void affiche_grille (grille g, int v);

// effacement d'une grille
/**
 * efface une grille 
 * \relatesalso grille
 * \param g grille g
 * \returns \c void
 */
void efface_grille (grille g);

// debute le jeu
/**
 * fait evoluer la grille 
 * \relatesalso grille
 * \param g grille g
 * \param gc grille gc
 * \returns \c void
 */
void debut_jeu(grille *g, grille *gc);

#endif
