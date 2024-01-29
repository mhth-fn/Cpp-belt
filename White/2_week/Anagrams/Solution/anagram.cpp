#include <iostream>
#include <string>
#include <map>

std::map<char, int> BuildCharCounter(const std::string& str){
	std::map<char, int> result;
	for (const char& c : str){
		++result[c];
	}
	return result;
}

int main(){
	int n;
	std::cin >> n;
	for (int i = 0; i != n; ++i){
		std::string first, second;
		std::cin >> first >> second;

		if (BuildCharCounter(first) == BuildCharCounter(second)){
			std::cout << "YES\n";
		} else {
			std::cout << "NO\n";
		}	
	}
	 
	return 0;
}
