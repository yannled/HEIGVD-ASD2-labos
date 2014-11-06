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

#include "Util.h"

namespace ASD2
{
    template<typename GraphType>
    class SymbolGraph
    {
        typedef GraphType Graph;
    private:
        Graph* g;
        std::vector<std::string> totalName;

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
            g = new Graph(10000000);

            std::ifstream s(filename);
            while (std::getline(s, line))
            {
                std::vector<std::string> names = ASD2::split(line,'/');
                std::string filmName = names.front();
                names.erase(names.begin());

                totalName.push_back(filmName);
                int w = totalName.size() - 1;

                for(std::string actorName : names) {
                    // std::cout << actorName << " "; //on affiche le contenu du fichier, vous devrez commencer a remplir le graphe ici;

                    int v = index(actorName);

                    if (v == -1) {
                        //std::vector<std::string> filmNeighborsList = adjacent(w);
                        //filmNeighborsList.push_back(v)
                        totalName.push_back(actorName);
                        v = totalName.size() - 1;
                    }

                    g->addEdge(v, w);
                }

                // std::cout << std::endl;
            }

            s.close();

            /* A IMPLEMENTER */
        }

        //verifie la presence d'un symbole
        bool contains(const std::string& name) {
            /* A IMPLEMENTER */
            return index(name) > 0;
        }

        //index du sommet correspondant au symbole
        /**
         * \return int, the index of the vertex,
         *         or -1 if there is no vertex found.
         */
        int index(const std::string& name) {
             /* A IMPLEMENTER */
             for (int i = 0; i < totalName.size(); i++){
                if (totalName.at(i) == name) {
                    return i;
                }
             }
             return -1;
        }

        //symbole correspondant au sommet
        std::string name(int idx) {
            /* A IMPLEMENTER */

            return totalName.at(idx);
        }

		//symboles adjacents a un symbole
		std::vector<std::string> adjacent(const std::string & vertexName) {
			/* A IMPLEMENTER */
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
