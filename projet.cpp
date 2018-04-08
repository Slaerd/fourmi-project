#include <projet.hpp>
#include <cstdlib>

const int TAILLE = 5;

{////////////////// BASE fourmi //////////////////

fourmi creerFourmi(int a, coord c){
    fourmi f;
    f.n = a;
    f.sucre = 0;
    f.c = c;
	return f;
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

{/////////////////// BASE tabFourmi ////////////////////

void chargerTabFourmis(tabFourmi &tf, ensCoord ec){
	for(int i=0; i<ec.nb; i++){
		tf.tab[i] = creerFourmi(i,ec.tab[i]);
		tf.nb++;
	}	
}

}

{/////////////////// BASE place ////////////////////////

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
	p.sucre++;
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


{/////////////////// BASE grille ///////////////////////

void chargerGrilleVide(grille &g){
	coord c;
	for(int i=0; i<TAILLE; i++){	//Faut voir pour les problèmes lie a TAILLE
		for(int j=0; j<TAILLE; j++){
			c = creerCoord(i,j);
			g[i][j] = creerPlaceVide(c);
		}
	}
}

void chargerPlace(grille g,coord c, place &p){
	p = g[c.x][c.y];
}

void rangerPlace(grille &g, place p){
	g[p.c.x][p.c.y] = p;
}


}



{//////////// COMPOSES ascendants ////////////////
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
		poserNid(p);
		rangerPlace(g,p);
	}
}

void placerSucre(grille &g, ensCoord ec){
	for(int i = 0; i < ec.nb; i++){
		place p;
		chargerPlace(g,ec.tab[i],p);
		poserSucre(p);
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

void initialiserGrille(grille &g,tabFourmi t, ensCoord ec_s, ensCoord ec_nid){
	chargerGrilleVide(g);
	placerNid(g,ec_n);
	placerSucre(g,ec_s);
	placerFourmis(g,t);
	//lineariserPheroNid(g);
}

void diminuerPheroSucreGrille(grille &g){
	for(int i = 0; i < TAILLE; i++){
		for(int j = 0; j < TAILLE; j++){
			g[i][j].phero = g[i][j].phero - 5;
}}}
}

{//////////// COMPOSES descendants ///////////////
bool condition_1(fourmi f, place p1, place p2){
	return not porteSucre(f) and contientSucre(p2);
}
	
void action_1(fourmi &f, place &p1, place &p2){
	if(condition_1(f,p1,p2){
		chargerSucre(f);
		p2.sucre = false;
		poserPheroSucre(p1, 255);
	}
}
bool condition_2(fourmi f, place p1, place p2){
	return porteSucre(f) and contientNid(p2);
}

void action_2(fourmi &f, place &p1, place &p2){
	if(condition_2(f,p1,p2)){
		poserSucre(p2);
		dechargerSucre(f);
	}
}
	
bool condition_3(fourmi f, place p1, place p2){
	return porteSucre(f) and estVide(p2) 
	and plusProcheNid(p2,p1);
}

void action_3(fourmi &f, place &p1, place &p2){
	
bool condition_4(fourmi f, place p1, place p2){
	return not porteSucre(f) and surUnePiste(p1) 
	and surUnePiste(p2) and plusLoinNid(p2,p1);
}

void action_4(fourmi &f, place &p1, place &p2){
	
bool condition_5(fourmi f, place p1, place p2){
	return not porteSucre(f) and surUnePiste(p2) 
	and estVide(p2);
}

void action_5(fourmi &f, place &p1, place &p2){
bool condition_6(fourmi f, place p1, place p2){
	return not porteSucre and estVide(p2);
}

void action_6(fourmi &f, place &p1, place &p2){

bool condition_n(int regle, fourmi f, place p1, place p2){
	switch(regle){
		case 1:
			return condition_1(f, p1, p2);
		case 2:
			return condition_2(f, p1, p2);
		case 3:
			return condition_3(f, p1, p2);
		case 4:
			return condition_4(f, p1, p2);
		case 5:
			return condition_5(f, p1, p2);
		case 6:
			return condition_6(f, p1, p2);
		default:
			cerr << "Regle " << regle << "inexistante." << endl;
			exit(1);
	}
}
void mettreAJourUneFourmi(grille &g, fourmi &f);

void initialiserEmplacements(tabFourmi &t, ensCoord &ec_sucre, ensCoord &ec_nid);
void dessinerGrille(grille &g);
void mettreAJourEnsFourmis(grille &g, tabFourmi &t){
	for(int i = 0; i < t.nb; i++)
		mettreAJourUneFourmi(g, t.tab[i]);
}
}

{//////////// Checks ou Tests ////////////////////

void coherence(tabFourmi t, grille g){
	for(int i = 0; i < t.nb; i++){
		if(t.tab[i].n != i) exit(1);
	//Vincent	
}}
	
int main(){
	grille g;
	tabFourmi t;
	ensCoord ec_sucre, ec_nid;
	initialiserEmplacements(tabFourmi &t, ensCoord &ec_sucre, ensCoord &ec_nid);
	initialiserGrille(g, t, ec_sucre, ec_nid);
	while(true){
		dessinerGrille(g);
		mettreAJourEnsFourmis(g,t);
	}
	return 0;
}
	
	

	
	
