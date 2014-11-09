/*
 * File:   ex3.cpp
 * Author: Olivier Cuisenaire
 *
 * Inspiré par http://oracleofbacon.org
 *
 * Created on 26. septembre 2014, 16:38
 */

#include <cstdlib>

#include "SymbolGraph.h"
#include "GraphUsingAdjacencyLists.h"
#include "ParcoursEnLargeur.h"

using namespace ASD2;
using namespace std;

/* 
 * PROCEDURE DE TEST
 * VOIR LA CAPTURE D'ECRAN EN ANNEXE.
 * 
 * EXEMPLE D'EXECUTION:
 * Debbouze, Jamel
 * Ast�rix & Ob�lix: Mission Cl�op�tre (2002)
 * Depardieu, G�rard
 * Novecento (1976)
 * Sutherland, Donald (I)
 * Animal House (1978)
 * Bacon, Kevin
 * 
 * 
 * Running time:
 * -g: 		~1.3s
 * -O -O2: 	~0.8s
 * 
 * */

int main(int argc, char** argv) {

    string file("movies.txt");
    string source("Debbouze, Jamel");
    string sink("Bacon, Kevin");

    SymbolGraph<GraphUsingAdjacencyLists> SG(file);

    BFS<GraphUsingAdjacencyLists> bfs(SG.G());
    bfs.visit(SG.index(sink),[](int){});

    int v = SG.index(source);
    while(v != bfs.parentOf(v))
    {
        cout << SG.name(v) << endl;
        v = bfs.parentOf(v);
    }
    cout << SG.name(v) << endl;

    return EXIT_SUCCESS;
}

