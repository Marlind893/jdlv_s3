#include "grille.h"
#include "jeu.h"

void init_grille_from_file (char * filename, grille* g){
	FILE * pfile = NULL;
	pfile = fopen(filename, "r");
	assert (pfile != NULL);
	
	int i,j,n,l,c,vivantes,non_viables=0;
	
	fscanf(pfile, "%d", & l);
	fscanf(pfile, "%d", & c);


	
	alloue_grille(l, c, g);

	
	
	fscanf(pfile, "%d", & vivantes);
	for (n=0; n < vivantes; n++){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_vivante(i,j,*g);
	}

	fscanf(pfile, "%d", & non_viables);
	for(n=0; n < non_viables; n++){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_non_viable(i,j,*g);
	}
	


	fclose (pfile);
	return;
}


void alloue_grille (int l, int c, grille* g){
	g -> nbl = l;
	g -> nbc = c;
	g->cellules = (int**) malloc(l*sizeof(int*));
	for(int i = 0;i < l; i++){
        g->cellules[i] =(int*) calloc(c , sizeof(int));
	}

}


void libere_grille (grille* g){
	for (int i =0;i< (g->nbl) ;i++){
		free(g->cellules[i]);
	}
	free(g->cellules);
}


void copie_grille (grille gs, grille gd){
	int i, j;
	for (i=0; i<gs.nbl; ++i) for (j=0; j<gs.nbc; ++j) gd.cellules[i][j] = gs.cellules[i][j];
	return;	
}



int Equal_grilles(grille *ga, grille *gb) {
	int i, j;
	for (i = 0; i < ga->nbl; i++) {
		for (j = 0; j < ga->nbc; j++) {
			if (ga->cellules[i][j] != gb->cellules[i][j]) {
				return 0;
			}
		}
	}
	return 1;
}


int grille_vide(grille *g) {
	int i, j;
	for (i = 0; i < g->nbl; i++) {
		for (j = 0; j < g->nbc; j++) {
			if (g->cellules[i][j] > 0) {
				return 0;
			}
		}
	}
	return 1;
}




int oscillante(grille* g, int (*compte_voisins_vivants) (int, int, grille), int v){
	
	int t = 0;
	grille orig_copy, next_copy, tmpr;
	alloue_grille (g->nbl, g->nbc, &orig_copy);
	copie_grille(*g, orig_copy);

	alloue_grille (g->nbl, g->nbc, &next_copy);
	copie_grille(*g, next_copy);

	alloue_grille (g->nbl, g->nbc, &tmpr);
	copie_grille(*g, tmpr);

	int maxEvolutions = 1000; // max 1000 evo

	int maxOSC = 100; // max 100 osc
	int i = 0;
	 do {
		while (t < maxEvolutions) {
			evolue(&next_copy,&tmpr,compte_voisins_vivants,v);
			t++;
			if (grille_vide(&orig_copy)) {
				return 0;
			}
			if (Equal_grilles(&orig_copy, &next_copy)) {
				return t;
			}
		}

		evolue(&orig_copy,&tmpr,compte_voisins_vivants,v);
		copie_grille(orig_copy, next_copy);
		t = 0;
		i++;
	} while (i < maxOSC);


	return 0;
}



