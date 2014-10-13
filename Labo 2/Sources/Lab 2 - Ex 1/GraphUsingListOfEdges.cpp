
#include "GraphUsingListOfEdges.h"

namespace ASD2 {

    GraphUsingListOfEdges::GraphUsingListOfEdges(int V) : numberOfVertices(V) {
    }

    GraphUsingListOfEdges::GraphUsingListOfEdges(std::istream& s) {
        int E,v,w;
        
        s >> numberOfVertices;
        s >> E;

        for (int i = 0; i < E; i++) {
            s >> v;
            s >> w;
            addEdge(v, w);
        }
    }

    void GraphUsingListOfEdges::addEdge(int v, int w) {
        edgeList.push_back(std::make_pair(v,w));
    }

    GraphUsingListOfEdges::Iterable GraphUsingListOfEdges::adjacent(int v) const {
        std::list<int> list;
        for(Edge edge : edgeList ){
            if(edge.first == v) 
                list.push_back(edge.second);
            else
                if(edge.second == v)
                    list.push_back(edge.first);
        }
        return list; 
    }

    int GraphUsingListOfEdges::V() const {
        return numberOfVertices;
    }
}