#include <iostream>

int main(){
	int a, b;
	std::cin >> a >> b;

	if (a % 2 != 0){
		++a;
	}
	while (a <= b){
		std::cout << a << ' ';
		a += 2;
	}
	std::cout << '\n';

	return 0;
}
