
#pragma once
#ifndef ALGO_GRAPHE_H
#define ALGO_GRAPHE_H

#include "Graphe.h"

	template <typename T>
	Graphe::GrapheC<T> fermetureGraphe(const Graphe::GrapheC<T>& g) throw(std::logic_error);

	template <typename T>
	bool isConnexe(const Graphe::GrapheC<T>& g) throw(std::logic_error);

	template <typename T>
	std::vector<T> triTopologique(const Graphe::GrapheC<T>& g) throw (std::logic_error);

#include "Algorithmes.inl"

#endif

\