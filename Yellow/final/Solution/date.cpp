#include "date.h"

int Date::GetDay() const{
	return day_;
}

int Date::GetMonth() const{
	return month_;
}

int Date::GetYear() const{
	return year_;
}

bool operator<(const Date& lhs, const Date& rhs){
	return std::make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) 
		< std::make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}
bool operator>(const Date& lhs, const Date& rhs){
	return std::make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) 
		> std::make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}
bool operator==(const Date& lhs, const Date& rhs){
	return std::make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) 
		== std::make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator<=(const Date& lhs, const Date& rhs){
	return std::make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) 
		<= std::make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}
bool operator>=(const Date& lhs, const Date& rhs){
	return std::make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) 
		>= std::make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}
bool operator!=(const Date& lhs, const Date& rhs){
	return std::make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) 
		!= std::make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

std::string Date::GetDate() const {
 	std::stringstream os;
	os << std::setfill('0') << std::setw(4);	
	os << year_ << "-" << 
	 std::setw(2) << month_ << "-" << std::setw(2) << day_; 
	return os.str();
}

std::ostream& operator<<(std::ostream& os, const Date& date){
	os << date.GetDate();
	return os;
}

Date ParseDate(std::istream& is){
	int year, month, day;
	is >> year;
	is.get();
	is >> month;
	is.get();
	is >> day;

	return Date(year, month, day);
}

