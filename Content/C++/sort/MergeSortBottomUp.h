#pragma once
#include <bits/stdc++.h>
using namespace std;

// Sorts an array using bottom up merge sort
// Time Complexity: O(N log N) worse case
// Memory Complexity: O(N) additional memory

const int INSERTION_SORT_CUTOFF = 8;

template <class It> void merge_sort_bottom_up(It st, It en) {
    typedef typename std::iterator_traits<It>::value_type T;
    int n = en - st; T *aux = new T[n];
    for (int i = 0; i < n; i++) aux[i] = st[i];
    bool flag = true; int len = 1;
    for (; len * 2 <= INSERTION_SORT_CUTOFF && len < n; len *= 2);
    for (int lo = 0; lo < n; lo += len + len) {
        int hi = min(lo + len + len - 1, n - 1);
        for (int i = lo; i <= hi; i++) for (int j = i; j > lo && aux[j] < aux[j - 1]; j--)
            swap(aux[j], aux[j - 1]);
    }
    len *= 2;
    for (; len < n; len *= 2) {
        if (flag) {
            for (int lo = 0; lo < n; lo += len + len) {
                int mid = lo + len - 1, hi = min(lo + len + len - 1, n - 1);
                if (mid + 1 < n && aux[mid + 1] >= aux[mid]) {
                    for (int i = lo; i <= hi; i++) st[i] = aux[i];
                } else {
                    int i = lo, j = mid + 1;
                    for (int k = lo; k <= hi; k++) {
                        if (i > mid) st[k] = aux[j++];
                        else if (j > hi) st[k] = aux[i++];
                        else if (aux[j] < aux[i]) st[k] = aux[j++];
                        else st[k] = aux[i++];
                    }
                }
            }
        } else {
            for (int lo = 0; lo < n; lo += len + len) {
                int mid = lo + len - 1, hi = min(lo + len + len - 1, n - 1);
                if (mid + 1 < n && st[mid + 1] >= st[mid]) {
                    for (int i = lo; i <= hi; i++) aux[i] = st[i];
                } else {
                    int i = lo, j = mid + 1;
                    for (int k = lo; k <= hi; k++) {
                        if (i > mid) aux[k] = st[j++];
                        else if (j > hi) aux[k] = st[i++];
                        else if (st[j] < st[i]) aux[k] = st[j++];
                        else aux[k] = st[i++];
                    }
                }
            }
        }
        flag = !flag;
    }
    if (flag) for (int i = 0; i < n; i++) st[i] = aux[i];
    delete[] (aux);
}

/////////////////// COMPARATOR SORT ///////////////////

template <class It, class Comparator> void merge_sort_bottom_up(It st, It en, Comparator cmp) {
    typedef typename std::iterator_traits<It>::value_type T;
    int n = en - st; T *aux = new T[n];
    for (int i = 0; i < n; i++) aux[i] = st[i];
    bool flag = true; int len = 1;
    for (; len * 2 <= INSERTION_SORT_CUTOFF && len < n; len *= 2);
    for (int lo = 0; lo < n; lo += len + len) {
        int hi = min(lo + len + len - 1, n - 1);
        for (int i = lo; i <= hi; i++) for (int j = i; j > lo && cmp(aux[j], aux[j - 1]); j--)
            swap(aux[j], aux[j - 1]);
    }
    len *= 2;
    for (; len < n; len *= 2) {
        if (flag) {
            for (int lo = 0; lo < n; lo += len + len) {
                int mid = lo + len - 1, hi = min(lo + len + len - 1, n - 1);
                if (mid + 1 < n && !cmp(aux[mid + 1], aux[mid])) {
                    for (int i = lo; i <= hi; i++) st[i] = aux[i];
                } else {
                    int i = lo, j = mid + 1;
                    for (int k = lo; k <= hi; k++) {
                        if (i > mid) st[k] = aux[j++];
                        else if (j > hi) st[k] = aux[i++];
                        else if (cmp(aux[j], aux[i])) st[k] = aux[j++];
                        else st[k] = aux[i++];
                    }
                }
            }
        } else {
            for (int lo = 0; lo < n; lo += len + len) {
                int mid = lo + len - 1, hi = min(lo + len + len - 1, n - 1);
                if (mid + 1 < n && !cmp(st[mid + 1], st[mid])) {
                    for (int i = lo; i <= hi; i++) aux[i] = st[i];
                } else {
                    int i = lo, j = mid + 1;
                    for (int k = lo; k <= hi; k++) {
                        if (i > mid) aux[k] = st[j++];
                        else if (j > hi) aux[k] = st[i++];
                        else if (cmp(st[j], st[i])) aux[k] = st[j++];
                        else aux[k] = st[i++];
                    }
                }
            }
        }
        flag = !flag;
    }
    if (flag) for (int i = 0; i < n; i++) st[i] = aux[i];
    delete[] (aux);
}
