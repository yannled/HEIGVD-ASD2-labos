/* 
 * File:   ComposantesConnexes.h
 * Author: Olivier Cuisenaire
 *
 * Created on 25. septembre 2014, 12:02
 */

#ifndef COMPOSANTESCONNEXES_H
#define	COMPOSANTESCONNEXES_H

#include <vector>
#include "ParcoursEnProfondeur.h"

namespace ASD2 {

    template<typename GraphType>
    class CC {
    private:
        std::vector<int> id;         // numéro de la CC à laquelle appartient chaque sommet
                                     // -1 si pas encore assigné
        int count;                   // nomre de composantes connexes

    public:
        bool Connected(int v, int w) {  // v et w sont-ils connectés? 
            return Id(v) == Id(w);    
        }
        int Id(int v) {                 // à quelle CC appartient v? 
            return id.at(v);
        }
        int Count() {                   // combien y a-t-il de CC?
            return count;
        }

        CC(const GraphType& g)  {  // constructeur. 
            id.assign(g.V(), -1);
            count = 0;

            for (int v = 0; v < g.V(); ++v) {
                if (id[v] == -1) {
                    DFS<GraphType> P(g);
                    P.visit(v, [&](int w) {
                        id[w] = count; });
                    ++count;
                }
            }
        }
    };
}

#endif	/* COMPOSANTESCONNEXES_H */

