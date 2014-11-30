// MODIFIED BY MINDER VALENTIN AND GHOZLANI KARIM // ASD2-LAB3
//  DirectedCycle.h
//  ASD2
//
//  Created by Olivier Cuisenaire on 08.10.14.
//  
//  A implementer
//  Classe permettant la detection de cycle sur un graphe oriente

#ifndef ASD2_DirectedCycle_h
#define ASD2_DirectedCycle_h

namespace ASD2 {

    template<typename GraphType>
    class DirectedCycle {
    private:
        /* A DEFINIR */
        const GraphType& graph;
        std::vector<bool> isOnVisitStack;
        std::vector<bool> isMarkedVisited;
        int vertexStartCycle = -1;
        std::list<int> cycleVerticesList; // Liste des sommets faisant partie d'un cycle  

        void dfs(int v) {
            // visited
            isMarkedVisited[v] = true;
            // on the visit stack
            isOnVisitStack[v] = true;

            for (int w : graph.adjacent(v)) {
                // if we found a cycle, we stop the recursion.
                if (HasCycle()) {
                    return;
                }
                // if vertex not visited so far, we recurse with this vertex
                if (!isMarkedVisited[w]) {
                    dfs(w);

                    /*
                     * When we return from the recursion, we add the predecessor
                     * to the cycle, until we reach the start cycle. At this point
                     * the start is removed from the "visit stack" in order that
                     * its predecessor are not taken as part of the cycle, even 
                     * if they are on the visit stack.
                     */
                    if (HasCycle() && isOnVisitStack[vertexStartCycle]) {
                        cycleVerticesList.push_back(v);
                        if (vertexStartCycle == v)
                            isOnVisitStack[v] = false;
                    }
                    // if its visited AND its on the stack, we have found a cycle.
                } else if (isOnVisitStack[w]) {
                    // edge w is the start AND the end of the found cycle
                    vertexStartCycle = w;
                    cycleVerticesList.push_back(w);
                    // v is also part of the cycle, other edges will be added when coming up from the recursion
                    cycleVerticesList.push_back(v);
                }
            }
            // end of recursion for v: removed frotm the stack.
            isOnVisitStack[v] = false;
        }

    public:

        // constructor

        DirectedCycle(const GraphType& g) : graph(g) {
            /* A IMPLEMENTER */
            // visits of each vertex
            isMarkedVisited.resize(g.V());
            isMarkedVisited.assign(g.V(), false);
            // on the visit stack, for each vertex
            isOnVisitStack.resize(g.V());
            isOnVisitStack.assign(g.V(), false);

            /*launch of the dfs from any vertex that is not marked so far.
             * if the graph is not connected, ensure that we check cycles 
             * in ALL components, until one with cycle is found. 
             * 
             * prerequis3 is an exemple of a non-connected graph that contains 
             * a cycle in the second component
             *  */
            for (int i = 0; i < graph.V(); i++) {
                if (!isMarkedVisited.at(i) && cycleVerticesList.empty()) {
                    dfs(i);
                }
            }

        }

        //indique la presence d'un cycle

        bool HasCycle() {
            /* A IMPLEMENTER */
            //return ...
            // check that the list of the vertices forming a cycle is empty
            return !(Cycle().empty());
        }

        //liste les indexes des sommets formant une boucle

        std::list<int> Cycle() {
            /* A IMPLEMENTER */
            //return ...
            // the list of the vertices forming a cycle
            return cycleVerticesList;
        }

    };

}

#endif
