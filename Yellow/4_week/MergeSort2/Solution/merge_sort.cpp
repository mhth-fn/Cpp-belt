#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end){
    int count = range_end - range_begin; 
    if (range_end - range_begin < 2){
        return;
    } else{
        vector<typename RandomIt::value_type> buf(range_begin, range_end);
        MergeSort(buf.begin(), buf.begin() + count / 3);
        MergeSort(buf.begin() + count / 3, buf.begin() + 2 * count / 3); 
        MergeSort(buf.begin() + 2 * count / 3, buf.end()); 
        vector<typename RandomIt::value_type> tmp;
        merge(buf.begin(), buf.begin() + count / 3, buf.begin() + count / 3, buf.begin() + 2 * count / 3, back_inserter(tmp));
        merge(tmp.begin(), tmp.end(), buf.begin() + 2* count / 3, buf.end(), range_begin);
        
    }

}


int main() {
  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
  MergeSort(begin(v), end(v));
  for (int x : v) {
    cout << x << " ";
  }
  cout << endl;
  return 0;
}