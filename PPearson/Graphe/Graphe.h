
#pragma once
#ifndef _GRAPHE_H
#define _GRAPHE_H

#include <iostream>
#include <stdexcept>
#include <vector>

#pragma warning( disable : 4290 )

namespace Graphe
{
	/**
	* \class Graphe
	*
	* \brief classe générique représentant un graphe
	*
	*  La classe gère un graphe générique. L'implémentation
	*  se fait par des listes d'adjacence.
	*/
	template <typename T>
	class GrapheC
	{
	public:
		/**
		 *  \brief Constructeur
		 *
		 *  \pre Il faut qu'il y ait suffisamment de mémoire
		 *  \pre nbSommet > 0
		 *  \post Une instance de la classe Graphe avec nbSommet est initialisée
		 *  \exception bad_alloc si la mémoire est insuffisante
		 *  \exception logic_error si nbSommet <= 0
		 */
		explicit GrapheC (int nbSommet)throw (std::logic_error, std::bad_alloc);

		/**
		 *  \brief Constructeur de copie
		 *
		 *  \pre Il faut qu'il y ait suffisamment de mémoire
		 *  \post une copie profonde du graphe source est instanciée
		 *  \exception bad_alloc s'il n'y a pas assez de mémoire
		 */
		GrapheC (const GrapheC&)throw (std::bad_alloc);

		/**
		 *  \brief Constructeur sous-Graphe
		 *
		 * \pre Il faut qu'il y ait suffisamment de mémoire
		 * \pre Les sommets dans le vector doivent appartenir au graphe g
		 * \post une copie profonde du graphe est instancieé, le graphe source en moins les sommets contenus dans le vector
		 * \exception bad_alloc s'il n'y a pas assez de mémoire
		 * \exception logic_error si les sommets dans le vector n'appartiennent pas à g
		 */
		GrapheC(const GrapheC& g,  const std::vector<T>&)throw(std::logic_error, std::bad_alloc);

		/**
		 *  \brief Destructeur
		 *
		 *  \post l'instance de Graphe est détruite
		 */
		~GrapheC (); // destructeur

		/**
		 * \brief Surcharger l'opérateur =
		 *
		 * \pre Il y a assez de mémoire pour l'opération
		 * \post Une copie d'un graphe est retournée
		 * \exception bad_alloc si la mémoire est insuffisante
		 */
		const GrapheC& operator = (const GrapheC&)throw (std::bad_alloc);


		/**
		 *  \brief Ajouter un sommet dans le graphe
		 *
		 * \pre Il y a assez de mémoire
		 * \pre Le sommet s ne fait pas partie déjà du graphe
		 * \post Le graphe comprend un sommet de plus
		 * \exception bad_alloc s'il n'y a pas assez de mémoire
		 * \exception logic_error si s appartient au graphe
		 */
		void ajouterSommet(const T& s) throw(std::length_error, std::logic_error);

		/**
		 *  \brief Ajouter un arc dans le graphe
		 *
		 * \pre Il y a assez de mémoire
		 * \pre Les 2 sommets s1 et s2 appartiennent au graphe
		 * \post Le graphe comprend un arc de plus
		 * \exception bad_alloc s'il n'y a pas assez de mémoire
		 * \exception logic_error si s1 ou s2 n'appartiennent pas au graphe
		 */
		void ajouterArc  (const T& s1, const T& S2)throw (std::logic_error, std::bad_alloc);

		/**
		 *  \brief enlever un arc du graphe
		 *
		 * \pre Les 2 sommets s1 et s2 appartiennent au graphe
		 * \post Le graphe comprend un arc de moins
		 * \exception logic_error si s1 ou s2 n'appartiennent pas au graphe
		 */
		void enleverArc (const T& s1, const T& s2)throw(std::logic_error);

		/**
		 *  \brief enlever un sommet du graphe
		 *
		 * \pre Le sommet s appartient au graphe
		 * \post Le graphe comprend un sommet de moins
		 * \exception logic_error si s n'appartient pas au graphe
		 */
		void enleverSommet ( const T& s)throw(std::logic_error);

		/**
		 *  \brief vérifier l'appartenance d'un sommet au graphe
		 *
		 * \post Le graphe est inchangé
		 */
		bool sommetExiste(const T& s) const;

		/**
		 *  \brief vérifier l'appartenance d'un arc au graphe
		 *
		 * \post Le graphe est inchangé
		 */
		bool arcExiste ( const T& s1, const T& s2) const;

		/**
		 *  \brief Retourner le nombre de sommets dans le au graphe
		 *
		 * \post Le graphe est inchangé
		 */
		int  nbSommets() const;

		/**
		 *  \brief Afficher un graphe
		 *
		 * Affiche le graphe de la facon la plus proche de la sa representation réelle en memoire
		 * Chaque sommet formant un arc est affiché sur une ligne
		 *
		 * \post Le graphe est inchangé
		 */
		void affiche()const;

		/**
		 *  \brief Lister les sommets d'un graphe
		 *
		 * Retourner dans un vector tous les sommets d'un graphe
		 * \pre Il y a assez de mémoire
		 * \post Le graphe est inchangé
		 * \exception bad_alloc lancee par vector si pas assez de mémoire
		 */
		std::vector<T> listerSommetsGraphe() const throw(std::bad_alloc);

		/**
		 *  \brief Retourner l'ordre d'entree d'un sommet dans le graphe
		 *
		 * \pre Le sommet doit appartenir au graphe
		 * \post Le graphe est inchangé
		 * \exception logic_error si le sommet n'appartient pas au graphe
		 */
		int ordreEntreeSommet(const T& sommet) const throw (std::logic_error);

		/**
		 *  \brief Lister les sommets adjacents à un sommet dans un graphe
		 *
		 * Retourner dans un vector tous les sommets adjacents
		 *
		 * \pre Il y a assez de mémoire
		 * \pre Le sommet doit appartenir au graphe
		 * \post Le graphe est inchangé
		 * \exception bad_alloc lancee par vector si pas assez de mémoire
		 * \exception logic_error si le sommet ne fait pas partie du graphe
		 */
		std::vector<T> listerSommetsAdjacents(const T& sommet) const throw (std::logic_error, std::bad_alloc);

		/**
		 *  \brief Retourner l'ordre de sortie d'un sommet dans le graphe
		 *
		 * \pre Le sommet doit appartenir au graphe
		 * \post Le graphe est inchangé
		 * \exception logic_error si le sommet n'appartient pas au graphe
		 */
		int ordreSortieSommet(const T& sommet) const throw (std::logic_error);

	private:
		/**
		* \class Noeud
		*
		* \brief classe interne représentant un noeud typique du graphe
		*
		*  La classe représente un noeud typique
		*  pour implémenter des listes d'adjacence.
		*/
		class Noeud
		{
		 public:
			T sommet; 			 /*!< l'étiquette d'un sommet */
			Noeud * suivant;     /*!< pour le chaînage dans les listes de noeuds adjacents */
		};

		int nbNoeud;     		/*!< nombre de sommets dans le graphe */
		int nbNoeudMax;			/*!< nombre total possible de sommets */
		T * tableauSommet;		/*!< tableau représentant les sommets (i.e. les étiquettes)*/
		Noeud** listeNoeud;     /*!< structure pour les listes de noeuds adjacents*/

	};

}//Fin du namespace

#include "Graphe.inl"

#endif
