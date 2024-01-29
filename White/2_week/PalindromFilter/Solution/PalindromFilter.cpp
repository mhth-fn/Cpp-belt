#include <iostream>
#include <string>
#include <vector>

bool IsPalindrom(const std::string& word) {
	for (size_t i = 0; i < word.size() / 2; ++i) {
		size_t reverse_index = word.size() - 1 - i;
		if (word[i] != word[reverse_index]) {
			return false;
		}
	}
	return true;
}

using Words = std::vector<std::string>;

Words PalindromFilter(const Words& words, int minLength){
	Words res;
	for (auto word : words){
		if (IsPalindrom(word) && word.size() >= minLength){
			res.push_back(word);
		}
	}
	return res;
}
