#include <iostream>
#include <string>

int main(){
	std::string first,
				second,
				third;
	std::cin >> first >> second >> third;

	if (first <= second && first <= third){
		std::cout << first << '\n';
	} else if (second <= third){
		std::cout << second << '\n';
	} else{
		std::cout << third << '\n';
	}
	return 0;
}
