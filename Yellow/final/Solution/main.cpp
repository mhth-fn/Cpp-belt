#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"
#include "test_db.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <string>

using namespace std;

string ParseEvent(istream& is) {
  // Реализуйте эту функцию
	string res;
	while (is.peek() == ' '){
		is.get();
	}
	getline(is, res);
	return res;
}
ostream & operator<<(ostream &os, const pair<Date, string> &pair) {
    os << pair.first << ' ' << pair.second;
    return os;
}

void TestAll()
{
    TestRunner tr;
    tr.RunTest(TestParseEvent, "Test Parse Event");
    tr.RunTest(TestParseCondition, "Test Parse Condition");
    tr.RunTest(TestEmptyNode, "Test Empty Node");
    tr.RunTest(TestDbAdd, "Test Db Add");
    tr.RunTest(TestDbFind, "Test Db Find");
    tr.RunTest(TestDbLast, "Test Db Last");

    tr.RunTest(TestInsertionOrder, "Test Insertion Order");
    tr.RunTest(TestsMyCustom, "Мои тесты");
    tr.RunTest(TestDatabase, "Тест базы данных с GitHub");
    tr.RunTest(TestLogicalOperationNode, "Test Logical Operation Node");
    tr.RunTest(TestEventComparisonNode, "Test Event Comparison Node");
    tr.RunTest(TestDateComparisonNode, "Test Date Comparison Node");
    tr.RunTest(TestDbRemoveIf, "Test Db Remove If");
    tr.RunTest(TestPrint, "Test Print");
    tr.RunTest(Test14, "Test 14");
    tr.RunTest(Test14_2, "Test 14-2");
    tr.RunTest(Test14_3, "Test 14-3");
}

ostream& operator<<(ostream& os, std::vector<string> vec){
	for (const auto& x : vec){
		os << x << " ";
	}
	return os;
}
int main() {
  TestAll();

  Database db;

  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "Add") {
      const auto date = ParseDate(is);
      const auto event = ParseEvent(is);
      db.Add(date, event);
    } else if (command == "Print") {
      db.Print(cout);
    } else if (command == "Del") {

      auto condition = ParseCondition(is);
	    auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };

      int count = db.RemoveIf(predicate);
      cout << "Removed " << count << " entries" << endl;
    } else if (command == "Find") {
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };

      const auto entries = db.FindIf(predicate);
      for (const auto& entry : entries) {
        cout << entry << endl;
      }
      cout << "Found " << entries.size() << " entries" << endl;
    } else if (command == "Last") {
      try {
          cout << db.Last(ParseDate(is)) << endl;
      } catch (invalid_argument&) {
          cout << "No entries" << endl;
      }
    } else if (command.empty()) {
      continue;
    } else {
      throw logic_error("Unknown command: " + command);
    }
  }

  return 0;
}


