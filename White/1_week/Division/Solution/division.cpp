#include <iostream>

int main(){
	int a, b;
	std::cin >> a >> b;

	if (b == 0){
		std::cout << "Impossible\n";
	} else {
		std::cout << a / b << '\n';
	}
	return 0;
}
