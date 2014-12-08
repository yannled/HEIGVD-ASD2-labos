//
//  RoadNetwork.h
//  ASD2
//
//  Created by Olivier Cuisenaire on 18.11.14.
//
//

#ifndef __ASD2__RoadGraphWrapper__
#define __ASD2__RoadGraphWrapper__

#include "RoadNetwork.h"
#include "EdgeWeightedGraphCommon.h"

// Classe lisant et donnant accès au reseau routier
class RoadGraphWrapper {
private:
    RoadNetwork rn;
    // million de francs
    int costFunction (int edge, int costMotorway = 15, int costRoad = 7) {
        int length = rn.roads.at(edge).lenght;
        int value = rn.roads.at(edge).motorway.Value();
        return length * value * costMotorway + length * (1-value) * costRoad;
    }

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
    void forEachEdge(Func f) {
        for (int i = 0; i < rn.roads.size(); i++) {
            f(ASD2::EdgeCommon<int>(rn.roads.at(i).cities.first,
                    rn.roads.at(i).cities.second,
                    costFunction(i)));
        }
    }

};

#endif /* defined(__ASD2__RoadNetwork__) */
