#include <iostream>
#include <string>
#include <set>

int main(){
	std::set<std::string> unique;

	int q;
	std::cin >> q;
	for (int i = 0; i != q; ++i){
		std::string str;
		std::cin >> str;
		unique.insert(str);
	}

	std::cout << unique.size() << '\n';
	return 0;
}
