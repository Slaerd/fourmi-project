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

bool egalFourmi(fourmi f1, fourmi f2){
	return f1.n == f2.n and f1.sucre == f2.sucre and egalCoord(f1.c,f2.c);
}


void testBaseFourmi(){
	//creerFourmis
	coord c; fourmi f;
	c.x = 3; c.y = 2;
	f = creerFourmi(4,c);
	ASSERT(f.n == 4 and egalCoord(f.c,c));
	c.x = 26; c.y = 3;
	f = creerFourmi(15,c);
	ASSERT(f.n == 15 and egalCoord(f.c,c));
	
	//coordFourmis
	c.x = 14; c.y = 12;
	f = creerFourmi(1,c);
	ASSERT(egalCoord(coordFourmis(f),c));
	c.x = 2; c.y = 2;
	f = creerFourmi(24,c);
	ASSERT(egalCoord(coordFourmis(f),c));
	
	//numFourmis
	f.n = 1;
	ASSERT(numFourmis(f) == 1);
	f.n = 24;
	ASSERT(numFourmis(f) == 24);
	
	//porteSucre
	f.sucre = 3;
	ASSERT(porteSucre(f));
	f.sucre = 0;
	ASSERT(not porteSucre(f));
	
	//rentreNid
	f.sucre = 3;
	ASSERT(rentreNid(f));
	f.sucre = 0;
	ASSERT(not rentreNid(f));
	
	//dechargerSucre
	f.sucre = 2;
	dechargerSucre(f);
	ASSERT(f.sucre == 0);
	f.sucre = 0;
	dechargerSucre(f);
	ASSERT(f.sucre == 0);
	
	//chargerSucre
	f.sucre = 2;
	chargerSucre(f);
	ASSERT(f.sucre == 3);
	f.sucre = 0;
	chargerSucre(f);
	ASSERT(f.sucre == 1);
	
	//deplaceFourmi
	c.x = 2; c.y = 3;
	deplaceFourmi(f,c);
	ASSERT(egalCoord(f.c,c));
	c.x = 0; c.y = 0;
	deplaceFourmi(f,c);
	ASSERT(egalCoord(f.c,c));
}

void testPlace(){
	/// BASE ///
	coord c = nouvCoord(0,0);
	place p = creerPlaceVide(c);
	ASSERT(egalCoord(coordPlace(p),c));
	ASSERT(estVide(p) and pheroSucre(p) == 0);
	
	poserSucre(p);
	ASSERT(contientSucre(p) and !estVide(p));
	
	poserNid(p);
	ASSERT(contientNid(p));
	p.nid = 0;
	
	fourmi f = creerFourmi(0,nouvCoord(5,5));
	poserFourmi(f,p);
	ASSERT(numeroFourmi(p) == 0);
	enleverFourmi(p);
	ASSERT(p.fourmi == -1);
	
	poserPheroSucre(p);
	ASSERT(p.phero == 255);
	
	place p2 = creerPlaceVide(nouvCoord(2,3));
	poserFourmi(f,p2);
	deplacerFourmi(f,p2,p);
	ASSERT(numeroFourmi(p) == 0);
	ASSERT(numeroFourmi(p2) == -1);
	
	/// COMPOSES ///
	p = creerPlaceVide(nouvCoord(15,15));
	p2 = creerPlaceVide(nouvCoord(11,11));
	poserPheroNid(p, 1.);
	poserPheroNid(p2,0.5);
	ASSERT(plusProcheNid(p,p2));
	ASSERT(plusLoinNid(p2,p));
}

void testCoord(){
	coord c = nouvCoord(10,10);
	ASSERT(c.x == 10 and c.y == 10);
	
	ensCoord ec = nouvEnsCoord();
	ASSERT(ec.nb == 0);
	ajouteEnsCoord(ec,c);
	ASSERT(ec.nb == 1 and egalCoord(ec.tab[0],c));
	ajouteEnsCoord(ec,c);
	ASSERT(ec.nb == 1 and egalCoord(ec.tab[0],c));
	
	c = nouvCoord(11,11);
	ajouteEnsCoord(ec,c);
	ASSERT(ec.nb == 2 and egalCoord(ec.tab[1],c));
	
	ensCoord voisin = voisines(nouvCoord(2,2));
	//afficheEnsCoord(voisin);
}

void testGrille(){
	/// BASE ///
	grille g;
	chargerGrilleVide(g);
	for(int i = 0; i < TAILLE; i++){
		for(int j = 0; j < TAILLE; j++)
			ASSERT(egalCoord(g[i][j].c,nouvCoord(i,j)));
	}
	
	place p;
	chargerPlace(g,nouvCoord(1,1),p);
	p.fourmi = 1;
	p.phero = 255;
	rangerPlace(g,p);
	ASSERT(g[1][1].fourmi == 1 and g[1][1].phero == 255);
	
	/// COMPOSES ///
	chargerGrilleVide(g);
	ensCoord ec_nid, ec_sucre, ec_fourmi;
	tabFourmi tf;
	ec_nid = ec_sucre = ec_fourmi = nouvEnsCoord();
	for(int i = 0; i < TAILLE; i++){
		ajouteEnsCoord(ec_nid,nouvCoord(i,i));
		if(i != 0){
			ajouteEnsCoord(ec_sucre,nouvCoord(i,0));
			ajouteEnsCoord(ec_fourmi,nouvCoord(0,i));
		}
	}
	
	chargerTabFourmis(tf, ec_fourmi);
	placerFourmis(g,tf);
	placerNid(g,ec_nid);
	placerSucre(g,ec_sucre);
	
	for(int i = 0; i < TAILLE; i++){
		ASSERT(g[i][i].nid == 1.);
		if(i != 0){
			ASSERT(i-1 == g[0][i].fourmi);
			ASSERT(g[i][0].sucre == 1);
		}
	}
	
	// initialiserGrille(g,tf,ec_sucre,ec_nid);
	// for(int i = 0; i < TAILLE; i++){
		// for(int j = 0; j < TAILLE; j++)
			// cout << g[i][j].nid << " ";
		// cout << endl;
	// }
	
	chargerGrilleVide(g);
	// for(int i = 0; i < TAILLE; i++)
		// g[i][i].phero = 255;
	// while(g[0][0].phero != 0){		
		// for(int i = 0; i < TAILLE; i++){
			// for(int j = 0; j < TAILLE; j++)
				// cout << g[i][j].phero << " ";
			// cout << endl;
		// }
		// diminuerPheroSucreGrille(g);
	// }	
}

void testMouvement(){
	grille g;
	place pf,p1,p2,p3;
	chargerGrilleVide(g);
	
	/// MOUVEMENTS UNAIRES ///
	
	fourmi f = creerFourmi(0,nouvCoord(0,0));
	chargerPlace(g,f.c,pf);
	chargerPlace(g,nouvCoord(1,1),p1);
	poserFourmi(f,pf);
	poserSucre(p1);
	ASSERT(condition_1(f,pf,p1));
	action_1(f,pf,p1);
	ASSERT(numeroFourmi(pf) == 0 and porteSucre(f) and !contientSucre(p1) and surUnePiste(pf));
	
	poserNid(p1);
	ASSERT(!condition_3(f,pf,p1));
	ASSERT(condition_2(f,pf,p1));
	action_2(f,pf,p1);
	ASSERT(!porteSucre(f) and contientSucre(p1));
	
	chargerGrilleVide(g);
	poserNid(g[10][10]);
	poserNid(g[10][11]);
	poserNid(g[11][10]);
	poserNid(g[11][11]);
	lineariserPheroNid(g);
	
	poserFourmi(f,pf);
	chargerSucre(f);
	chargerPlace(g,nouvCoord(1,1),p1);
	ASSERT(condition_3(f,pf,p1));
	action_3(f,pf,p1);
	ASSERT(numeroFourmi(pf) == -1 and surUnePiste(pf) and numeroFourmi(p1) == f.n);
	
	dechargerSucre(f);
	poserPheroSucre(p1);
	ASSERT(condition_4(f,p1,pf));
	action_4(f,p1,pf);
	ASSERT(numeroFourmi(pf) == f.n and numeroFourmi(p1) == -1);
	
	chargerPlace(g,nouvCoord(0,1),p2);
	deplacerFourmi(f,pf,p2);
	ASSERT(condition_5(f,p2,pf));
	action_5(f,p2,pf);
	ASSERT(numeroFourmi(pf) == f.n and numeroFourmi(p2) == -1);
	
	ASSERT(condition_6(f,pf,p1));
	action_6(f,pf,p1);
	ASSERT(numeroFourmi(pf) == -1 and numeroFourmi(p2) == -1);
	
	/// MISE A JOUR COMPLETE ///
	
	chargerGrilleVide(g);
	poserNid(g[10][10]);
	poserNid(g[10][11]);
	poserNid(g[11][10]);
	poserNid(g[11][11]);
	lineariserPheroNid(g);
	
	int cpt = 0;
	/// Regle 1 + 2 ///
	// f = creerFourmi(0,nouvCoord(9,9)); 
	
	// poserFourmi(f, g[9][9]); 
	// poserSucre(g[8][8]); 
	// poserSucre(g[9][8]);
	// cpt = 0;
	
	// while(g[10][10].sucre == 0){
		// mettreAJourUneFourmi(g,f);
		// cpt++;
	// }	
	// ASSERT(contientSucre(g[10][10]) and !contientSucre(g[8][8]));
	
	/// Regle 2 + 3 ///
	// f = creerFourmi(0,nouvCoord(6,6));
	// chargerSucre(f);
	// cpt = 0;
	
	// while(g[10][10].sucre == 0 and cpt < 10){
		// mettreAJourUneFourmi(g,f);
		// cpt++;
	// }
	
	// ASSERT(contientSucre(g[10][10]) and !porteSucre(f));
	
	/// BLOQUE ///
	// tabFourmi tf;
	// ensCoord ec_fourmi;
	// for(int i = 0; i < 3; i++){
		// for(int j = 0; j < 3; j++){
			// ajouteEnsCoord(ec_fourmi,nouvCoord(i,j));
		// }
	// }
	// chargerTabFourmis(tf,ec_fourmi);
	// placerFourmis(g,tf);
	
	// while(cpt < 10){
		// mettreAJourUneFourmi(g,tf.tab[4]);
		// cpt++;
	// }	
	// ASSERT(egalCoord(tf.tab[4].c,nouvCoord(1,1)));
	f = creerFourmi(0,nouvCoord(6,6));
	while(g[10][10].sucre == 0 and cpt < 100){
		mettreAJourUneFourmi(g,f);
		//cout << "splitchan" << endl;
		cpt++;
	}	
	
	
	while(g[10][10].sucre == 0 and cpt < 10){
		mettreAJourUneFourmi(g,f);
		//cout << "splitchan" << endl;
		cpt++;
	}	
	
	
}
	
	
	

int main(){
	testCreerFourmi();
	testCoordFourmis();
	testNumFourmis();
	testPorteSucre();
	testRentreNid();
	testDechargerSucre();
	testChargerSucre();
	testDeplaceFourmi();
	testPlace();
	testCoord();
	testGrille();
	testMouvement();
	return 0;
}
