#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
  T* Allocate(){
		T* object;
		if (free.empty()){
			object = new T;
		} else{
			object = free.front();
			free.pop();
		}
		busy.insert(object);

		return object;
	}
  T* TryAllocate(){
		if (free.empty()){
			return nullptr;
		} else {
			return Allocate();	
		}
	}

  void Deallocate(T* object){
		auto it = busy.find(object);
		if (it == busy.end()){
			throw invalid_argument("No object in busy set");
		} else {
			free.push(*it);
			busy.erase(it);
		}
	}

  ~ObjectPool(){
		while (!free.empty()){
			T* object = free.front();
			free.pop();
			delete object;
		}
	  for (auto x : busy) {
    	delete x;
		}
	}
private:
  // Добавьте сюда поля
	queue<T*> free;
	set<T*> busy;

};

void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}
