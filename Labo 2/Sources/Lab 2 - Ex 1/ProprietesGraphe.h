/* 
 * File:   ProprietesGraphe.h
 * Author: Olivier Cuisenaire
 *
 * Created on 5. septembre 2014, 08:55
 */

#ifndef PROPRIETESGRAPHE_H
#define	PROPRIETESGRAPHE_H


namespace ASD2 {

    class ProprietesGraphe {
    public:

        template<typename GraphType>
        static int degree(const GraphType& G, int v) {
            int degre = 0;
            for (int w : G.adjacent(v)) degre++;
            return degre;
        }

        template<typename GraphType>
        static int degreeMax(const GraphType& G) {
            int max = 0;
            for (int v = 0; v < G.V(); v++)
                max = std::max(max, degree(G, v));
            return max;
        }

        template<typename GraphType>
        static int nrOfLoops(const GraphType& G) {
            int count = 0;
            for (int v = 0; v < G.V(); v++)
                for (int w : G.adjacent(v))
                    if (v == w) count++;
            return count;
        }
    };
}
#endif	/* PROPRIETESGRAPHE_H */

