#include <iostream>
#include <ostream>
#include <vector>
#include <string>
#include <numeric>
#include <iterator>

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
		for (size_t i = 1700; i != _year; ++i){
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

class Budget{
public:
	Budget(){
		budget.resize(4 * 366000, 0);
	}
	void Earn(Date date, double value){
		budget[date.GetDays()] += value;	
	}
	void Partial_sim(){
		std::partial_sum(budget.begin(), budget.end(), budget.begin());
	}
	void ComputeIncome(Date from, Date to){
		size_t begin = from.GetDays(),
		end = to.GetDays();

		std::cout << 	budget[end] - budget[begin-1] << std::endl;
	}
private:
	std::vector<double> budget;
};

int main(){
	Budget personal;

	size_t Q;
	std::cin >> Q;
	for(size_t i = 0; i != Q; ++i){
		Date date;
		double value;
		std::cin >> date >> value;
		personal.Earn(date, value);		
	}
	std::cin >> Q;
	personal.Partial_sim();
	for(size_t i = 0; i != Q; ++i){
		Date from, to;
		std::cin >> from >> to;
		std::cout.precision(25);
		personal.ComputeIncome(from, to);
	}
	return 0;
}
