/* 
 * File:   GraphUsingListOfEdges.h
 * Author: Olivier Cuisenaire
 *
 * Created on 19. septembre 2014, 04:25
 */

#ifndef GRAPHUSINGLISTOFEDGES_H
#define	GRAPHUSINGLISTOFEDGES_H


#include <iostream>
#include <list>
#include <utility>

namespace ASD2 
{
    class GraphUsingListOfEdges {
    public:      
        typedef std::list<int> Iterable;
 
        GraphUsingListOfEdges(std::istream& stream); 
        GraphUsingListOfEdges(int V);

        void addEdge(int v, int w);              // ajoute une arête
        Iterable adjacent(int v) const;          // voisins du sommet v
        int V() const;                           // ordre du graphe
        
    private:
        GraphUsingListOfEdges(const GraphUsingListOfEdges& G) {};               // constructeurs non autorises
        GraphUsingListOfEdges();
        
         int numberOfVertices; 
         
        typedef std::pair<int,int> Edge;
        std::list<Edge> edgeList; 
    };
}

#endif	/* GRAPHUSINGLISTOFEDGES_H */

