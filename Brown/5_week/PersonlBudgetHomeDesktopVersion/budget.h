#include <algorithm>
#include <ctime>
#include <iostream>
#include <optional>
#include <numeric>
#include <stdint.h>
#include <string>
#include <vector>
#include <utility>


std::pair<std::string, std::string> 
    SplitTwoStrict(std::string s, std::string delimiter);
std::string ReadToken(std::string& token);

class Date{
public:
    Date(int year, int month, int day) :
    year_(year), month_(month), day_(day){}

    static Date FromString(std::string date){
    //2000-01-01
        int year = stoi(ReadToken(date));
        int month = stoi(ReadToken(date));
        int day = stoi(ReadToken(date));
        return {year, month, day};
    }

    time_t AsTimestamp() const;
    bool operator==(const Date& other) const{
        return year_ == other.year_
        && month_ == other.month_
        && day_ == other.day_;
    }
    friend std::ostream& operator<<(std::ostream& out, const Date& date){
        out << date.year_ << "-" << date.month_ << date.day_;
        return out;
    }
private:
    int year_, month_, day_;
};

int ComputeDaysDiff(const Date& date_to, const Date& date_from);


class Budget{
public:
    Budget();
    void Earn(const Date& from, const Date& to, int value);
    double ComputeIncome(const Date& from, const Date& to) const;
    void PayTax(const Date& from, const Date& to);
private:
    std::vector<double> budget_;
};

