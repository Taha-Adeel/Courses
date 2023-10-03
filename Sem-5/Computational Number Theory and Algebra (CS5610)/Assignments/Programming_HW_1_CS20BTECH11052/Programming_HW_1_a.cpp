#include <iostream>
#include <numeric>
#include <gmpxx.h>

int main(){
	mpz_class a, b;
	std::cin >> a >> b;
	
	std::cout << "gcd(" << a << ", " << b << ")\n\t= " << gcd(abs(a), abs(b)) << std::endl;
	
	return 0;
}