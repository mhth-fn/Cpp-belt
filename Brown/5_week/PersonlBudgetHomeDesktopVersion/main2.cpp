#include <iostream>
#include <numeric>
#include <string>
#include <vector>

bool IsLeap(size_t year){
	return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0); 
}

class Date{
public:
	
	size_t& NewYear(){
		return _year;
	}

	size_t& NewMonth(){
		return _month;
	}

	size_t& NewDay(){
		return _day;
	}

	size_t GetDays() const{
		size_t res = 0;
		for (size_t i = 2000; i != _year; ++i){
			if (IsLeap(i)){
				res += 366;
			} else {
				res += 365;
			}
		}	
		
		std::vector<size_t> days_in_month{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		if (IsLeap(_year)){
			++days_in_month[1];
		}
		for (size_t i = 1; i != _month; ++i){
			res += days_in_month[i - 1];
		}

		res += _day;
		
		return res;
	}
private:
	size_t _year, _month, _day;
};

class Budget{
public:
	Budget(){
		budget.resize(40000);
	}

	void Earn(const Date& from, const Date& to, const double& earn){
		size_t begin = from.GetDays(),
					 end = to.GetDays() + 1;

		double daily_earn = earn / (end - begin);
		
		for (size_t it = begin; it != end; ++it){
			budget[it] += daily_earn;
		}
	}

	double ComputeIncome(const Date& from, const Date& to) const{
		size_t begin = from.GetDays(),
	 				 end = to.GetDays() + 1;
		
		return std::accumulate(budget.begin() + begin, budget.begin() + end, 0.0);
	}

private:
	std::vector<double> budget;
};

std::istream& operator>>(std::istream& is, Date& date){
	size_t year, month, day;
	is >> year;
	is.get();
	is >> month;
	is.get();
	is >> day;
	
	date.NewYear() = year;
	date.NewMonth() = month;
	date.NewDay() = day;
	
	return is;
}

int main(){
	size_t Q = 0;
	std::cin >> Q;

	Budget personal;
	for (size_t i = 0; i != Q; ++i){
		std::string command;
		std::cin >> command;

		if (command == "Earn"){
			Date from, to;
			double earn;
			std::cout.precision(25);
			std::cin >> from >> to >> earn;

			personal.Earn(from, to, earn);			
		}else if (command == "ComputeIncome"){
			Date from, to;
			std::cin >> from >> to;
			
			std::cout.precision(25);
			std::cout << personal.ComputeIncome(from, to) << std::endl;
		}
	}

	return 0;
}
