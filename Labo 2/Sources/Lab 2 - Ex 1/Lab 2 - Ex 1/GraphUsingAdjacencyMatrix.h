/* 
 * File:   GraphUsingAdjacencyMatrix.h
 * Author: Olivier Cuisenaire
 *
 * Created on 19. septembre 2014, 04:51
 */

#ifndef GRAPHUSINGADJACENCYMATRIX_H
#define	GRAPHUSINGADJACENCYMATRIX_H

#include <iostream>
#include <list>
#include <vector>

namespace ASD2 
{
    class GraphUsingAdjacencyMatrix {
    public:      
        typedef std::list<int> Iterable;
 
        GraphUsingAdjacencyMatrix(std::istream& stream); 
        GraphUsingAdjacencyMatrix(int V);

        void addEdge(int v, int w);              // ajoute une arête
        Iterable adjacent(int v) const;          // voisins du sommet v
        int V() const;                           // ordre du graphe
        
    private:
        GraphUsingAdjacencyMatrix(const GraphUsingAdjacencyMatrix& G) {}; // constructeurs non autorises
        GraphUsingAdjacencyMatrix();
        
        void Init(int V);
        std::vector<std::vector<bool> > adjMatrix;
    };
}

#endif	/* GRAPHUSINGADJACENCYMATRIX_H */

