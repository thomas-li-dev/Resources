#pragma once
#include <bits/stdc++.h>
#include "../../datastructures/unionfind/UnionFind.h"
using namespace std;

// Computes the connected components of a graph using Union Find
// Vertices are 0-indexed
// Constructor Arguments:
//   V: number of vertices in the graph
//   edges: a vector of pairs containing the endpoints of each edge
// Members:
//   id: a vector of the index of the component each vertex is part of
//   components: a vector of vectors containing the vertices in each component
// In practice, has a small constant, faster than bfs and dfs
// Time Complexity:
//   constructor: O((V + E) * alpha(V))
// Memory Complexity: O(V) additional memory
// Testd:
//   https://dmoj.ca/problem/ccc03s3
//   https://codeforces.com/contest/1253/problem/D
struct CC {
  vector<int> id; vector<vector<int>> components; UnionFind uf;
  CC(int V, const vector<pair<int, int>> &edges) : id(V, -1), uf(V) {
    for (auto &&e : edges) uf.join(e.first, e.second);
    for (int v = 0; v < V; v++) if (uf.find(v) == v) {
      id[v] = components.size(); components.emplace_back(1, v);
    }
    for (int v = 0; v < V; v++) if (id[v] == -1)
      components[id[v] = id[uf.find(v)]].push_back(v);
  }
};
