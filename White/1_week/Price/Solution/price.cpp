#include <iostream>

int main(){
	double n, a, b,
    x, y;
	std::cin >> n >> a >> b 
		>> x >> y;
	
	if (n > a){
		if (n > b){
			n -= (n * y / 100);
		} else {
			n -= (n * x / 100);
		}
	}

	std::cout << n << '\n';
	return 0;
}
