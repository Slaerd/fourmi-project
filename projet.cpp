#include <projet.hpp>
#include <cstdlib>

const int TAILLE = 5;

{//Fourmi base

fourmi creerFourmi(int a, coord c){
    fourmi f;
    f.n = a;
    f.sucre = 0;
    f.c = c;
}

coord coordFourmis(fourmi f){
    return f.c;
}

int numFourmis(fourmi f){
    return f.n;
}

bool porteSucre(fourmi f){
    if(f.sucre > 0) return true;
    else return false;
}

bool rentreNid(fourmi f){
    return porteSucre(f);
}

void dechargerSucre(fourmi &f){
    f.sucre = 0;
}

void chargerSucre(fourmi &f){
    f.sucre++;
}

void deplaceFourmi(fourmi &f,coord c){
    f.c = c;
}

}

{//TabFourmi base

void chargerTabFourmis(tabFourmi &tf, ensCoord ec){
	for(int i=0; i<ec.nb; i++){
		tf.tab[i] = creerFourmi(i,ec.tab[i]);
		tf.nb++;
	}	
}

}

{//Place base

struct place{
	coord c;
	bool sucre;
	int fourmi;
	int phero;
	float nid;
};

place creerPlaceVide(coord c){
	place p;
	p.c = c;
	p.sucre = p.sucre = p.nid = p.phero = 0;
	p.fourmi = -1;
	return p;
}

coord coordPlace(place p){
	return p.c;
}
float pheroNid(place p){
	return p.nid;
}
int pheroSucre(place p){
	return p.phero;
}
int numeroFourmi(place p){
	return p.fourmi;
}

bool contientSucre(place p){
	return p.sucre;
}
bool contientNid(place p){
	return p.nid == 1;
}
bool surUnePiste(place p){
	return p.phero;
}

void poserSucre(place &p){
	p.sucre = true;
}
void poserNid(place &p){
	p.nid = 1.;
}
void poserFourmi(fourmi &f,place &p){
	p.fourmi = fourmi.n;
	fourmi.c = p.c;
}
void enleverFourmi(place &p){
	p.fourmi = -1;
}
void poserPheroNid(place &p, float i){
	p.nid = i;
}
void poserPheroSucre(place &p, float i){
	p.phero = i;
}
void diminuerPheroSucre(place &p){
	if(p.phero != 0) p.phero-= 5;
}

void deplacerFourmi(fourmi &f, place &p1, place &p2){
	poserFourmi(f,p2);
	enleverFourmi(p1);
}
}


{//Grile base

void chargerGrilleVide(grille &g){
	coord c;
	for(int i=0; i<TAILLE; i++){	//Faut voir pour les problèmes lie a TAILLE
		for(int j=0; j<TAILLE; j++){
			c = creerCoord(i,j);
			g.t[i][j] = creerPlaceVide(c);
		}
	}
}



}



//Composes
bool estVide(place p){
	b = numeroFourmi(p) == -1;
	b = b and not contientSucre(p);
	b = b and not contientNid(p);
	return (b and not surUnePiste(p));
}

bool plusProcheNid(place p1, place p2){
	return pheroNid(p1) > pheroNid(p2);
}

bool plusLoinNid(place p1, place p2){
	return pheroNid(p1) <= pheroNid(p2);
}

void placerNid(grille &g, ensCoord ec){
	for(int i = 0; i < ec.nb; i++){
		place p;
		chargerPlace(g,ec.tab[i],p);
		p.nid = 1.;
		rangerPlace(g,p);
	}
}

void placerSucre(grille &g, ensCoord ec){
	for(int i = 0; i < ec.nb; i++){
		place p;
		chargerPlace(g,ec.tab[i],p);
		p.sucre = true;
		rangerPlace(g,p);
	}
}

void placerFourmis(grille &g, tabFourmi t){
	for(int i = 0; i < t.nb; i++){
		place p;
		chargerPlace(g,t.c,p);
		p.fourmi = t.tab[i].n;
		rangerPlace(g,p);
	}
}

void initialiserGrille(grille &g,tabFourmi t, ensCoord ec_s, ensCoord ec_n,){
	placerNid(g,ec_n);
	placerSucre(g,ec_s);
	placerFourmis(g,t);
	//lineariserPheroNid(g);
}

void diminuerPheroSucreGrille(grille &g){
	for(int i = 0; i < TAILLE; i++){
		for(int j = 0; j < TAILLE; j++){
			//Vincent
}}}

//Checks

void coherence(tabFourmi t, grille g){
	for(int i = 0; i < t.nb; i++){
		if(t.tab[i].n != i) exit(1);
	//Vincent	
}}
	

	
	
