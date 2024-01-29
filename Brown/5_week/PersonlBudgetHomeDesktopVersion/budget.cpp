#include "budget.h"

using namespace std;

static const Date START_DATE = Date::FromString("2000-01-01");
static const Date END_DATE = Date::FromString("2100-01-01");
static const size_t DAY_COUNT = ComputeDaysDiff(START_DATE, START_DATE);

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

time_t Date::AsTimestamp() const{
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

int ComputeDaysDiff(const Date& date_from, const Date& date_to) {
  const time_t timestamp_from = date_from.AsTimestamp();
  const time_t timestamp_to = date_to.AsTimestamp();
  static const int SECONDS_IN_DAY = 60 * 60 * 24;
  return (timestamp_to - timestamp_from) / SECONDS_IN_DAY;
}

Budget::Budget(){
    budget_.resize(DAY_COUNT, 0.0);
}

void Budget::Earn(const Date& from, const Date& to, int value){
    if (from == to){
        budget_[ComputeDaysDiff(START_DATE, from)] += value;
    } else{
        int from_index = ComputeDaysDiff(START_DATE, from);
        int to_index = ComputeDaysDiff(START_DATE, to) + 1;
        double daily_value = value / (to_index - from_index);
        while (from_index != to_index){
            budget_[from_index++] += daily_value;
        }
   }
}

double Budget::ComputeIncome(const Date& from, const Date& to) const{
    if (from == to){
        return budget_[ComputeDaysDiff(START_DATE, from)];
    } else {
        int from_index = ComputeDaysDiff(START_DATE, from);
        int to_index = ComputeDaysDiff(START_DATE, to) + 1;
        return std::accumulate(budget_.begin() + from_index, budget_.begin() + to_index, 0.0);
    } 
}


void Budget::PayTax(const Date& from, const Date& to){
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