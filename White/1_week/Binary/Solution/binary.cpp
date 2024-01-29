#include <iostream>
#include <vector>
int main(){
	int n;
	std::cin >> n;

	std::vector<int> binary;
	while (n != 0){
		if (n % 2 == 0){
			binary.push_back(0);
		} else {
			binary.push_back(1);
		}	
		n /= 2;
	}
	
	for (int i = binary.size() - 1; i > -1; --i){
		std::cout << binary[i];
	}

	return 0;
}
