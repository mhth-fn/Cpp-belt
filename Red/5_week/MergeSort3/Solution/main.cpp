#include "../../test_runner/test_runner.h"
#include <algorithm>
#include <iterator>
#include <memory>
#include <vector>

using namespace std;


template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end){

	if (range_end - range_begin < 2){
		return;
	}

	vector<typename RandomIt::value_type> elements(make_move_iterator(range_begin),
																						make_move_iterator(range_end));
	
	auto first_part = begin(elements) + elements.size() / 3;
	auto second_part = begin(elements) + 2 * elements.size() / 3;

	MergeSort(begin(elements), first_part);
	MergeSort(first_part, second_part);
	MergeSort(second_part, end(elements));

	vector<typename RandomIt::value_type> tmp;
	merge(make_move_iterator(begin(elements)), make_move_iterator(first_part),
			make_move_iterator(first_part), make_move_iterator(second_part), back_inserter(tmp));
	merge(make_move_iterator(begin(tmp)), make_move_iterator(end(tmp)),
			make_move_iterator(second_part), make_move_iterator(end(elements)), range_begin);
}
 
template <typename RandomIt>
vector<typename RandomIt::value_type> MergeSortCopy(RandomIt range_begin, RandomIt range_end) {
  // Напишите реализацию функции,
  // не копируя сортируемые элементы
	if (range_end - range_begin < 2){
		return {};
	}

	vector<typename RandomIt::value_type> tmp(range_begin,
																						range_end);
	size_t part = (range_end - range_begin) / 3;	

	auto res1 = MergeSortCopy(begin(tmp), begin(tmp) + part);
	auto res2 =	MergeSortCopy(begin(tmp) + part, begin(tmp) + 2 * part);
	auto res3 = MergeSortCopy(begin(tmp) + 2 * part, begin(tmp) + 3 * part);
	
	vector<typename RandomIt::value_type> res;
	merge(begin(res1), end(res1), begin(res2), end(res2), back_inserter(res));	
	vector<typename RandomIt::value_type> res10;
	merge(begin(res), end(res), begin(res3), end(res3), back_inserter(res10));

	return res10;
}

void TestIntVector() {
  vector<int> numbers = {1, 3, 7, 4, 2, 9, 6 , 8, 4};
  MergeSort(begin(numbers), end(numbers));
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

void TestIntVectorManyCopy() {
  vector<int> numbers = {3 , 2, 1};
  auto sorted = MergeSortCopy(begin(numbers), end(numbers));
  ASSERT(is_sorted(begin(sorted), end(sorted)));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  return 0;
}
