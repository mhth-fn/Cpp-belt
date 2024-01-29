#include <iostream>
#include <string>

int main(){
	char ch = 'f';
	std::string str;
	std::cin >> str;
	
	int count = 0;
	int i = 0;
	for (const auto& c : str){
		if (c == ch){
			++count;
		}
		if (count == 2){
			break;
		}
		++i;
	}
	 if (count == 0){
		 std::cout << "-2\n";
	 } else if (count == 1){
		 std::cout << "-1\n";
	 } else{
		 std::cout << i << '\n';
	 }
}
