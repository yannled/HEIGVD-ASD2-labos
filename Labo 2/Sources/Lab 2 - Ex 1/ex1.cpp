/*
 * File:   ex1.cpp
 * Author: Olivier Cuisenaire
 *
 * Created on 4 sept. 2014, 13:18:18
 */

#include <stdlib.h>
#include <iostream>

#include "GraphUsingAdjacencyLists.h"
#include "GraphUsingListOfEdges.h"
#include "GraphUsingAdjacencyMatrix.h"
#include "ParcoursEnLargeur.h"
#include "ComposantesConnexes.h"

#include <fstream>
#include <chrono>
#include <limits.h>

#define LIMIT INT_MAX

using namespace ASD2;
using namespace std;

template<typename Graph>
int CountEdges(const Graph& G) {
    int cnt = 0;
    for (int v = 0; v < G.V(); ++v)
        for (int w : G.adjacent(v))
            if (v <= w)
                cnt++;
    return cnt;
}

// Cette methode doit retourner la distance maximum entre le sommet v et le sommet le plus eloigne dans sa composante connexe

template<typename Graph>
int FindMaxDistanceFrom(const Graph& G, int v) {
    /* A IMPLEMENTER */
    vector<int> distances;

    // on initialise une distance "pseudo-infinie" (INT_MAX) à chaque sommet...
    for (int i = 0; i < G.V(); i++) {
        distances.push_back(LIMIT);
    }

    // ... sauf l'origine de la recherche (distance 0)
    distances.at(v) = 0;

    BFS<Graph> bfs(G);
    bfs.visit(v, [&](int v) {
        GraphUsingAdjacencyMatrix::Iterable neighbors = G.adjacent(v);

        /* pour chacun des voisins, on vérifie si la distance peut être obtenue
         * de manière plus courte en passant par v, et on met a jour 
         */
        for (GraphUsingAdjacencyMatrix::Iterable::iterator u = neighbors.begin(); u != neighbors.end(); u++) {
            if (distances.at(v) < LIMIT && distances.at(v) < distances.at(*u)) {
                distances.at(*u) = distances.at(v) + 1;
            }
        }
    });

    // on recherche le maximum en ignorant les valeurs à pseudo-infini
    int maxDist = 0;
    for (vector<int>::iterator dist = distances.begin(); dist != distances.end(); dist++) {
        if (*dist > maxDist && *dist < LIMIT) {
            maxDist = *dist;
        }
    }

    return maxDist;
}

template<typename Graph>
void Analyse(const Graph& G, const string& message) {
    CC<Graph> cc(G);

    /* NOUS CONSTATONS QUE LES RESULTATS SONT IDENTIQUES QUEL QUE SOIENT LES TYPES DE REPRESENTATION!
     * 
     * PAR AILLEURS, NOUS AVONS REPRESENTE SUR PAPIER LE TINYGRAPH ET CONSTATE QUE 
     * LES RESULTATS CORRESPONDENT A LA REALITE DU GRAPHE.
     * 
     * NOTRE METHODE FONCTIONNE DONC.
     * */
    cout << message << " a " << G.V() << " sommets, " << CountEdges(G) << " aretes et " << cc.Count() << " composantes connexes \n";
    cout << "le sommet " << 0 << " fait partie de la CC " << cc.Id(0) << ". La distance maximale a ce sommet dans cette CC est de " << FindMaxDistanceFrom(G, 0) << "\n";
    cout << "le sommet " << 3 << " fait partie de la CC " << cc.Id(3) << ". La distance maximale a ce sommet dans cette CC est de " << FindMaxDistanceFrom(G, 3) << "\n";
    cout << "le sommet " << G.V() - 1 << " fait partie de la CC " << cc.Id(G.V() - 1) << ". La distance maximale a ce sommet dans cette CC est de " << FindMaxDistanceFrom(G, G.V() - 1) << "\n";

    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
    int nrOfTests = 1000.0;
    for (int i = 0; i < nrOfTests; ++i)
        CC<Graph> cctest(G);
    chrono::high_resolution_clock::duration time = chrono::high_resolution_clock::now() - start;
    cout << "temps de calcul de CC: " << chrono::duration_cast<chrono::milliseconds>(time).count() << " micro secondes" << endl;
    cout << endl;
}

int main(int argc, char** argv) {
    string filename("mediumG.txt"); // "tinyG.txt" ou "mediumG.txt"
    ifstream s(filename);

    GraphUsingAdjacencyLists G1(s);
    s.close();
    Analyse(G1, "GraphUsingAdjacencyLists");

    s.open(filename);
    GraphUsingListOfEdges G2(s);
    s.close();
    Analyse(G2, "GraphUsingListOfEdges");

    s.open(filename);
    GraphUsingAdjacencyMatrix G3(s);
    s.close();
    Analyse(G3, "GraphUsingAdjacencyMatrix");

    return (EXIT_SUCCESS);

}
