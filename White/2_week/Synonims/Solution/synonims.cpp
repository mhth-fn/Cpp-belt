#include <iostream>
#include <string>
#include <map>
#include <set>

int main(){
	std::map<std::string, std::set<std::string>> synonims;

	int q;
	std::cin >> q;
	for (int i = 0; i != q; ++i){
		std::string command;
		std::cin >> command;

		if (command == "ADD"){
			std::string word1, word2;
			std::cin >> word1 >> word2;
			
			synonims[word1].insert(word2);
			synonims[word2].insert(word1);
		} else if (command == "COUNT"){
			std::string word;
			std::cin >> word;

			std::cout << synonims[word].size() << '\n';
		} else if (command == "CHECK"){
			std::string word1, word2;
			std::cin >> word1 >> word2;
			
			if (synonims[word1].count(word2) != 0){
				std::cout << "YES\n";
			} else {
				std::cout << "NO\n";
			}
		}
	}
}
