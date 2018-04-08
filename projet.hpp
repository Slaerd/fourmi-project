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
    fourmi tab[TAILLE];
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


struct grille{
	vector<vector<place>> t;
};
	

{//	BASIC fourmi
/*Cree une fourmi ne portant pas de sucre
 * @param a l'indice de la fourmi dans tabFourmi
 * @param c les coordonnées de la fourmi
 * @return f une fourmi
*/
fourmi creerFourmi(int a, coord c);

/*Retourne les coordonnées d'une fourmi
 * @param f fourmi
 * @return les coordonnées de la fourmi f
*/
coord coordFourmis(fourmi f);

/*Retourne l'indice d'une fourmi
 * @param f fourmi
 * @return son indice dans le tableau des fourmis
*/
int numFourmis(fourmi f);

/*Retourne vrai si la fourmi porte du sucre
 * @param f la fourmi
 * @return bool
*/
bool porteSucre(fourmi f);

/*Retourne vrai si la fourmi rentre au nid
 * @param f la fourmir
 * @return bool
*/
bool rentreNid(fourmi f);

/*Supprime la charge portée par la fourmi
 * @param f la fourmi
*/
void dechargerSucre(fourmi &f);

/*Ajoute une charge de sucre a la fourmi
 * @param f la fourmi
*/
void chargerSucre(fourmi &f);

/*Deplace une fourmi
 * @param f la fourmi
*/
void deplaceFourmi(&fourmi, coord);
}

/**Crée un ensemble de fourmi positionnees aux coordonnees spécifiees par l'ensemble de coordonnees donné en 2eme parametre
 * @param[out] tf un tabFourmi
 * @param[in] ec un ensCoord
**/
void chargerTabFourmis(tabFourmi &tf, ensCoord ec);


//	BASIC place
/*Cree une place vide
 *@param c les coordonnées de la place
 *@return la place
 */
place creerPlaceVide(coord c);

/*Donne la coordonnee d'une place
 *@param p la place
 *@return la coordonnee
 */
coord coordPlace(place p);
/*Donne l'intensite des pheromones de nid sur la place
 *@param p la place
 *@return l'intensite
 */
float pheroNid(place p);

/*Donne l'intensite des pheromones de sucre sur la place
 *@param p la place
 *@return l'intensite
 */
int pheroSucre(place p);
 
/*Donne le numero eventuel de la fourmi sur la place
 *@param p la place
 *@return le numero de la fourmi
 */
int numeroFourmi(place p);

/*Verifie si une place contient du sucre
 *@param p la place
 *@return oui ou non
 */
bool contientSucre(place p);

/*Verifie si une place contient un element de nid
 *@param p la place
 *@return oui ou non
 */
bool contientNid(place p);

/*Verifie si une place contient des pheromones de sucre
 *@param p la place
 *@return oui ou non
 */
bool surUnePiste(place p);

/*Pose du sucre sur une place
 *@param/res p la place
 */
void poserSucre(place &p);

/*Pose un element de nid sur une place
 *@param/res p la place
 */
void poserNid(place &p);

/*Pose une fourmi sur une place
 *@param/res f la fourmi
 *@param/res p la place
 */
void poserFourmi(fourmi &f, place &p);

/*Enleve eventuellement une fourmi d'une place
 *@param/res p la place
 */
void enleverFourmi(place &p);

/*Pose une pheromone de nid d'une certaine intensite sur une place
 *@param/res p la place
 */
void poserPheroNid(place &p, float i);

/*Pose des pheromone de sucre d'une certaine intensite sur une place
 *@param/res p la place
 */
void poserPheroSucre(place &p, float i);

/*Diminue l'intensite de la pheromone de sucre de 5
 *@param/res p la place
 */
void diminuerPheroSucre(place &p);

/*Deplace une fourmi d'une place a une autre
 *@param/res f la fourmi
 *@param/res p1 la place de depart
 *@param/res p2 la place d'arrivee
 */
void deplaceFourmi(fourmi &f, place &p1, place &p2);

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
