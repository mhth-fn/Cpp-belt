#include <iostream>
#include "phone_number.h"
#include <stdexcept>

string Parser(const string& number, size_t& id, bool is_a_local_number){
    string res;
    for (; (is_a_local_number || number[id] != '-') && id < number.size(); ++id){
        res+= number[id];
    }   
    if (res.size() == 0){
        throw invalid_argument("Parser");
    }
    ++id;
    return res;
}

PhoneNumber::PhoneNumber(const string &international_number){
    
    if (international_number[0] != '+'){
        throw invalid_argument("+");
    } else {
        size_t i = 1;
        country_code_ = Parser(international_number, i, false);
        city_code_ = Parser(international_number, i, false);
        local_number_ = Parser(international_number, i, true);
    }
}

string PhoneNumber::GetCountryCode() const{
    return country_code_;
}

string PhoneNumber::GetCityCode() const{
    return city_code_;
}

string PhoneNumber::GetLocalNumber() const{
    return local_number_;
}

string PhoneNumber::GetInternationalNumber() const{
    return '+' + country_code_ + '-' + city_code_ + '-' + local_number_;
}
