

namespace Graphe
{
	/**
	 * \fn Graphe<T>:: Graphe (int nbSommet) throw (std::logic_error, std::bad_alloc)
	 *
	 * \param[in] nbSommet Le nombre de sommets total dans le graphe
	 */
	template <typename T>
	GrapheC<T>:: GrapheC (int nbSommet) throw (std::logic_error, std::bad_alloc)
	{
		if( nbSommet < 0) throw std::logic_error("Constructeur: nombre de sommet est négatif\n");

		nbNoeud = 0;
		nbNoeudMax = nbSommet;

		// Initialisation des tableaux de sommet et des listes d'adjacence
		tableauSommet = new T[nbNoeudMax];
		listeNoeud = new Noeud*[nbNoeudMax];

		for (int i = 0; i < nbSommet; i++)
		{
			listeNoeud[i] = 0; // Toutes les listes sont vides
		}

	}

	/**
	 * \fn Graphe<T>::  ~Graphe()
	 */
	template <typename T>
	GrapheC<T>::  ~GrapheC()
	{
		/* Supression de tous les arcs du graphe */
		for (int i = 0; i < nbNoeud; i++)
			for (int j=0; j< nbNoeud; j++)
				if(arcExiste(tableauSommet[i], tableauSommet[j])) enleverArc(tableauSommet[i],tableauSommet[j]);

		//on supprime les tableaux
		delete[] tableauSommet;
		delete[] listeNoeud;
	}

	/**
	 * \fn Graphe<T>:: Graphe(const Graphe& g)throw (std::bad_alloc)
	 *
	 * \param[in] g Le graphe source
	 */
	template <typename T>
	GrapheC<T>:: GrapheC(const GrapheC& g)throw (std::bad_alloc)
	{
		Noeud *courant, *nouveau;

		nbNoeud = g.nbNoeud;
		nbNoeudMax = g.nbNoeudMax;
		tableauSommet = new T[nbNoeudMax];
		listeNoeud = new Noeud*[nbNoeudMax];

		// Copie des sommets
		for (int i = 0; i < g.nbNoeud; i++)
		{
			tableauSommet[i] = g.tableauSommet[i];
		}

		// Copie de la liste des noeuds adjacents
		for (int i = 0; i < g.nbNoeud; i++)
		{
			if(g.listeNoeud[i]==0)
				listeNoeud[i] =0;
			else
			{
				nouveau = listeNoeud[i] = new Noeud;
				nouveau->sommet = g.listeNoeud[i]->sommet;
				nouveau->suivant =0;
				courant = g.listeNoeud[i]->suivant;
				while(courant!=0)
				{
					nouveau->suivant =  new Noeud;
					nouveau = nouveau->suivant;
					nouveau->sommet = courant->sommet;
					nouveau->suivant = 0;
					courant = courant->suivant;
				}
			}
		}
	}

	/**
	 * \fn Graphe<T>:: Graphe(const Graphe& g, const std::vector<T>& v) throw (std::bad_alloc)
	 *
	 * \param[in] g Le graphe source
	 * \param[in] v Un vector contenant des sommets
	 */
	template <typename T>
	GrapheC<T>:: GrapheC(const GrapheC& g, const std::vector<T>& v) throw (std::logic_error, std::bad_alloc)
	{
		Noeud *courant, *nouveau;

		nbNoeud = g.nbNoeud;
		nbNoeudMax = g.nbNoeudMax;

		tableauSommet = new T[nbNoeudMax];
		listeNoeud = new Noeud*[nbNoeudMax];

		/* Copie des sommets */
		for (int i = 0; i < g.nbNoeud; i++)
		{
			tableauSommet[i] = g.tableauSommet[i];
		}

		/* Copie de la liste des noeuds adjacents */
		for (int i = 0; i < g.nbNoeud; i++)
		{
			if(g.listeNoeud[i]==0)
				listeNoeud[i] =0;
			else
			{
				nouveau = listeNoeud[i] = new Noeud;
				nouveau->sommet = g.listeNoeud[i]->sommet;
				nouveau->suivant =0;
				courant = g.listeNoeud[i]->suivant;
				while(courant!=0)
				{
					nouveau->suivant =  new Noeud;
					nouveau = nouveau->suivant;
					nouveau->sommet = courant->sommet;
					nouveau->suivant = 0;
					courant = courant->suivant;
				}
			}
		}

		// Les noeuds dans le tableau tab doivent appartenir au Graphe g
		for ( size_t i = 0, size = v.size(); i < size; ++i )
		{
			bool existe = false;
			for (int j = 0; j < g.nbNoeud; j++)
			{
				if(v[i] == g.tableauSommet[j])
				{
					existe = true;
				}
			}
			if (!existe)
				throw std::logic_error("SousGraphe: le tableau contient des sommets inexistants.\n");
		}

		// Supression des sommets de tab
		for ( size_t i = 0, size = v.size(); i < size; ++i )
		{
			enleverSommet(v[i]);
		}
	}

	/**
	 * \fn const Graphe<T>& Graphe<T>:: operator = (const Graphe& g) throw (std::bad_alloc)
	 *
	 * \param[in] g Le graphe source qu'on veut affecter
	 * \return Un graphe, copie profonde de la source
	 */
	template <typename T>
	const GrapheC<T>& GrapheC<T>:: operator = (const GrapheC& g) throw (std::bad_alloc)
	{
		Noeud *courant, *nouveau;

		// Supression de tous les sommets du graphe
		for (int i = 0; i < nbNoeud; i++)
			for (int j=0; j< nbNoeud; j++)
				if(arcExiste(tableauSommet[i], tableauSommet[j])) enleverArc(tableauSommet[i], tableauSommet[j]);

		delete[] tableauSommet;
		delete[] listeNoeud;

		nbNoeud = g.nbNoeud;
		nbNoeudMax = g.nbNoeudMax;
		tableauSommet = new T[nbNoeudMax];
		listeNoeud = new Noeud*[nbNoeudMax];

		// Copie des sommets
		for (int i = 0; i < g.nbNoeud; i++)
		{
			tableauSommet[i] = g.tableauSommet[i];
		}

		// Copie de la liste des noeuds adjacents
		for (int i = 0; i < g.nbNoeud; i++)
		{
			if(g.listeNoeud[i]==0)
				listeNoeud[i] =0;
			else
			{
				nouveau = listeNoeud[i] = new Noeud;
				nouveau->sommet = g.listeNoeud[i]->sommet;
				nouveau->suivant =0;
				courant = g.listeNoeud[i]->suivant;
				while(courant!=0)
				{
					nouveau->suivant =  new Noeud;
					nouveau = nouveau->suivant;
					nouveau->sommet = courant->sommet;
					nouveau->suivant = 0;
					courant = courant->suivant;
				}
			}
		}
		return (*this);
	}

	/**
	 * \fn bool Graphe<T>:: sommetExiste(const T& s) const
	 *
	 * \param[in] s Le sommet qu'on veut vérifier sa présence dans le graphe
	 * \return VRAI si le sommet fait partie du graphe, FAUX sinon
	 */
	template <typename T>
	bool GrapheC<T>:: sommetExiste(const T& s) const
	{

		for (int j = 0; j < nbNoeud; j++)
		{
			if(s == tableauSommet[j])
				return  true;
		}

		return false;
	}

	/**
	 * \fn void Graphe<T>:: ajouterSommet(const T& s)  throw(std::length_error, std::logic_error)
	 *
	 * \param[in] s Le sommet qu'on veut ajouter dans le graphe
	 */
	template <typename T>
	void GrapheC<T>:: ajouterSommet(const T& s)  throw(std::length_error, std::logic_error)
	{
		if(sommetExiste(s)) throw std::logic_error("AjouterSommet: le sommet existe deja!\n");
		if (nbNoeud == nbNoeudMax) throw std::length_error("AjouterSommet: le nombre de sommets est au maximum\n");
		//notez qu'on peut allouer des tableaux plus grand et y transférer le contenu des tableaux "pleins"
		//on peut également représenter ces tableaux dans des vectors

		tableauSommet[nbNoeud] = s;
		listeNoeud[nbNoeud] = 0;
		nbNoeud++;
	}

	/**
	 * \fn 	void Graphe<T>:: ajouterArc (const T& s1, const T& s2)throw (std::logic_error, std::bad_alloc)
	 *
	 * \param[in] s1 Le sommet de départ de l'arc
	 * \param[in] s2 Le sommet d'arrivée de l'arc
	 */
	template <typename T>
	void GrapheC<T>:: ajouterArc (const T& s1, const T& s2)throw (std::logic_error, std::bad_alloc)
	{
		// Déterminer si les deux noeuds existe, si oui quel est leurs positions dans le tableau
		bool existeS1 = false;
		bool existeS2 = false;
		int n1;
		int n2;
		for(int i = 0; i < nbNoeud; i++)
		{
			if (s1 == tableauSommet[i])
			{
				n1 = i;
				existeS1 = true;
			}
			if (s2 == tableauSommet[i])
			{
				n2 = i;
				existeS2 = true;
			}
		}
		if(!existeS1 || !existeS2) // Si un des sommets n'existe pas
			throw std::logic_error("AjouterArc: un des 2 sommets est inexistant\n");

		Noeud* nouveau =  new Noeud;
		nouveau->sommet = s2;
		nouveau->suivant = 0;

		Noeud* courant = listeNoeud[n1];

		if(courant == 0) // Si la liste de noeuds est vide
		{
			listeNoeud[n1] = nouveau;
		}

		else // Si la liste de noeuds n'est pas vide
		{
			while(courant->suivant != 0)
			{
				courant = courant->suivant;
			}
			courant->suivant = nouveau;
		}

	}

	/**
	 * \fn void Graphe<T>:: enleverArc (const T& s1, const T& s2) throw(std::logic_error)
	 *
	 * \param[in] s1 Le sommet de départ de l'arc
	 * \param[in] s2 Le sommet d'arrivée de l'arc
	 */
	template <typename T>
	void GrapheC<T>:: enleverArc (const T& s1, const T& s2) throw(std::logic_error)
	{
		// Déterminer si les deux noeuds existe, si oui quel est leur position dans le tableau
		bool existeS1 = false;
		bool existeS2 = false;
		int n1;  // Posisiton du premier sommet dans le tableau
		int n2; // Position du deuxième sommet dans le tableau
		for(int i = 0; i < nbNoeud; i++)
		{
			if (s1 == tableauSommet[i])
			{
				n1 = i;
				existeS1 = true;
			}
			if (s2 == tableauSommet[i])
			{
				n2 = i;
				existeS2 = true;
			}
		}
		if(!existeS1 || !existeS2) /* Si un des sommets n'existe pas */
			throw std::logic_error("EnleverArc: un des 2 sommets est inexistant\n");

		// Déterminer la position du sommet S2 dans la liste des noeuds adjacents
		bool existeArc = false;
		bool chercher = true;
		int pos = 1;
		Noeud* courant = listeNoeud[n1];
		while((courant != 0) && chercher)
		{
			if (courant->sommet == s2)
			{
				existeArc = true;
				chercher = false;
			}

			else
			{
				courant = courant->suivant;
				pos++;
			}
		}
		if(!existeArc)
				throw std::logic_error("EnleverArc: l'arc a enlever est inexistant\n");

		/** Supression **/
		Noeud *aSupprimer;
		if (pos == 1) // Si le noeud à supprimer est le premier de la liste
		{
			aSupprimer = listeNoeud[n1];
			listeNoeud[n1] = listeNoeud[n1]->suivant;
		}
		else
		{
			courant = listeNoeud[n1] ;
			for (int i = 1; i < pos -1 ; i ++) // positionnement sur le noeud précédent à celui à supprimer
			{
				courant = courant->suivant;
			}

			aSupprimer = courant->suivant;
			courant->suivant = aSupprimer->suivant;
		}

		delete aSupprimer;
	}

	/**
	 * \fn void Graphe<T>:: enleverSommet (const T& s) throw(std::logic_error)
	 *
	 * \param[in] s Le sommet à enlever
	 */
	template <typename T>
	void GrapheC<T>:: enleverSommet (const T& s) throw(std::logic_error)
	{
		// Déterminer si le noeud existe, si oui quel est sa position dans le tableau
		int n; /* indice du sommet S dans le tableau */
		bool existe = false;
		for(int i = 0; i < nbNoeud; i++)
		{
			if (s == tableauSommet[i])
			{
				n = i;
				existe = true;
			}
		}
		if(!existe) // Si le sommet n'existe pas
			throw std::logic_error("EnleverSommet: le sommet est inexistant\n");

		// Destruction des arcs pointant sur ce noeud
		Noeud *courant;
		for(int i = 0; i < nbNoeud; i++)
		{
			courant = listeNoeud[i];
			while(courant != 0)
			{
				if(courant->sommet == s) // Si S est adjacent à ce noeud
				{
					courant = courant ->suivant; // On passe au suivant avant la destruction de ce noeud!
					try{
						enleverArc(tableauSommet[i], s);
					} catch(std::exception&)
					{
						std::cerr << "EnleverSommet: enleverArc a echoue\n";
						throw;
					}
				}
				else
				{
					courant = courant ->suivant;
				}
			}
		}

		// Destruction de la liste de noeuds adjacents correspondand à ce noeud
		courant = listeNoeud[n];
		while(listeNoeud[n] != 0)
		{
			try{
				enleverArc(s, listeNoeud[n]->sommet);
			} catch(std::exception&)
			{
				std::cerr << "EnleverSommet: enleverArc a echoue\n";
				throw;
			}
		}

		// Réduction du tableau des noeuds adjacents
		for(int i = n; i < nbNoeud - 1 ; i++)
		{
			listeNoeud[i] = listeNoeud[i + 1];
		}

		// Réduction du tableau de sommets
		for(int i = n; i < nbNoeud - 1 ; i++)
		{
			tableauSommet[i] = tableauSommet[i + 1];
		}
		nbNoeud--;
	}

	/**
	 * \fn bool Graphe<T>::arcExiste (const T& s1, const T& s2) const
	 *
	 * \param[in] s1 Le sommet de départ de l'arc
	 * \param[in] s2 Le sommet d'arrivée de l'arc
	 */
	template <typename T>
	bool GrapheC<T>::arcExiste (const T& s1, const T& s2) const
	{
		// Déterminer si les deux noeuds existe, si oui quel est leurs positions dans le tableau
		int n1;
		int n2;
		bool existeS1 = false;
		bool existeS2 = false;
		for(int i = 0; i < nbNoeud; i++)
		{
			if (s1 == tableauSommet[i])
			{
				n1 = i;
				existeS1 = true;
			}
			if (s2 == tableauSommet[i])
			{
				n2 = i;
				existeS2 = true;
			}
		}
		if(!existeS1 || !existeS2) // Si un des sommets n'existe pas
			return false;

		Noeud * courant = listeNoeud[n1];
		while(courant != 0)
		{
			if(courant->sommet == s2)
			{
				return true;
			}
			courant = courant->suivant;
		}
		return false;
	}

	/**
	 * \fn int Graphe<T>:: nbSommets() const
	 *
	 * \return Le nombre de sommets dans le graphe
	 */
	template <typename T>
	int GrapheC<T>:: nbSommets() const
	{
		return nbNoeud;
	}


	/**
	 * \fn void Graphe<T>:: affiche() const
	 */
	template <typename T>
	void GrapheC<T>:: affiche() const
	{
			if(nbNoeud==0)
					std::cout << "Le graphe graphe est vide \n";
			if(nbNoeud==1)
				std::cout << "Le contient un seul sommet: " << tableauSommet[0] << std::endl;

			else
			{       std::cout << "Le graphe comprend " << nbNoeud << " sommets" <<std::endl;
					for(int cpt=0;cpt<nbNoeud;cpt++)
						std::cout <<tableauSommet[cpt] << " ";

					std::cout << "\n";
					std::cout << "\nVoici tous ses arcs: \n";
					Noeud* tmp;
					int ind;
					for(int i=0;i<nbNoeud;i++)
					{
							tmp=listeNoeud[i];
							while(tmp)
							{
									//Chercher l'indice du sommet dans le tableau de sommet (changement effectué a ce niveau)
									for(int j=0;j<nbNoeud;j++) if(tableauSommet[j]==(tmp->sommet)) ind=j;
									std::cout << tableauSommet[i] << tableauSommet[ind]<<std::endl;
									tmp=tmp->suivant;
							}
							if( listeNoeud[i]!=0) std::cout << "\n";
					}
			}
	}

	/**
	 * \fn vector<T> Graphe<T>::listerSommetsGraphe() const throw(std::bad_alloc)
	 *
	 * \return Un vector de sommets dans le graphe
	 */
	template <typename T>
	std::vector<T> GrapheC<T>::listerSommetsGraphe() const throw(std::bad_alloc)
	{
			std::vector <T> v;

			for (int i=0; i < nbNoeud;i++)
			{
					v.push_back(tableauSommet[i]);
			}

		   return v;
	}

	/**
	 * \fn 	int Graphe<T>::ordreEntreeSommet(const T& sommet) const throw (std::logic_error)
	 *
	 * \param[in] sommet Le sommet dont on veut déteminer son ordre d'entrée
	 * \return L'ordre d'entrée de dommet
	 *
	 */
	template <typename T>
	int GrapheC<T>::ordreEntreeSommet(const T& sommet) const throw (std::logic_error)
	{
		int i=0;
		while (i < nbNoeud  && tableauSommet[i] != sommet)
		{
				i++;
		}

		if (i==nbNoeud)
			throw std::logic_error("OrdreEntreeSommet: le sommet n'existe pas\n");

		Noeud * N;
		int count=0;
		for (i=0;i<nbNoeud;i++)
		{
				N=listeNoeud[i];
				while(N)
				{
						if (N->sommet==sommet)
						count++;
						N=N->suivant;
				}
		}

		return count;
	}

	/**
	 * \fn std::vector<T> Graphe<T>::listerSommetsAdjacents(const T& sommet) const throw(std::logic_error, std::bad_alloc)
	 *
	 * \param[in] sommet Le sommet dont on cherche ses voisins
	 *
	 * \return Un vector des sommets adjacents à sommet
	 */
	template <typename T>
	std::vector<T> GrapheC<T>::listerSommetsAdjacents(const T& sommet) const throw(std::logic_error, std::bad_alloc)
	{
			std::vector<T> v;
			int i=0;
			/* recherche de Sommet dans tableauSommet*/
			while (i<nbNoeud && tableauSommet[i] != sommet)
			{
				  i++;
			}

			if (i==nbNoeud)
				throw std::logic_error("ListerSommetsAdjacents: le sommet n'existe pas\n");

			Noeud * N = listeNoeud[i];
			while(N)
			{
				v.push_back(N->sommet);
				N=N->suivant;
			}

		return v;
	}

	/**
	 * \fn int Graphe<T> ::ordreSortieSommet(const T& sommet) const throw (std::logic_error)
	 *
	 * \param[in] sommet Le sommet dont on veut déteminer son ordre de sortie
	 * \return L'ordre de sortie de dommet
	 */
	template <typename T>
	int GrapheC<T> ::ordreSortieSommet(const T& sommet) const throw (std::logic_error)
	{
			// recherche de Sommet dans tableauSommet
			int i=0;
			while (i <nbNoeud && tableauSommet[i] != sommet )
			{
					i++;
			}

			if (i==nbNoeud)
				throw std::logic_error("ListerSommetsAdjacents: le sommet n'existe pas\n");

			// compteur de noeuds adjacents à Sommet
			 Noeud * N=listeNoeud[i];
			 int count=0;
			while (N)
			{
					N=N->suivant;
					count++;
			}

			return count;
	}
}//Fin du namespace
