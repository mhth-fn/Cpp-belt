#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

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
	  std::vector<std::string> fn = FindNameByYear(year, firstname);
	  std::vector<std::string> ln = FindNameByYear(year, lastname);

	  if (fn.empty() && ln.empty()){
		  return "Incognito";
	  } else if (fn.empty()){
		  return ln.back() + " with unknown first name";
	  } else if (ln.empty()){
		  return fn.back() + " with unknown last name";
	  }

	  return fn.back() + " " + ln.back();
  }
  std::string GetFullNameWithHistory(int year){
	// получить имя и фамилию с историй по состоянию на конец года year
	  std::vector<std::string> all_fn = FindNameByYear(year, firstname);
	  std::vector<std::string> all_ln = FindNameByYear(year, lastname);
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
  
  std::vector<std::string> FindNameByYear(int year, const std::map<int, std::string> container){
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

  std::string BuildNameByYear(std::vector<std::string>& container){
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
  Person person;
  
  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  for (int year : {1900, 1965, 1990}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeFirstName(1970, "Appolinaria");
  for (int year : {1969, 1970}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeLastName(1968, "Volkova");
  for (int year : {1969, 1970}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeFirstName(1990, "Polina");
  person.ChangeLastName(1990, "Volkova-Sergeeva");
  cout << person.GetFullNameWithHistory(1990) << endl;
  
  person.ChangeFirstName(1966, "Pauline");
  cout << person.GetFullNameWithHistory(1966) << endl;
  
  person.ChangeLastName(1960, "Sergeeva");
  for (int year : {1960, 1967}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeLastName(1961, "Ivanova");
  cout << person.GetFullNameWithHistory(1967) << endl;
  
  return 0;
}