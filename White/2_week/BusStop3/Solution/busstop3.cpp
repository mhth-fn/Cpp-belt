#include <iostream>
#include <string>
#include <map>
#include <set>

int main(){
	std::map<std::set<std::string>, int> buses;
	
	
	int q;
	std::cin >> q;
	for (int i = 0; i != q; ++i){
		int count;
		std::cin >> count;
		
		std::set<std::string> stops;
		for (int j = 0; j != count; ++j){
			std::string stop;
			std::cin >> stop;

			stops.insert(stop);
		}

		if (buses.count(stops) == 0){
			int bus = buses.size() + 1;
			buses[stops] = bus;
			std::cout << "New bus " << bus << '\n';
		} else {
			std::cout << "Already exists for " << buses.at(stops) << '\n';
		}
	}
	
	return 0;
}
