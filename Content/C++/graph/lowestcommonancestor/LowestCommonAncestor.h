#pragma once
#include <bits/stdc++.h>
#include "../../datastructures/FischerHeunStructure.h"
using namespace std;

// Supports queries for the lowest common ancestor of 2 vertices in a forest
//   and the distance between 2 vertices by reduing the problem to a
//   range minimum query using the Fischer Heun Structure
// Vertices are 0-indexed
// Template Arguments:
//   T: the type of the weight of the edges in the forest
// Constructor Arguments:
//   G: a generic forest data structure (weighted or unweighted)
//     with the [] operator (const) defined to iterate over the adjacency list
//     (which is a list of ints for an unweighted forest, or a list of
//     pair<int, T> for a weighted forest with weights of type T), as well as a
//     member function size() (const) that returns the number of vertices
//     in the forest
//   rt: a single root vertex
//   roots: a vector of root vertices
// Fields:
//   root: vector of roots for the forest each vertex is in
//   dist: vector of distance to each vertex from the root of its forest
// Functions:
//   lca(v, w): returns the lowest common ancestor of vertices v and w assuming
//     v and w are connected
//   connected(v, w): returns true if and only if v and w are connected
//   getDist(v, w): returns the distance between vertices v and w assuming
//     v and w are connected
// In practice, lca and getDist have a moderate constant, constructor is
//   dependent on the forest data structure
// Time Complexity:
//   constructor: O(V)
//   lca, connected, getDist: O(1)
// Memory Complexity: O(V)
// Tested:
//   https://judge.yosupo.jp/problem/lca
//   https://www.spoj.com/problems/LCASQ
//   https://codeforces.com/contest/1062/problem/E
//   https://dmoj.ca/problem/rte16s3
template <class T = int> struct LCA {
  using RMQ = FischerHeunStructure<int, function<bool(int, int)>>;
  int V, ind; vector<int> root, pre, vert; vector<T> dist; RMQ FHS;
  int getTo(int e) { return e; }
  T getWeight(int) { return 1; }
  int getTo(const pair<int, T> &e) { return e.first; }
  T getWeight(const pair<int, T> &e) { return e.second; }
  template <class Forest>
  void dfs(const Forest &G, int v, int prev, int r, T d) {
    root[v] = r; dist[v] = d; vert[pre[v] = ind++] = v; for (auto &&e : G[v]) {
      int w = getTo(e);
      if (w != prev) { dfs(G, w, v, r, d + getWeight(e)); vert[ind++] = v; }
    }
  }
  template <class Forest> RMQ init(const Forest &G, const vector<int> &roots) {
    ind = 0; if (roots.empty()) {
      for (int v = 0; v < V; v++) if (root[v] == -1) dfs(G, v, -1, v, T());
    } else for (int rt : roots) dfs(G, rt, -1, rt, T());
    return RMQ(vert.begin(), vert.begin() + ind, [&] (int v, int w) {
                 return dist[v] > dist[w];
               });
  }
  template <class Forest>
  LCA(const Forest &G, const vector<int> &roots = vector<int>())
      : V(G.size()), root(V, -1), pre(V), vert(max(0, V * 2 - 1)), dist(V),
        FHS(init(G, roots)) {}
  template <class Forest> LCA(const Forest &G, int rt)
      : LCA(G, vector<int>(1, rt)) {}
  int lca(int v, int w) {
    if (pre[v] > pre[w]) swap(v, w);
    return FHS.query(pre[v], pre[w]);
  }
  bool connected(int v, int w) { return root[v] == root[w]; }
  T getDist(int v, int w) { return dist[v] + dist[w] - 2 * dist[lca(v, w)]; }
};
