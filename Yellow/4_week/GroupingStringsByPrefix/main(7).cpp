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
    char prefix){
	auto bit =	lower_bound(range_begin, range_end, prefix, [](const std::string& str, const char c){
			return str[0] < c;
			});
	auto eit = lower_bound(range_begin, range_end, prefix, [](const std::string& str, char c){
			return str[0] < ++c;
			});

	if (bit == range_end){
		bit = eit;
	}
	return {bit, eit};
}


int main() {
  const vector<string> sorted_strings = {"moscow", "murmansk", "vologda"};
  
  const auto m_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), 'm');
  for (auto it = m_result.first; it != m_result.second; ++it) {
    cout << *it << " ";
  }
  cout << endl;
  
  const auto p_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), 'p');
  cout << (p_result.first - begin(sorted_strings)) << " " <<
      (p_result.second - begin(sorted_strings)) << endl;
  
  const auto z_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), 'z');
  cout << (z_result.first - begin(sorted_strings)) << " " <<
      (z_result.second - begin(sorted_strings)) << endl;
  
  return 0;
}
