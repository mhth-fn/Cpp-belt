#include <iostream>
#include <iterator>
#include <string>
#include <map>

std::string FindName(int year,
										const std::map<int, std::string>& container){
	if (container.begin() == container.end()){
		return "";
	}

	auto it = container.lower_bound(year);
	
	if (it == container.begin() && it->first > year){
		return "";
	} else if	(it != container.end() && it->first == year){
		return it->second;
	} else {
		return std::prev(it)->second;
	}

}
class Person {
public:
  void ChangeFirstName(int year, const std::string& first_name) {
    // добавить факт изменения имени на first_name в год year
		firstname_history[year] = first_name;
  }
  void ChangeLastName(int year, const std::string& last_name) {
    // добавить факт изменения фамилии на last_name в год year
		lastname_history[year] = last_name;
  }
	std::string GetFullName(int year) {
    // получить имя и фамилию по состоянию на конец года year
    // с помощью двоичного поиска
		std::string fn = FindName(year, firstname_history);
		std::string ln = FindName(year, lastname_history);

		if (fn.empty() && ln.empty()){
			return "Incognito";
		} else if (fn.empty() && !ln.empty()){
			return ln + " with unknown first name";
		} else if (!fn.empty() && ln.empty()){
			return fn + " with unknown last name";
		} else {
			return fn + " " + ln;
		}

  }
private:
  // приватные поля
	std::map<int, std::string> firstname_history, lastname_history;
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
