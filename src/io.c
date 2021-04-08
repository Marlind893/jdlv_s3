#include "io.h"
<<<<<<< HEAD
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
#define CAIRO_LINE_WIDTH 2

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

	cairo_t *cr, *crcells;
	cr = cairo_create(surf);
	crcells = cairo_create(surf);
	
	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_set_source_rgb(crcells, 0.5, 0.5, 0.5);
	cairo_set_line_width(cr, CAIRO_LINE_WIDTH);
	
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
			cairo_rectangle(crcells, MARGE_GAUCHE_GRILLE + i * taille_Col + 3, MARGE_HAUTE_GRILLE + (hauteur * taille_Lgn + 3),
			taille_Col - 3, taille_Lgn - 3);
			cairo_fill(crcells);

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

	cairo_fill(crcells);
	cairo_stroke(cr);
	cairo_destroy(cr);
	cairo_destroy(crcells);
		
	return;
}

void affiche_trait (int c, int hauteur, float taille_Lgn){
	cairo_t *cr;
	cr = cairo_create(surf);
	
	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_set_line_width(cr, CAIRO_LINE_WIDTH);
	
	cairo_move_to(cr, MARGE_GAUCHE_GRILLE, MARGE_HAUTE_GRILLE + (hauteur * taille_Lgn));

	int i;
	for (i = 0; i < c; ++i) {
		cairo_line_to(cr, MARGE_GAUCHE_GRILLE + LARGEUR_GRILLE, MARGE_HAUTE_GRILLE + (hauteur * taille_Lgn));
		cairo_move_to(cr, MARGE_GAUCHE_GRILLE, MARGE_HAUTE_GRILLE + (hauteur * taille_Lgn));
	}
	cairo_stroke(cr);
	cairo_destroy(cr);
}

void affiche_grille (grille g, int tempsEvolution, int comptageCyclique, int vieillissement, int tempsOscillation){
	int i, l=g.nbl, c=g.nbc;

	char strTemps[255], strOscillation[255];
	sprintf(strTemps, "Temps d'evolution: %d", tempsEvolution);
	sprintf(strOscillation, "Oscilliation : %d", tempsOscillation);

	cairo_t *cr;
	cr = cairo_create(surf);

	cairo_set_source_rgb(cr, 1, 1, 1);

	cairo_select_font_face(cr, "Arial",
		CAIRO_FONT_SLANT_NORMAL,
		CAIRO_FONT_WEIGHT_BOLD);

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
	int tempsEvolution = 1;
	int vieillissement = 0;
	char next[N];
	int tempsOscillation = -1; // -1 par défaut => oscillation non testée

	int comptageCyclique = 1;
	int (*compte_voisins_vivants) (int, int, grille) = compte_voisins_vivants_cycl;

	XEvent e;

	while(e.xkey.keycode != 38 && e.xbutton.button != 3) { // q and right click
		XNextEvent(cairo_xlib_surface_get_display(surf), &e);
		
		if (e.type==Expose && e.xexpose.count<1) {
			affiche_grille(*g, tempsEvolution, comptageCyclique, vieillissement, tempsOscillation);
		} else if (e.type == KeyPress) {
			if (e.xkey.keycode == 36 || e.xkey.keycode == 104) { // \n 
				evolue(g,gc,compte_voisins_vivants,vieillissement);
				tempsEvolution++;
				efface_grille();
				affiche_grille(*g, tempsEvolution, comptageCyclique, vieillissement, tempsOscillation);

			} else if (e.xkey.keycode == 57) { // n
				cairo_t *cr;
				cr = cairo_create(surf);

				libere_grille(g);
				libere_grille(gc);

				char inputN[255];
				sprintf(inputN, "Entrez la nouvelle grillle:        (format: grilles/grilleX.txt).\n");
				cairo_move_to(cr, 20, 490);
				cairo_show_text(cr, inputN);

				scanf("%s", next);
				init_grille_from_file(next, g);
				alloue_grille(g->nbl, g->nbc, gc);


				
				tempsEvolution = 1; // Réinitialisation du temps
				tempsOscillation = -1; // Réinitialisation de l'oscillation
				alloue_grille (g->nbl, g->nbc, gc);
				
				efface_grille();
				affiche_grille(*g, tempsEvolution, comptageCyclique, vieillissement, tempsOscillation);

			} else if (e.xkey.keycode == 54) { // c
				
				if (comptageCyclique) {
					comptageCyclique = 0;
					compte_voisins_vivants = &(compte_voisins_vivants_non_cycl);
				} else { // On repasse à un comptage cyclique
					comptageCyclique = 1;
					compte_voisins_vivants = &(compte_voisins_vivants_cycl);
				}
				efface_grille();
				affiche_grille(*g, tempsEvolution, comptageCyclique, vieillissement, tempsOscillation);

			} else if (e.xkey.keycode == 55) { // v
				vieillissement = !vieillissement;
				efface_grille();
				affiche_grille(*g, tempsEvolution, comptageCyclique, vieillissement, tempsOscillation);

			} else if (e.xkey.keycode == 40) {
				system("doxygen && firefox ./doc/html/index.html");
			} else if (e.xkey.keycode == 32) { // o (oscillation)
				tempsOscillation = oscillante(g, compte_voisins_vivants, vieillissement);
				efface_grille();
				affiche_grille(*g, tempsEvolution, comptageCyclique, vieillissement, tempsOscillation);
			}

		} else if (e.type == ButtonPress) {
			if (e.xbutton.button == 1) { // laft click
				evolue(g,gc,compte_voisins_vivants,vieillissement);
				efface_grille();
				affiche_grille(*g, tempsEvolution, comptageCyclique, vieillissement, tempsOscillation);
			
			}
		}
	
	}

}




#else //mode texte





=======
#define N 25

>>>>>>> 9e6146a607b89ae9e65f9a069ab9669897a6246b
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

<<<<<<< HEAD
void affiche_grille (grille g, int vieilliss, int oscill){
=======
void affiche_grille (grille g, int v){
>>>>>>> 9e6146a607b89ae9e65f9a069ab9669897a6246b
	int i, l=g.nbl, c=g.nbc;
	printf("\n");
	affiche_trait(c);
	for (i=0; i<l; ++i) {
<<<<<<< HEAD
		if(vieilliss%2){
=======
		if(v%2){
>>>>>>> 9e6146a607b89ae9e65f9a069ab9669897a6246b
			affiche_ligne_avec_v(c, g.cellules[i]);
		}else{
			affiche_ligne(c, g.cellules[i]);
		}
		affiche_trait(c);
	}
<<<<<<< HEAD
	

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



=======
	printf("\n"); 
	return;
}

>>>>>>> 9e6146a607b89ae9e65f9a069ab9669897a6246b
void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 5); 
}


void debut_jeu(grille *g, grille *gc){
	char c = getchar();
	int cycl=1;
	int vieil=0;
<<<<<<< HEAD
	int osc = -1;
	int temps = 1;
	char next[N];
	printf("\e[H\e[2J");
=======
	int temps = 1;
	char next[N];
>>>>>>> 9e6146a607b89ae9e65f9a069ab9669897a6246b
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
<<<<<<< HEAD
				affiche_grille(*g, vieil, osc);
=======
				affiche_grille(*g, vieil);
>>>>>>> 9e6146a607b89ae9e65f9a069ab9669897a6246b
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
<<<<<<< HEAD
				osc = -1;
=======
>>>>>>> 9e6146a607b89ae9e65f9a069ab9669897a6246b
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
<<<<<<< HEAD

				osc = oscillante(g, compte_voisins_vivants, vieil);
				
=======
				grille gcopie;
				alloue_grille(g->nbl, g->nbc, &gcopie);
				copie_grille(*g, gcopie);
				int colo;
				printf("Entrez la colonne: \n");
				scanf("%d", &colo);
				int osc = oscillante(*g, gcopie, colo);
				libere_grille(&gcopie);
				printf("Colonne %d est oscillante pour une periode de %d ", colo, osc);
>>>>>>> 9e6146a607b89ae9e65f9a069ab9669897a6246b
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


<<<<<<< HEAD
#endif
=======

>>>>>>> 9e6146a607b89ae9e65f9a069ab9669897a6246b
