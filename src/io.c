#include "io.h"
#include <string.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#define N 25


#if MODECAIRO //mode cairo
	
#define MARGE_GAUCHE_GRILLE 20
#define MARGE_HAUTE_GRILLE 60
#define LARGEUR_GRILLE 450
#define HAUTEUR_GRILLE 400


extern cairo_surface_t *surf;


cairo_surface_t *cairo_create_x11_surf(int x, int y) {
    Display *dpy;
    Drawable da;
    int screen;
	Window rootwin;
    cairo_surface_t *surf;

    if ((dpy = XOpenDisplay(NULL)) == NULL) {
		fprintf(stderr, "ERROR: Could not open display\n");
        exit(1);
	}

    screen = DefaultScreen(dpy);
	rootwin = RootWindow(dpy, screen);

	unsigned long background = 0x0033004d;
	da=XCreateSimpleWindow(dpy, rootwin, 1, 1, x, y, 0, 
			background, background);

	XSelectInput(dpy, da, ExposureMask|ButtonPressMask|KeyPressMask);
    XMapWindow(dpy, da);


	XStoreName(dpy, da, "JDLV 5.0");

	
    surf = cairo_xlib_surface_create(dpy, da, DefaultVisual(dpy, screen), x, y);
    cairo_xlib_surface_set_size(surf, x, y);

    return surf;
}

void cairo_close_x11_surf() {
   Display *dpy = cairo_xlib_surface_get_display(surf);
   cairo_surface_destroy(surf);
   XCloseDisplay(dpy);
}

void affiche_ligne (int c, int* ligne, int vieillissement, int hauteur, float taille_Lgn){
	int i;
	char ageBuffer[255];
	float taille_Col = (float) LARGEUR_GRILLE / (float) c;

	cairo_t *cr, *cells;
	cr = cairo_create(surf);
	cells = cairo_create(surf);
	
	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_set_source_rgb(cells, 0.5, 0.5, 0.5);
	cairo_set_line_width(cr, 2);
	
	cairo_move_to(cr, MARGE_GAUCHE_GRILLE, MARGE_HAUTE_GRILLE + (hauteur * taille_Lgn));


	for (i=0; i<c; ++i) {

		if (ligne[i] == 0) {
			cairo_line_to(cr, MARGE_GAUCHE_GRILLE + i * taille_Col, MARGE_HAUTE_GRILLE + (hauteur * taille_Lgn) + taille_Lgn);
			cairo_move_to(cr, MARGE_GAUCHE_GRILLE + ((i+1) * taille_Col), MARGE_HAUTE_GRILLE + (hauteur * taille_Lgn));
			cairo_line_to(cr, MARGE_GAUCHE_GRILLE + ((i+1) * taille_Col), MARGE_HAUTE_GRILLE + (hauteur * taille_Lgn) + taille_Lgn);
		} else if (ligne[i] == -1) {
			cairo_line_to(cr, MARGE_GAUCHE_GRILLE + i * taille_Col, MARGE_HAUTE_GRILLE + (hauteur * taille_Lgn) + taille_Lgn);
			cairo_line_to(cr, MARGE_GAUCHE_GRILLE + ((i+1) * taille_Col), MARGE_HAUTE_GRILLE + (hauteur * taille_Lgn) + 1);
			cairo_line_to(cr, MARGE_GAUCHE_GRILLE + ((i+1) * taille_Col), MARGE_HAUTE_GRILLE + (hauteur * taille_Lgn) + taille_Lgn);
			cairo_line_to(cr, MARGE_GAUCHE_GRILLE + i * taille_Col, MARGE_HAUTE_GRILLE + (hauteur * taille_Lgn) + taille_Lgn);
			cairo_move_to(cr, MARGE_GAUCHE_GRILLE + ((i) * taille_Col), MARGE_HAUTE_GRILLE + (hauteur * taille_Lgn));
			cairo_line_to(cr, MARGE_GAUCHE_GRILLE + ((i+1) * taille_Col), MARGE_HAUTE_GRILLE + (hauteur * taille_Lgn) + taille_Lgn);
			cairo_line_to(cr, MARGE_GAUCHE_GRILLE + ((i+1) * taille_Col), MARGE_HAUTE_GRILLE + (hauteur * taille_Lgn));
		} else {
			cairo_line_to(cr, MARGE_GAUCHE_GRILLE + i * taille_Col, MARGE_HAUTE_GRILLE + (hauteur * taille_Lgn) + taille_Lgn);
			cairo_move_to(cr, MARGE_GAUCHE_GRILLE + ((i-1) * taille_Col) + 2, MARGE_HAUTE_GRILLE + (hauteur * taille_Lgn) + 2);
			cairo_rectangle(cells, MARGE_GAUCHE_GRILLE + i * taille_Col + 3, MARGE_HAUTE_GRILLE + (hauteur * taille_Lgn + 3),
			taille_Col - 3, taille_Lgn - 3);
			cairo_fill(cells);

			if (vieillissement) {
				sprintf(ageBuffer, "%d", ligne[i]);
				cairo_move_to(cr, MARGE_GAUCHE_GRILLE + ((i) * taille_Col) + taille_Col/2 - 5, MARGE_HAUTE_GRILLE + (hauteur * taille_Lgn) + (taille_Lgn*2/3) - 3);
				cairo_set_source_rgb (cr, 0, 0, 0);
				cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
				cairo_set_font_size(cr, 15);
				cairo_show_text(cr, ageBuffer);

				cairo_set_source_rgb(cr, 1, 1, 1);
			}

			cairo_move_to(cr, MARGE_GAUCHE_GRILLE + ((i+1) * taille_Col), MARGE_HAUTE_GRILLE + (hauteur * taille_Lgn));
		}
	}

	cairo_fill(cells);
	cairo_stroke(cr);
	cairo_destroy(cr);
	cairo_destroy(cells);
		
	return;
}

void affiche_trait (int c, int hauteur, float taille_Lgn){
	cairo_t *cr;
	cr = cairo_create(surf);
	
	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_set_line_width(cr, 2);
	
	cairo_move_to(cr, MARGE_GAUCHE_GRILLE, MARGE_HAUTE_GRILLE + (hauteur * taille_Lgn));

	int i;
	for (i = 0; i < c; ++i) {
		cairo_line_to(cr, MARGE_GAUCHE_GRILLE + LARGEUR_GRILLE, MARGE_HAUTE_GRILLE + (hauteur * taille_Lgn));
		cairo_move_to(cr, MARGE_GAUCHE_GRILLE, MARGE_HAUTE_GRILLE + (hauteur * taille_Lgn));
	}
	cairo_stroke(cr);
	cairo_destroy(cr);
}

void affiche_grille (grille g, int tempsEvo, int vieillissement, int tempsOsc){
	int i, l=g.nbl, c=g.nbc;

	char strTemps[255], strOscillation[255];
	sprintf(strTemps, "Temps d'evolution: %d", tempsEvo);
	sprintf(strOscillation, "Oscilliation : %d", tempsOsc);

	cairo_t *cr;
	cr = cairo_create(surf);


	cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_set_font_size(cr, 18);

	cairo_move_to(cr, 20, 30);
	cairo_show_text(cr, strTemps);
	cairo_move_to(cr, 500, 100);
	cairo_show_text(cr, strOscillation); 

	int hauteur = 0;
	float tailleLigne = (float) HAUTEUR_GRILLE / (float) g.nbl;
	affiche_trait(c, hauteur, tailleLigne);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i], vieillissement, hauteur, tailleLigne);
		affiche_trait(c, ++hauteur, tailleLigne);
	}
	return;
}



void efface_grille () {
	cairo_t *cr;
	cr = cairo_create(surf);
	cairo_set_source_rgb (cr, 0.2, 0, 0.3);
	cairo_paint(cr);
	cairo_destroy(cr);
}



void debut_jeu(grille *g, grille *gc) {
	int tempsEvo = 1;
	int vieillissement = 0;
	int tempsOsc = -1; // -1 par défaut => oscillation non testée

	int comptageCyclique = 1;
	int (*compte_voisins_vivants) (int, int, grille) = compte_voisins_vivants_cycl;

	XEvent e;
	char keybuf[255];
	KeySym key;

	while(e.xkey.keycode != 38 && e.xbutton.button != 3) { // q and right click
		XNextEvent(cairo_xlib_surface_get_display(surf), &e);
		char next[100] = "grilles/grille";
		
		if (e.type==Expose && e.xexpose.count<1) {
			affiche_grille(*g, tempsEvo, vieillissement, tempsOsc);
		} else if (e.type == KeyPress) {
			if (e.xkey.keycode == 36 || e.xkey.keycode == 104) { // Entrée 
				evolue(g,gc,compte_voisins_vivants,vieillissement);
				tempsEvo++;
				efface_grille();
				affiche_grille(*g, tempsEvo, vieillissement, tempsOsc);

			} else if (e.xkey.keycode == 57) { // n
				cairo_t *cr;
				cr = cairo_create(surf);

				libere_grille(g);
				libere_grille(gc);

				cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
				cairo_set_source_rgb(cr, 1, 1, 1);
				cairo_set_font_size(cr, 18);

				char inputN[255];
				sprintf(inputN, "Entrez le numero de la grillle:        ( Numero de 1 à 8, NE PAS APPUIER SUR Maj ). \n");
				cairo_move_to(cr, 20, 490);
				cairo_show_text(cr, inputN);
				
				XNextEvent(cairo_xlib_surface_get_display(surf), &e);
				if (e.type == KeyPress){
					XLookupString(&e.xkey, keybuf, sizeof(keybuf), &key, NULL);
					strcat(next, keybuf);
					strcat(next, ".txt");
				}
				
				init_grille_from_file(next, g);
				alloue_grille(g->nbl, g->nbc, gc);

				
				tempsEvo = 1;
				tempsOsc = -1;
				alloue_grille (g->nbl, g->nbc, gc);
				
				efface_grille();
				affiche_grille(*g, tempsEvo, vieillissement, tempsOsc);


			} else if (e.xkey.keycode == 54) { // c
				
				if (comptageCyclique) {
					comptageCyclique = 0;
					compte_voisins_vivants = &(compte_voisins_vivants_non_cycl);
				} else { // On repasse à un comptage cyclique
					comptageCyclique = 1;
					compte_voisins_vivants = &(compte_voisins_vivants_cycl);
				}
				efface_grille();
				affiche_grille(*g, tempsEvo, vieillissement, tempsOsc);

			} else if (e.xkey.keycode == 55) { // v
				vieillissement = !vieillissement;
				efface_grille();
				affiche_grille(*g, tempsEvo, vieillissement, tempsOsc);

			} else if (e.xkey.keycode == 32) { // o (oscillation)
				tempsOsc = oscillante(g, compte_voisins_vivants, vieillissement);
				efface_grille();
				affiche_grille(*g, tempsEvo, vieillissement, tempsOsc);
			}

		} else if (e.type == ButtonPress) {
			if (e.xbutton.button == 1) { // left click
				evolue(g,gc,compte_voisins_vivants,vieillissement);
				efface_grille();
				affiche_grille(*g, tempsEvo, vieillissement, tempsOsc);
			
			}
		}
	
	}

}




#else //mode texte





void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i) 
		if (ligne[i] == 0 ) printf ("|   "); else if (ligne[i] == -1) printf("| X "); else printf ("| O ");
	printf("|\n");
	return;
}

void affiche_ligne_avec_v (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i) 
		if (ligne[i] == 0 ) printf ("|   "); else if (ligne[i] == -1) printf("| X "); else printf ("| %d ", ligne[i]);
	printf("|\n");
	return;
}

void affiche_grille (grille g, int vieilliss, int oscill){
	int i, l=g.nbl, c=g.nbc;
	printf("\n");
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		if(vieilliss%2){
			affiche_ligne_avec_v(c, g.cellules[i]);
		}else{
			affiche_ligne(c, g.cellules[i]);
		}
		affiche_trait(c);
	}
	

	if(oscill == -1){
		printf("Oscillation non teste");
	}else if(oscill == 0){
		printf("Pas oscillante");
	}else{
		printf("Temps d'oscillation:  %d", oscill);
	}
	printf("\n");

	return;
}



void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 5); 
}


void debut_jeu(grille *g, grille *gc){
	char c = getchar();
	int cycl=1;
	int vieil=0;
	int osc = -1;
	int temps = 1;
	char next[N];
	printf("\e[H\e[2J");
	//pointeur fonction cycl ou non
	int (*compte_voisins_vivants) (int, int, grille) = compte_voisins_vivants_cycl;

	while (c != 'q') // touche 'q' pour quitter
	{ 
		switch (c) {
			case '\n' : 
			{ // touche "entree" pour évoluer
				evolue(g, gc, compte_voisins_vivants, vieil);
				efface_grille(*g);
				printf("Temps d'evolution: %d  ", temps);
				affiche_grille(*g, vieil, osc);
				temps++;
				
				break;
			}
			case 'n' :
			{ //touche 'n' pour next grille
				
				libere_grille(g);
				libere_grille(gc);
				printf("Entrez la nouvelle grillle:        (format: grilles/grilleX.txt).\n");
				scanf("%s", next);
				init_grille_from_file(next, g);
				alloue_grille(g->nbl, g->nbc, gc);
				temps = 0;
				osc = -1;
				printf("\e[H\e[2J");
				break;
			}
			case 'c':
			{ //touche 'c' pour cuclique ou non cyclique
				//cycl++;
				if (cycl) {
					cycl = 0;
					compte_voisins_vivants = &(compte_voisins_vivants_non_cycl);
				} else {
					cycl = 1;
					compte_voisins_vivants = &(compte_voisins_vivants_cycl);
				}
				printf("\e[H\e[2J");
				break;
			}
			case 'v':
			{ //touche 'v' pour viellisement
				vieil++;
				printf("\e[H\e[2J");
				break;
			}
			case 'o':
			{ //touche 'o' pour oscillence

				osc = oscillante(g, compte_voisins_vivants, vieil);
				
				printf("\e[H\e[2J");
				break;
			}
			default : 
			{ // touche non traitée
				printf("\e[H\e[2J");
				break;
			}
		}
		c = getchar(); 
	}

}


#endif
