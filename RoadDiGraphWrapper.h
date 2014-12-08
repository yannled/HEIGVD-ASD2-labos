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

    RoadDiGraphWrapper(const RoadNetwork rne) : rn(rne) {

    }

    int V() {
        return rn.cities.size();
    }

    template<typename Func>
    void forEachAdjacentEdge(int v, Func f) const {
        std::vector<int> e = rn.cities.at(v).roads;
        for (int i = 0; i < e.size(); i++) {
            std::pair<int, int> p = rn.roads.at(e.at(i)).cities;
            f(ASD2::EdgeCommon<int>(p.first,
                    p.second, rn.roads.at(e.at(i)).lenght));
        }
    }
    
    template<typename Func>
    void forEachEdge(Func f) const {
        for (int i = 0; i < rn.roads.size(); i++) {
            f(ASD2::EdgeCommon<int>(rn.roads.at(i).cities.first,
                    rn.roads.at(i).cities.second, rn.roads.at(i).lenght));
        }
    }

};


#endif /* defined(__ASD2__RoadNetwork__) */
