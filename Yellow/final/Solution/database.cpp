#include "database.h"

//need check
void Database::Add(const Date& date, const std::string& event){
	if (db[date].find(event) == db[date].end()){
		db[date].insert(event);
		last[date].push_back(event);
	}
}

//check
void Database::Print(std::ostream& os) const{
	for (const auto& x : last){
		for (const auto& y : x.second){
			os << x.first << " " << y << std::endl;
		}
	}	
}

//need check

pair<Date, string> Database::Last(const Date &date) const {
    auto it = last.upper_bound(date);
    if (it != last.begin())
    {
        it = prev(it);
        return make_pair(it->first, it->second.back());
    } else {
        throw invalid_argument("There is no last element");
    }
}
//need check
std::ostream& operator<<(std::ostream& os, const std::pair<Date, 
					const std::set<std::string>>& date_to_event){
	for (const auto& x : date_to_event.second){
		os << date_to_event.first << " " << x << std::endl;
	}

	return os;
}
