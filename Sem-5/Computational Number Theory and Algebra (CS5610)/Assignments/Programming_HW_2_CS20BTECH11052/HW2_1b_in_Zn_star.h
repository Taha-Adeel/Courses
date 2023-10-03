#ifndef IN_Zn_STAR
#define IN_Zn_STAR

#include <gmpxx.h>
using BigInt = mpz_class;

// Returns true if a belongs to Zn*, false otherwise
bool in_Zn_star(BigInt& a, const BigInt& n){
	if(gcd(a, n) == 1)
		return true;
	else
		return false;
}

#endif