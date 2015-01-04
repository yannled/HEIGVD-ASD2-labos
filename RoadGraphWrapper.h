//
//  RoadGraphWrapper.h
//  ASD2
//
//  Created by MM. Léonard BERNEY et Valentin MINDER // 04.01.2015

#ifndef __ASD2__RoadGraphWrapper__
#define __ASD2__RoadGraphWrapper__

#include "RoadNetwork.h"
#include "EdgeWeightedGraph.h"

// Classe formant un wrapper autour d'un graphe non oriente
class RoadGraphWrapper {
private:
    RoadNetwork rn;
    // million de francs
    int costFunction (int edge, int costMotorway = 15, int costRoad = 7) const {
        double length = rn.roads.at(edge).lenght;
        double value = rn.roads.at(edge).motorway.Value();
        return length * value * costMotorway + length * (1-value) * costRoad;
    }

public:
    typedef ASD2::WeightedEdge<int> Edge;
    
    RoadGraphWrapper(const RoadNetwork rne) : rn(rne) {

    }

    int V() const {
        return rn.cities.size();
    }
    
    // useless: removed forEachAdjacentEdge() 
    template<typename Func>
    void forEachEdge(Func f) const {
        for (int i = 0; i < rn.roads.size(); i++) {
            f(ASD2::WeightedEdge<int>(rn.roads.at(i).cities.first,
                    rn.roads.at(i).cities.second,
                    costFunction(i)));
        }
    }

};

#endif /* defined(__ASD2__RoadNetwork__) */
