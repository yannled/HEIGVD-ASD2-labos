// MINDER/GHOZLANI ASD2 - LAB 4
//  TopologicalSort.h
//  ASD2
//
//  Created by Olivier Cuisenaire on 08.10.14.
//
//  A implementer
//  Classe permettant le tri topologique d'un graphe oriente

#ifndef ASD2_TopologicalSort_h
#define ASD2_TopologicalSort_h

#include "DirectedCycle.h"
#include "ParcoursEnProfondeur.h"

namespace ASD2 {

    template < typename GraphType >
    class TopologicalSort {
    private:
        /* A DEFINIR */
        const GraphType& graph;
        std::vector<int> order;

    public:
        //constructeur

        TopologicalSort(const GraphType & g) : graph(g) {
            /* A IMPLEMENTER */
            /* vous devez verifier la presence d'un cycle */
            if (IsDAG()) {
                order.resize(g.V());
                int count = 0;

                DFS<GraphType> dfs(g);

                dfs.visit([] (int) {
                },
                [&] (int v) {
                    order[count++] = v; }
                );
            }
        }

        //indique si le graphe est DAG (Directed Acyclic Graph))

        bool IsDAG() {
            /* A IMPLEMENTER */
            //return ...
            // we reuse our function HasCycle() from DirectedGraph
            return !(DirectedCycle<GraphType>(this->graph).HasCycle());
        }

        //tableau contenant l'ordre de parcours des indexes des sommets dans le graphe

        const std::vector<int>& Order() {
            /* A IMPLEMENTER */
            //return ...
            return this->order;
        }
    };
}
#endif
