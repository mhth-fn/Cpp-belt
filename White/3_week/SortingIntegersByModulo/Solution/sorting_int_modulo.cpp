#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

int main(){
	int q;
	std::cin >> q;

	std::vector<int> numbers(q);
	for (int& i : numbers){
		std::cin >> i;
	}

	std::sort(numbers.begin(), numbers.end(), [](int x, int y){
			if (abs(x) > abs(y)){
				return false;
			} else {
				return true;
			}
			});

	for (int& i : numbers){
		std::cout << i << " ";
	}	
	std::cout << '\n';

	return 0;
}
