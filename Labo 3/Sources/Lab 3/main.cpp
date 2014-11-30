// MODIFIED BY MINDER VALENTIN AND GHOZLANI KARIM // ASD2-LAB3
//
//  main.cpp
//  Labo 3
//
//  Created by Olivier Cuisenaire on 03.11.14.
//

#include <iostream>
#include <stdlib.h>
#include "DiGraph.h"
#include "TopologicalSort.h"

// vous devez reutiliser celui du labo 2, ex 3 (cf. donnee)
#include "SymbolGraph.h"

using namespace ASD2;
using namespace std;

//methode permettant de verifier le graphe trie par rapport au fichier d'entree

bool checkOrder(const std::vector<int> order,
        const SymbolGraph<DiGraph> SG,
        const std::string filename,
        char delim) {

    std::vector<int> positionInOrder(order.size());
    for (size_t i = 0; i < order.size(); ++i)
        positionInOrder[order[i]] = int(i);

    bool ok = true;

    std::string line;

    std::ifstream s(filename);
    while (std::getline(s, line)) {
        auto names = ASD2::split(line, delim);

        for (size_t i = 1; i < names.size(); ++i) {

            int v = SG.index(names[0]); // cours
            int w = SG.index(names[i]); // ieme prerequis

            if (positionInOrder[ v ] < positionInOrder [ w ]) {
                cout << "Erreur d'ordre : " << names[0] << " avant " << names[i] << endl;
                ok = false;
            }
        }
    }
    s.close();

    return ok;
}

void runWithFileName(const string fileName, const char delimiter = ',') {
    SymbolGraph<DiGraph> symbolGraph(fileName, delimiter);
    DirectedCycle<DiGraph> directedCycle(symbolGraph.G());

    // DirectedCycle Test
    if (directedCycle.HasCycle()) {
        cout << fileName << " contains a cycle and is not a DAG. Cycle found: \n";
        // if there is a cycle, we print the cycle found
        for (int i : directedCycle.Cycle())
            cout << "<" << symbolGraph.name(i) << "> ";
    } else {
        cout << fileName << " does not contain a cycle/circuit";
    }
    cout << endl;

    // we test the TopologicalSort class
    TopologicalSort<DiGraph> topoSort(symbolGraph.G());

    // First we test if the graph is a DAG
    if (topoSort.IsDAG()) {
        // Afficher l'ordre de parcours du tri topologique
        cout << "Topological order: ";
        for (int i : topoSort.Order())
            cout << "<" << symbolGraph.name(i) << "> ";
        cout << endl;
        if (checkOrder(topoSort.Order(), symbolGraph, fileName, delimiter)) {
             cout << "Checked verification! ;)";
        } else {
             cout << "Verification FAILED!";
        };
       
    }
    cout << endl;
}

int main(int argc, const char * argv[]) {
    runWithFileName("prerequis2.txt");
    runWithFileName("prerequis3.txt");
    runWithFileName("prerequis.txt");
    return EXIT_SUCCESS;
}