/* MINDER/GHOZLANI ASD2 - LAB 4
 * File:   ParcoursEnProfondeur.h
 * Author: Olivier Cuisenaire
 * COPY FROM LAB 2
 *
 * Created on 18. septembre 2014, 10:46
 */

#ifndef PARCOURSENPROFONDEUR_H
#define	PARCOURSENPROFONDEUR_H


#include <vector>
#include <stack>
#include <functional>
#include <utility>
#include <tuple>

namespace ASD2 {

    template<typename GraphType> class DFS {
    private:
        const GraphType& g;
        std::vector<int> marked;

        template <typename FuncPre, typename FuncPost> void recursion(int v, FuncPre fpre, FuncPost fpost) {
            fpre(v);
            marked[v] = true;

            for (int w : g.adjacent(v))
                if (!marked[w])
                    recursion(w, fpre, fpost);
            fpost(v);
        }

    public:

        DFS(const GraphType& G) : g(G) {
        }

        template <typename FuncPre, typename FuncPost> DFS(const GraphType& G, int v, FuncPre fpre, FuncPost fpost) : g(G) {
            visit(v, fpre, fpost);
        }

        template <typename Func>
        void visit(int v, Func f) {
            visit(v, f, [](int) {
            });
        }

        template <typename FuncPre, typename FuncPost>
        void visit(int v, FuncPre fpre, FuncPost fpost) {
            marked.assign(g.V(), false);
            recursion(v, fpre, fpost);
        }

        // we use this new visit in order to restart the visit if we finish the recursion after a component.
        template <typename FuncPre, typename FuncPost>
        void visit(FuncPre fpre, FuncPost fpost) {
            marked.assign(g.V(), false);
            for (int v = 0; v < g.V(); ++v)
                if (!marked[v])
                    recursion(v, fpre, fpost);
        }

        template <typename Func> void iterativeVisit(int v, Func f) {
            marked.assign(g.V(), false);

            std::stack<int> pile;
            marked[v] = v;
            pile.push(v);

            while (!pile.empty()) {
                v = pile.top();
                pile.pop();

                for (int w : g.adjacent(v))
                    if (!marked[w]) {
                        marked[w] = true;
                        pile.push(w);
                    }

                f(v);
            }
        }
    };
}

#endif	/* PARCOURSENPROFONDEUR_H */

