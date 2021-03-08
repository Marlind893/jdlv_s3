#include "io.h"
#define N 25

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

void affiche_grille (grille g, int v){
	int i, l=g.nbl, c=g.nbc;
	printf("\n");
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		if(v%2){
			affiche_ligne_avec_v(c, g.cellules[i]);
		}else{
			affiche_ligne(c, g.cellules[i]);
		}
		affiche_trait(c);
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
	int temps = 1;
	char next[N];
	int (*compte_voisins_vivants) (int, int, grille) = compte_voisins_vivants_cyclique;

	while (c != 'q') // touche 'q' pour quitter
	{ 
		switch (c) {
			case '\n' : 
			{ // touche "entree" pour évoluer
				evolue(g, gc, compte_voisins_vivants, vieil);
				efface_grille(*g);
				printf("Temps d'evolution: %d  ", temps);
				affiche_grille(*g, vieil);
				temps++;
				
				break;
			}
			case 'n' :
			{ //touche 'n' pour next grille
				
				libere_grille(g);
				libere_grille(gc);
				printf("Entrez la nouvelle grillle: \n");
				scanf("%s", next);
				init_grille_from_file(next, g);
				alloue_grille(g->nbl, g->nbc, gc);
				temps = 0;
				printf("\e[H\e[2J");
				break;
			}
			case 'c':
			{ //touche 'c' pour cuclique ou non cyclique
				//cycl++;
				if (cycl) {
					cycl = 0;
					compte_voisins_vivants = &(compte_voisins_vivants_non_cyclique);
				} else {
					cycl = 1;
					compte_voisins_vivants = &(compte_voisins_vivants_cyclique);
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
				grille gcopie;
				alloue_grille(g->nbl, g->nbc, &gcopie);
				copie_grille(*g, gcopie);
				int colo;
				printf("Entrez la colonne: \n");
				scanf("%d", &colo);
				int osc = oscillante(*g, gcopie, colo);
				libere_grille(&gcopie);
				printf("Colonne %d est oscillante pour une periode de %d ", colo, osc);
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



