#include <iostream>
#include <vector>

int main(){
	int n;
	std::cin >> n ;
	
	if (n == 0){
		return 0;
	}

	std::vector<int> days_temp(n);
	
	int avg = 0;
	for (int i = 0; i != n; ++i){
		std::cin >> days_temp[i];
		avg += days_temp[i];
	}
	avg /= n;	

	std::vector<int> indexs;
	for (int i = 0; i != n; ++i){
		if (days_temp[i] > avg){
			indexs.push_back(i);
		}
	}
	
	std::cout << indexs.size() << '\n';
	for (const int& i : indexs){
		std::cout << i << ' ';
	}

	return 0;
}
