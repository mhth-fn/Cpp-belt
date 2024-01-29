#include <iostream>
#include <string>
#include <vector>
#include <map>

int main(){
	std::map<std::vector<std::string>, int> stops_for_bus;
	
	std::vector<std::string> buf;
	int q, buses_number = 0;
	std::cin >> q;
	for (int i = 0; i != q; ++i){
		int count;
		std::cin >> count;

		for (int j = 0; j != count; ++j){
			std::string stop;
			std::cin >> stop;
			buf.push_back(stop);
		}
		if (stops_for_bus.count(buf) == 0){
			stops_for_bus[buf] = ++buses_number;
			std::cout << "New bus " << buses_number << '\n';
		} else {
			std::cout << "Already exists for " << stops_for_bus.at(buf) << '\n';
		}
		buf.clear();

	}
}

