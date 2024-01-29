#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

struct Date{
	int day;
	int month;
	int year;
};

struct Student{
	std::string firstname;
	std::string lastname;
	Date date;
};

int main(){
	std::vector<Student> list;
	
	int N;
	std::cin >> N;
	for (int i = 0; i != N; ++i){
		std::string fn, ln;
		int day, month, year;
		std::cin >> fn >> ln >> day >> month >> year;
		list.push_back({fn, ln, {day, month, year}});
	}

	std::cin >> N;
	for (int i = 0; i != N; ++i){
		std::string command;
		int number;
		std::cin >> command >> number;
		--number;

		if (command == "name" && number >= 0 && number <= list.size()){
			std::cout << list[number].firstname << " " << list[number].lastname << '\n';
		} else if (command == "date" && number >= 0 && number <= list.size()){
			std::cout << list[number].date.day << '.'
				<< list[number].date.month << '.' << list[number].date.year << '\n';
		} else {
			std::cout << "bad request\n";
		}
	}
	
	return 0;
}
