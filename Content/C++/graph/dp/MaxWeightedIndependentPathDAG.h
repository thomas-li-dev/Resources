#pragma once
#include <bits/stdc++.h>
using namespace std;

// Computes the maximum sum of non adjacent vertices on any path between
// a source an (optional) destination vertex on a Directed Acyclic Graph
// Time Complexity: O(V + E)
// Memory Complexity: O(V + E)
template <const int MAXV, class T> struct MaxWeightedIndependentPathDAG {
    vector<int> adj[MAXV]; T val[MAXV], dp[MAXV][2];
    void addEdge(int v, int w) { adj[v].push_back(w); }
    T dfs(int v, int t, bool take) {
        if (v == t) return take ? val[v] : 0;
        if (dp[v][take] != numeric_limits<T>::max()) return dp[v][take];
        T ret = numeric_limits<T>::lowest();
        for (int w : adj[v]) {
            if (!take) ret = max(ret, dfs(w, true));
            ret = max(ret, dfs(w, false));
        }
        return take ? (dp[v][take] = ret + val[v]) : (dp[v][take] = ret);
    }
    void clear(int V = MAXV) { for (int i = 0; i < V; i++) adj[i].clear(); }
    T solve(int V, int s, int t) {
        for (int i = 0; i < V; i++) dp[i][0] = dp[i][1] = numeric_limits<T>::max();
        return dfs(s, t, true);
    }
};
