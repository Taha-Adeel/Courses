#ifndef MOD_POW
#define MOD_POW

#include <gmpxx.h>
using BigInt = mpz_class;

// Returns a ^ b (mod n);
BigInt mod_pow(BigInt a, BigInt b, const BigInt& n){
	if(b == 0) return 1;
	BigInt p =  mod_pow(a, b/2, n) % n;
	BigInt p2 = (p * p) % n;

	return (b % 2 == 1) ? (a * p2) % n : p2;
}

#endif