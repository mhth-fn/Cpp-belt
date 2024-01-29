#include <iostream>
#include <string>
#include <vector>

int main(){
	std::vector<bool> queue;
	
	int Q, k;
	std::cin >> Q;
	std::string command;
	for (int i = 0; i != Q; ++i){
		std::cin >> command;
		if (command == "WORRY"){
			std::cin >> k;
			queue[k] = true;
		} else if (command == "QUIET"){
			std::cin >> k;
			queue[k] = false;
		} else if (command == "COME"){
			std::cin >> k;
			queue.resize(queue.size() + k, false);
		} else if (command == "WORRY_COUNT"){
			int count = 0;
			for (size_t j = 0; j != queue.size(); ++j){
				if (queue[j] == true){
					++count;
				}	
			}	
			std::cout << count << '\n';
		}
	}	
}
