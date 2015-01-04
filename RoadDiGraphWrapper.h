//
//  RoadDiGraphWrapper.h
//  ASD2
//
//  Created by MM. Léonard BERNEY et Valentin MINDER // 04.01.2015

#ifndef __ASD2__RoadDiGraphWrapper__
#define __ASD2__RoadDiGraphWrapper__


#include <stdio.h>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <fstream>
#include <sstream>

#include "Util.h"

#include "RoadNetwork.h"
#include "EdgeWeightedGraph.h"

// Classe formant un wrapper autour d'un graphe non oriente
// le critere est ici la longueur d'une route de A à B.
class RoadDiGraphWrapper {
private:
    RoadNetwork rn;

public:

    typedef ASD2::WeightedDirectedEdge<double> Edge;
    RoadDiGraphWrapper(const RoadNetwork rne) : rn(rne) {

    }

    int V() const {
        return rn.cities.size();
    }

    // useless: removed forEachEdge() 
    template<typename Func>
    void forEachAdjacentEdge(int v, Func f) const {
        std::vector<int> e = rn.cities.at(v).roads;
        for (int i = 0; i < e.size(); i++) {
            std::pair<int, int> p = rn.roads.at(e.at(i)).cities;
            // the first must be v, the second the other one.
            // in order that to() function works
            int other = p.first;
            if (p.first == v) {
                other = p.second;
            }
            f(ASD2::WeightedDirectedEdge<double>(v,
                    other, rn.roads.at(e.at(i)).lenght));
        }
    }
};


#endif /* defined(__ASD2__RoadNetwork__) */
