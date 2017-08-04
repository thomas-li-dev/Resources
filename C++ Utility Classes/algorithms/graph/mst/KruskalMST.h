/*
 * KruskalMST.h
 *
 *  Created on: Aug 4, 2017
 *      Author: Wesley Leung
 */

#ifndef ALGORITHMS_GRAPH_MST_KRUSKALMST_H_
#define ALGORITHMS_GRAPH_MST_KRUSKALMST_H_

#include <bits/stdc++.h>
#include <datastructures/graph/WeightedGraph.h>
#include <datastructures/math/UF.h>

using namespace std;

/**
 *  The {@code KruskalMST} class represents a data type for computing a
 *  <em>minimum spanning tree</em> in an edge-weighted graph.
 *  The edge weights can be positive, zero, or negative and need not
 *  be distinct. If the graph is not connected, it computes a <em>minimum
 *  spanning forest</em>, which is the union of minimum spanning trees
 *  in each connected component. The {@code weight()} method returns the
 *  weight of a minimum spanning tree and the {@code edges()} method
 *  returns its edges.
 *  <p>
 *  This implementation uses <em>Krusal's algorithm</em> and the
 *  union-find data type.
 *  The constructor takes time proportional to <em>E</em> log <em>E</em>
 *  and extra space (not including the graph) proportional to <em>V</em>,
 *  where <em>V</em> is the number of vertices and <em>E</em> is the number of edges.
 *  Afterwards, the {@code weight()} method takes constant time
 *  and the {@code edges()} method takes time proportional to <em>V</em>.
 *  <p>
 *  For additional documentation,
 *  see <a href="http://algs4.cs.princeton.edu/43mst">Section 4.3</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *  For alternate implementations, see {@link LazyPrimMST}, {@link PrimMST},
 *  and {@link BoruvkaMST}.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class KruskalMST {
private:
    double weight;              // weight of MST
    vector<WeightedEdge*> mst;  // edges in MST

public:
    /**
     * Compute a minimum spanning tree (or forest) of an edge-weighted graph.
     * @param G the edge-weighted graph
     */
    KruskalMST(WeightedGraph *G) {
        weight = 0.0;
        // more efficient to build heap by passing array of edges
        priority_queue<WeightedEdge*, vector<WeightedEdge*>, WeightedEdge_greater> pq;
        for (WeightedEdge *e : G->edges()) {
            pq.push(e);
        }

        // run greedy algorithm
        UF uf(G->getV());
        while (!pq.empty() && mst.size() < G->getV() - 1) {
            WeightedEdge *e = pq.top();
            pq.pop();
            int v = e->either();
            int w = e->other(v);
            if (!uf.connected(v, w)) { // v-w does not create a cycle
                uf.join(v, w);  // merge v and w components
                mst.push_back(e);  // add edge e to mst
                weight += e->getWeight();
            }
        }
    }

    /**
     * Returns the edges in a minimum spanning tree (or forest).
     * @return the edges in a minimum spanning tree (or forest) as
     *    an iterable of edges
     */
    vector<WeightedEdge*> &edges() {
        return mst;
    }

    /**
     * Returns the sum of the edge weights in a minimum spanning tree (or forest).
     * @return the sum of the edge weights in a minimum spanning tree (or forest)
     */
    double getWeight() {
        return weight;
    }
};

#endif /* ALGORITHMS_GRAPH_MST_KRUSKALMST_H_ */