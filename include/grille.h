/** 
 * \file grille.h 
 * header pour les grilles
 * \author Marlind Tahiri
 */

#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// structure grille : nombre de lignes, nombre de colonnes, tableau de tableau de cellules
/**
 * \typedef typedef struct grille
 * déclaration du type structure grille
 */
typedef struct {int nbl; int nbc; int** cellules;} grille;
 
// alloue une grille de taille l*c, et initialise toutes les cellules à mortes
/**
 * alloue une grille
 * \relatesalso grille
 * \param l nombre de lignes
 * \param c nombre de colonnes
 * \param g grille a allouer
 * \returns \c void
 */
void alloue_grille (int l, int c, grille* g);


// libère une grille
/**
 * libere une grille
 * \relatesalso grille
 * \param g grille a liberer
 * \returns \c void
 */
void libere_grille (grille* g);


// alloue et initalise la grille g à partir d'un fichier
/**
 * initialise une grille a partir d'un fichier
 * \relatesalso grille
 * \param filename nom du fichier a initaliser
 * \param g variable ou on place cette nouvelle grille
 * \returns \c void
 */
void init_grille_from_file (char * filename, grille* g);

// rend vivante la cellule (i,j) de la grille g
/**
 * teste une cellule vivante
 * \relatesalso grille
 * \param i numero ligne
 * \param j numero colonne
 * \param g grille affecté
 * \returns \c static inline void
 */
static inline void set_vivante(int i, int j, grille g){
    if(g.cellules[i][j] != -1){
        g.cellules[i][j] = 1;
    }

}


// rend non viable la cellule (i,j) de la grille g
/**
 * teste une cellule vivante
 * \relatesalso grille
 * \param i numero ligne
 * \param j numero colonne
 * \param g grille affecté
 * \returns \c static inline void
 */
static inline void set_non_viable(int i, int j, grille g){g.cellules[i][j] = -1;}



// rend morte la cellule (i,j) de la grille g
/**
 * teste si une cellule est morte
 * \relatesalso grille
 * \param i numero ligne
 * \param j numero colonne
 * \param g grille affecté
 * \returns \c static inline void
 */
static inline void set_morte(int i, int j, grille g){g.cellules[i][j] = 0;}

// teste si la cellule (i,j) de la grille g est vivante
/**
 * teste si une cellule est vivante
 * \relatesalso grille
 * \param i numero ligne
 * \param j numero colonne
 * \param g grille affecté
 * \returns \c static inline void
 */
static inline int est_vivante(int i, int j, grille g){return g.cellules[i][j] >= 1;}

// recopie gs dans gd (sans allocation)
/**
*recopie une grille dans une autre
* \relatesalso grille
* \param gs grille recopié
* \param gd grille affecté
* \returns \c void
*/
void copie_grille (grille gs, grille gd);


/**
*verifie si une grille est oscillante
* \relatesalso grille
* \param ga grille originale
* \param gcop grille copié
* \param col colonne a vrifier
* \returns \c int
*/
int oscillante(grille ga, grille gcop, int col);



#endif
