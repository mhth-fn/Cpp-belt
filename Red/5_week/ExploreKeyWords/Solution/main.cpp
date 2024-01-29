#include "test_runner.h"

#include <map>
#include <string>
#include <future>
#include <string_view>
using namespace std;

struct Stats {
  map<string, int> word_frequences;

  void operator += (const Stats& other){
		for (const auto& item : other.word_frequences){
			word_frequences[item.first] += item.second;
		}
	}
};

Stats ExploreLine(const set<string>& key_words, const string& line) {
	Stats result;
	string_view str(line);
	
	while (true){
		size_t space = str.find(" ");
		string word(str.substr(0, space));	
		if (key_words.find(word) != end(key_words)){
			++result.word_frequences[word];
		}	
		if (space == str.npos) {
			break;
		} else {
			str.remove_prefix(space + 1);
		}
	}
	return result;
}

Stats ExploreKeyWordsSingleThread(
  const set<string>& key_words, const vector<string>& words
) {
  Stats result;
  for (const auto& str : words) {
    result += ExploreLine(key_words, str);
  }
  return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
	size_t threads = 4;
	vector<vector<string>> words_from_input(threads);
	
	size_t i = 0;
  for (string line; getline(input, line); ) {
		words_from_input[i++ % threads].push_back(line);
	}
	
	vector<future<Stats>> futures;
	futures.reserve(threads);
	for (i = 0; i != threads; ++i){
		futures.push_back(async(ExploreKeyWordsSingleThread, ref(key_words), ref(words_from_input[i])));
	}

	Stats result;
	for (auto& part_result : futures){
		result += part_result.get();
	}
  return result;
}

void TestBasic() {
  const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

  stringstream ss;
  ss << "this new yangle service really rocks\n";
  ss << "It sucks when yangle isn't available\n";
  ss << "10 reasons why yangle is the best IT company\n";
  ss << "yangle rocks others suck\n";
  ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

  const auto stats = ExploreKeyWords(key_words, ss);
  const map<string, int> expected = {
    {"yangle", 6},
    {"rocks", 2},
    {"sucks", 1}
  };
  ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestBasic);
}
