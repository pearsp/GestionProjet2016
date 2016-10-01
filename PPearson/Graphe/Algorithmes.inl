#include <queue>
#include <list>
#include <stack>
/**
	* \Auteur: Patrick Pearson
	*		   Bobby Lavoie
	*
	* \Date de la dernière modification: 2014-12-11
	*
	* \brief Contient les algorithmes de graphes
	*
	*  
 */


/**
* \pre Le graphe n'est pas vide
*
* Permet de trouver la fermeture transitive d'un graphe et de retourner une instance de ce graphe
*
*/
template <typename T>
Graphe::GrapheC<T> fermetureGraphe (const Graphe::GrapheC<T> & g) throw(std::logic_error)
{
	int nbSommets = g.nbSommets(); //On stocke le nombre de sommets dans une variable
	GrapheC<T> gTranstive(g); //On fait une copie du graphe

	//On vérifie si le graphe est vide...
	_isEmptyGraph(g);

	//Pour chaque sommets K et pour chaque paire de noeuds {i,j}
	for (int k = 0; k < nbSommets; k++)
	{
		for (int i = 0; i < nbSommets; i++)
		{
			for (int j = 0; j < nbSommets;j++)
			{
				//Si il existe un arc qui va de i à k et un arc de k à j et que l'arc n'existe pas déjà...
				//Alors on ajoute un arc de i à j
				if (gTranstive.arcExiste(i,k) && gTranstive.arcExiste(k,j) && gTranstive.arcExiste(i,j) == false)
					gTranstive.ajouterArc(i,j);
			}
		}
	}

   return gTranstive;
}

/**
* \pre Le graphe n'est pas vide
*
* Permet de determiner si un Graphe est faiblement ou fortement connexe
*
*/
template <typename T>
bool isConnexe (const Graphe::GrapheC<T>& g) throw(std::logic_error)
{
	//Creation de la transposé du graphe
	Graphe::GrapheC<T> gTranspose(g.nbSommets());
	gTranspose = _getTranspose(g);

	// Si le graphe et sa transposé est connexe le graphe est connexe
	// Alors return true
	// Sinon un des deux n'est pas connexe et return false
	return _isConnexe(g) && _isConnexe(gTranspose);
}

/**
* \pre Le graphe n'est pas vide
* \pre Le graphe est acyclique
*
* Retourne une vecteur contenant les neuds du graphe triés topologiquement
*
*/
template <typename T>
std::vector<T> triTopologique(const Graphe::GrapheC<T>& g) throw (std::logic_error)
{
	int nbSommets = g.nbSommets();
	std::vector<T> vectTopological;
	std::vector<bool> vectVisited;

	//On vérifie si le graphe est vide...
	_isEmptyGraph(g);

	vectVisited.resize(nbSommets + 1);

	for (int i = 0; i < nbSommets; i++)
		vectVisited[i] = false;
 
	// Call the recursive helper function to store Topological Sort
	// starting from all vertices one by one
	for (int i = 0; i < nbSommets; i++)
	  if (vectVisited[i] == false)
		_DepthFirstSearch(i, vectVisited, vectTopological, g, nbSommets);

	return vectTopological;
}

//Fonction permettant de vérifier si le graphe est vide
template <typename T>
void _isEmptyGraph(const Graphe::GrapheC<T>& g) throw(std::logic_error)
{	
	//Si le graphe ne possède aucun sommet, alors on le considère comme vide et on lance une exception
	if( g.listerSommetsGraphe().size() == 0)
		throw std::logic_error("Impossible de trouver la fermeture d'un graphe vide!");
}

//Fonction permettant de retourner un object Graphe Transposé
template <typename T>
Graphe::GrapheC<T> _getTranspose(const Graphe::GrapheC<T>& g)
{
	Graphe::GrapheC<T> gTranspose(g.nbSommets()); //Creation d'un instance d'un Graphe Transposé
	std::vector<T> vecSommets = g.listerSommetsGraphe(); //Création d'un Vecteur contenant les sommets du graphes
	std::vector<T> vecAdjSommet; 

	// Ajout des sommets dans le Graphe transposé
	for (int i = 0; i < g.nbSommets(); i++)
		gTranspose.ajouterSommet(vecSommets[i]);

	// Pour tous les sommets v dans notre graphe
	for (int v = 0; v < gTranspose.nbSommets(); v++)
	{
		// Si le sommet correspondant existe dans la matrice des sommets
		if (g.sommetExiste(vecSommets[v])) 
		{
			// On remplit le veteur des sommets adjacents correspondant au sommet courant
			vecAdjSommet = g.listerSommetsAdjacents(vecSommets[v]); 

			//Pour tous les sommets adjacents
			for (int i = 0; i < vecAdjSommet.size(); i++)
			{
				//Ajout des arcs dans l'ordre inverse
				gTranspose.ajouterArc(vecAdjSommet[i], vecSommets[v]);
			}
		}
	}
	return gTranspose;
}

//Fonction privée permettant de déterminer si un graphe est connexe ou non
template <typename T>
bool _isConnexe(const Graphe::GrapheC<T>& g)
{
	int nbSommets = g.nbSommets();
	std::vector<bool> vectVisited;

	//On vérifie si le graphe est vide...
	_isEmptyGraph(g);

	//On redimensionne la Matrice conformément au nombre de noeuds
	vectVisited.resize(nbSommets + 1);

	//On initialise chaque case à FALSE
	for (int i = 0; i < nbSommets; i++)
		vectVisited[i] = false;

	//Appel de l'algorithme de parcours en profondeur, avec l'aide d'une matrice de Booléen on marque les noeuds  atteignables 
	_DepthFirstSearch(1, vectVisited, g, nbSommets);

	// Si le parcours en profondeur ne visite pas tous les noeuds...
	// Alors le graphe est faiblement connexe et on return false
	for (int i = 1; i <= nbSommets; i++)
		if (vectVisited[i] == false)
			return false;

	// Sinon le graphe est fortement connexe et on return true
	return true;
}

// Surcharge du parcours en profondeur permettant de marqué les noeuds atteints 
template <typename T>
void _DepthFirstSearch(int noNoeud, std::vector<bool> & vectVisited, const Graphe::GrapheC<T> & g, const int nbSommets)
{
	//Lorsque un sommet est atteint, on l'ajoute comme TRUE dans le vecteur de booléen
	vectVisited[noNoeud] = true;

	//Pour chaque paire de noeud entre le noeud courant et le noeud I
	for(int i = 0; i <= nbSommets; i++)
	{
		//Si un arc existe entre les deux noeuds 
		//Alors on appel récursivement la fonction de parcours en profondeur
		if(g.arcExiste(noNoeud, i) && vectVisited[i] != true)
			_DepthFirstSearch(i, vectVisited, g, nbSommets);
	}
}

// Surcharge du parcours en profondeur permettant de remplir le vecteur avec les données triées topologiquement
template <typename T>
void _DepthFirstSearch(int noNoeud, std::vector<bool> vectVisited, std::vector<T> & vectTopological, const Graphe::GrapheC<T> & g, const int nbSommets)
{
	// Marquer le noeud courant comme visité
	vectVisited[noNoeud] = true;
 
	//Pour chaque paire de noeud entre le noeud  courant et le noeud I
	for (int i = 1; i <= nbSommets; i++)
	{
		//Si un arc existe entre les deux noeuds 
		//Alors on appel récursivement la fonction de parcours en profondeur
		if (g.arcExiste(noNoeud, i) && vectVisited[i] != true)
			_DepthFirstSearch(i, vectVisited, vectTopological, g, nbSommets);
	}
 
	// Ajouter le noeud courant au vecteur des noeuds triés topologiquement, si il n'est pas déjà dans le vecteur
	if(std::find(vectTopological.begin(), vectTopological.end(), g.listerSommetsGraphe().at(noNoeud)) == vectTopological.end())
		vectTopological.push_back(g.listerSommetsGraphe().at(noNoeud));
}
