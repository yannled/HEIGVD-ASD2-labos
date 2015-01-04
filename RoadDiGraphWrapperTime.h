//
//  RoadNetwork.h
//  ASD2
//
//  Created by Olivier Cuisenaire on 18.11.14.
//
//

#ifndef __ASD2__RoadDiGraphWrapperTime__
#define __ASD2__RoadDiGraphWrapperTime__


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
// le critere est ici le temps necessaire pour aller de A à B.
class RoadDiGraphWrapperTime {
private:
    RoadNetwork rn;
    
    // minutes
    double costFunction (int edge, int costMotorway = 120, int costRoad = 70) const {
        double length = rn.roads.at(edge).lenght;
        double value = rn.roads.at(edge).motorway.Value();
        return length * value / costMotorway + length * (1-value) / costRoad;
    }

public:

    typedef ASD2::WeightedDirectedEdge<double> Edge;
    RoadDiGraphWrapperTime(const RoadNetwork rne) : rn(rne) {

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
                    other, costFunction(i)));
        }
    }
};


#endif /* defined(__ASD2__RoadNetwork__) */
