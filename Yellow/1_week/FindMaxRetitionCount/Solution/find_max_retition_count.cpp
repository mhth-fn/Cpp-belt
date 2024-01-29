#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <set>

using namespace std;

int FindMaxRepetitionCount(const vector<Region>& regions){
    if (regions.size() == 0){
        return 0;
    }
	map<Region, int> exclusive;
	for (const auto& region : regions){
		++exclusive[region];	
	}

    int max = 0;
    for (const auto& item : exclusive){
        if (item.second >= max){
            max = item.second;
        }
    }

    if (max == 1){
        return 1;
    } else {
	return max;
    }
}

bool operator<(const Region& one, const Region& two){
	return tie(one.std_name, one.parent_std_name, one.names, one.population)
		< tie(two.std_name, two.parent_std_name, two.names, two.population);
}

