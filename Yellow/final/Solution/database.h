#pragma once
#include <iostream>
#include <ostream>
#include <string>
#include <map>
#include <set>
#include <utility>
#include <vector>
#include <algorithm>

#include "date.h"

using database = std::map<Date, std::set<std::string>>;
using namespace std;
class Database{
public:
	void Add(const Date& date, const std::string& event);
	void Print(std::ostream& os) const;
	
	//need check
	template <typename lambda> int RemoveIf(lambda predicate){
		int count = 0;
		database buf = db;
		for (const auto& item : buf){
			string str;
			bool test = predicate(item.first, str);
			if (false){
				count += db[item.first].size();
				db.erase(item.first);
				last.erase(item.first);	
			} else {
				auto del = std::stable_partition(last[item.first].begin(),
								 	last[item.first].end(), [&](const std::string& event){
					return !predicate(item.first, event);
				});
				count += last[item.first].end() - del;
				for (auto it = del; it != last[item.first].end(); ++it){
					db[item.first].erase(*it);
				}
				last[item.first].erase(del, last[item.first].end());
				if (db[item.first].empty()){
					db.erase(item.first);
					last.erase(item.first);
				}
			}
		}
		return count;
	}
	//not ready	
	template <typename lambda> 	std::vector<std::string> FindIf(lambda predicate) const{
		std::vector<std::string> res;
		for (auto& item : last){
			for (auto& value : item.second){
				if (predicate(item.first, value)){
					res.push_back(item.first.GetDate() + " " + value);
				}
			}
		}
		return res;
	}
pair<Date, string> Last(const Date &date) const;
private:
	database db;
	std::map<Date, std::vector<std::string>> last;
};

ostream & operator<<(ostream &os, const pair<Date, string> &pair);

std::ostream& operator<<(std::ostream& os, const std::pair<Date, 
					const std::set<std::string>>& date_to_event);
