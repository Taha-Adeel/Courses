#ifndef CHINESE_REMAINDER_THEOREM
#define CHINESE_REMAINDER_THEOREM

#include <iostream>
#include <gmpxx.h>
#include "HW1_1c_extended_euclidean_algo.h"

using BigInt = mpz_class;

// Returns the smallest positive integer x that satisfies both x ≡ a (mod m) and x ≡ b (mod n)
BigInt CRT(BigInt a, BigInt b, BigInt m, BigInt n){
	a %= m; b %= n;

	// x = a + m y1 = b + n y2
	// Therefore we solve (m y1 - n y2 = b - a) using Bezout's Lemma / Extended euclidean algorithm
	try{
		auto [y1, y2, g] = extended_euclidean_algo(m, -n, b - a);

		BigInt x = (a + m * y1) % (m*n/g);
		if(x < 0) x += m*n/g;
		return x;
	}
	catch(char* error){
		std::cout << error << std::endl;
		return -1;
	}
}

#endif