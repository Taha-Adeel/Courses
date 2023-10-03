#ifndef GENERALIZED_INVERSE
#define GENERALIZED_INVERSE

#include <gmpxx.h>
#include "HW1_1c_extended_euclidean_algo.h"
using BigInt = mpz_class;

// Returns b such that a*b ≡ gcd(a, n)
BigInt generalized_inverse(BigInt& a, const BigInt& n){
	auto [x, y, g] = extended_euclidean_algo(a, n, gcd(a, n));
	x = (x%n + n) % n; // Normalizing x to Zn

	// Any b ≡ x (mod n/g) satisfies ab ≡ gcd(a, n)
	return x % (n/g);
}

#endif