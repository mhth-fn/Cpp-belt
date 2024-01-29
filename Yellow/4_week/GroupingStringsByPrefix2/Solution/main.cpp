#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <tuple>
#include <vector>
#include <utility>
#include <string>

using namespace std;

template <typename RandomIt>
std::pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt range_begin, RandomIt range_end,
    const string& prefix){
	auto bit =lower_bound(range_begin, range_end, prefix);
	
	string next = prefix;
	++next[next.size() - 1];
	auto eit = lower_bound(range_begin, range_end, next);

	return {bit, eit};
}


int main() {
  const vector<string> sorted_strings = {"moscow", "motovilikha", "murmansk"};
  
  const auto mo_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
  for (auto it = mo_result.first; it != mo_result.second; ++it) {
    cout << *it << " ";
  }
  cout << endl;
  
  const auto mt_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
  cout << (mt_result.first - begin(sorted_strings)) << " " <<
      (mt_result.second - begin(sorted_strings)) << endl;
  
  const auto na_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
  cout << (na_result.first - begin(sorted_strings)) << " " <<
      (na_result.second - begin(sorted_strings)) << endl;
  
  return 0;
}
