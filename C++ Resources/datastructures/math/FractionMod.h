#pragma once
#include <bits/stdc++.h>
#include "../../algorithms/math/Combinatorics.h"
using namespace std;

// Data structure representing a Fraction modulo MOD
template <class T, T MOD> struct FractionMod {
    T num, den;
    FractionMod(T num = 0, T den = 0) : num(num % MOD), den(den % MOD) {}
    FractionMod<T, MOD> operator + (const FractionMod<T, MOD> &f) const {
        return FractionMod<T, MOD>((num * f.den % MOD + f.num * den % MOD) % MOD, den * f.den % MOD);
    }
    FractionMod<T, MOD> &operator += (const FractionMod<T, MOD> &f) {
        num = (num * f.den % MOD + f.num * den % MOD) % MOD; den = den * f.den % MOD;
        return *this;
    }
    FractionMod<T, MOD> operator - (const FractionMod<T, MOD> &f) const {
        return FractionMod<T, MOD>((num * f.den % MOD - f.num * den % MOD + MOD) % MOD, den * f.den % MOD);
    }
    FractionMod<T, MOD> &operator -= (const FractionMod<T, MOD> &f) {
        num = (num * f.den % MOD - f.num * den % MOD + MOD) % MOD; den = den * f.den % MOD;
        return *this;
    }
    FractionMod<T, MOD> operator * (const FractionMod<T, MOD> &f) const {
        return FractionMod<T, MOD>(num * f.num % MOD, den * f.den % MOD);
    }
    FractionMod<T, MOD> &operator *= (const FractionMod<T, MOD> &f) {
        num = num * f.num % MOD; den = den * f.den % MOD;
        return *this;
    }
    FractionMod<T, MOD> operator / (const FractionMod<T, MOD> &f) const {
        return FractionMod<T, MOD>(num * f.den % MOD, den * f.num % MOD);
    }
    FractionMod<T, MOD> &operator /= (const FractionMod<T, MOD> &f) {
        T t_num = num * f.den % MOD, t_den = den * f.num % MOD; num = t_num; den = t_den;
        return *this;
    }
    bool operator == (const FractionMod<T, MOD> &f) { return divMod(num, den, MOD) == divMod(f.num, f.den, MOD); }
    bool operator != (const FractionMod<T, MOD> &f) { return !(*this == f); }
};