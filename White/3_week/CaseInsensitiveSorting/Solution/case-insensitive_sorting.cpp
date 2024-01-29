#include <algorithm>
#include <iostream>
#include <cctype>
#include <string>
#include <vector>

int main(){
	int q;
	std::cin >> q;

	std::vector<std::string> str(q);
	for (auto& i : str){
		std::cin >> i;
	}

	std::sort(str.begin(), str.end(), [](std::string l, std::string r){
			int lenght = std::min(l.size(), r.size());
			for (int i = 0; i != lenght; ++i){
				if (tolower(l[i]) != tolower(r[i])){
					return tolower(l[i]) <= tolower(r[i]);
				}
			}
			return false;
			});

	for (const auto& i : str){
		std::cout << i << ' ';
	}
	std::cout << '\n';

	return 0;
}
