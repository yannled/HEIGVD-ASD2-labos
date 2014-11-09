/*
 * File:   SymbolGraph.h
 * Author: Olivier Cuisenaire
 *
 * Created on 26. septembre 2014, 15:08
 */

#ifndef SYMBOLGRAPH_H
#define	SYMBOLGRAPH_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>

#include "Util.h"

namespace ASD2
{
    template<typename GraphType>
    class SymbolGraph
    {
        typedef GraphType Graph;
    private:
        Graph* g;
        // Map à double sens pour éviter de longues boucles.
        // Nous avons choisi de favoriser la vitesse d'execution,
        // mais cette méthode consomme 2 fois plus de mémoire.
        std::vector<std::string> indexToName;
        std::map<std::string, int> nameToIndex;

    public:
        ~SymbolGraph()
        {
            delete g;
        }

        //creation du SymbolGraph a partir du fichier movies.txt
        SymbolGraph(const std::string& filename) {
            //lecture du fichier, ligne par ligne puis element par element (separe par des /)
            std::string line;
            int cnt=0;

            // Création des sommets du graphe
            std::ifstream s(filename);
            while (std::getline(s, line))
            {
                std::vector<std::string> names = ASD2::split(line,'/');
                std::string filmName = names.front();
                names.erase(names.begin());

                indexToName.push_back(filmName);
                int w = indexToName.size() - 1;
                nameToIndex.insert(std::pair<std::string, int>(filmName, w));

                for(std::string actorName : names) {
                    if (!contains(actorName)) {
                        // On crée un nouveau vertex pour l'acteur
                        indexToName.push_back(actorName);
                        int v = indexToName.size() - 1;
                        nameToIndex.insert(std::pair<std::string, int>(actorName, v));
                    }
                }
            }

            g = new Graph(indexToName.size());

            // Remise à zéro du pointeur depuis le début
            s.clear();
            s.seekg(0, std::ios::beg);
            // Second passage de lecture du fichier pour la création des arêtes
            while (std::getline(s, line))
            {
                std::vector<std::string> names = ASD2::split(line,'/');
                std::string filmName = names.front();
                names.erase(names.begin());

                int w = index(filmName);

                for (std::string actorName : names) {
                    int v = index(actorName);

                    g->addEdge(v, w);
                }
            }

            s.close();
        }

        // verifie la presence d'un symbole
        bool contains(const std::string& name) {
            return index(name) > 0;
        }

        // retourne l'index du symbole ou -1 s'il n'existe pas
        int index(const std::string& name) {
            std::map<std::string, int>::const_iterator index = nameToIndex.find(name);
            if (index == nameToIndex.end()) { // élément introuvable
                return -1;
            } else {
                return index->second;
            }
        }

        //symbole correspondant au sommet
        std::string name(int idx) {
            return indexToName.at(idx);
        }

		//symboles adjacents a un symbole
		std::vector<std::string> adjacent(const std::string & vertexName) {
			int idxSearch = index(vertexName);
			std::vector<int> neighbors = g->adjacent(idxSearch);
			std::vector<std::string> ret;
			for (int i = 0; i < neighbors.size(); i++) {
                ret.push_back(name(neighbors.at(i)));
			}

			return ret;
		}

        const Graph& G() {
            return *g;
        }

    };

}

#endif	/* SYMBOLGRAPH_H */
