#include <iostream>
#include <cmath>

int main(){
	double a, b, c;
	std::cin >> a >> b >> c;

	if (a == 0){
		if (b == 0){
			std::cout << " " << '\n';
		} else{
			std::cout << - c / b << '\n';
		}
	} else {
		double D = b * b - 4 * a * c;
		if (D > 0){
			std::cout << (-b + sqrt(D)) / (2 * a) << " " << (-b - sqrt(D)) / (2 * a) << '\n';
		} else if (D < 0){
			std::cout << " " << '\n';
		} else {
			std::cout << -b / (2 * a) << '\n';
		}
	}

  return 0;
}
