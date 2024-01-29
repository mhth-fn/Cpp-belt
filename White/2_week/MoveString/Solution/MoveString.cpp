#include <string>
#include <vector>

using Words = std::vector<std::string>;
void MoveStrings(Words& source,
				 Words& destination){
	for (const auto& str : source){
		destination.push_back(str);
	}
	source.clear();
}
