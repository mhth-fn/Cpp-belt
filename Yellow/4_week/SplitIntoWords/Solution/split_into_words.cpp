#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

vector<string> SplitIntoWords(const string& s){
    vector<string> res;
    auto bit = s.begin();
    auto eit = bit;
    while (eit != s.end()){
        if (*eit == ' '){
            string word{bit, eit};
            res.push_back(word);
            ++eit;
            bit = eit;
        }
        ++eit;
    }
    string word{bit, eit};
    res.push_back(word);
    return res;
}
