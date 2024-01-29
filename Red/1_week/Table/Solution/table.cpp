#include "test_runner.h"
#include <utility>
#include <vector>

using namespace std;

// Реализуйте здесь шаблонный класс Table
template <typename T>
class Table{
public:
	Table(size_t rows, size_t cols){
		Resize(rows, cols);
	}
	
	pair<size_t, size_t> Size() const{
		return {rows_, cols_};
	}
	
	void Resize(size_t rows, size_t cols){
		rows_ = rows;
		cols_ = cols;
		table.resize(rows);
		for (auto& x : table){
			x.resize(cols);
		};
	}
	
	vector<T>& operator[](size_t rows){
		return table[rows];	
	}

	vector<T>& operator[](size_t rows) const{
		return table.at(rows);
	}

private:
	vector<vector<T>> table;
	size_t rows_, cols_;
};

void TestTable() {
  Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
  t[0][0] = 42;
  ASSERT_EQUAL(t[0][0], 42);
  t.Resize(3, 4);
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}
