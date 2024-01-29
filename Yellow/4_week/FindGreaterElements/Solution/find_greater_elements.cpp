#include <vector>
#include <set>
#include <algorithm>
#include <iostream>

using namespace std;


template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border){
    auto it = find_if(elements.begin(), elements.end(), [&](const T& elements){
        return elements > border;
    });
    return vector<T>(it, elements.end());
}