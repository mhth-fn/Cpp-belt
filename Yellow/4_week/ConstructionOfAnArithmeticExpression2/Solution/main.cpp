#include <iostream>
#include <deque>
#include <ostream>
#include <string>


int main(){
	int x;
	size_t N;

	std::cin >> x >> N;
	
	std::deque<std::string> expression = {std::to_string(x)};
	bool first = true;
	std::string operation, last_operation;
	for (size_t i = 0; i != N; ++i){
		int number;
		std::cin >> operation >> number;
		if (!first){
			if ((operation == "*" || operation == "/") &&
					(last_operation == "+" || last_operation == "-")){
				expression.push_front("(");
				expression.push_back(")");
			}
		}
		first = false;
		expression.push_back(" " + operation +  " " + std::to_string(number));
		last_operation = operation;
	}
	for (const auto& str : expression){
		std::cout << str;
	}

	return 0;
}
