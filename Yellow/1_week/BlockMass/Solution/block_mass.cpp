#include <iostream>

int main(){
	uint64_t mass = 0;
	size_t N, p;
	std::cin >> N >> p;
	for (size_t i = 0; i != N; ++i){
		int a, b, c;
		std::cin >> a >> b >> c;

		mass += (static_cast<uint64_t>(a) * b * c) * p;
	}
	std::cout << mass;
	return 0;
}
