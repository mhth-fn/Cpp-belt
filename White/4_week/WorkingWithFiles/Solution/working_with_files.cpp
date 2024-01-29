#include <iostream>
#include <fstream>
#include <string>

int main(){
	std::ifstream input("input.txt");
	std::string line;
	
	if (input){
		while (getline(input, line)){
			std::cout << line << '\n';
		}
	}

	return 0;
}
