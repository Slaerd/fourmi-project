#include <projet.hpp>


{//Fourmi base
/*Crée une fourmi ne portant pas de sucre
 * @param a l'indice de la fourmi dans tabFourmi
 * @param c les coordonnées de la fourmi
 * @return f une fourmi
*/
fourmi creerFourmi(int a, coord c){
    fourmi f;
    f.n = a;
    f.sucre = 0;
    f.c = c;
}


/*Retourne les coordonnées d'une fourmi
 * @param f fourmi
 * @return les coordonnées de la fourmi f
*/
coord coordFourmis(fourmi f){
    return f.c;
}

/*Retourne l'indice d'une fourmi
 * @param f fourmi
 * @return son indice dans le tableau des fourmis
*/
int numFourmis(fourmi f){
    return f.n;
}

/*Retourne vrai si la fourmi porte du sucre
 * @param f la fourmi
 * @return bool
*/
bool porteSucre(fourmi f){
    if(f.sucre > 0) return true;
    else return false;
}


/*Retourne vrai si la fourmi rentre au nid
 * @param f la fourmir
 * @return bool
*/
bool rentreNid(fourmi f){
    return porteSucre(f);
}

/*Supprime la charge portée par la fourmi
 * @param f la fourmi
*/
void dechargerSucre(fourmi &f){
    f.sucre = 0;
}

/*Ajoute une charge de sucre à la fourmi
 * @param f la fourmi
*/
void chargerSucre(fourmi &f){
    f.sucre++;
}


/*Déplace une fourmi
 * @param f la fourmi
*/
void déplaceFourmi(fourmi &f,coord c){
    f.c = c;
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
	

void deplacerFourmi(fourmi &f, place &p1, place &p2);
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

void placerNid(grille &g, ensCoord ec);
	