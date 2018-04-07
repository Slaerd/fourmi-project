const int TAILLE = 5;

struct coord{
	int x;
	int y;
};

struct fourmi{
	coord c;
	int sucre;
	int n;
};

struct tabFourmi{
    int tab[TAILLE];
    int nb; //nombre d'éléments du tableau
};

struct place{
	coord c;
	bool sucre;
	int fourmi;
	int phero;
	float nid;
};

struct ensCoord {
	coord tab[TAILLE];
	int nb;
};
	

//	BASIC fourmi
fourmi creerFourmi(int a, coord c);

coord coordFourmis(fourmi f);
int numFourmis(fourmi f);

bool porteSucre(fourmi f);
bool rentreNid(fourmi f);

void dechargerSucre(fourmi &f);
void chargerSucre(fourmi &f);
void deplaceFourmi(&fourmi, coord);

void chargerTabFourmis(fourmi &f; ensCord);

//	BASIC place
place creerPlaceVide(coord c);

coord coordPlace(place p);
float pheroNid(place p);
float pheroSucre(place p);
int numeroFourmi(place p);

bool contientSucre(place p);
bool contientNid(place p);
bool surUnePiste(place p);

void poserSucre(place &p);
void poserNid(place &p);
void poserFourmi(fourmi &f, place &p);
void enleverFourmi(place &p);
void poserPheroNid(place &p, float i);
void poserPheroSucre(place &p, float i);
void diminuerPheroSucre(place &p);

void deplacerFourmi(fourmi &f, place &p1, place &p2);

//	BASIC grille
void chargerGrilleVide(grille &g);

void chargerPlace(grille g, coord c, place &p);
void rangerPlace(grille &g, place p);

//Composes place
bool estVide(place p);
bool plusProcheNid(place p1, place p2);
bool plusLoinNid(place p1, place p2);

//Composes grille
void placerNid(grille &g, ensCoord ec);
void placerSucre(grille &g, ensCoord ec);
void placerFourmis(grille &g, tabFourmi t);
void lineariserPheroNid(grille &g);
void diminuerPheroSucreGrille(grille &g);
