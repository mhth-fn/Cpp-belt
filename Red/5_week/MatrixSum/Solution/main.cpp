#include "test_runner.h"
#include <numeric>
#include <vector>
#include <future>
using namespace std;


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
		while (begin != end){
			size_t size = end - begin;
			if (size <= page_size){
				pages.push_back({begin, end});
				begin = end;
			} else {
				auto page_end = begin + page_size;
				pages.push_back({begin, page_end});
				begin = page_end;
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

template <typename C>
int64_t GetPartitionMatrixSum(const C& part_matrix){
	int64_t result = 0;
	for (const auto& row : part_matrix){
		result += std::accumulate(row.begin(), row.end(), 0);
	}
	return result;
	
}

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
  // Реализуйте эту функцию
	vector<future<int64_t>> futures;
	futures.reserve(4);
	int64_t result = 0;
	for (const auto& part_matrix : Paginate(matrix, 2000)){
		futures.push_back(async([&part_matrix]{
					return GetPartitionMatrixSum(part_matrix);
				}));
	}
	for (auto& part_sum : futures){
		result += part_sum.get();
	}
	return result;
}

void TestCalculateMatrixSum() {
  const vector<vector<int>> matrix = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
  };
  ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
	vector<vector<int>> matrix1(9000);
	for (auto& x : matrix1){
		x.resize(9000, 1);
	}
	ASSERT_EQUAL(CalculateMatrixSum(matrix1), 81000000);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestCalculateMatrixSum);
}
