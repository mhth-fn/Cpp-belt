#include "airline_ticket.h"
#include "test_runner.h"
#include <iomanip>
#include <istream>
#include <sstream>

using namespace std;

bool operator<(const Date& lhs, const Date& rhs){
	return make_tuple(lhs.year, lhs.month, lhs.day) 
		< make_tuple(rhs.year, rhs.month, rhs.day); 
}

bool operator<(const Time& lhs, const Time& rhs){
	return make_tuple(lhs.hours, lhs.minutes) 
		< make_tuple(rhs.hours, lhs.minutes); 
}

bool operator==(const Date& lhs, const Date& rhs){
	return make_tuple(lhs.year, lhs.month, lhs.day) 
		== make_tuple(rhs.year, rhs.month, rhs.day); 
}

bool operator==(const Time& lhs, const Time& rhs){
	return make_tuple(lhs.hours, lhs.minutes) 
		== make_tuple(rhs.hours, rhs.minutes); 
}


ostream& operator<<(ostream& os, const Date& date){	
	os << std::setfill('0') << std::setw(4);	
	os << date.year << "-" << 
	 std::setw(2) << date.month << "-" << std::setw(2) << date.day; 
	return os;
}

ostream& operator<<(ostream& os, const Time& time){	
	os << std::setfill('0') << std::setw(2);	
	os << time.hours << ":" << 
	 std::setw(2) << time.minutes; 
	return os;
}


istream& operator>>(istream& is, Date& date){
	is >> date.year;
	is.get();
	is >> date.month;
	is.get();
	is >> date.day;
	return is;
}

istream& operator>>(istream& is, Time& time){
	is >> time.hours;
	is.get();
	is >> time.minutes;
	return is;
}

#define UPDATE_FIELD(ticket, field, values){ \
	auto it = values.find(#field);   					 \
	if (it != values.end()) { 								 \
		istringstream is(it->second);            \
		is >> ticket.field;										   \
	}										   										 \
} 




void TestUpdate() {
  AirlineTicket t;
  t.price = 0;

  const map<string, string> updates1 = {
    {"departure_date", "2018-2-28"},
    {"departure_time", "17:40"},
  };
  UPDATE_FIELD(t, departure_date, updates1);
  UPDATE_FIELD(t, departure_time, updates1);
  UPDATE_FIELD(t, price, updates1);

  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 0);

  const map<string, string> updates2 = {
    {"price", "12550"},
    {"arrival_time", "20:33"},
  };
  UPDATE_FIELD(t, departure_date, updates2);
  UPDATE_FIELD(t, departure_time, updates2);
  UPDATE_FIELD(t, arrival_time, updates2);
  UPDATE_FIELD(t, price, updates2);

  // updates2 не содержит ключей "departure_date" и "departure_time", поэтому
  // значения этих полей не должны измениться
  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 12550);
  ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestUpdate);
}
