#include <string>
#include <map>
#include <set>

std::set<std::string> BuildMapValuesSet(const std::map<int, std::string>& m) {
	std::set<std::string> res;
	for (const auto [key, value] : m){
		res.insert(value);
	}
	return res;
}


