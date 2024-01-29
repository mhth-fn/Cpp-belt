#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
struct Item{
	Item(int priority, size_t id) : 
		priority_(priority), id_(id){};


	int priority_;
	size_t id_;

};

template <typename T>
bool operator<(const Item<T>& lhs, const Item<T>& rhs){
		return std::tie(lhs.priority_, lhs.id_) < std::tie(rhs.priority_, rhs.id_);
}
template <typename T>
class PriorityCollection{
public:
	PriorityCollection(){
		vector_id.reserve(1000000);
		vector_value.reserve(1000000);
	}
	using Id = size_t;

	size_t Add(T value){
		typename std::set<Item<T>>::iterator it = queue.insert({0, vector_id.size()}).first;
		vector_value.push_back(std::move(value));	
		vector_id.push_back(it);	
		return vector_id.size() - 1;
	}
  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end,
           IdOutputIt ids_begin){
		std::vector<size_t> tmp;
		for (auto it = range_begin; it != range_end; ++it){
			 tmp.push_back(Add(std::move(*it)));	
		}
		move(tmp.begin(), tmp.end(), ids_begin);
	}


  bool IsValid(Id id) const{
		if (vector_id.size() > id && vector_id[id] != end(queue)){
			return true;
		} else{
			return false;
		}
	}

  const T& Get(Id id) const{
		return vector_value[id];
	}

  void Promote(Id id){
		//ERROR!
		auto max_elem = queue.extract(*vector_id[id]);
		Item tmp = std::move(max_elem.value());
		++tmp.priority_;	
		typename std::set<Item<T>>::iterator it = queue.insert(std::move(tmp)).first;
		vector_id[id] = it;	
	}
	std::pair<const T&, int> GetMax(){
		auto max_elem = rbegin(queue);
		const T& item = vector_value[max_elem->id_];
		return {item, max_elem->priority_};
	}
	std::pair<T, int> PopMax(){
		auto max_elem = queue.extract(*rbegin(queue));
		Item tmp = max_elem.value();
		T value = std::move(vector_value[tmp.id_]);
		vector_id[tmp.id_] = queue.end();
		return {std::move(value), tmp.priority_};
	}
private:
	std::set<Item<T>> queue;
	std::vector<T> vector_value;
	std::vector<typename std::set<Item<T>>::iterator> vector_id;
};


class StringNonCopyable : public string {
public:
  using string::string;  // Позволяет использовать конструкторы строки
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
  PriorityCollection<StringNonCopyable> strings;
  const auto white_id = strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");

  strings.Promote(yellow_id);
  for (int i = 0; i < 2; ++i) {
    strings.Promote(red_id);
  }
  strings.Promote(yellow_id);
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "yellow");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "white");
    ASSERT_EQUAL(item.second, 0);
  }
}
void TestGetMax(){
	PriorityCollection<StringNonCopyable> strings;
  const auto white_id = strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");

  const auto item = strings.GetMax(); 
  ASSERT_EQUAL(item.first, "red");
  ASSERT_EQUAL(item.second, 0);

}
void TestRange(){
	PriorityCollection<int> strings;
	vector<int> in = {1, 2, 3, 4, 5};
	vector<size_t> out;
	out.resize(5);
	strings.Add(in.begin(), in.end(), out.begin());


  ASSERT_EQUAL(out[0], 0);

}
int main() {
  TestRunner tr;
  RUN_TEST(tr, TestNoCopy);
	RUN_TEST(tr, TestGetMax);
	RUN_TEST(tr, TestRange);
  return 0;
}
