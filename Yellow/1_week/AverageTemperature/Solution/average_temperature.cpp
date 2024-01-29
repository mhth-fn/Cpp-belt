#include <iostream>
#include <vector>

int main(){
	size_t n;
	std::cin >> n;

	int64_t sum = 0;
	std::vector<int> temp(n);
	for (size_t i = 0; i != n; ++i){
		std::cin >> temp[i];
		sum += temp[i];
	}
	int avg = sum / static_cast<int64_t>(temp.size());
	
	size_t quantity = 0;
	for (const auto& daystemp : temp){
		if (daystemp > avg){
			++quantity;
		}
	}
	
	bool not_first = false;
	std::cout << quantity << '\n';
	for (size_t i = 0; i != temp.size(); ++i){
		if (temp[i] > avg){
			if (not_first){
				std::cout << ' ';
			}
			std::cout << i;
			not_first = true;
		}
	}
	std::cout << '\n';
	return 0;
}
