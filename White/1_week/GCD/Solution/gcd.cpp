#include <iostream>

int main(){
	int a, b;
	std::cin >> a >> b;

	if (b > a){
		int buf = b;
		b = a;
		a = buf;
	}
	
	while (a % b != 0){
		a -= b;
		if (b > a){
			int buf = b;
			b = a;
			a = buf;
		}
	}
	
	std::cout << b << '\n';
	return 0;;
}
