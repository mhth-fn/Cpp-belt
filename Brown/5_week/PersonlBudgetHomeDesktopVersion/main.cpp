#include "test_runner.h"

#include <iomanip>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <optional>
#include <numeric>
#include <stdint.h>
#include <string>
#include <vector>
#include <utility>

using namespace std;

pair<string, string> SplitTwoStrict(string s, string delimiter) {
  const size_t pos = s.find(delimiter);
  if (pos == s.npos) {
    return {s, ""};
  } else {
    return {s.substr(0, pos), s.substr(pos + 1)};
  }
}

string ReadToken(string& token){
    auto [lhs, rhs] = SplitTwoStrict(token, "-");
    token = rhs;
    return lhs;
}

class Date{
public:
    Date(int year, int month, int day) :
    year_(year), month_(month), day_(day){}

    static Date FromString(std::string date){
        int year = stoi(ReadToken(date));
        int month = stoi(ReadToken(date));
        int day = stoi(ReadToken(date));
        return {year, month, day};
    }

    time_t AsTimestamp() const{
        std::tm t;
        t.tm_sec   = 0;
        t.tm_min   = 0;
        t.tm_hour  = 0;
        t.tm_mday  = day_;
        t.tm_mon   = month_ - 1;
        t.tm_year  = year_ - 1900;
        t.tm_isdst = 0;
        return mktime(&t);
    }
    
    bool operator==(const Date& other) const{
        return year_ == other.year_
        && month_ == other.month_
        && day_ == other.day_;
    }

    friend std::ostream& operator<<(std::ostream& out, const Date& date){
        out << date.year_ << "-" << date.month_ << "-" << date.day_;
        return out;
    }
private:
    const int year_, month_, day_;
};

int ComputeDaysDiff(const Date& date_from, const Date& date_to) {
    const time_t timestamp_from = date_from.AsTimestamp();
    const time_t timestamp_to = date_to.AsTimestamp();
    static const int SECONDS_IN_DAY = 60 * 60 * 24;
    return (timestamp_to - timestamp_from) / SECONDS_IN_DAY;
}

static const Date START_DATE = Date::FromString("2000-01-01");
static const Date END_DATE = Date::FromString("2100-02-01");
static const size_t DAY_COUNT = ComputeDaysDiff(START_DATE, END_DATE);

class Budget{
public:
    Budget(){
        budget_.resize(DAY_COUNT, 0);
    }

    void Earn(const Date& from, const Date& to, int value){
        if (from == to){
            budget_[ComputeDaysDiff(START_DATE, from)] += value;
        } else{
            int from_index = ComputeDaysDiff(START_DATE, from);
            int to_index = ComputeDaysDiff(START_DATE, to) + 1;
            double daily_value = (1.0 * value) / (to_index - from_index);
            while (from_index != to_index){
                budget_[from_index++] += daily_value;
            }
        }
    }

    double ComputeIncome(const Date& from, const Date& to) const{
        if (from == to){
            return budget_[ComputeDaysDiff(START_DATE, from)];
        } else {
            int from_index = ComputeDaysDiff(START_DATE, from);
            int to_index = ComputeDaysDiff(START_DATE, to) + 1;
            return std::accumulate(budget_.begin() + from_index, budget_.begin() + to_index, 0.0);
        } 
    }

    void PayTax(const Date& from, const Date& to){
        if (from == to){
            budget_[ComputeDaysDiff(START_DATE, from)] *= 0.87;
        } else{
            int from_index = ComputeDaysDiff(START_DATE, from);
            int to_index = ComputeDaysDiff(START_DATE, to) + 1;
            while (from_index != to_index){
                budget_[from_index++] *= 0.87;
            }
        }
    }

private:
    std::vector<double> budget_;
};

void TestEarn(){
    {//test a one day
        Budget test;
        test.Earn(Date::FromString("2000-01-01"), 
                  Date::FromString("2000-01-01"), 20);
        test.Earn(Date::FromString("2000-01-01"), 
                  Date::FromString("2000-01-01"), 20);
        test.Earn(Date::FromString("2000-01-01"), 
                  Date::FromString("2000-01-01"), 20);
        ASSERT_EQUAL(test.ComputeIncome(Date::FromString("2000-01-01"), 
                                        Date::FromString("2000-01-01")), 60);
    }
    {//test a few days with int daily_value
        Budget test;
        test.Earn(Date::FromString("2000-01-01"), 
                  Date::FromString("2000-01-02"), 20);
        test.Earn(Date::FromString("2000-01-01"), 
                  Date::FromString("2000-01-02"), 20);
        test.Earn(Date::FromString("2000-01-01"), 
                  Date::FromString("2000-01-02"), 20);
        ASSERT_EQUAL(test.ComputeIncome(Date::FromString("2000-01-01"), 
                                        Date::FromString("2000-01-01")), 30);
        ASSERT_EQUAL(test.ComputeIncome(Date::FromString("2000-01-02"), 
                                        Date::FromString("2000-01-02")), 30);
        ASSERT_EQUAL(test.ComputeIncome(Date::FromString("2000-01-01"), 
                                        Date::FromString("2000-01-02")), 60);
    }
    {//test a few days with int daily_value
        Budget test;
        test.Earn(Date::FromString("2000-01-01"), 
                  Date::FromString("2000-01-02"), 3);
        ASSERT_EQUAL(test.ComputeIncome(Date::FromString("2000-01-01"), 
                                        Date::FromString("2000-01-01")), 1.5);
        test.Earn(Date::FromString("2000-01-01"), 
                  Date::FromString("2000-01-02"), 3);
        test.Earn(Date::FromString("2000-01-01"), 
                  Date::FromString("2000-01-02"), 3);
        ASSERT_EQUAL(test.ComputeIncome(Date::FromString("2000-01-01"), 
                                        Date::FromString("2000-01-01")), 4.5);
        ASSERT_EQUAL(test.ComputeIncome(Date::FromString("2000-01-02"), 
                                        Date::FromString("2000-01-02")), 4.5);
        ASSERT_EQUAL(test.ComputeIncome(Date::FromString("2000-01-01"), 
                                        Date::FromString("2000-01-02")), 9);
    }
}
void TestAll(){
    TestRunner tr; 
    RUN_TEST(tr, TestEarn);
   // TestComputeIncome();
   // TestPayTax();
}
int main(){
    TestAll();
    std::cout.precision(25);

    int query;
    cin >> query;

    Budget personal;
    for (int i = 0; i != query; ++i){
        string command, date_from, date_to;
        cin >> command >> date_from >> date_to;
        if (command == "Earn"){
            int value;
            cin >> value;
            personal.Earn(Date::FromString(date_from), 
                                Date::FromString(date_to), value);
        } else if (command == "ComputeIncome"){
            cout << personal.ComputeIncome(Date::FromString(date_from), 
                                                Date::FromString(date_to)) << endl;
        } else if (command == "PayTax"){
            personal.PayTax(Date::FromString(date_from),
                                        Date::FromString(date_to));
        }
    }
    return 0;
}