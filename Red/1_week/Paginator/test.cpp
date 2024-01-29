#include "../../test_runner/test_runner.h"

#include <numeric>
#include <iostream>
#include <pthread.h>
#include <vector>
#include <string>
using namespace std;


/* На вход подается вектор:
	 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}
	 Вызывая функцию Paginate от вектора и числа 3 мы получаем 
	 объект класса paginator, который должен выглядеть следующим 
	 образом:
	 {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}} */


/* ИДЕИ 
1) Класс Paginator хранит в себе vector<page>
*/

// Реализуйте шаблон класса Paginator

template <typename Iterator>
class Page{
private:
	Iterator first, last;
public:
	Page(Iterator f, Iterator l) : 
		first(f), last(l) {}

	Iterator begin() const{
		return first;
	}
	
	Iterator end() const{
		return last;
	}

	size_t size() const{
		return last-first;
	}
};

template <typename Iterator>
class Paginator {
private:
 vector<Page<Iterator>> pages;
public:
	Paginator(Iterator begin, Iterator end, size_t page_size){
		size_t size = end - begin;
		while (begin != end){
			if (size <= page_size){
				pages.push_back({begin, end});
				begin = end;
			} else {
				auto page_end = begin + page_size;
				pages.push_back({begin, page_end});
				begin = page_end;
				size = end - begin;
			}
		}
	}

	auto begin() const{
		return pages.begin();
	}

	auto end() const{
		return pages.end();
	}

	size_t size() const{
		return pages.size();
	}

};

template <typename C>
auto Paginate(C& c, size_t page_size) {
  // Реализуйте этот шаблон функции
	return Paginator(c.begin(), c.end(), page_size);
}

void TestPageCounts() {
  vector<int> v(15);

  ASSERT_EQUAL(Paginate(v, 1).size(), v.size());
  ASSERT_EQUAL(Paginate(v, 3).size(), 5u);
  ASSERT_EQUAL(Paginate(v, 5).size(), 3u);
	ASSERT_EQUAL(Paginate(v, 4).size(), 4u);
  ASSERT_EQUAL(Paginate(v, 15).size(), 1u);
  ASSERT_EQUAL(Paginate(v, 150).size(), 1u);
  ASSERT_EQUAL(Paginate(v, 14).size(), 2u);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestPageCounts);

}

