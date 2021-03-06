#pragma once
#include <bits/stdc++.h>
using namespace std;

// Node classes for Treap and Splay trees, as well as Link Cut Trees
// A node class must contain at a minimum,
//     the following for Treap and Splay support:
//   HAS_PAR: const static bool indicating whether this node has
//     a parent pointer
//   sz: integer representing the size of the subtree
//   l: pointer of the same node type to the left child
//   r: pointer of the same node type to the right child
//   constructor: takes a single argument with the information for the node
//   update: void() that updates the size of subtree,
//     along with any additional information
//   propagate: void() that pushes information lazily to the children
//   If HAS_PAR is true, then it should also contain the following:
//     p: pointer of the same node type to the parent
//   If the node class is used in conjunction with DynamicRangeOperations,
//       then it must also contain the following:
//     Data: typedef/using of the value type this node stores
//     Lazy: typedef/using of the lazy type used to update the node
//       (even if no lazy propagation occurs)
//     RANGE_UPDATES: const static bool indicating whether range updates
//       are supported
//     RANGE_QUERIES: const static bool indicating whether range queries
//       are supported
//     RANGE_REVERSALS: const static bool indicating whether range reversals
//       are supported
//     val: Data representing the value of the node
//     apply: void(const Lazy &v) that updates the information of the node
//       (including optional aggregate and lazy information)
//   If RANGE_UPDATES is true, then the following are required:
//     lz: Lazy representing the lazy information that will be pushed to
//       the child nodes
//   If RANGE_QUERIES is true, then the following are required:
//     sbtr: Data representing the aggregate data of the subtree
//     qdef: static Data() returning the query default value
//   If RANGE_REVERSALS is true, then the following are required:
//     reverse: void() that reverses the subtree rooted at that node
//       (aggregate data and any lazy flags should be reversed)

// Sample node class for a single value of type T, supporting range reversals,
//   and point assignment
// Tested:
//   https://dmoj.ca/problem/ds4
//   https://codeforces.com/contest/1288/problem/E
//   https://codeforces.com/contest/863/problem/D
//   https://oj.uz/problem/view/JOI13_synchronization
template <class T> struct NodeVal {
  using Data = T;
  using Lazy = Data;
  const static int RANGE_UPDATES = false;
  const static int RANGE_QUERIES = false;
  const static int RANGE_REVERSALS = true;
  const static int HAS_PAR = true;
  bool rev; int sz; NodeVal *l, *r, *p; Data val;
  NodeVal(const Data &v)
      : rev(false), sz(1), l(nullptr), r(nullptr), p(nullptr), val(v) {}
  void update() {
    sz = 1;
    if (l) sz += l->sz;
    if (r) sz += r->sz;
  }
  void propagate() {
    if (rev) {
      swap(l, r); rev = false;
      if (l) l->reverse();
      if (r) r->reverse();
    }
  }
  void apply(const Lazy &v) { val = v; }
  void reverse() { rev = !rev; }
};

// Sample node class for aggregate range queries using a Combine struct,
//   along with range reversals, and point assignment
// The combine struct must have typedefs/using for data and lazy,
//   a query default value (qdef), and implementations of merge, applyLazy,
//   and if RANGE_REVERSALS is true, revData
// merge, and applyLazy must both be associative
// Below is a sample struct for point assignment and range sum queries,
//  and range reversals
// struct Combine {
//   using Data = int;
//   using Lazy = int;
//   const Data qdef = 0;
//   Data merge(const Data &l, const Data &r) const { return l + r; }
//   Data applyLazy(const Data &l, const Lazy &r) const { return r; }
//   void revData(Data &v) const {}
// };
// Tested:
//   https://dmoj.ca/problem/dmpg17g2
//   https://dmoj.ca/problem/ccoprep16c2q3
//   https://dmoj.ca/problem/coi08p2
//   https://www.spoj.com/problems/QTREE2/
//   https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite
template <class Combine> struct NodeAgg {
  using Data = typename Combine::Data;
  using Lazy = typename Combine::Lazy;
  const static int RANGE_UPDATES = false;
  const static int RANGE_QUERIES = true;
  const static int RANGE_REVERSALS = true;
  const static bool HAS_PAR = true;
  bool rev; int sz; NodeAgg *l, *r, *p; Data val, sbtr;
  NodeAgg(const Data &v)
      : rev(false), sz(1), l(nullptr), r(nullptr), p(nullptr),
        val(v), sbtr(v) {}
  void update() {
    sz = 1; sbtr = val;
    if (l) { sz += l->sz; sbtr = Combine().merge(l->sbtr, sbtr); }
    if (r) { sz += r->sz; sbtr = Combine().merge(sbtr, r->sbtr); }
  }
  void propagate() {
    if (rev) {
      swap(l, r); rev = false;
      if (l) l->reverse();
      if (r) r->reverse();
    }
  }
  void apply(const Lazy &v) {
    val = Combine().applyLazy(val, v); sbtr = Combine().applyLazy(sbtr, v);
  }
  void reverse() { rev = !rev; Combine().revData(sbtr); }
  static Data qdef() { return Combine().qdef; }
};

// Sample node class for aggregate range queries and lazy range updates
//  using a Combine struct, along with range reversals
// The combine struct must have typedefs/using for data and lazy,
//   a query default value (qdef), and implementations of merge, applyLazy,
//   getSegmentVal, mergeLazy, and if RANGE_REVERSALS is true, revData
// merge, applyLazy, and mergeLazy must all be associative
// Below is a sample struct for range assignment and range sum queries,
//   and range reversals
// struct Combine {
//   using Data = int;
//   using Lazy = int;
//   const Data qdef = 0;
//   const Lazy ldef = numeric_limits<int>::min();
//   Data merge(const Data &l, const Data &r) const { return l + r; }
//   Data applyLazy(const Data &l, const Lazy &r) const { return r; }
//   Lazy getSegmentVal(const Lazy &v, int k) const { return v * k; }
//   Lazy mergeLazy(const Lazy &l, const Lazy &r) const { return r; }
//   void revData(Data &v) const {}
// };
// Tested:
//   https://dmoj.ca/problem/acc1p1
//   https://dmoj.ca/problem/noi05p2
//   https://dmoj.ca/problem/ds5easy
template <class Combine> struct NodeLazyAgg {
  using Data = typename Combine::Data;
  using Lazy = typename Combine::Lazy;
  const static int RANGE_UPDATES = true;
  const static int RANGE_QUERIES = true;
  const static int RANGE_REVERSALS = true;
  const static int HAS_PAR = true;
  bool rev; int sz; NodeLazyAgg *l, *r, *p; Lazy lz; Data val, sbtr;
  NodeLazyAgg(const Data &v)
      : rev(false), sz(1), l(nullptr), r(nullptr), p(nullptr),
        lz(Combine().ldef), val(v), sbtr(v) {}
  void update() {
    sz = 1; sbtr = val;
    if (l) { sz += l->sz; sbtr = Combine().merge(l->sbtr, sbtr); }
    if (r) { sz += r->sz; sbtr = Combine().merge(sbtr, r->sbtr); }
  }
  void propagate() {
    if (rev) {
      swap(l, r); rev = false;
      if (l) l->reverse();
      if (r) r->reverse();
    }
    if (lz != Combine().ldef) {
      if (l) l->apply(lz);
      if (r) r->apply(lz);
      lz = Combine().ldef;
    }
  }
  void apply(const Lazy &v) {
    val = Combine().applyLazy(val, v);
    sbtr = Combine().applyLazy(sbtr, Combine().getSegmentVal(v, sz));
    lz = Combine().mergeLazy(lz, v);
  }
  void reverse() { rev = !rev; Combine().revData(sbtr); }
  static Data qdef() { return Combine().qdef; }
};
