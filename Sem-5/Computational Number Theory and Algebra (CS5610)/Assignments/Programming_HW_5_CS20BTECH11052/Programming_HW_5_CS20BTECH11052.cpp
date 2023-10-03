#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cassert>

#include <gmpxx.h>
using BigInt = mpz_class;
using ll = long long;

// Zn and Polynomial class from programming assignment 3

// Class to perform operations in Zn = {0...(N-1)}
struct Zn{
	static int N;
	ll val; 

	// Constructors to allow impilicit type conversions
	Zn(const int& z = 0) {if(N == -1) val = z; else val = z%N;}
	static void set_N(int _N){N = _N;}

	// Overloaded operators to perform arithematic in Zn
	int mod(ll a, int b) {return (a%b + b)%b;}
	Zn& operator += (const Zn& b) {val += b.val; val = mod(val, N); return *this;}
	Zn& operator -= (const Zn& b) {val -= b.val; val = mod(val, N); return *this;}
	Zn& operator *= (const Zn& b) {val *= b.val; val = mod(val, N); return *this;}
	Zn& operator /= (const Zn& b) {return *this *= b.inverse();}
	Zn operator + (const Zn& b) const {Zn lhs(*this); return lhs += b;}
	Zn operator - (const Zn& b) const {Zn lhs(*this); return lhs -= b;}
	Zn operator * (const Zn& b) const {Zn lhs(*this); return lhs *= b;}
	Zn operator / (const Zn& b) const {Zn lhs(*this); return lhs /= b;}

	// Performs binary exponentiation in Zn
	Zn pow(const int& k) const {
		if(k == 0) return 1;
		Zn p = pow(k/2);
		return (k % 2) ? p * p * val : p * p;
	}

	// Returns inverse of x in Zn using Fermat's little theorem. Assumes that n is prime.
	Zn inverse() const {
		return this->pow(N-2);
	}

	bool operator == (const Zn& b) const {return val == b.val;}
	bool operator != (const Zn& b) const {return val != b.val;}
	friend std::istream& operator >> (std::istream& in, Zn& z) {return in >> z.val;}
	friend std::ostream& operator << (std::ostream& out, const Zn& z){return out << z.val;}
};
int Zn::N = -1;
BigInt power(int _a, int b){
	BigInt res = 1, a = _a;
	while(b){
		if(b%2) res *= a;
		a *= a;
		b /= 2;
	}
	return res;
}

template<typename T = Zn>
class Polynomial{
private:
	std::vector<T> coeffs;

public:
	int degree() const {return coeffs.size() - 1;} // Returns the degree of the polynomial
	void set_degree(int d) {d = std::max(0, d); coeffs = std::vector<T>(d+1, 0);}
	Polynomial& reduce() {while(coeffs.size() > 1 && coeffs.back() == 0) coeffs.pop_back(); return *this;} // Removes leading 0 coefficients
	const T coeff(int i) const {if(i > degree()) return 0; return coeffs[i];} // Get the coeeficient of x^i in the polynomial

	Polynomial(int c = 0){coeffs.push_back(c);}
	Polynomial(Zn c){coeffs.push_back(c);}
	Polynomial(std::vector<T> _coeffs): coeffs(_coeffs) {reduce();}

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
	bool operator == (const Polynomial& b) {return coeffs == b.coeffs;}
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


// New functions for programming assignment 5
public:
	// Utility function to find the derivative of a polynomial
	Polynomial derivative() const {
		Polynomial result; result.set_degree(degree() - 1);
		for(int i = 1; i <= degree(); i++)
			result.coeffs[i - 1] = Zn(i) * coeff(i);
		return result;
	}

	static Polynomial getRandomPolynomial(int degree){
		Polynomial result; result.set_degree(degree);
		std::generate(result.coeffs.begin(), result.coeffs.end()-1, rand);
		result.coeffs.back() = 1;
		return result;
	}

	// Utility function to find the gcd of two polynomials
	static Polynomial gcd(Polynomial a, Polynomial b){
		while(b != 0){
			Polynomial r = a % b;
			a = b;
			b = r;
		}
		return a/a.coeff(a.degree());
	}

	// Utility function to find g(x)^k modulo f(x)
	static Polynomial mod_pow(Polynomial g, BigInt k, Polynomial f){
		if(k == 0) return Polynomial(1);
		return (k % 2 == 0) ? mod_pow(g * g % f, k / 2, f) : g * mod_pow(g, k - 1, f) % f;
	}

	// Utility function to print the coefficients of the polynomial
	void printCoeffs(std::string separator = " ") const {
		for(int i = degree(); i >= 0; i--)
			std::cout << coeff(i) << (separator+"\n")[i == 0];
	}

public:
	/***********************************************
	 *  		Cantor-Zassenhaus algorithm		   *
	 ***********************************************/

	/**
	 * @brief Returns a polynomial g such that each irreducible factor of f occurs only once in g.
	 * @return Polynomial 
	 */
	Polynomial getSquareFreePart() const {
		Polynomial g = *this, f = *this, F = *this, h; int p = Zn::N;
		while(g != 0)
			h = g,
			g = g.derivative();
		F = F/h;

		if(h.degree() == 0) 
			return f/gcd(f, f.derivative());
		
		// Divide each power of x in h by p;
		std::vector<T> coeffs_h(h.degree() + 1);
		for(int i = 0; i <= h.degree(); i++) if(h.coeff(i) != 0) {
			if(i % p == 0) coeffs_h[i/p] = h.coeff(i);
			else throw std::runtime_error("h(x) should have all coefficients divisible by p"); 
		}
		h = Polynomial(coeffs_h);
		h = h.getSquareFreePart();

		return h * F.getSquareFreePart();
	};

	/**
	 * @brief Partitions the square free part of f into factors fi(x), where fi(x) is the product of all monic irreducible factors of g(x) that have degree equal to i. 
	 * 
	 * Finds f1(x),f2(x),... where fi(x) is the product of monic irreducible factors of f(x) of degree i in Zp[x].
	 * 
	 * @return std::vector<Polynomial> 
	 */
	std::vector<Polynomial> distinctDegreeFactorization() const {
		// Assumes that f is square free
		Polynomial f = *this, g = f, x = Polynomial({0, 1}); int p = Zn::N;

		std::vector<Polynomial> factors;
	 	for(int i = 1; g != 1; i++){
			factors.push_back(gcd(g, mod_pow(x, power(p, i), g) - x));
			g = g/factors.back();
		}

		return factors;
	};

	/**
	 * @brief Get the Irreducible Factors of degree i from fi(x)
	 * 
	 * @param degree 
	 * @return std::vector<Polynomial> 
	 */
	std::vector<Polynomial> getIrreducibleFactors(int i) const {
		// Assumes that f(x) is square-free and has only irreducible factors of degree i
		Polynomial f = *this; int p = Zn::N;
		if(f == 1) return {};
		if(f.degree() == i) return {f};
		
		Polynomial h1 = 1, h2 = 1;
		while(h1 == 1 or h2 == 1){
			Polynomial g = getRandomPolynomial(f.degree()-1);
			h1 = gcd(f, mod_pow(g, (power(p, i)-1)/2, f) - 1);
			h2 = f/h1;
		}
		auto factors_h1 = h1.getIrreducibleFactors(i), factors_h2 = h2.getIrreducibleFactors(i);
		factors_h1.insert(factors_h1.end(), factors_h2.begin(), factors_h2.end());

		return factors_h1;
	};

public:
	/**
	 * @brief Returns all irreducible factors of f(x)
	 * 
	 * @return std::vector<Polynomial> 
	 */
	std::vector<Polynomial> getIrreducibleFactors() const {
		assert(Zn::N != 2 && "For p = 2, in phase 3, we must use h1 = gcd(f, x + x^2 + x^4 + ... + x^(2^i - 1)) instead of h1 = gcd(f, g ^ ((p^i - 1)/2)) - 1), which isnt supported");
		std::vector<Polynomial> factors;
		Polynomial g = getSquareFreePart();
		auto prod_irreducibles = g.distinctDegreeFactorization();
		for(int i = 0; i < prod_irreducibles.size(); i++){
			auto irreducible_factors = prod_irreducibles[i].getIrreducibleFactors(i+1);
			factors.insert(factors.end(), irreducible_factors.begin(), irreducible_factors.end());
		}
		return factors;
	}

	/**
	 * @brief Return the irreducible factors along with their multiplicity
	 * 
	 * @return std::vector<std::pair<Polynomial, int>> 
	 */
	std::vector<std::pair<Polynomial, int>> getFactorization() const {
		Polynomial f = *this;
		auto factors = getIrreducibleFactors();
		std::vector<std::pair<Polynomial, int>> factorization;
		for(auto& factor: factors){
			int multiplicity = 0;
			while(f % factor == 0)
				f /= factor, multiplicity++;
			factorization.push_back({factor, multiplicity});
		}
		return factorization;
	}
};

template<typename T = Zn>
void read_input(std::string& csv_row, int& d, int& i, Polynomial<T>& f){
	std::stringstream ss(csv_row);

	ss >> d, ss.ignore(); 
	ss >> i, ss.ignore();

	std::vector<T> coeffs(d+1);
	for(int j = 0; j <= d; j++)
		ss >> coeffs[j], ss.ignore();

	std::reverse(coeffs.begin(), coeffs.end());
	f = Polynomial<T>(coeffs);
}

int main(){
	std::string input_file = "input-CZ.csv";
	std::ifstream input(input_file);

	int p;
	input >> p;
	Zn::set_N(p);

	std::string testcase;
	while(input >> testcase){
		int d, i;
		Polynomial<Zn> f;
		read_input(testcase, d, i, f);

		/* Below commented code works for our problem statement, however the next implementation is more general */
		// for(auto& factor: f.getSquareFreePart().getIrreducibleFactors(i))
		// 	factor.printCoeffs(",");
		// std::cout << std::endl;

		for(auto& [factor, multiplicity]: f.getFactorization())
			factor.printCoeffs(",");
		std::cout << std::endl;
	}

	return 0;
}