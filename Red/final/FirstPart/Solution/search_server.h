#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <unordered_map>
#include <vector>
#include <map>
#include <string>
using namespace std;

class InvertedIndex {
public:
  void Add(string& document);
  const vector<pair<size_t, size_t>>& Lookup(string word);

private:
	unordered_map<string, vector<pair<size_t, size_t>>> index;
/*Что должен хранить индекс?
	Слово, id, количество вхождений	*/
	vector<pair<size_t, size_t>> void_;
	size_t count = 0;
};

class SearchServer {
public:
  SearchServer() = default;
  explicit SearchServer(istream& document_input);
  void UpdateDocumentBase(istream& document_input);
  void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
  InvertedIndex index;
};
