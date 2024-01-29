#include <algorithm>
#include <exception>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <set>

using namespace std;

class Date{
public:
	Date(int new_year, int new_month, int new_day){
		year = new_year;
		if (new_month > 12 || new_month < 1){
			throw invalid_argument("Month value is invalid: " + to_string(new_month)); 
		}
		month = new_month;
		if (new_day > 31 || new_day < 1) {
		   throw invalid_argument("Day value is invalid: " + to_string(new_day));
		}
		day = new_day;
	}
	
	int GetYear() const{
		return year;
	}
	int GetMonth() const{
		return month;
	}
	int GetDay() const {
		return day;
	}

private:
	int day;
	int month;
	int year;
};


bool operator<(const Date& lhs, const Date& rhs){
	return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} <
			vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

ostream& operator<<(ostream& stream, const Date& date) {
	stream << setw(4) << setfill('0') << date.GetYear() <<
		"-" << setw(2) << setfill('0') << date.GetMonth() <<
		"-" << setw(2) << setfill('0') << date.GetDay();
	return stream;
}

class Database {
public:
	void AddEvent(const Date& date, const string& event){
		db[date].insert(event);
  }

	bool DeleteEvent(const Date& date, const string& event){
		if (db.count(date) != 0 && db[date].count(event) != 0){
			db[date].erase(event);
			return true;
		}
		return false;
	}
	int  DeleteDate(const Date& date){
		if (db.count(date) == 0){
			return 0;
		} 
		int size = db[date].size();
		db.erase(date);
		return size;
	}

	set<string> Find(const Date& date) const{
		if (db.count(date) != 0){
			return db.at(date);
		}
		return {};
	}
  
	void Print() const{
		for (const auto [date, events] : db){
			for (const auto event : events){
				cout << date << ' ' << event << endl;
			}
		}
	}
private:
	map<Date, set<string>> db;
};

void ReadPartAndIgnore(stringstream& ss, bool& flag, int& part){
	flag = flag && (ss >> part);
	flag = flag && (ss.peek() == '-' || ss.eof());
	ss.ignore(1);

}
Date ParseDate(const string& date) {
	stringstream ss(date);
	bool flag = true;

	int year;
	ReadPartAndIgnore(ss, flag, year);	
  
	int month;
	ReadPartAndIgnore(ss, flag, month);

	int day;
	ReadPartAndIgnore(ss, flag, day);
	
	if (!flag) {
		throw invalid_argument("Wrong date format: " + date);
	}
	return Date(year, month, day);
}

int main() {
  try {
    Database db;

    string command_line;
    while (getline(cin, command_line)) {
      stringstream ss(command_line);

      string command;
      ss >> command;

      if (command == "Add") {

        string date_str, event;
        ss >> date_str >> event;
        const Date date = ParseDate(date_str);
        db.AddEvent(date, event);

      } else if (command == "Del") {

        string date_str;
        ss >> date_str;
        string event;
        if (!ss.eof()) {
          ss >> event;
        }
        const Date date = ParseDate(date_str);
        if (event.empty()) {
          const int count = db.DeleteDate(date);
          cout << "Deleted " << count << " events" << endl;
        } else {
          if (db.DeleteEvent(date, event)) {
            cout << "Deleted successfully" << endl;
          } else {
            cout << "Event not found" << endl;
          }
        }

      } else if (command == "Find") {

        string date_str;
        ss >> date_str;
        const Date date = ParseDate(date_str);
        for (const string& event : db.Find(date)) {
          cout << event << endl;
        }

      } else if (command == "Print") {

        db.Print();

      } else if (!command.empty()) {

        throw logic_error("Unknown command: " + command);

      }
    }
  } catch (const exception& e) {
    cout << e.what() << endl;
  }

  return 0;
}
