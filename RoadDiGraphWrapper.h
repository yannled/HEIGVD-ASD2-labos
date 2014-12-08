//
//  RoadNetwork.h
//  ASD2
//
//  Created by Olivier Cuisenaire on 18.11.14.
//
//

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
#include "EdgeWeightedGraphCommon.h"

// Classe lisant et donnant accès au reseau routier

class RoadDiGraphWrapper {
private:
    RoadNetwork rn;

public:

    RoadGraphWrapper(const RoadNetwork rne) : rn(rne) {

    }

    int V() {
        return rn.cities.size();
    }

    // does nothing, probably useless

    void forEachAdjacentEdge() const {
    }
    
    template<typename Func>
    void forEachEdge(Func f) const {
        for (int i = 0; i < rn.roads.size(); i++) {
            f(ASD2::EdgeCommon(rn.roads.at(i).cities.first,
                    rn.roads.at(i).cities.second, rn.roads.at(i).lenght));
        }
    }

    std::vector<int> adjacentEdges(int v) {
        std::vector<int> ret;
        std::vector<int> e = rn.cities.at(v).roads;

        // this is useless ?
        for (int i = 0; i < e.size(); i++) {
            std::pair<int, int> p = rn.roads.at(e.at(i)).cities;
            if (p.first == v) {
                ret.push_back(p.second);
            } else if (p.second == v) {
                ret.push_back(p.first);
            }
        }
        //return ret;
        return e;
    }

};


#endif /* defined(__ASD2__RoadNetwork__) */
