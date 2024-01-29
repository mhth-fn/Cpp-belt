#pragma once
#include <algorithm>
#include <filesystem>
#include "iterator_range.h"
#include <istream>
#include <mutex>
#include <ostream>
#include <set>
#include <list>
#include <unordered_map>
#include <vector>
#include <map>
#include <string>
#include <future>
using namespace std;


class InvertedIndex {
public:
  void Add(string document);
  const vector<pair<size_t, size_t>>& Lookup(const string& word);
	size_t GetCount(){
		return count;
	}
private:
	map<string, vector<pair<size_t, size_t>>> index;
	vector<pair<size_t, size_t>> void__; size_t count = 0;
};

class SearchServer {
public:
  SearchServer() = default;
	~SearchServer();
  explicit SearchServer(istream& document_input);
  void UpdateDocumentBase(istream& document_input);
  void AddQueriesStream(istream& query_input, ostream& search_results_output);
	void AddQueriesStreamThread(istream& query_input, ostream& search_results_output);
private:
  InvertedIndex index;
	vector<future<void>> futures;
	mutex m;
};
