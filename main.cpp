//
//  main.cpp
//  Labo4
//
//  Created by Olivier Cuisenaire on 18.11.14.
//
//

#include <iostream>
#include <ctime>

#include "EdgeWeightedGraph.h"
#include "EdgeWeightedDiGraph.h"
#include "RoadNetwork.h"
#include "MinimumSpanningTree.h"
#include "ShortestPath.h"
#include "RoadGraphWrapper.h"
#include "RoadDiGraphWrapper.h"
#include "RoadDiGraphWrapperTime.h"

using namespace std;

// Calcule et affiche le plus court chemin de la ville depart a la ville arrivee
// en passant par le reseau routier rn. Le critere a optimiser est la distance.

void PlusCourtChemin(const string& depart, const string& arrivee, RoadNetwork& rn) {
    /* A IMPLEMENTER */
    RoadDiGraphWrapper rdgw(rn);
    ASD2::DijkstraSP<RoadDiGraphWrapper> sp(rdgw, rn.cityIdx.at(depart));
    
    double total = 0;
    std::string spaces = "                    "; // 20 char
    for (ASD2::WeightedDirectedEdge<double> e : sp.PathTo(rn.cityIdx.at(arrivee))) {
        std::string from = rn.cities.at(e.From()).name + spaces;
        std::string to = rn.cities.at(e.To()).name + spaces;
        from.resize(20); // max: 17 char utiles, min: 20 char spaces
        to.resize(20); // pour affichage joli en colonnes.
        cout << "From:   " << from
                << "  to  " << to 
                << "  with distance of   " << e.Weight() << " km" << endl;
        total += e.Weight();
    }
    cout << "Total km: " << total << endl;
}

// Calcule et affiche le plus rapide chemin de la ville depart a la ville arrivee via la ville "via"
// en passant par le reseau routier rn. Le critere a optimiser est le temps de parcours
// sachant que l'on roule a 120km/h sur autoroute et 70km/h sur route normale.
double PlusRapideChemin(const string& depart, const string& arrivee, RoadNetwork& rn) {
    RoadDiGraphWrapperTime rdgw(rn);
    ASD2::DijkstraSP<RoadDiGraphWrapperTime> sp(rdgw, rn.cityIdx.at(depart));
    
    double total = 0;
    std::string spaces = "                    "; // 20 char
    for (ASD2::WeightedDirectedEdge<double> e : sp.PathTo(rn.cityIdx.at(arrivee))) {
        std::string from = rn.cities.at(e.From()).name + spaces;
        std::string to = rn.cities.at(e.To()).name + spaces;
        from.resize(20); // max: 17 char utiles, min: 20 char spaces
        to.resize(20); // pour affichage joli en colonnes.
        cout << "From:   " << from
                << "  to  " << to 
                << "  with time of   " << e.Weight() << " km" << endl;
        total += e.Weight();
    }
    return total;
}

void PlusRapideChemin(const string& depart, const string& arrivee, const string& via, RoadNetwork& rn) {
    /* A IMPLEMENTER */
    double total = PlusRapideChemin(depart, via, rn) + PlusRapideChemin(via, arrivee, rn);
    cout << "Total time: " << total << endl;
}

// Calcule et affiche le plus reseau a renover couvrant toutes les villes le moins
// cher, en sachant que renover 1km d'autoroute coute 15 MF, et renover 1km de route normale
// coute 7 MF.

void ReseauLeMoinsCher(RoadNetwork &rn) {
    /* A IMPLEMENTER: done */
    RoadGraphWrapper rgw(rn);
    auto mst = ASD2::MinimumSpanningTree<RoadGraphWrapper>::Kruskal(rgw);
    int total = 0;
    // le plus long: "La Chaux-de-Fonds" en 17 char
    std::string spaces = "                    "; // 20 char
    for (ASD2::WeightedEdge<int> e : mst) {
        total += e.Weight();
        std::string from = rn.cities.at(e.Either()).name + spaces;
        std::string to = rn.cities.at(e.Other(e.Either())).name + spaces;
        from.resize(20); // max: 17 char utiles, min: 20 char spaces
        to.resize(20); // pour affichage joli en colonnes.
        cout << "From:   " << from
                << "  to  " << to 
                << "  for a cost of   " << e.Weight() << " MCHF" << endl;
    }
    cout << endl;
    cout << "Renovation total cost: " << total << " MCHF" << endl;
}

// compare les algorithmes Dijkstra et BellmanFord pour calculer les plus courts chemins au
// sommet 0 dans le graphe defini par filename.

void testShortestPath(string filename)
{
    cout << "Testing " << filename << endl;
    
    bool ok = true;
    
    typedef ASD2::EdgeWeightedDiGraph<double> Graph;
    Graph ewd(filename);
    
    clock_t startTime = clock();

    ASD2::BellmanFordQueueSP<Graph> referenceSP(ewd,0);
    
    cout << "Bellman-Ford: " << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << endl;
    startTime = clock();

    ASD2::DijkstraSP<Graph> testSP(ewd,0);
    
    cout << "Dijkstra:     " << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << endl;

    for (int v=0; v<ewd.V(); ++v) {
        if (referenceSP.DistanceTo(v) != testSP.DistanceTo(v) ) {
            cout << "Oops: vertex" << v << " has " << referenceSP.DistanceTo(v) << " != " <<  testSP.DistanceTo(v) << endl;
            ok = false;
            break;
        }
    }
    
    if(ok) cout << " ... test succeeded " << endl << endl;
}

int main(int argc, const char * argv[]) {
   // /*
   testShortestPath("tinyEWD.txt");
   testShortestPath("mediumEWD.txt");
   testShortestPath("1000EWD.txt");
   testShortestPath("10000EWD.txt");
   //testShortestPath("largeEWD.txt"); // disponible sur dossier du cours
    
   RoadNetwork rn("reseau.txt");
    
   cout << "1. Chemin le plus court entre Geneve et Emmen" << endl;
    
   PlusCourtChemin("Geneve", "Emmen", rn);
    
   cout << "2. Chemin le plus court entre Lausanne et Bale" << endl;
    
   PlusCourtChemin("Lausanne", "Basel", rn);
  
   cout << "3. chemin le plus rapide entre Geneve et Emmen en passant par Yverdon" << endl;
    
   PlusRapideChemin("Geneve", "Emmen", "Yverdon-Les-Bains", rn);
    
   cout << "4. chemin le plus rapide entre Geneve et Emmen en passant par Vevey" << endl;
    
   PlusRapideChemin("Geneve", "Emmen", "Vevey", rn);

   cout << "5. Quelles routes doivent etre renovees ? Quel sera le cout de la renovation de ces routes ?" << endl;
    // */ RoadNetwork rn("reseau.txt");
    ReseauLeMoinsCher(rn);

    return 0;
}
