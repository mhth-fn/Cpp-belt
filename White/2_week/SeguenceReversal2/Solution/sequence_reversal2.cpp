#include <algorithm>
#include <vector>

using Sequence = std::vector<int>;

void Reverse(Sequence& numbers){
	for (std::size_t i = 0; i != numbers.size() / 2; ++i){
		int& lhs = numbers[numbers.size() - 1 - i];
		int& rhs =  numbers[i];
		std::swap(lhs, rhs);
	}
}

Sequence Reversed(const Sequence& sequence){
	Sequence result = sequence;
	Reverse(result);
	return result;
}
