#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>

class Person {
public:
  void ChangeFirstName(int year, const std::string& first_name) {
    // добавить факт изменения имени на first_name в год year
		firstname[year] = first_name;
  }
  void ChangeLastName(int year, const std::string& last_name) {
    // добавить факт изменения фамилии на last_name в год year
		lastname[year] = last_name;
  }
  std::string GetFullName(int year) {
    // получить имя и фамилию по состоянию на конец года year
	  std::string fn = FindNameByYear(year, firstname);
	  std::string ln = FindNameByYear(year, lastname);

	  if (fn.empty() && ln.empty()){
		  return "Incognito";
	  } else if (fn.empty()){
		  return ln + " with unknown first name";
	  } else if (ln.empty()){
		  return fn + " with unknown last name";
	  }

	  return fn + " " + ln;
  }
private:
   // приватные поля
  std::map<int, std::string> firstname;
  std::map<int, std::string> lastname;
  
  std::string FindNameByYear(int year, const std::map<int, std::string> container){
		std::string res;

		for (const auto& [key, value] : container){
			if (key > year){
				break;
			} else {
				res = value;
			}
		}
		return res;
  }
};



int main() {
  Person person;
  
  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  for (int year : {1900, 1965, 1990}) {
	  std::cout << person.GetFullName(year) << std::endl;
  }
  
  person.ChangeFirstName(1970, "Appolinaria");
  for (int year : {1969, 1970}) {
	  std::cout << person.GetFullName(year) << std::endl;
  }
  
  person.ChangeLastName(1968, "Volkova");
  for (int year : {1969, 1970}) {
	  std::cout << person.GetFullName(year) << std::endl;
  }
  
  return 0;
}
