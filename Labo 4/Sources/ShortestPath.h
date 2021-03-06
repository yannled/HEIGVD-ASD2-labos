//
//  ShortestPath.h
//  ASD2
//
//  Created by Olivier Cuisenaire on 05.11.14.
//
// modified MM. Léonard BERNEY et Valentin MINDER // 04.01.2015

#ifndef ASD2_ShortestPath_h
#define ASD2_ShortestPath_h

#include <algorithm>
#include <queue>
#include <vector>
#include <set>
#include <functional>


namespace ASD2 {

	// Classe parente de toutes les classes de plus court chemin.
	// Defini les membres edgeTo et distanceTo commun à toutes ces
	// classes, ainsi que les methodes DistanceTo, EdgeTo et PathTo
	// qui permettent de les interroger.
	//
	// Le calcul des plus courts chemins est fait dans les constructeurs
	// des classes derivees.

	template<typename GraphType>   // Type du graphe pondere oriente a traiter
	// GraphType doit se comporter comme un
	// EdgeWeightedDiGraph et definir le
	// type GraphType::Edge
	class ShortestPath {
	public:
		// Type des arcs. Normalement ASD2::DirectedEdge<double>
		typedef typename GraphType::Edge Edge;

		// Type des poids. Normalement double ou int.
		typedef typename Edge::WeightType Weight;

		// Listes d'arcs et de poids
		typedef std::vector<Edge> Edges;
		typedef std::vector<Weight> Weights;

		// Renvoie la distance du chemin le plus court du sommet source a v
		Weight DistanceTo(int v) {
			return distanceTo.at(v);
		}

		// Renvoie le dernier arc u->v du chemin le plus court du sommet source a v
		Edge EdgeTo(int v) {
			return edgeTo.at(v);
		}

		// Renvoie la liste ordonnee des arcs constituant un chemin le plus court du
		// sommet source à v.
		Edges PathTo(int v) {
			/* A IMPLEMENTER 
                         * 
                         * remonte la liste de edgeTo jusqu'à la source, 
                         * identifiée par une boucle sur elle-meme,
                         * en prenant l'arete arrivant au sommet cherché 
                         * et en deplacement le sommet de recherche sur 
                         * le sommet partant de cette arrête.
                         */
			Edges edges;
			while (edgeTo[v].From() != edgeTo[v].To())
			{
				edges.insert(edges.begin(), edgeTo[v]);
				v = edgeTo[v].From();
			}

			return edges;
		}

	protected:
		Edges edgeTo;
		Weights distanceTo;                
	};

	// Classe a mettre en oeuvre au labo 4. S'inspirer de BellmaFordSP pour l'API

	template<typename GraphType>
	class DijkstraSP : public ShortestPath < GraphType > {
	private:
		/**
                 * Paire de <dist,v> indiquant la distance connue au sommet v.
                 */
		typedef std::pair<double,int> DistSom;
		/**
                 * Queue de priorité (implémentée par un set de <distances,sommets>
                 */
		std::set<DistSom> queue;
		/**
                 * Lorsque le sommet a été retiré de la queue et traité définitivement.
                 */
		std::vector<bool> marked;

	public:
		typedef ShortestPath<GraphType> BASE;
		typedef typename BASE::Edge Edge;
		typedef typename BASE::Weight Weight;

		DijkstraSP(const GraphType& g, int v)  {
			/* A IMPLEMENTER */
			//on suppose que le graphe ne contient que des poids positifs
                    
			// initilisation de marked a false, sauf pour le départ
			marked.assign(g.V(),false);
			marked[v] = true;
                        
			// réservation de edgeTo, initialisation du premier sommet
			// on a besoin d'une boucle a 0 comme condition d'arret sur v
			this->edgeTo.reserve(g.V());
			this->edgeTo[v] = Edge (v,v,0);
                        
			// inilialisation de distanceTo, max pour tous sauf départ à 0
			this->distanceTo.assign(g.V(), std::numeric_limits<Weight>::max());
			this->distanceTo.at(v) = 0;
                        
                        // insertion du sommet de départ dans la queue
			queue.insert(std::make_pair(0, v));

			while (!queue.empty())
			{
				// les données du sommet le plus proche sont récupérées
				double dist = queue.begin()->first;
				int vertexFrom = queue.begin()->second;
                                // sommet retiré de la queue et marqué définitif.
				queue.erase(queue.begin());
                                marked[vertexFrom] = true;

                                // parcours de tous les voisins
				g.forEachAdjacentEdge(vertexFrom, [&](const Edge& e){
					// distToAlternative est la distance possible pour vertexTo en passant par vertexFrom
					double distToAlternative = dist + e.Weight();
					int vertexTo = e.To();
					if (!marked[vertexTo] && distToAlternative < this->distanceTo[e.To()])
					{
						// erase puis insert permet le decrease_key !
						this->queue.erase(std::make_pair(this->distanceTo[vertexTo], vertexTo));
						this->queue.insert(std::make_pair(distToAlternative, vertexTo));
						// mise a jour des tableaux distanceTo et edgeTo
						this->distanceTo[vertexTo] = distToAlternative;
						this->edgeTo[vertexTo] = e;
					}
				});

			}
		}
	};

	// Algorithme de BellmanFord.

	template<typename GraphType> // Type du graphe pondere oriente a traiter
	// GraphType doit se comporter comme un
	// EdgeWeightedDiGraph et definir forEachEdge(Func),
	// ainsi que le type GraphType::Edge. Ce dernier doit
	// se comporter comme ASD2::DirectedEdge, c-a-dire definir From(),
	// To() et Weight()

	class BellmanFordSP : public ShortestPath < GraphType > {

	private:
		typedef ShortestPath<GraphType> BASE;
		typedef typename BASE::Edge Edge;
		typedef typename BASE::Weight Weight;

		// Relachement de l'arc e
		void relax(const Edge& e) {
			int v = e.From(), w = e.To();
			Weight distThruE = this->distanceTo[v] + e.Weight();

			if (this->distanceTo[w] > distThruE) {
				this->distanceTo[w] = distThruE;
				this->edgeTo[w] = e;
			}
		}

	public:

		// Constructeur a partir du graphe g et du sommet v a la source
		// des plus courts chemins
		BellmanFordSP(const GraphType& g, int v) {

			this->edgeTo.reserve(g.V());
			this->distanceTo.assign(g.V(), std::numeric_limits<Weight>::max());

			this->edgeTo[v] = Edge(v, v, 0);
			this->distanceTo[v] = 0;

			for (int i = 0; i < g.V(); ++i)
				g.forEachEdge([this](const Edge& e){
				this->relax(e);
			});
		}
	};



	// Algorithme de BellmanFord avec queue simple reprenant les sommets ayant
	// ete modifies par la derniere iteration.

	template<typename GraphType> // Type du graphe pondere oriente a traiter
	// GraphType doit se comporter comme un
	// EdgeWeightedDiGraph et definir forEachAdjacentEdge(int,Func),
	// ainsi que le type GraphType::Edge. Ce dernier doit
	// se comporter comme ASD2::DirectedEdge, c-a-dire definir From(),
	// To() et Weight()

	class BellmanFordQueueSP : public ShortestPath < GraphType > {

	private:
		typedef ShortestPath<GraphType> BASE;
		typedef typename BASE::Edge Edge;
		typedef typename BASE::Weight Weight;

		std::queue<int> queue;
		std::vector<int> inQueue;

		void relax(const Edge& e) {
			int v = e.From(), w = e.To();
			Weight distThruE = this->distanceTo[v] + e.Weight();
			if (this->distanceTo[w] > distThruE) {
				this->distanceTo[w] = distThruE;
				this->edgeTo[w] = e;

				if (!inQueue[w]) {
					inQueue[w] = true;
					queue.push(w);
				}
			}
		}

	public:
		BellmanFordQueueSP(const GraphType& g, int v) {

			inQueue.assign(g.V(), false);

			this->edgeTo.reserve(g.V());
			this->distanceTo.assign(g.V(), std::numeric_limits<Weight>::max());

			this->edgeTo[v] = Edge(v, v, 0);
			this->distanceTo[v] = 0;
			queue.push(v);
			inQueue[v] = true;

			while (!queue.empty()) {
				int v = queue.front();
				inQueue[v] = false;
				queue.pop();

				g.forEachAdjacentEdge(v, [&](const Edge& e) {
					this->relax(e);
				});
			}
		}
	};
}

#endif
