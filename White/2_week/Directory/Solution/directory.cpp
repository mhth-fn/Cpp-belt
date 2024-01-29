#include <iostream> 
#include <string>
#include <map>

int main(){
	std::map<std::string, std::string> country_to_capital;

	int q;
	std::cin >> q;
	for (int i = 0; i != q; ++i){
		std::string command;
		std::cin >> command;

		if (command == "CHANGE_CAPITAL"){
			std::string country, capital;
			std::cin >> country >> capital;
			
			if (country_to_capital.count(country)){
				if (country_to_capital.at(country) == capital){
					std::cout << "Country " << country << " hasn't changed its capital\n";
				} else{
					std::cout << "Country " << country << " has changed its capital from "
							  << country_to_capital.at(country) << " to " << capital << '\n';
					country_to_capital[country] = capital;
				}
			} else {
				country_to_capital[country] = capital;
				std::cout << "Introduce new country " << country << " with capital " << capital << '\n';
			}	
		} else if (command == "RENAME"){
			std::string old_country, new_country;
			std::cin >> old_country >> new_country;

			if (old_country == new_country || !country_to_capital.count(old_country)
					|| country_to_capital.count(new_country)){
				std::cout << "Incorrect rename, skip\n";
			} else{
				std::cout << "Country " << old_country << " with capital " << country_to_capital[old_country]
					<< " has been renamed to " << new_country << '\n'; 
				country_to_capital[new_country] = country_to_capital[old_country];
				country_to_capital.erase(old_country);
			}
	
		} else if (command == "ABOUT"){
			std::string country;
			std::cin >> country;

			if (country_to_capital.count(country)){
				std::cout << "Country " << country << " has capital " << country_to_capital[country] << '\n';
			} else {
				std::cout << "Country " << country << " doesn't exist\n";
			}
		} else if (command == "DUMP"){
			if (country_to_capital.size() == 0){
				std::cout << "There are no countries in the world\n";
			} else {
				for (const auto& [key, value] : country_to_capital){
					std::cout << key << "/" << value << ' ';
				}
			}

		}
	}

	return 0;
}
