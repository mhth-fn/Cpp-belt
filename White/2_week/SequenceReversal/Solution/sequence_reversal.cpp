#include <algorithm>
#include <vector>

void Reverse(std::vector<int>& numbers){
	for (std::size_t i = 0; i != numbers.size() / 2; ++i){
		int& lhs = numbers[numbers.size() - 1 - i];
		int& rhs =  numbers[i];
		std::swap(lhs, rhs);
	}
}
