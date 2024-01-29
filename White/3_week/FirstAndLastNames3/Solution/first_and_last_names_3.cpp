#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Person {
public:
  Person(const std::string& _firstname, const std::string& _lastname, int _year){
	  firstname[_year] = _firstname;
	  lastname[_year] = _lastname;
	  year = _year;
  }
  void ChangeFirstName(int _year, const std::string& first_name) {
    // добавить факт изменения имени на first_name в год year
		if (_year >= year){
		firstname[_year] = first_name;
		}
  }
  void ChangeLastName(int _year, const std::string& last_name) {
    // добавить факт изменения фамилии на last_name в год year
	  	if (_year >= year){
		lastname[_year] = last_name;
		}
  }
  std::string GetFullName(int _year) const {
    // получить имя и фамилию по состоянию на конец года year
	  if (_year < year){
		  return "No person";
	  }
	  std::vector<std::string> fn = FindNameByYear(_year, firstname);
	  std::vector<std::string> ln = FindNameByYear(_year, lastname);

	  if (fn.empty() && ln.empty()){
		  return "Incognito";
	  } else if (fn.empty()){
		  return ln.back() + " with unknown first name";
	  } else if (ln.empty()){
		  return fn.back() + " with unknown last name";
	  }

	  return fn.back() + " " + ln.back();
  }
  std::string GetFullNameWithHistory(int _year) const{
	// получить имя и фамилию с историй по состоянию на конец года year
	  if (_year < year){
		  return "No person";
	  }
	  std::vector<std::string> all_fn = FindNameByYear(_year, firstname);
	  std::vector<std::string> all_ln = FindNameByYear(_year, lastname);
	  std::string fn = BuildNameByYear(all_fn);
	  std::string ln = BuildNameByYear(all_ln);

	  if (fn.empty() && ln.empty()){
		  return "Incognito";
	  } else if (fn.empty()){
		  return ln + " with unknown first name";
	  } else if (ln.empty()){
		  return fn  + " with unknown last name";
	  }

	  return fn + " " + ln;
  }

	

private:
   // приватные поля
  std::map<int, std::string> firstname;
  std::map<int, std::string> lastname;
  int year;

  std::vector<std::string> FindNameByYear(int year, const std::map<int, std::string> container) const{
		std::vector<std::string> res;

		for (const auto& [key, value] : container){
			if (key > year){
				break;
			} else {
				res.push_back(value);
			}
		}
		return res;
  }

  std::string BuildNameByYear(const std::vector<std::string>& container) const{
	  std::vector<std::string> hist_names;
	  std::string res;
	  if (container.empty()){
		  return res;
	  }
	  res = container.back();

	  for (const auto& x : container){
		  int count = 0;
		  for (const auto& y : hist_names){
			  if (x == y){
				  ++count;
			  }
		  }
		  if (count == 0){
			  hist_names.push_back(x);
		  }
		}	
	  reverse(hist_names.begin(), hist_names.end());
	  int j = 0;
	  while (hist_names[j] == res){
		++j;
	  }
	  bool flag = false;
	  if (hist_names.size() > 0){
		  for (int i = j; i != hist_names.size(); ++i){
			  if (i == j){
				  res += " (" + hist_names[i];
				  flag = true;
			  } else {
				  res += ", " + hist_names[i];
			  }
		  }
		  if (flag)
		  res += ")";
	  }
	  return res;
  }
  };

int main() {
  Person person("Polina", "Sergeeva", 1960);
  for (int year : {1959, 1960}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeFirstName(1965, "Appolinaria");
  person.ChangeLastName(1967, "Ivanova");
  for (int year : {1965, 1967}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }

  return 0;
}
