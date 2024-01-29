#include <fstream>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <numeric>

using namespace std;

template <typename Iterator>
class IteratorRange {
public:
  IteratorRange(Iterator begin, Iterator end)
    : first(begin)
    , last(end)
  {
  }

  Iterator begin() const {
    return first;
  }

  Iterator end() const {
    return last;
  }

private:
  Iterator first, last;
};

template <typename Collection>
auto Head(Collection& v, size_t top) {
  return IteratorRange{v.begin(), next(v.begin(), min(top, v.size()))};
}

struct Person {
  string name;
  int age, income;
  bool is_male;
};

vector<Person> ReadPeople(istream& input) {
  int count;
  input >> count;

  vector<Person> result(count);
  for (Person& p : result) {
    char gender;
    input >> p.name >> p.age >> p.income >> gender;
    p.is_male = gender == 'M';
  }

  return result;
}

void PrintVectorPerson(const vector<Person>& people){
  for (const auto& item : people){
    std::cout << item.name << " " << item.age << " " 
    << item.is_male << " " << item.income << '\n';
  }
}
class Statistic{
public:
  Statistic(istream& input) : by_age(ReadPeople(input)){
    by_wealthy = by_age;
    sort(begin(by_age), end(by_age), [](const Person& lhs, const Person& rhs) {
      return lhs.age < rhs.age;
    });
    sort(begin(by_wealthy), end(by_wealthy), [](const Person& lhs, const Person& rhs) {
      return lhs.income > rhs.income;
    });
  }
  string GetPopularName(char gender) const{
    if (gender == 'M'){
      return m_name;
    } else if (gender == 'W'){
      return w_name;
    }
  }

  int GetMutarityAge(int adult_age) const{
    auto adult_begin = lower_bound(
      begin(by_age), end(by_age), adult_age, [](const Person& lhs, int age) {
        return lhs.age < age;
      }
    );

    return std::distance(adult_begin, end(by_age));
  }
  int GetWealthy(int count) const{
      auto head = Head(by_wealthy, count); //maybe wrong

      int total_income = accumulate(
        head.begin(), head.end(), 0, [](int cur, const Person& p) {
          return p.income + cur;
        }
      );

      return total_income;
  }
private:
  string w_name, m_name;
  vector<Person> by_age, by_wealthy;

  
  vector<Person> ReadPeople(istream& input) {
    int count;
    input >> count;
    unordered_map<string, int>  wname, mname;
    vector<Person> result(count);
    for (Person& p : result) {
      char gender;
      input >> p.name >> p.age >> p.income >> gender;
      p.is_male = gender == 'M';
      gender == 'M' ? ++mname[p.name] : ++wname[p.name];
    }
    w_name = GetMaxFromMap(wname);
    m_name = GetMaxFromMap(mname);

    return result;
  }
  string GetMaxFromMap(const unordered_map<string, int>& container){
    int count = 0;
    string res;
    for (const auto& item : container){
      if (item.second > count){
        res = item.first;
        count = item.second;
      } else if (item.second == count && item.first < res){
        res = item.first;
      }
    }
    return res;
  }
};
int main(){
  Statistic people(cin);

  for (string command; cin >> command; ) {
    if (command == "AGE") {
      int adult_age;
      cin >> adult_age;


      std::cout << "There are " << people.GetMutarityAge(adult_age)
           << " adult people for maturity age " << adult_age << '\n';
    } else if (command == "WEALTHY") {
      int count;
      cin >> count;

      std::cout << "Top-" << count << " people have total income " << people.GetWealthy(count) << '\n';
    } else if (command == "POPULAR_NAME") {
      char gender;
      cin >> gender;
      
      string name = people.GetPopularName(gender);
      if (name.empty()) {
        std::cout << "No people of gender " << gender << '\n';
      } else {
        std::cout << "Most popular name among people of gender " << gender << " is "
             << name << '\n';
      }
    } 
  }
}