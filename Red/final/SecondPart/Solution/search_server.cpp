#include <utility>

#include "search_server.h"
#include "iterator_range.h"
#include "profile.h"

#include <algorithm>
#include <exception>
#include <iterator>
#include <mutex>
#include <sstream>
#include <iostream>

vector<string> SplitIntoWords(const string& line) {
  istringstream words_input(line);
  return {istream_iterator<string>(words_input), istream_iterator<string>()};
}

SearchServer::SearchServer(istream& document_input) {
  UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
  InvertedIndex new_index;

  for (string current_document; getline(document_input, current_document); ) {
    new_index.Add(std::move(current_document));
  }
	lock_guard g(m);
	std::swap<InvertedIndex>(index, new_index);
}
void SearchServer::AddQueriesStream(
	istream& query_input, ostream& search_results_output
)	{
	futures.push_back(async([&](){
					AddQueriesStreamThread(query_input, search_results_output);
	}));
}

void SearchServer::AddQueriesStreamThread(
  istream& query_input, ostream& search_results_output
) {

  for (string current_query; getline(query_input, current_query); ) 
	{
		vector<size_t> docid_count(index.GetCount());
    const auto words = SplitIntoWords(current_query);
    for (auto& word : words) {
			m.lock();
			const vector<pair<size_t, size_t>>& container = index.Lookup(word);
			m.unlock();
			for (const auto docid : container){
					docid_count[docid.first] += docid.second;
      }
 	 }
  	vector<pair<size_t, size_t>> search_results;
		search_results.reserve(docid_count.size());
		for (size_t i = 0; i != docid_count.size(); ++i){
			if (docid_count[i] != 0){
				search_results.push_back({i, docid_count[i]});
			}
		}
		partial_sort(
   	   begin(search_results),begin(search_results) + std::min<size_t>(5, search_results.size()), end(search_results),
   	   [](const pair<size_t, size_t>& lhs, const pair<size_t, size_t>& rhs) {
   	     int64_t lhs_docid = lhs.first;
   	     auto lhs_hit_count = lhs.second;
   	     int64_t rhs_docid = rhs.first;
   	     auto rhs_hit_count = rhs.second;
   	     return make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
   	   }
    	);
		search_results_output << current_query << ':';
    for (auto [docid, hitcount] : Head(search_results, 5)) {
    	search_results_output << " {" << "docid: " << docid << ", "
     	<< "hitcount: " << hitcount << '}';
    }
    search_results_output << endl;
	}	

}

void InvertedIndex::Add(string document) {
  for (const auto& word : SplitIntoWords(std::move(document))) {
		if (!index[word].empty() && index[word].back().first == count){
			++index[word].back().second;
		} else {
			index[word].push_back({count, 1});
		}
  }
	++count;
}

 const vector<pair<size_t, size_t>>& InvertedIndex::Lookup(const string& word) {
		if (auto it = index.find(word); it != end(index)){
			return it->second;
		}
		return void__;
}

SearchServer::~SearchServer(){
	for(auto& thread : futures){
		thread.get();
	}
}

