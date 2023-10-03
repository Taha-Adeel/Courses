#ifndef GENERALIZED_INVERSE
#define GENERALIZED_INVERSE

#include <gmpxx.h>
#include "HW1_1c_extended_euclidean_algo.h"
using BigInt = mpz_class;

// Returns the inverse of a in Zn. Throws an error if inverse doesnt exist
BigInt inverse(BigInt& a, const BigInt& n){
	auto [x, y, g] = extended_euclidean_algo(a, n, gcd(a, n));
	if(g != 1) throw "a doesnt have an inverse in Zn";

	x = (x%n + n) % n; // Normalizing x to Zn
	return x;
}

#endif