
#pragma once
#include<iostream>
#include "Algorithmes.h"

using namespace std;
using namespace Graphe;

/**
 * \fn int main (void)
 * \brief fonction principale.
 *
 * Un main() testeur de la classe Liste
 * \return 0 - Arrêt normal du programme.
 */
int main()
{
	try{
		{// fermeture transitive

				/*Construction du graphe (g1)*/
				GrapheC<int> g1(7); for(int i =1; i<=7; i++) g1.ajouterSommet(i);

				g1.ajouterArc(6,5);
				g1.ajouterArc(6,3);
				g1.ajouterArc(5,2);
				g1.ajouterArc(4,2);
				g1.ajouterArc(1,2);
				g1.ajouterArc(7,1);
				g1.ajouterArc(7,3);

				/*Construction du graphe (g2)*/
				GrapheC<int> g2(6); for(int i =1; i<=6; i++) g2.ajouterSommet(i);

				g2.ajouterArc(1,2);
				g2.ajouterArc(1,3);
				g2.ajouterArc(2,4);
				g2.ajouterArc(2,6);
				g2.ajouterArc(2,3);
				g2.ajouterArc(3,6);
				g2.ajouterArc(4,5);
				g2.ajouterArc(5,2);
				g2.ajouterArc(6,4);

				/*fermeture transitive du Graphe g1*/
				cout << "TEST  DE LA FERMETURE TRANSITIVE\n";
				cout << "\nFermeture transitive de (g1) \n";

				GrapheC<int> gf1(0);
				gf1 = fermetureGraphe (g1);
		        gf1.affiche();
				cout << "\n";

		 		cout<< "\nFermeture transitive de (g2) \n";
				GrapheC<int> gf2(0);
				gf2 = fermetureGraphe (g2);
				gf2.affiche();
				cout << "\n";
		}//fermeture

		{ // isConnexe

			/*Construction du graphe (g1)*/
				GrapheC<int> g1(6); for(int i=1; i<=6; i++) g1.ajouterSommet(i);
				g1.ajouterArc(1,2);
				g1.ajouterArc(1,3);
				g1.ajouterArc(2,4);
				g1.ajouterArc(2,6);
				g1.ajouterArc(2,3);
				g1.ajouterArc(3,6);
				g1.ajouterArc(4,5);
				g1.ajouterArc(5,2);
				g1.ajouterArc(6,4);

			/*Construction du graphe (g2)*/
				GrapheC<int> g2(12);for(int i=1; i<=12; i++) g2.ajouterSommet(i);
				g2.ajouterArc(2,4);
				g2.ajouterArc(2,8);
				g2.ajouterArc(2,6);
				g2.ajouterArc(2,10);
				g2.ajouterArc(2,12);
				g2.ajouterArc(3,6);
				g2.ajouterArc(3,9);
				g2.ajouterArc(3,12);
				g2.ajouterArc(4,8);
				g2.ajouterArc(4,12);
				g2.ajouterArc(5,10);
				g2.ajouterArc(6,12);

				/*Test de isConnexe*/
				cout << "TEST  DE ISCONNEXE\n\n";
				cout << "Graphe (g1)\n";
				if(isConnexe(g1))
					cout << "Le graphe g1 est connexe\n";
				else cout << "Le graphe g1 n'est pas connexe\n";

				cout << "\n\nGraphe (g2)\n";
				if(isConnexe(g2))
					cout << "Le graphe g2 est connexe\n";
					else cout << "Le graphe g2 n'est pas connexe\n\n";
		}//Fin isConnexe

		{// tri topologique

				/*Construction du graphe (g1)*/
				GrapheC<int> g1(7); for(int i =1; i<=7; i++) g1.ajouterSommet(i);

				g1.ajouterArc(6,5);
				g1.ajouterArc(6,3);
				g1.ajouterArc(5,2);
				g1.ajouterArc(4,2);
				g1.ajouterArc(1,2);
				g1.ajouterArc(7,1);
				g1.ajouterArc(7,3);

				/*Construction du graphe (g2)*/
				GrapheC<int> g2(6); for(int i =1; i<=6; i++) g2.ajouterSommet(i);

				g2.ajouterArc(1,2);
				g2.ajouterArc(1,3);
				g2.ajouterArc(2,4);
				g2.ajouterArc(2,6);
				g2.ajouterArc(2,3);
				g2.ajouterArc(3,6);
				g2.ajouterArc(4,5);
				g2.ajouterArc(5,2);
				g2.ajouterArc(6,4);

				/*Tri topologique du Graphe g1*/
				cout << "\nTri Topologique de (g1) \n";
		
				std::vector<int> v = triTopologique(g1);
				for ( size_t i = 0, size = v.size(); i < size; ++i )
					cout << v[i] << " ";
				cout << "\n";

				v.clear();
				/*test de tri topologique du Graphe g2: lancera une exception..devinez pourquoi!*/
		/*		cout<< "\nTri Topologique de (g2) \n";
				v=triTopologique(g2);
				cout << "Le resultat du tri Topologique de (g2):\n";
				for ( size_t i = 0, size = v.size(); i < size; ++i )
					cout << v[i] << " ";
				cout << "\n";
		*/
		}//Fin tri topologique
		
	} catch (std::exception& e)
	{
		cerr << e.what() << endl;
		return 0;
	}

	return 0;
}
