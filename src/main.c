#include <stdio.h>
#include<cairo.h>
#include<cairo-xlib.h>
#include<X11/Xlib.h>

#include "grille.h"
#include "io.h"
#include "jeu.h"


cairo_surface_t *surf;

int main (int argc, char ** argv) {
	
	if (argc != 2 )
	{
		printf("usage : main <fichier grille>");
		return 1;
	}

	grille g, gc;
	init_grille_from_file(argv[1],&g);
	alloue_grille (g.nbl, g.nbc, &gc);

	#if MODECAIRO //mode cairo
	
		surf = cairo_create_x11_surf(tailleX, tailleY);
		debut_jeu(&g, &gc);
		cairo_close_x11_surf();

	#else //mode texte

		affiche_grille(g, 0, -1);
		
		debut_jeu(&g, &gc);

	#endif

	libere_grille(&g);
	libere_grille(&gc);
	
	return 0;
}


