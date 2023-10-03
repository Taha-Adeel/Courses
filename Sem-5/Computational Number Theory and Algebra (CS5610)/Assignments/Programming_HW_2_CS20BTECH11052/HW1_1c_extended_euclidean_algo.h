#ifndef EXTENDED_EUCLIDEAN_ALGO
#define EXTENDED_EUCLIDEAN_ALGO

#include <gmpxx.h>
using BigInt = mpz_class;

// Returns (x, y, gcd(x, y)) that satisfies ax + by = c. Throws an error if no solution exists
std::tuple<BigInt, BigInt, BigInt> extended_euclidean_algo(BigInt a, BigInt b, BigInt c){
	BigInt A = std::max(abs(a), abs(b)), B = std::min(abs(a), abs(b)); // Initialize A and B
	BigInt x = 1, y = 0, u = 0, v = 1; // Initialize the transformation matrix

	// Extended Eucledian algorithm
	BigInt r, q, x_, y_;
	while(B != 0){
		x_ = x; y_ = y;
		r = A%B; q = A/B;

		x = u; u = x_ - q * u;
		y = v; v = y_ - q * v;

		A = B; B = r;
	}

	if(abs(a) < abs(b)) swap(x, y);
	if(a < 0) x *= -1;
	if(b < 0) y *= -1;


	if(c%A == 0){
		auto k = c/A;
		return {x * k, y * k, A};
		// std::cout << "(" << x * k << ", " << y * k <<") " << "is a solution to " << a << "x + " << b << "y = " << c << std::endl;
	}
	else{
		throw "No solution";
		// std::cout << "No integer solution exists for " << a << "x + " << b << "y = " << c << std::endl;
	}
}

#endif