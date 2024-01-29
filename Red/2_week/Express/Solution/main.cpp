#include <algorithm>
#include <iterator>
#include <set>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

auto near_element(const set<int>& c, int result){ //logQ
	auto res = c.upper_bound(result);
	if (res == c.end() || abs(result - *res) > abs(result - *prev(res)))
		return prev(res);
	else {
		return res;
	}
}

class RouteManager {
public:
  void AddRoute(int start, int finish) {
    reachable_lists_[start].insert(finish); //(LogQ + 1)
    reachable_lists_[finish].insert(start); //(LogQ + 1)
  } //O(Log Q)
  int FindNearestFinish(int start, int finish) const {
    int result = abs(start - finish); //1
    if (reachable_lists_.count(start) < 1) {
        return result;
    }
    const set<int>& reachable_stations = reachable_lists_.at(start); //Log Q
    if (!reachable_stations.empty()) {
      result = min(
          result,
          abs(finish - *near_element(reachable_stations, finish)) //LogQ
      );
    }
    return result;
  } //O(Log Q + Q) = O(LogQ)
private:
  map<int, set<int>> reachable_lists_;
};


int main() {
	RouteManager routes;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) { // Q
    string query_type;
		cin >> query_type;
    int start, finish;
    cin >> start >> finish;
    if (query_type == "ADD") {
      routes.AddRoute(start, finish);
    } else if (query_type == "GO") {
      cout << routes.FindNearestFinish(start, finish) << "\n";
    }
  } //O(Q(LogQ + Q)) = O(QlogQ + Q^2) = O(Q^2);  new version O(QLogQ)

  return 0;
}
