#include <iostream>
#include <deque>
#include <ostream>
#include <string>


int main(){
	int x;
	size_t N;

	std::cin >> x >> N;
	
	std::deque<std::string> expression = {std::to_string(x)};
	for (size_t i = 0; i != N; ++i){
		std::string operation;
		int number;
		std::cin >> operation >> number;
		expression.push_front("(");
		expression.push_back(") " + operation +  " " + std::to_string(number));
	}
	for (const auto& str : expression){
		std::cout << str;
	}

	return 0;
}
