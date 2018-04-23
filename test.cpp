#include <iostream>
#include "projet.hpp"
#include "projet.cpp"
using namespace std;

#define ASSERT(test) if (!(test)) cout << "Test failed in file " << __FILE__ \
<< " line " << __LINE__ << ": " #test << endl



void afficheFourmi(fourmi f){
	cout << "Fourmi n : " << f.n << endl << "Sucre : " << f.sucre << endl << "Place : ("
	<< f.c.x << ";" << f.c.y << ")" << endl; 
}

void testCreerFourmi(){
	coord c; fourmi f;
	c.x = 3; c.y = 2;
	f = creerFourmi(4,c);
	ASSERT(f.n == 4 and egalCoord(f.c,c));
	c.x = 26; c.y = 3;
	f = creerFourmi(15,c);
	ASSERT(f.n == 15 and egalCoord(f.c,c));
}


void testCoordFourmis(){
	coord c;
	c.x = 14; c.y = 12;
	fourmi f = creerFourmi(1,c);
	ASSERT(egalCoord(coordFourmis(f),c));
	c.x = 2; c.y = 2;
	f = creerFourmi(24,c);
	ASSERT(egalCoord(coordFourmis(f),c));
}


void testNumFourmis(){
	fourmi f;
	f.n = 1;
	ASSERT(numFourmis(f) == 1);
	f.n = 24;
	ASSERT(numFourmis(f) == 24);
}


void testPorteSucre(){
	fourmi f;
	f.sucre = 3;
	ASSERT(porteSucre(f));
	f.sucre = 0;
	ASSERT(not porteSucre(f));	
}

void testRentreNid(){
	fourmi f;
	f.sucre = 3;
	ASSERT(rentreNid(f));
	f.sucre = 0;
	ASSERT(not rentreNid(f));
}

void testDechargerSucre(){
	fourmi f;
	f.sucre = 2;
	dechargerSucre(f);
	ASSERT(f.sucre == 0);
	f.sucre = 0;
	dechargerSucre(f);
	ASSERT(f.sucre == 0);
}

void testChargerSucre(){
	fourmi f;
	f.sucre = 2;
	chargerSucre(f);
	ASSERT(f.sucre == 3);
	f.sucre = 0;
	chargerSucre(f);
	ASSERT(f.sucre == 1);
}

void testDeplaceFourmi(){
	fourmi f;
	coord c;
	c.x = 2; c.y = 3;
	deplaceFourmi(f,c);
	ASSERT(egalCoord(f.c,c));
	c.x = 0; c.y = 0;
	deplaceFourmi(f,c);
	ASSERT(egalCoord(f.c,c));
	}

void testPlace(){
	coord c = nouvCoord(0,0);
	place p = creerPlaceVide(c);
	ASSERT(egalCoord(coordPlace(p),c));
	ASSERT(estVide(p) and pheroSucre(p) == 0);
	poserSucre(p);
	ASSERT(contientSucre(p));
	poserNid(p);
	ASSERT(contientNid(p));
	p.nid = 0;
	fourmi f = creerFourmi(0,nouvCoord(5,5));
	afficheFourmi(f);
	poserFourmi(f,p);
	afficheFourmi(f);
	ASSERT(numeroFourmi(p) == 0);
	enleverFourmi(p);
	ASSERT(p.fourmi == -1);
	poserPheroSucre(p);
	ASSERT(p.phero == 255);
	place p2 = creerPlaceVide(nouvCoord(2,3));
	poserFourmi(f,p2);
	afficheFourmi(f);
	deplacerFourmi(f,p2,p);
	ASSERT(numeroFourmi(p) == 0);
	ASSERT(numeroFourmi(p2) == -1);
	afficheFourmi(f);
}
	
int main(){
	/*tabFourmi tf;
	ensCoord ec_f = nouvEnsCoord();
	for(int i = 0; i < 5; i++)
		ajouteEnsCoord(ec_f,nouvCoord(i,i));
	chargerTabFourmi(tf,ec_f);
	for(int i = 0; i < tf.nb; i++)
		afficheFourmi(tf.tab[i]);*/
	testCreerFourmi();
	testCoordFourmis();
	testNumFourmis();
	testPorteSucre();
	testRentreNid();
	testDechargerSucre();
	testChargerSucre();
	testDeplaceFourmi();
	testPlace();
	return 0;
}
