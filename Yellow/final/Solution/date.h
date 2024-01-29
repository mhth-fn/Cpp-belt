#pragma once
#include <iomanip>
#include <sstream>
#include <tuple>
#include <ostream>

class Date{
public:
	Date(int year, int month, int day) 
		: year_(year),
		month_(month),
		day_(day) {}
	
	int GetDay() const;
	int GetMonth() const;
	int GetYear() const;
	
	std::string GetDate() const;
private:
	const int year_ = 0, month_ = 0, day_ = 0;
};

bool operator<(const Date& lhs, const Date& rhs);

bool operator>(const Date& lhs, const Date& rhs);

bool operator==(const Date& lhs, const Date& rhs);

bool operator<=(const Date& lhs, const Date& rhs);

bool operator>=(const Date& lhs, const Date& rhs);

bool operator!=(const Date& lhs, const Date& rhs);


std::ostream& operator<<(std::ostream& os, const Date& date);

Date ParseDate(std::istream& is);
