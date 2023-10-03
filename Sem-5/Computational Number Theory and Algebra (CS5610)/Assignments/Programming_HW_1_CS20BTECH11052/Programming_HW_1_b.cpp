#include <iostream>
#include <gmpxx.h>

int main(){
	mpz_class a, b;
	std::cin >> a >> b;

	mpz_class A = std::max(abs(a), abs(b)), B = std::min(abs(a), abs(b)); // Initialize A and B
	mpz_class x = 1, y = 0, u = 0, v = 1; // Initialize the transformation matrix

	// Extended Eucledian algorithm
	mpz_class r, q, x_, y_;
	while(B != 0){
		x_ = x; y_ = y;

		r = A%B;
		q = A/B;

		x = u; u = x_ - q * u;
		y = v; v = y_ - q * v;

		A = B;
		B = r;
	}

	if(abs(a) < abs(b)) swap(x, y);
	if(a < 0) x *= -1;
	if(b < 0) y *= -1;
	
	std::cout << "(" << x << ", " << y <<") " << "is a solution to " << a << "x + " << b << "y = " << A << std::endl;

	return 0;
}