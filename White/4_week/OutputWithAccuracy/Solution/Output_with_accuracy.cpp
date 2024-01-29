#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

int main(){
	std::ifstream input("input.txt");
	double number;

	if (input){
		std::cout << std::fixed << std::setprecision(3);
		while (input >> number){
			std::cout << number << '\n';
		}
	}

	return 0;
}
