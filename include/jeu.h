/** 
 * \file jeu.h 
 * header pour le jeu
 * \author Marlind Tahiri
 */

#ifndef __JEU_H
#define __JEU_H

#include "grille.h"

// modulo modifié pour traiter correctement les bords i=0 et j=0
// dans le calcul des voisins avec bords cycliques
/**
 * fonc pour non cyclique
 * \param i nombre de lignes
 * \param m nombre de colonnes
 * \returns \c static inline int
 */
static inline int modulo(int i, int m) {return (i+m)%m;}


/**
 * fonc pour cyclique
 * \param i nombre de lignes
 * \param m nombre de colonnes
 * \returns \c static inline int
 */
static inline int modulo1(int i, int m) {
    int res;
    if(i<0){
        res = 0;
    }else if (i>m){
        res = m;
    }else{
        res = (i+m)%m;
    }
    return res;
}


/**
 * fonc pour le vieillissement
 * \relatesalso grille
 * \param g grille g
 * \param gc grille gc
 * \returns \c void
 */
void vieillissement(grille *g, grille *gc);

// compte le nombre de voisins vivants de la cellule (i,j)
// les bords sont cycliques.
/**
 * compte le nombre de voisins
 * \relatesalso grille
 * \param i nombre de lignes
 * \param j nombre de colonnes
 * \returns \c int
 */
int compte_voisins_vivants (int i, int j, grille g);

// fait évoluer la grille g d'un pas de temps
/**
 * fait evoluer la grille 
 * \relatesalso grille
 * \param g grille g
 * \param gc grille gc
 * \param cy toggle cyclique
 * \param vj toggle vieillisement
 * \returns \c void
 */
void evolue (grille *g, grille *gc, int cy, int vj);

#endif
