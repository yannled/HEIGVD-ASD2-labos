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

using namespace ASD2;
using namespace std;

template<typename Graph> 
int CountEdges(const Graph& G)
{
    int cnt = 0;
    for (int v = 0; v < G.V(); ++v)
        for (int w : G.adjacent(v))
            if (v <= w)
                cnt++;
    return cnt;
}

template<typename Graph> 
int FindMaxDistanceFrom(const Graph& G,int v)
{
    /* A IMPLEMENTER */
    // Cette methode doit retourner la distance maximum entre le sommet v et le sommet le plus eloigne dans sa composante connexe 
}

template<typename Graph>
void Analyse(const Graph& G,const string& message)
{    
    CC<Graph> cc(G);
    
    cout << message << " a " << G.V() << " sommets, " << CountEdges(G) << " aretes et " << cc.Count() << " composantes connexes \n";
    cout << "le sommet " << 0 << " fait partie de la CC " << cc.Id(0) << ". La distance maximale a ce sommet dans cette CC est de " << FindMaxDistanceFrom(G,0) << "\n";     
    cout << "le sommet " << G.V()-1 << " fait partie de la CC " << cc.Id(G.V()-1) << ". La distance maximale a ce sommet dans cette CC est de " << FindMaxDistanceFrom(G,G.V()-1) << "\n";     
 
   chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
   int nrOfTests = 1000.0;
   for(int i=0;i<nrOfTests;++i)
       CC<Graph> cctest(G);
   chrono::high_resolution_clock::duration time = chrono::high_resolution_clock::now() - start;
   cout << "temps de calcul de CC: " << chrono::duration_cast<chrono::milliseconds>(time).count() << " micro secondes" << endl;
   cout << endl;
}

int main(int argc, char** argv) {

    string filename("tinyG.txt"); // ou "mediumG.txt"
    ifstream s(filename);
    
    GraphUsingAdjacencyLists G1(s);
    s.close();
    Analyse(G1,"GraphUsingAdjacencyLists");
    
    s.open(filename);
    GraphUsingListOfEdges G2(s);
    s.close();
    Analyse(G2,"GraphUsingListOfEdges");
    
    s.open(filename);
    GraphUsingAdjacencyMatrix G3(s);
    s.close();
    Analyse(G3,"GraphUsingAdjacencyMatrix");
    
    return (EXIT_SUCCESS);
    
}
