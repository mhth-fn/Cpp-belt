#include <iostream>
#include <string>
#include <vector>
#include <map>

int main(){
	std::map<std::string, std::vector<std::string>> buses_for_stop;
	std::map<std::string, std::vector<std::string>> stops_for_bus;

	int q;
	std::cin >> q;
	for (int i = 0; i != q; ++i){
		std::string command;
		std::cin >> command;

		if (command == "NEW_BUS"){
			int stop_count;
			std::string bus, stop;
			std::cin >> bus >> stop_count;

			for (int j = 0; j != stop_count; ++j){
				std::cin >> stop; 

				stops_for_bus[bus].push_back(stop);
				buses_for_stop[stop].push_back(bus);
			}
		} else if (command == "BUSES_FOR_STOP"){
			std::string stop;
			std::cin >> stop;
			
			if (!buses_for_stop[stop].empty()){
				for (const auto& bus : buses_for_stop[stop]){
					std::cout << bus << " ";
				}
			}else {
				std::cout << "No stop";
			}
			std::cout << '\n';
		} else if (command == "STOPS_FOR_BUS"){
			std::string bus;
			std::cin >> bus;

			if (stops_for_bus.count(bus) == 0){
				std::cout << "No bus\n";
			} else {
				for (const auto& stop : stops_for_bus[bus]){
					std::cout << "Stop " << stop << ": ";
					if (buses_for_stop[stop].size() == 1){
						std::cout << " no interchange\n";
					} else {
						for (const auto& sbus : buses_for_stop[stop]){
							if (sbus != bus){
								std::cout << sbus << " ";
							}
						}					
						std::cout << '\n';
					}
				}
			}
		} else if (command == "ALL_BUSES"){
			if (stops_for_bus.empty()){
				std::cout << "No buses\n";
			} else {
				for (const auto& [bus, stops] : stops_for_bus){
					std::cout << "Bus " << bus << ": ";
					for (const auto& stop : stops){
						std::cout << stop << ' ';
					}
					std::cout << '\n';
				}
			}
		}
	}
	return 0;
}
