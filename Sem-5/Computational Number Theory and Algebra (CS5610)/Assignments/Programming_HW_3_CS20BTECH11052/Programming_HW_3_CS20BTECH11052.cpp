#include <iostream>
#include <vector>
#include <gmpxx.h>

using BigInt = mpz_class;

// Overloads modulo to always return value in {0...(N-1)}
BigInt operator % (const BigInt& a, const BigInt N){BigInt result = a - N * (a / N); return (result < 0) ? result + N : result;}
BigInt operator % (const BigInt& a, const int N){return a % (BigInt)N;}

// Class to perform operations in Zn = {0...(N-1)}
struct Zn{
	static BigInt N;
	BigInt val; 

	// Constructors to allow impilicit type conversions
	Zn(const BigInt& z) {if(N == -1) val = z; else val = z % N;}
	Zn(const int& z = 0): Zn((BigInt)z) {}
	static void set_N(BigInt _N){N = _N;}

	// Overloaded operators to perform arithematic in Zn
	Zn& operator += (const Zn& b) {val += b.val; val = val % N; return *this;}
	Zn& operator -= (const Zn& b) {val -= b.val; val = val % N; return *this;}
	Zn& operator *= (const Zn& b) {val *= b.val; val = val % N; return *this;}
	Zn& operator /= (const Zn& b) {return *this *= b.inverse();}
	Zn operator + (const Zn& b) const {Zn lhs(*this); return lhs += b;}
	Zn operator - (const Zn& b) const {Zn lhs(*this); return lhs -= b;}
	Zn operator * (const Zn& b) const {Zn lhs(*this); return lhs *= b;}
	Zn operator / (const Zn& b) const {Zn lhs(*this); return lhs /= b;}

	// Performs binary exponentiation in Zn
	Zn pow(const BigInt& k) const {
		if(k == 0) return 1;
		Zn p = pow(k/2);
		return (k % 2) ? p * p * val : p * p;
	}

	// Returns inverse of x in Zn using Fermat's little theorem. Assumes that n is prime.
	Zn inverse() const {
		return this->pow(N - 2);
	}

	bool operator == (const Zn& b) const {return val == b.val;}
	bool operator != (const Zn& b) const {return val != b.val;}
	friend std::ostream& operator << (std::ostream& out, const Zn& z){return out << z.val;}
};
BigInt Zn::N = -1;

template<typename T = Zn>
class Polynomial{
private:
	std::vector<T> coeffs;

public:
	int degree() const {return coeffs.size() - 1;} // Returns the degree of the polynomial
	void set_degree(int d) {coeffs = std::vector<T>(d+1);}
	Polynomial& reduce() {while(coeffs.size() > 1 && coeffs.back() == 0) coeffs.pop_back(); return *this;} // Removes leading 0 coefficients
	const T coeff(int i) const {if(i > degree()) return 0; return coeffs[i];} // Get the coeeficient of x^i in the polynomial

	Polynomial(int c = 0){coeffs.push_back(c);}
	Polynomial(Zn c){coeffs.push_back(c);}
	Polynomial(std::vector<T> _coeffs): coeffs(_coeffs) {}

	// Returns f(x) + g(x)
	Polynomial operator + (const Polynomial& g) const {
		int result_degree = std::max(degree(), g.degree());
		Polynomial result; result.set_degree(result_degree);
		for(int i = 0; i <= result_degree; i++)
			result.coeffs[i] = coeff(i) + g.coeff(i);
		
		return result.reduce();
	}

	// Returns f(x) - g(x)
	Polynomial operator - (const Polynomial& g) const {
		int result_degree = std::max(degree(), g.degree());
		Polynomial result; result.set_degree(result_degree);
		for(int i = 0; i <= result_degree; i++)
			result.coeffs[i] = coeff(i) - g.coeff(i);
		
		return result.reduce();
	}

	// Returns f(x) * g(x)
	Polynomial operator * (const Polynomial& g) const {
		int result_degree = degree() + g.degree();
		Polynomial result; result.set_degree(result_degree);
		for(int i = 0; i <= degree(); i++)
			for(int j = 0; j <= g.degree(); j++)
				result.coeffs[i + j] += coeff(i) * g.coeff(j);
		
		return result.reduce();
	}

	// Returns q(x) s.t f(x) = g(x) * q(x) + r(x);
	Polynomial operator / (const Polynomial& g) const {
		Polynomial q, r = *this;
		while(r != 0 && r.degree() >= g.degree()){
			Polynomial qi; qi.set_degree(r.degree() - g.degree()); 
			qi.coeffs.back() = r.coeffs.back()/g.coeffs.back();
			q += qi;
			r -= g * qi;
		}
		return q;
	}

	// Returns r(x) s.t f(x) = g(x) * q(x) + r(x);
	Polynomial operator % (const Polynomial& g) const {
		Polynomial q, r = *this;
		while(r != 0 && r.degree() >= g.degree()){
			Polynomial qi; qi.set_degree(r.degree() - g.degree()); 
			qi.coeffs.back() = r.coeffs.back()/g.coeffs.back();
			q += qi;
			r -= g * qi;
		}
		return r;
	}

	Polynomial& operator += (const Polynomial& g) {return *this = *this + g;}
	Polynomial& operator -= (const Polynomial& g) {return *this = *this - g;}
	Polynomial& operator *= (const Polynomial& g) {return *this = *this * g;}
	Polynomial& operator /= (const Polynomial& g) {return *this = *this / g;}
	Polynomial& operator %= (const Polynomial& g) {return *this = *this % g;}
	bool operator == (const int& b) {return (degree() == 0 && coeffs[0] == b);}
	bool operator != (const int& b) {return !(*this == b);}

	// Overloading the << operator to print a polynomial;
	friend std::ostream& operator << (std::ostream& out, const Polynomial& p){
		int last = p.degree();
		for(int i = 0; last == p.degree() && i <= p.degree(); i++)
			if(p.coeff(i) != 0)
				last = i; 
		
		for(int i = p.degree(); i >= last; i--){
			if(i == 0 || p.coeff(i) != 0){
				if(i == 0 || p.coeff(i) != 1) out << p.coeff(i);
				if(i > 1) out << "x^" << i ;
				else if(i == 1) out << "x";
				if(i != last) out << " + ";
			}
		}
		return out;
	}
};

// Returns (x, y, gcd(x, y)) that satisfies ax + by = gcd(a, b)
template<typename T>
std::tuple<T, T, T> extended_euclidean_algo(T a, T b){
	// Initialize the transformation matrix
	T x = 1, y = 0, u = 0, v = 1;

	// Extended Eucledian algorithm
	T r, q, x_, y_;
	while(b != 0){
		r = a%b; q = a/b;

		x_ = x; x = u; u = x_ - q * u;
		y_ = y; y = v; v = y_ - q * v;

		a = b; b = r;
	}
	auto leading_coeff = a.coeff(a.degree());
	return {x/leading_coeff, y/leading_coeff, a/leading_coeff};
}

int main(){
	int p = 5;
	Zn::set_N(p);
		
	Polynomial<Zn> f({-1, 0, 0, 0, 0, 1}), g({-3, 1});

	std::cout << "f(x) = " << f << " , g(x) = " << g << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	// Part 1
	std::cout << "f(x) + g(x) = " << f + g << std::endl;
	std::cout << std::endl;

	// Part 2
	std::cout << "f(x) * g(x) = " << f * g << std::endl;
	std::cout << std::endl;

	// Part 3
	auto q = f/g, r = f%g;
	std::cout << "q(x) = f(x) / g(x) = " << q << std::endl;
	std::cout << "r(x) = f(x) % g(x) = " << r << std::endl;
	std::cout << "q(x) * g(x) + r(x) = " << q * g + r << " = f(x)" << std::endl;
	std::cout << std::endl;

	// Part 4 and 5
	auto [u, v, gcd] = extended_euclidean_algo(f, g);

	// Part 4
	std::cout << "gcd(f(x), g(x)) = " << gcd << std::endl;
	std::cout << "f(x) % gcd = " << f % gcd << std::endl;
	std::cout << "g(x) % gcd = " << g % gcd << std::endl;
	std::cout << std::endl;

	// Part 5
	std::cout << "f(x)u(x) + g(x)v(x) = " << '(' << f << ") * (" << u << ") + (" << g << ") * (" << v << ") = " << f*u + g*v << " = gcd" << std::endl;
	std::cout << std::endl;

	return 0;
}