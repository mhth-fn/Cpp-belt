#include "test_runner.h"
#include <string>
#include <string_view>
#include <algorithm>
#include <vector>
#include <map>
#include <list>
using namespace std;

class Translator {
public:
	void Add(string_view source, string_view target){
		const string_view source_view = GetView(string(source));
		const string_view target_view = GetView(string(target));	
		source_to_target[source_view] = target_view;
		target_to_source[target_view] = source_view;
	}
  string_view TranslateForward(string_view source) const{
		return Translate(source_to_target, source);
	}
  string_view TranslateBackward(string_view target) const{
		return Translate(target_to_source, target);
	}
  private:
  // ???
	list<string> words;
	map<string_view, string_view> source_to_target;
	map<string_view, string_view> target_to_source;

	string_view Translate(const map<string_view, string_view>& dict, 
			string_view word) const{
		if (dict.find(word) == end(dict)){
			return "";
		} else {
			return dict.at(word);
		}
	}

	string_view GetView(string str){
		auto it = find(begin(words), end(words), str);
		if (it == end(words)){
			words.push_back(str);
			return words.back();
		} else {
			return *it;
		}
	}
};

void TestSimple() {
  Translator translator;
  translator.Add(string("okno"), string("window"));
  translator.Add(string("stol"), string("table"));

  ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
  ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
  ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSimple);

  return 0;
}
