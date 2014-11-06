
#include "GraphUsingAdjacencyMatrix.h"

namespace ASD2 {

    void GraphUsingAdjacencyMatrix::Init(int V) {
        adjMatrix.resize(V);
        for (int v = 0; v < V; v++)
            adjMatrix[v].resize(V);
    }

    GraphUsingAdjacencyMatrix::GraphUsingAdjacencyMatrix(int V) {
        Init(V);
    }

    GraphUsingAdjacencyMatrix::GraphUsingAdjacencyMatrix(std::istream& s) {
        int V, E, v, w;

        s >> V;
        s >> E;

        Init(V);

        for (int i = 0; i < E; i++) {
            s >> v;
            s >> w;
            addEdge(v, w);
        }
    }

    //throws std::out_of_range

    void GraphUsingAdjacencyMatrix::addEdge(int v, int w) {
        /* A IMPLEMENTER 
         * Ajoute true a l'adjacence (v,w) ET (w,v) car c'est un graphe non orienté
         * On choisit donc les positions v,w en 1ere et 2eme dimension, puis l'inverse.
         */
        adjMatrix.at(v).at(w) = true;
        adjMatrix.at(w).at(v) = true;
    }

    //throws std::out_of_range

    GraphUsingAdjacencyMatrix::Iterable GraphUsingAdjacencyMatrix::adjacent(int v) const {
        /* A IMPLEMENTER 
         * 
         * Pour chaque sommet i, on regarde si il est adjacent à v 
         * et on l'ajoute dans l'itérateur retourné
         */
        Iterable it;

        for (int i = 0; i < V(); i++) {
            if (adjMatrix.at(v).at(i)) {
                it.push_back(i);
            }
        }

        return it;
    }

    int GraphUsingAdjacencyMatrix::V() const {
        /* A IMPLEMENTER 
         * Retourne la taille de la matrice.
         */
        return adjMatrix.size();
    }

}
