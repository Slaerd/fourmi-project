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