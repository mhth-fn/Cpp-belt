#include "deque.h"
#include "../../test_runner/test_runner.h"
#include <iostream>
#include <vector>

void TestAt(){
	Deque<int> test;

	bool except = true;
	try{
		test.At(1);
	} catch (out_of_range e){
		except = false;
	}
	if (except){
		ASSERT(0);
	}

	test.PushFront(0);
	ASSERT_EQUAL(test.At(0), 0);
	test.PushBack(1);
	ASSERT_EQUAL(test.At(1), 1);
	test.PushFront(-1);
	test.PushBack(2);
	ASSERT_EQUAL(test.At(0), -1);
	ASSERT_EQUAL(test.At(1), 0);
	ASSERT_EQUAL(test.At(2), 1);
	ASSERT_EQUAL(test.At(3), 2);
}

void TestOperator(){
	Deque<int> test;
	test.PushFront(5);
	ASSERT_EQUAL(test[0], 5);
	test[0] = 10;
	ASSERT_EQUAL(test[0], 10);
	test.PushBack(5);
	ASSERT_EQUAL(test[0], 10);
	test[1] = 6;
	ASSERT_EQUAL(test[1], 6);
}

void TestPushAndSize(){
	Deque<int> test;
	
	ASSERT(test.Empty());
	ASSERT_EQUAL(test.Size(), 0);
	test.PushFront(1);
	ASSERT_EQUAL(test.Front(), 1);
	test.PushBack(2);
	ASSERT_EQUAL(test.Back(), 2);
	test.PushFront(0);
	ASSERT_EQUAL(test.Front(), 0);
	ASSERT_EQUAL(test.Size(), 3);
	test.PushBack(3);
	ASSERT_EQUAL(test.Back(), 3);
	ASSERT_EQUAL(test.Size(), 4);
	ASSERT(!test.Empty());
}

void TestAll(){
	TestRunner tr;
	RUN_TEST(tr, TestPushAndSize);
	RUN_TEST(tr, TestAt);
	RUN_TEST(tr, TestOperator);
}

int main(){
	TestAll();
	return 0;
}
