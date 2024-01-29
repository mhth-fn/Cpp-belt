#include "test_runner.h"
#include "profile.h"

#include <forward_list>
#include <unordered_set>
#include <iterator>
#include <cmath>
#include <algorithm>

using namespace std;

template <typename Type, typename Hasher>
class HashSet {
public:

  using BucketList = forward_list<Type>;

  explicit HashSet(
      size_t num_buckets,
      const Hasher& hasher = {}
  ) : hasher_(hasher){
		table.resize(num_buckets);
	}

  void Add(const Type& value){ //N
		auto it = find(BucketBegin(value), BucketEnd(value), value);
		if (it == BucketEnd(value)){
			table[Bucket(value)].push_front(value);
		}
	}

  bool Has(const Type& value) const{ //N 
		auto it = find(BucketBegin(value), BucketEnd(value), value);
		return it != BucketEnd(value);
	}
  void Erase(const Type& value){ //Nkkjj
			table[Bucket(value)].remove(value);
	}
  const BucketList& GetBucket(const Type& value) const{//1
		return table[Bucket(value)];
	}
	
	auto BucketBegin(const Type& value) const{
		return table[Bucket(value)].begin();
	}

	auto BucketEnd(const Type& value) const{
		return table[Bucket(value)].end();
	}
private:
	vector<BucketList> table;
	Hasher hasher_;

	size_t Bucket(const Type& value) const{
		return hasher_(value) % table.size(); 
	}
};

struct IntHasher {
  size_t operator()(int value) const {
    // Это реальная хеш-функция из libc++, libstdc++.
    // Чтобы она работала хорошо, std::unordered_map
    // использует простые числа для числа бакетов
    return value;
  }
};

struct TestValue {
  int value;

  bool operator==(TestValue other) const {
    return value / 2 == other.value / 2;
  }
};

struct TestValueHasher {
  size_t operator()(TestValue value) const {
    return value.value / 2;
  }
};

void TestSmoke() {
  HashSet<int, IntHasher> hash_set(2);
  hash_set.Add(3);
  hash_set.Add(4);

  ASSERT(hash_set.Has(3));
  ASSERT(hash_set.Has(4));
  ASSERT(!hash_set.Has(5));

  hash_set.Erase(3);

  ASSERT(!hash_set.Has(3));
  ASSERT(hash_set.Has(4));
  ASSERT(!hash_set.Has(5));

  hash_set.Add(3);
  hash_set.Add(5);

  ASSERT(hash_set.Has(3));
  ASSERT(hash_set.Has(4));
  ASSERT(hash_set.Has(5));
}

void TestEmpty() {
  HashSet<int, IntHasher> hash_set(10);
  for (int value = 0; value < 10000; ++value) {
    ASSERT(!hash_set.Has(value));
  }
}

void TestIdempotency() {
  HashSet<int, IntHasher> hash_set(10);
  hash_set.Add(5);
  ASSERT(hash_set.Has(5));
  hash_set.Add(5);
  ASSERT(hash_set.Has(5));
  hash_set.Erase(5);
  ASSERT(!hash_set.Has(5));
  hash_set.Erase(5);
  ASSERT(!hash_set.Has(5));
}

void TestEquivalence() {
  HashSet<TestValue, TestValueHasher> hash_set(10);
  hash_set.Add(TestValue{2});
  hash_set.Add(TestValue{3});

  ASSERT(hash_set.Has(TestValue{2}));
  ASSERT(hash_set.Has(TestValue{3}));

  const auto& bucket = hash_set.GetBucket(TestValue{2});
  const auto& three_bucket = hash_set.GetBucket(TestValue{3});
  ASSERT_EQUAL(&bucket, &three_bucket);

  ASSERT_EQUAL(1, distance(begin(bucket), end(bucket)));
  ASSERT_EQUAL(2, bucket.front().value);
}

void TestVsUnorderedSet(){
  HashSet<int, IntHasher> hash_set(239);
	unordered_set<int> un_set;

	size_t N = 20000;
	{LOG_DURATION("Hash set add")
		for (size_t i = 0; i != N; ++i){
			hash_set.Add(i);
		}
	}
	{LOG_DURATION("Unordered set add")
		for (size_t i = 0; i != N; ++i){
			un_set.insert(i);
		}
	}
	{LOG_DURATION("Hash set erase")
		for (size_t i = 0; i != N; ++i){
			hash_set.Erase(i);
		}
	}
	{LOG_DURATION("Unordered set erase")
		for (size_t i = 0; i != N; ++i){
			un_set.erase(i);
		}
	}
	{LOG_DURATION("Hash set has")
		for (size_t i = 0; i != N; ++i){
			hash_set.Has(i);
		}
	}
	{LOG_DURATION("Unordered set has")
		for (size_t i = 0; i != N; ++i){
			un_set.count(i);
		}
	}
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSmoke);
  RUN_TEST(tr, TestEmpty);
  RUN_TEST(tr, TestIdempotency);
  RUN_TEST(tr, TestEquivalence);
	RUN_TEST(tr, TestVsUnorderedSet);
  return 0;
}
