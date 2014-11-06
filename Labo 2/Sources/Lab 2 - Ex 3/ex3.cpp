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

// Running time:
// -g: 		~204s
// -O -O2: 	~40s

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

