#include "jeu.h"

int compte_voisins_vivants_non_cycl (int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);

	return v; 
}

int compte_voisins_vivants_cycl (int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	v+= est_vivante(modulo1(i-1,l),modulo1(j-1,c),g);
	v+= est_vivante(modulo1(i-1,l),modulo1(j,c),g);
	v+= est_vivante(modulo1(i-1,l),modulo1(j+1,c),g);
	v+= est_vivante(modulo1(i,l),modulo1(j-1,c),g);
	v+= est_vivante(modulo1(i,l),modulo1(j+1,c),g);
	v+= est_vivante(modulo1(i+1,l),modulo1(j-1,c),g);
	v+= est_vivante(modulo1(i+1,l),modulo1(j,c),g);
	v+= est_vivante(modulo1(i+1,l),modulo1(j+1,c),g);

	return v; 
}


void evolue (grille *g, grille *gc, int (*compte_voisins_vivants) (int, int, grille), int vj){
	copie_grille (*g,*gc); // copie temporaire de la grille
	int i,j,l=g->nbl, c = g->nbc,v;

	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{
			if (!est_non_viable(i, j, *g)){
				v = compte_voisins_vivants(i, j, *gc);
			
				if (est_vivante(i,j,*g)) 
				{ // evolution d'une cellule vivante
					if ( v!=2 && v!= 3 || g->cellules[i][j]>=8){
						 set_morte(i,j,*g);
					}else if(vj%2){
						g->cellules[i][j]++;
					}
				}
				else 
				{ // evolution d'une cellule morte
					if ( v==3 ) set_vivante(i,j,*g);
				}
			}
		}
	}
	return;
}


