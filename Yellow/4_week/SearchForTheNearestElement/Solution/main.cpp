#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <set>

using namespace std;

set<int>::const_iterator FindNearestElement(
    const set<int>& numbers,
    int border){
	
	if (numbers.begin() == numbers.end()){
		return numbers.begin();
	}

	set<int>::const_iterator it = numbers.lower_bound(border);
	if (it == numbers.end()){
		return prev(it);
	} else if (*it != border){
		if (abs(*it - border) >= abs(*prev(it) - border)){
			return prev(it);
		}
	}
	return it;
}

// set<int>::const_iterator —
// тип итераторов для константного множества целых чисел

int main() {
  set<int> numbers = {1, 4, 6};
  cout <<
      *FindNearestElement(numbers, 0) << " " <<
      *FindNearestElement(numbers, 3) << " " <<
      *FindNearestElement(numbers, 5) << " " <<
      *FindNearestElement(numbers, 6) << " " <<
      *FindNearestElement(numbers, 100) << endl;
      
  set<int> empty_set;
  
  cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
  return 0;
}
