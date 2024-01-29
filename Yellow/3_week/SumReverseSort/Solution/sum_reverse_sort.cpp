#include "sum_reverse_sort.h"
#include <algorithm>
int Sum(int x, int y){
  return x + y;
}

string Reverse(string s){
  string res = s;
  for (size_t i = s.size(); i != 0; --i){
    res[s.size() - i] = s[i - 1];
  }
  return res;
}

void Sort(vector<int>& nums){
  return sort(nums.begin(), nums.end());
}
