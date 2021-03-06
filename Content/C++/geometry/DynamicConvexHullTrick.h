#pragma once
#include <bits/stdc++.h>
using namespace std;

using T = long double; const T EPS = 1e-9;

bool lt(T a, T b) { return a + EPS < b; }
bool le(T a, T b) { return !lt(b, a); }
bool gt(T a, T b) { return lt(b, a); }
bool ge(T a, T b) { return !lt(a, b); }
bool eq(T a, T b) { return !lt(a, b) && !lt(b, a); }
bool ne(T a, T b) { return lt(a, b) || lt(b, a); }

struct Line {
    T m, b; bool isQuery; mutable function<const Line*()> succ; Line(T m, T b, bool isQuery) : m(m), b(b), isQuery(isQuery) {}
    bool operator < (const Line &L) const {
        if (!L.isQuery) return lt(m, L.m);
        const Line *s = succ(); T x = L.m;
        if (!s) return 0;
        return lt(b - s->b, (s->m - m) * x);
    }
};

// Supports adding lines in the form f(x) = mx + b and finding the maximum value of f(x) at any given x
// Dynamic variant (allows for updates and queries in arbitrary order)
// Time Complexity:
//   addLine, getMax: O(log N)
// Memory Complexity: O(N) where N is the total number of lines added
template <const bool maxHull> struct DynamicConvexHullTrick : public multiset<Line> {
    bool bad(iterator y) {
        auto z = next(y);
        if (y == begin()) {
            if (z == end()) return 0;
            return eq(y->m, z->m) && le(y->b, z->b);
        }
        auto x = prev(y);
        if (z == end()) return eq(y->m, x->m) && le(y->b, x->b);
        return ge((x->b - y->b) * (z->m - y->m), (y->b - z->b) * (y->m - x->m));
    }
    void addLine(T m, T b) {
        if (!maxHull) { m = -m; b = -b; }
        auto y = emplace(m, b, false);
        if (bad(y)) { erase(y); return; }
        while (next(y) != end() && bad(next(y))) erase(next(y));
        y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
        while (y != begin() && bad(prev(y))) erase(prev(y));
        if (y != begin()) prev(y)->succ = [=] { return &*y; };
    }
    T getMax(T x) { auto l = *lower_bound(Line(x, 0, true)); return maxHull ? l.m * x + l.b : -(l.m * x + l.b); }
};
