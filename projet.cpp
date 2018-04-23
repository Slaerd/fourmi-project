#include <cstdlib>
#include <vector>

////////////////// BASE fourmi //////////////////

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



/////////////////// BASE tabFourmi ////////////////////

void chargerTabFourmis(tabFourmi &tf, ensCoord ec){
	tf.nb = 0;
	for(int i=0; i<ec.nb; i++){
		tf.tab[i] = creerFourmi(i,ec.tab[i]);
		tf.nb++;
	}	
}



/////////////////// BASE place ////////////////////////

place creerPlaceVide(coord c){
	place p;
	p.c = c;
	p.sucre = p.nid = p.phero = 0;
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
	p.fourmi = f.n;
	deplaceFourmi(f,p.c);
}
void enleverFourmi(place &p){
	p.fourmi = -1;
}
void poserPheroNid(place &p, float i){
	p.nid = i;
}
void poserPheroSucre(place &p){
	p.phero = 255;
}
void diminuerPheroSucre(place &p){
	if(p.phero != 0) p.phero-= 5;
}

void deplacerFourmi(fourmi &f, place &p1, place &p2){
	poserFourmi(f,p2);
	enleverFourmi(p1);
}


/////////////////// BASE coord ////////////////////////
coord nouvCoord(int lin, int col){
	if(lin >= TAILLE or col >= TAILLE){
		cerr << "Depassement coordonnees." << endl;
		exit(1);
	}else{
		coord c;
		c.x = lin;
		c.y = col;
		return c;
	}
}

void afficheCoord(coord c){
	cout << "(" << c.x << "," << c.y << ")";
}

void afficheEnsCoord(ensCoord ec){
	cout << "[";
	for(int i = 0; i < ec.nb; i++){
		afficheCoord(ec.tab[i]);
		cout << "; ";
	}
	cout << "]" << endl;
}

ensCoord nouvEnsCoord(){
	ensCoord ec;
	ec.nb = 0;
	return ec;
}

bool egalCoord(coord c1, coord c2){
	return c1.x == c2.x and c1.y == c2.y;
}

void ajouteEnsCoord(ensCoord &ec, coord c){
	bool stop = false;
	for(int i = 0; i < ec.nb; i++){
		if(egalCoord(c,ec.tab[i]))
			stop = true;
	}
	if(!stop){
		ec.tab[ec.nb] = c;
		ec.nb++;
	}
}

int max(int a, int b){
	if(a > b)
		return a;
	else
		return b;
}
int min(int a, int b){
	if(a < b)
		return a;
	else 
		return b;
}
ensCoord voisines(coord c){
	ensCoord ec;
	ec = nouvEnsCoord();
	for(int i = max(c.x - 1, 0); i <= min(c.x + 1, TAILLE -1); i++){
		for(int j = max(c.y - 1, 0); j <= min(c.y + 1, TAILLE -1); j++){
			if(i != c.x or j != c.y){
				ajouteEnsCoord(ec,nouvCoord(i,j));
			}
		}
	}
	return ec;
}



//////////// COMPOSES ascendants ////////////////

bool estVide(place p){
	bool b = numeroFourmi(p) == -1;
	b = b and not contientSucre(p);
	return (b and not contientNid(p));
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
		if(estVide(p))
			poserNid(p);
		rangerPlace(g,p);
	}
}

void placerSucre(grille &g, ensCoord ec){
	for(int i = 0; i < ec.nb; i++){
		place p;
		chargerPlace(g,ec.tab[i],p);
		if(estVide(p))
			poserSucre(p);
		rangerPlace(g,p);
	}
}

void placerFourmis(grille &g, tabFourmi tf){
	for(int i = 0; i < tf.nb; i++){
		place p;
		chargerPlace(g,tf.tab[i].c,p);
		p.fourmi = tf.tab[i].n;
		rangerPlace(g,p);
	}
}

void initialiserGrille(grille &g,tabFourmi t, ensCoord ec_s, ensCoord ec_n){
	chargerGrilleVide(g);
	placerFourmis(g,t);
	placerNid(g,ec_n);
	placerSucre(g,ec_s);
	lineariserPheroNid(g);
}

void diminuerPheroSucreGrille(grille &g){
	for(int i = 0; i < TAILLE; i++){
		for(int j = 0; j < TAILLE; j++){
			diminuerPheroSucre(g[i][j]);
}}}

void lineariserPheroNid(grille &g){
	for(int k = 0; k < TAILLE; k++){
		for(int i = 0; i < TAILLE; i++){
			for(int j = 0; j < TAILLE; j++){
				ensCoord voisin = voisines(g[i][j].c);
				for(int v = 0; v < voisin.nb; v++){
					place p;
					chargerPlace(g,voisin.tab[v],p);
					g[i][j].nid = max(p.nid,g[i][j].nid);
				g[i][j].nid = max(0,g[i][j].nid-(1./TAILLE));
				}
			}
		}
	}
}

/////////////////// BASE grille ///////////////////////

void chargerGrilleVide(grille &g){
	coord c;
	for(int i=0; i<TAILLE; i++){	//Faut voir pour les problemes lie a TAILLE
		for(int j=0; j<TAILLE; j++){
			c = nouvCoord(i,j);
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

//////////// COMPOSES descendants ///////////////
bool condition_1(fourmi f, place p1, place p2){
	return not porteSucre(f) and contientSucre(p2);
}
	
void action_1(fourmi &f, place &p1, place &p2){
		chargerSucre(f);
		p2.sucre = false;
		poserPheroSucre(p1);
}

bool condition_2(fourmi f, place p1, place p2){
	return porteSucre(f) and contientNid(p2);
}

void action_2(fourmi &f, place &p1, place &p2){
		poserSucre(p2);
		dechargerSucre(f);
}
	
bool condition_3(fourmi f, place p1, place p2){
	return porteSucre(f) and estVide(p2) 
	and plusProcheNid(p2,p1);
}

void action_3(fourmi &f, place &p1, place &p2){
	deplacerFourmi(f,p1,p2);
	poserPheroSucre(p1);
}
	
bool condition_4(fourmi f, place p1, place p2){
	return not porteSucre(f) and surUnePiste(p1) and estVide(p2)
	and surUnePiste(p2) and plusLoinNid(p2,p1);
}

void action_4(fourmi &f, place &p1, place &p2){
	deplacerFourmi(f,p1,p2);
}
	
bool condition_5(fourmi f, place p1, place p2){
	return not porteSucre(f) and surUnePiste(p2) 
	and estVide(p2);
}

void action_5(fourmi &f, place &p1, place &p2){
	deplacerFourmi(f,p1,p2);
}

bool condition_6(fourmi f, place p1, place p2){
	return not porteSucre and estVide(p2);
}

void action_6(fourmi &f, place &p1, place &p2){
	deplacerFourmi(f,p1,p2);
}

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

void action_n(int regle, fourmi &f, place &p1, place &p2){
	switch(regle){
		case 1:
			action_1(f, p1, p2);
		case 2:
			action_2(f, p1, p2);
		case 3:
			action_3(f, p1, p2);
		case 4:
			action_4(f, p1, p2);
		case 5:
			action_5(f, p1, p2);
		case 6:
			action_6(f, p1, p2);
		default:
			cerr << "Regle " << regle << "inexistante." << endl;
			exit(1);
	}
}

void mettreAJourUneFourmi(grille &g, fourmi &f){
	place p1,p2,p_temp;
	chargerPlace(g,f.c,p1);
	ensCoord voisin = voisines(p1.c);
	vector<place> voisin_vide;
	int regle_app = 6;
	for(int regle = 1; regle < 7; regle++){
		for(int v = 0; v < voisin.nb; v++){
			chargerPlace(g,voisin.tab[v],p_temp);
			if(condition_n(regle,f,p1,p_temp) and regle <= regle_app){
				regle_app = regle;
				p2 = p_temp;
				if(regle_app == 6)
					voisin_vide.push_back(p2);
			}
		}
	}
	if(regle_app == 6)
		action_n(regle_app,f,p1,voisin_vide[rand()%voisin_vide.size()]);
	else
		action_n(regle_app,f,p1,p2);
	rangerPlace(g,p1);
	rangerPlace(g,p2);
}

void initialiserEmplacements(tabFourmi &tf, ensCoord &ec_sucre, ensCoord &ec_nid){
	//////// MANUEL //////////
	ensCoord ec_fourmi = nouvEnsCoord();
	/*int k, x, y;
	cout << "Nb fourmis ?" << endl;
	cin >> k;
	while(ec_fourmi.nb < k){
		cout << "x = "; cin >> x; cout << "  y = "; cin >> y;
		ajouteEnsCoord(ec_fourmi,nouvCoord(x,y));
	cout << endl << "Nb nid ?" << endl;
	cin >> k;
	while(ec_nid.nb < k){
		cout << "x = "; cin >> x; cout << "  y = "; cin >> y;
		ajouteEnsCoord(ec_nid,nouvCoord(x,y));
	cin >> k;
	while(ec_sucre.nb < k){
		cout << "x = "; cin >> x; cout << "  y = "; cin >> y;
		ajouteEnsCoord(ec_sucre,nouvCoord(x,y));
		chargerTabFourmis(tf,ec_fourmi);*/
		
	//////// AUTOBASE ////////////
	ajouteEnsCoord(ec_fourmi,nouvCoord(9,9));
	ajouteEnsCoord(ec_fourmi,nouvCoord(9,10));
	ajouteEnsCoord(ec_fourmi,nouvCoord(9,11));
	ajouteEnsCoord(ec_fourmi,nouvCoord(9,12));
	ajouteEnsCoord(ec_fourmi,nouvCoord(10,9));
	ajouteEnsCoord(ec_fourmi,nouvCoord(11,9));
	ajouteEnsCoord(ec_fourmi,nouvCoord(12,9));
	ajouteEnsCoord(ec_fourmi,nouvCoord(12,10));
	ajouteEnsCoord(ec_fourmi,nouvCoord(12,11));
	ajouteEnsCoord(ec_fourmi,nouvCoord(12,12));
	ajouteEnsCoord(ec_fourmi,nouvCoord(11,12));
	ajouteEnsCoord(ec_fourmi,nouvCoord(10,12));
	
	ajouteEnsCoord(ec_nid,nouvCoord(10,10));
	ajouteEnsCoord(ec_nid,nouvCoord(11,10));
	ajouteEnsCoord(ec_nid,nouvCoord(10,11));
	ajouteEnsCoord(ec_nid,nouvCoord(11,11));
	
	for(int i = 0; i < TAILLE; i++){
		ajouteEnsCoord(ec_sucre,nouvCoord(0,i));
		ajouteEnsCoord(ec_sucre,nouvCoord(i,0));
	}
	chargerTabFourmis(tf,ec_fourmi);
}

void dessinerGrille(grille &g){
	//REMPLIR
}

void mettreAJourEnsFourmis(grille &g, tabFourmi &tf){
	for(int i = 0; i < tf.nb; i++)
		mettreAJourUneFourmi(g, tf.tab[i]);
}


//////////// Checks ou Tests ////////////////////

void coherence(tabFourmi tf, grille g){
	for(int i = 0; i < tf.nb; i++){
		if(tf.tab[i].n != i) exit(1);
		if(i != g[tf.tab[i].c.x][tf.tab[i].c.y].fourmi);
	}
}



/*int programain(){
	grille g;
	tabFourmi tf;
	ensCoord ec_sucre = nouvEnsCoord(), ec_nid = nouvEnsCoord();
	initialiserEmplacements(tf, ec_sucre, ec_nid);
	initialiserGrille(g, tf, ec_sucre, ec_nid);
	while(true){
		dessinerGrille(g);
		mettreAJourEnsFourmis(g,tf);
		diminuerPheroSucreGrille(g);
	}
	return 0;
}*/
	
	

	
	
