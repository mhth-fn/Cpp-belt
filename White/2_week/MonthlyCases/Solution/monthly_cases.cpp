#include <iostream> 
#include <string> 
#include <vector> 

std::vector<int> days = {31, 28, 31, 30, 31, 30,
							 31, 31, 30, 31, 30, 31};

int main(){	
	int m = 0; //Текущий месяц
	std::vector<std::vector<std::string>> diary(days[m]); 

	int q;
	std::cin >> q;
	for (int i = 0; i != q; ++i){
		std::string command;
		std::cin >> command;

		if (command == "NEXT"){
			int	current = m % 12,
				next = (m + 1) % 12;
		
			if (days[current] > days[next]){
				for (int j = days[current]; j != days[next]; --j){
					diary[days[next] - 1].insert(end(diary[days[next] - 1]),
												 begin(diary[j - 1]),
												 end(diary[j - 1]));
				}
			}

			diary.resize(days[next]);
			++m;
		} else if (command == "ADD"){
			int k;
			std::string str;
			std::cin >> k >> str;

			diary[k - 1].push_back(str);
		} else if (command == "DUMP"){
			int k;
			std::cin >> k;
			
			std::cout << diary[k - 1].size() << ' ';
			for (const auto& str : diary[k - 1]){
				std::cout << str << ' ';
			}
			std::cout << '\n';
		}
	}
}
