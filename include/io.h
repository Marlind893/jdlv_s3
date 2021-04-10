/** 
 * \file io.h 
 * header pour le io
 * \author Marlind Tahiri
 */

#ifndef __IO_H__
#define __IO_H__

#include <stdio.h>
#include "grille.h"
#include "jeu.h"
#include <string.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>


#define tailleX 900
#define tailleY 500

#if MODECAIRO
    

    // creation surface cairo
    /**
     * affiche un trait
     * \param x numero x px
     * \param y numero y px
     * \returns \c void
     */
    cairo_surface_t *cairo_create_x11_surf(int x, int y);

    /**
     * Fermeture d'une surface cairo
     * \returns \c void
     */
    void cairo_close_x11_surf();

    // affichage d'un trait horizontal
    /**
     * affiche un trait
     * \param c numero de colonnes
     * \param hauteur hauteur grille
     * \param taille_Lgn taille de ligne
     * \returns \c void
     */
    void affiche_trait (int c, int hauteur, float taille_Lgn);

    // affichage d'une ligne de la grille
    /**
     * affiche une ligne verticale
     * \param c numero de colonnes
     * \param vieillissement viellisement
     * \param hauteur hauteur grille
     * \param taille_Lgn taille de ligne
     * \param ligne tableau ligne
     * \returns \c void
     */
    void affiche_ligne (int c, int* ligne, int vieillissement, int hauteur, float taille_Lgn);

    // affichage d'une grille
    /**
     * affiche une grille
     * \relatesalso grille
     * \param g grille g
     * \param vieillissement toggle vieillisement
     * \param tempsEvolution temps
     * \param tempsOscillation oscillation
     * \returns \c void
     */
    void affiche_grille (grille g, int tempsEvolution, int vieillissement, int tempsOscillation);


    // effacement d'une grille
    /**
     * efface une grille 
     * \relatesalso grille
     * \returns \c void
     */
    void efface_grille ();

    // effacement d'une grille
    /**
     * entree text en bas de l'ecran
     * \relatesalso grille
     * \param input input nom grille
     * \param erreur erreur input
     * \returns \c void
     */
    void drawTextInput(char *input, char *erreur);


#else



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



    // effacement d'une grille
    /**
     * efface une grille 
     * \relatesalso grille
     * \param g grille g
     * \returns \c void
     */
    void efface_grille (grille g);



    // affichage d'une grille
    /**
     * affiche une grille
     * \relatesalso grille
     * \param g grille g
     * \param v toggle vieillisement
     * \param oscill oscillation
     * \returns \c void
     */
    void affiche_grille (grille g, int v, int oscill);

#endif
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
