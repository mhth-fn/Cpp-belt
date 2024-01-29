#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
      os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

//class Person {
//public:
//  // Вы можете вставлять сюда различные реализации класса,
//  // чтобы проверить, что ваши тесты пропускают корректный код
//  // и ловят некорректный
//  void ChangeFirstName(int year, const string& first_name) {
//	  history_firstname[year] = first_name;
//  }
//
//  void ChangeLastName(int year, const string& last_name) {
//	  history_lastname[year] = last_name;
//  }
//
//  string GetFullName(int year) {
//	  string fn = GetNameByYear(year, history_firstname);
//	  string ln = GetNameByYear(year, history_lastname);
//
//	  if (fn.size() == 0 && ln.size() == 0){
//		  return "Incognito";
//	  } else if (fn.empty()){
//		  return ln + " with unknown first name";
//	  } else if (ln.empty()){
//		  return fn + " with unknown last name";
//	  } else {
//		  return fn + " " + ln;
//	  }
//  }
//
//private:
//  map<int, string> history_firstname;
//  map<int, string> history_lastname;
//
//  string GetNameByYear(const int year, const map<int, string>& history_name){
//	  string res;
//	  for (const auto& [key, value] : history_name){
//		if (year >= key){
//			res = value;
//		} else {
//			break;
//		}
//	  }
//	  return res;
//  }
//
//};

//void TestChangeFirstName();
//void TestChangeLastName();
void TestGetFullName(){
	{
		Person person;
		person.ChangeFirstName(1970, "Polina");
		AssertEqual(person.GetFullName(1969), "Incognito");
		AssertEqual(person.GetFullName(1970), "Polina with unknown last name");
		AssertEqual(person.GetFullName(1971), "Polina with unknown last name");
		person.ChangeLastName(1965, "Grigoryan");
		AssertEqual(person.GetFullName(1964), "Incognito");
		AssertEqual(person.GetFullName(1965), "Grigoryan with unknown first name");
		AssertEqual(person.GetFullName(1967), "Grigoryan with unknown first name");
		AssertEqual(person.GetFullName(1970), "Polina Grigoryan");
	}
}

void TestAll(){
	TestRunner runner;
//	runner.RunTest(TestChangeFirstName, "ChangeFirstName");
//	runner.RunTest(TestChangeLastName, "ChangeLastName");
	runner.RunTest(TestGetFullName, "GetFullName");

}
int main() {
  TestAll();
  // добавьте сюда свои тесты
  return 0;
}
