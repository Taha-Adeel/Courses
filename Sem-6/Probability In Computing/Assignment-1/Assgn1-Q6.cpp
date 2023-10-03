#include <iostream>

int main(){
	int n;
	std::cout << "Enter the number of times you want to flip the coin: ";
	std::cin >> n;

	for(int r = 1; r <= n; r++){
		int expected_value = 0;

		for(int i = 0; i < (1<<n); i++){
			int num_heads = 0, j = 0;
			for(j = 0; j < r; j++)
				num_heads += !!(i & (1 << j));
			if(num_heads == r) expected_value++;

			for(; j < n; j++){
				num_heads -= !!(i & (1 << (j-r)));
				num_heads += !!(i & (1 << j));
				if(num_heads == r) expected_value++;
			}
		}

		std::cout << "The expected number of sequences of " << r << " consecutive heads is: " 
			<< expected_value  << "/" << (1<<n) << " = " << double(expected_value)/(1<<n) << std::endl;
	}

	return 0;
}