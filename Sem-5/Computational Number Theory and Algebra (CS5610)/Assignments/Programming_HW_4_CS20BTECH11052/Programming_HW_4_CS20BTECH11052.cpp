#include <iostream>
#include <fstream>

using ll = __int128;

ll modPow(ll a, ll b, ll p){
	if(b == 0) return 1;
	ll c = modPow(a, b/2, p);
	return (((b%2)?a:1) * c*c) % p;
}

ll findK(ll z, ll p){
	ll k = 0;
	while(z != 1)
		k++,
		z = (z*z)%p;

	return k;
}

long tonelliShanksAlgorithm(ll a, ll p){
	// Finding t, m such that p - 1 = 2^t * m, with m odd.
	ll t = 0, m = p-1; 
	while(m % 2 == 0)
		m /= 2,
		t++;

	ll b = modPow(a, m, p);
	ll k = findK(b, p);

	if(k == t) return 0; // Not a quadratic residue

	// Finding r such that r ^ ((p-1)/2) is -1
	ll r = rand() % p;
	while(modPow(r, (p-1)/2, p) != p-1)
		r = rand() % p;

	ll x = modPow(a, (m+1)/2, p);
	ll s = modPow(r, m, p);
	ll S = modPow(s, 1 << (t-k), p);
	while(k > 0){
		b = (b * S) % p;
		x = (x * modPow(s, 1 << (t-k-1), p)) % p;
		k = findK(b, p);
		S = modPow(s, 1 << (t-k), p);
	}

	return std::min(x, p-x);
}

int main(){
	std::string input_file = "inputSquareRoots.csv";
	std::ifstream input(input_file);

	std::string testcase;
	while(input >> testcase){
		int comma_pos = testcase.find(',');
		long a = std::stol(testcase.substr(0, comma_pos));
		long p = std::stol(testcase.substr(comma_pos + 1));

		// std::cout << "The solution for x^2 = a(mod p) with (a, p) = (" << a << ", " << p << ") is ";
		std::cout << tonelliShanksAlgorithm(a, p) << std::endl;
	}

	input.close();
	return 0;
}