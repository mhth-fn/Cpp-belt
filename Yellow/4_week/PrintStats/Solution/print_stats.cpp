#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;


void PrintStats(vector<Person> persons){
    std::cout << "Median age = " << ComputeMedianAge(persons.begin(), persons.end()) << endl;
    std::cout << "Median age for females = " << ComputeMedianAge(persons.begin(), partition(persons.begin(), persons.end(), [](Person unit){
        return unit.gender == Gender::FEMALE;
    })) << endl;
    std::cout << "Median age for males = " << ComputeMedianAge(persons.begin(), partition(persons.begin(), persons.end(), [](Person unit){
        return unit.gender == Gender::MALE;
    })) << endl;
    std::cout << "Median age for employed females = " << ComputeMedianAge(persons.begin(), partition(persons.begin(), persons.end(), [](Person unit){
        return unit.gender == Gender::FEMALE && unit.is_employed == true;
    })) << endl;
    std::cout << "Median age for unemployed females = " << ComputeMedianAge(persons.begin(), partition(persons.begin(), persons.end(), [](Person unit){
        return unit.gender == Gender::FEMALE && unit.is_employed == false;
    })) << endl;
    std::cout << "Median age for employed males = " << ComputeMedianAge(persons.begin(), partition(persons.begin(), persons.end(), [](Person unit){
        return unit.gender == Gender::MALE && unit.is_employed == true;
    })) << endl;
    std::cout << "Median age for unemployed males = " << ComputeMedianAge(persons.begin(), partition(persons.begin(), persons.end(), [](Person unit){
        return unit.gender == Gender::MALE && unit.is_employed == false;
    })) << endl;
    
}
