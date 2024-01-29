#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void PrintVectorPart(const vector<int>& numbers){
    auto it = numbers.begin();
    for (; it != numbers.end(); ++it){
        if (*it < 0){
            break;
        }
    }
    while (it != numbers.begin()){
        --it;
        cout << *it << " ";
    }
}
