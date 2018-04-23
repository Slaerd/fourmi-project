#include <iostream>
#include <projet.hpp>
#include <projet.cpp>
using namespace std;

#define ASSERT(test) if (!(test)) cout << "Test failed in file " << __FILE__ \
<< " line " << __LINE__ << ": " #test << endl



void afficheFourmi(fourmi f){
	cout << "Fourmi n : " << f.n << endl << "Sucre : " << f.sucre << endl << "Place : ("
	<< f.c.x << ";" << f.c.y << ")" << endl; 
}

void testFourmi();

void testCreerFourmi(){
	coord c; fourmi f;
	c.x = 3; c.y = 2;
	f = creerFourmi(4,c);
	ASSERT(f.n == 4 and f.c = c);
	c.x = 26; c.y = 3;
	f = creerFourmi(15,c);
	ASSERT(f.n == 15 and f.c = c);
}


void testCoordFourmis(){
	coord c;
	c.x = 14; c.y = 12;
	fourmi f = creerFourmi(1,c);
	ASSERT(coordFourmis(f) == c);
	c.x = 2; c.y = 2;
	f = creerFourmi(24,c);
	ASSERT(coordFourmis(f) == c);
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
	ASSERT(f.c == c);
	c.x = 0; c.y = 0;
	deplacefourmi(f,c);
	ASSERT(f.c == c);
}


int main(){
	tabFourmi tf;
	ensCoord ec_f = nouvEnsCoord();
	for(int i = 0; i < 5; i++)
		ajouteEnsCoord(ec_f,nouvCoord(i,i));
	chargerTabFourmi(tf,ec_f);
	for(int i = 0; i < tf.nb; i++)
		afficheFourmi(tf.tab[i]);
	return 0;
}
