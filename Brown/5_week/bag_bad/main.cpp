#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum class Gender {
  FEMALE,
  MALE
};

struct Person {
  int age;
  Gender gender;
  bool is_employed;
};

bool operator==(const Person& lhs, const Person& rhs) {
  return lhs.age == rhs.age
      && lhs.gender == rhs.gender
      && lhs.is_employed == rhs.is_employed;
}

ostream& operator<<(ostream& stream, const Person& person) {
  return stream << "Person(age=" << person.age 
      << ", gender=" << static_cast<int>(person.gender)
      << ", is_employed=" << boolalpha << person.is_employed << ")";
}

struct AgeStats {
  int total;
  int females;
  int males;
  int employed_females;
  int unemployed_females;
  int employed_males;
  int unemployed_males;

  bool operator==(const AgeStats& other) const{
    return total == other.total
    && females == other.females
    && males == other.males
    && employed_females == other.employed_females
    && unemployed_females == other.unemployed_females
    && employed_males == other.employed_males
    && unemployed_males == other.unemployed_males;
  }
};
template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
  if (range_begin == range_end) {
    return 0;
  }
  vector<typename iterator_traits<InputIt>::value_type> range_copy(
      range_begin,
      range_end
  );
  auto middle = begin(range_copy) + range_copy.size() / 2;
  nth_element(
      begin(range_copy), middle, end(range_copy),
      [](const Person& lhs, const Person& rhs) {
        return lhs.age < rhs.age;
      }
  );
  return middle->age;
}

vector<Person> ReadPersons(istream& in_stream = cin) {
  int person_count;
  in_stream >> person_count;
  vector<Person> persons;
  persons.reserve(person_count);
  for (int i = 0; i < person_count; ++i) {
    int age, gender, is_employed;
    in_stream >> age >> gender >> is_employed;
    Person person{
        age,
        static_cast<Gender>(gender),
        is_employed == 1
    };
    persons.push_back(person);
  }
  return persons;
}

AgeStats ComputeStats(vector<Person> persons) {
  //                 persons
  //                |       |
  //          females        males
  //         |       |      |     |
  //      empl.  unempl. empl.   unempl.

  auto females_end = partition(
      begin(persons), end(persons),
      [](const Person& p) {
        return p.gender == Gender::FEMALE;
      }
  );
  auto employed_females_end = partition(
      begin(persons), females_end,
      [](const Person& p) {
        return p.is_employed;
      }
  );
  auto employed_males_end = partition(
      females_end, end(persons),
      [](const Person& p) {
        return p.is_employed;
      }
  );

  return {
       ComputeMedianAge(begin(persons), end(persons)),
       ComputeMedianAge(begin(persons), females_end),
       ComputeMedianAge(females_end, end(persons)),
       ComputeMedianAge(begin(persons),  employed_females_end),
       ComputeMedianAge(employed_females_end, females_end),
       ComputeMedianAge(females_end, employed_males_end),
       ComputeMedianAge(employed_males_end, end(persons))
  };
}

void PrintStats(const AgeStats& stats,
                ostream& out_stream = cout) {
  out_stream << "Median age = "
             << stats.total              << endl
             << "Median age for females = "
             << stats.females            << endl
             << "Median age for males = "
             << stats.males              << endl
             << "Median age for employed females = "
             << stats.employed_females   << endl
             << "Median age for unemployed females = "
             << stats.unemployed_females << endl
             << "Median age for employed males = "
             << stats.employed_males     << endl
             << "Median age for unemployed males = "
             << stats.unemployed_males   << endl;
}
void TestComputeMedianAge(){
  {//Empty vector
    std::vector<Person> person;
    try{
    ASSERT_EQUAL(ComputeMedianAge(person.begin(), person.end()), 0);
    } catch (...){
      ASSERT(0);
    }
  }
  {//Test Median age
    std::vector<Person> person;
    person.push_back({10, Gender::FEMALE, 0});
    person.push_back({20, Gender::FEMALE, 0});
    person.push_back({30, Gender::FEMALE, 0});
    person.push_back({40, Gender::FEMALE, 0});
    person.push_back({50, Gender::FEMALE, 0});
    ASSERT_EQUAL(ComputeMedianAge(begin(person), end(person)), 30);
  }
  {
    std::vector<Person> person;
    person.push_back({10, Gender::FEMALE, 0});
    person.push_back({20, Gender::FEMALE, 0});
    person.push_back({30, Gender::FEMALE, 0});
    person.push_back({40, Gender::FEMALE, 0});
    person.push_back({50, Gender::FEMALE, 0});
    person.push_back({60, Gender::FEMALE, 0});
    ASSERT_EQUAL(ComputeMedianAge(begin(person), end(person)), 40);
  }
}

void TestReadPersons(){
  stringstream ss("5\n10 0 0\n20 1 0\n30 1 1\n40 0 1\n10 1 1");
  auto res = ReadPersons(ss);
  vector<Person> expect = {{10, Gender::FEMALE, 0},
  {20, Gender::MALE, 0},
  {30, Gender::MALE, 1},
  {40, Gender::FEMALE, 1},
  {10, Gender::MALE, 1}};
  ASSERT_EQUAL(res, expect);
}

void TestComputeStats(){
  std::vector<Person> person;
  person.push_back({40, Gender::FEMALE, 1});
  person.push_back({40, Gender::FEMALE, 1});
  person.push_back({30, Gender::FEMALE, 0});
  person.push_back({30, Gender::FEMALE, 0});
  person.push_back({30, Gender::MALE, 1});
  person.push_back({30, Gender::MALE, 1});
  person.push_back({20, Gender::MALE, 0});
  person.push_back({20, Gender::MALE, 0});
  auto res = ComputeStats(person);
  AgeStats expect{30, 40, 30, 40, 30, 30, 20};
  //ASSERT_EQUAL(res, expect);
}

void TestPrintStats(){
  AgeStats stats{30, 40, 30, 40, 30, 30, 20};
  stringstream res;
  PrintStats(stats, res);
  stringstream expect;
  expect << "Median age = "
             << stats.total              << endl
             << "Median age for females = "
             << stats.females            << endl
             << "Median age for males = "
             << stats.males              << endl
             << "Median age for employed females = "
             << stats.employed_females   << endl
             << "Median age for unemployed females = "
             << stats.unemployed_females << endl
             << "Median age for employed males = "
             << stats.employed_males     << endl
             << "Median age for unemployed males = "
             << stats.unemployed_males   << endl;
  ASSERT_EQUAL(res.str(), expect.str());
}
void TestAll(){
  TestRunner tr;
  RUN_TEST(tr, TestComputeMedianAge);
  RUN_TEST(tr, TestReadPersons);
  RUN_TEST(tr, TestComputeStats);
  RUN_TEST(tr, TestPrintStats);
}
int main() {
  TestAll();
  //PrintStats(ComputeStats(ReadPersons()));
  return 0;
}