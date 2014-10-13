
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
       /* A IMPLEMENTER */
    }
    
    //throws std::out_of_range
    GraphUsingAdjacencyMatrix::Iterable GraphUsingAdjacencyMatrix::adjacent(int v) const {
        /* A IMPLEMENTER */
    }

    int GraphUsingAdjacencyMatrix::V() const {
        /* A IMPLEMENTER */
    }
    
}
