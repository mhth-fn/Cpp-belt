#include "profile.h"
#include "test_runner.h"

#include <algorithm>
#include <mutex>
#include <numeric>
#include <future>
#include <system_error>
#include <vector>
#include <string>
#include <random>
using namespace std;

template <typename K, typename V>
class ConcurrentMap {
public:
  static_assert(is_integral_v<K>, "ConcurrentMap supports only integer keys");

	struct Access {
		lock_guard<mutex> g;
    V& ref_to_value;
	};
	
  explicit ConcurrentMap(size_t bucket_count) : 
		submaps(bucket_count){}

  Access operator[](const K& key){
		size_t index = key % submaps.size();
		return {lock_guard{submaps[index].first}, 
			submaps[index].second[key]};
	}

  map<K, V> BuildOrdinaryMap(){
		map<K, V> result;
		for (auto& item : submaps){
			lock_guard<mutex> g(item.first);
			result.insert(item.second.begin(), item.second.end());
		}
		return std::move(result);
	}
private:
	vector<pair<mutex, map<K,V>>> submaps;
};

void RunConcurrentUpdates(
    ConcurrentMap<int, int>& cm, size_t thread_count, int key_count
) {
  auto kernel = [&cm, key_count](int seed) {
    vector<int> updates(key_count);
    iota(begin(updates), end(updates), -key_count / 2);
    shuffle(begin(updates), end(updates), default_random_engine(seed));

    for (int i = 0; i < 2; ++i) {
      for (auto key : updates) {
        cm[key].ref_to_value++;
      }
    }
  };

  vector<future<void>> futures;
  for (size_t i = 0; i < thread_count; ++i) {
    futures.push_back(async(kernel, i));
  }
}

void TestConcurrentUpdate() {
  const size_t thread_count = 3;
  const size_t key_count = 50000;

  ConcurrentMap<int, int> cm(thread_count);
  RunConcurrentUpdates(cm, thread_count, key_count);

  const auto result = cm.BuildOrdinaryMap();
  ASSERT_EQUAL(result.size(), key_count);
  for (auto& [k, v] : result) {
    AssertEqual(v, 6, "Key = " + to_string(k));
  }
}

void TestReadAndWrite() {
  ConcurrentMap<size_t, string> cm(5);

  auto updater = [&cm] {
    for (size_t i = 0; i < 50000; ++i) {
      cm[i].ref_to_value += 'a';
    }
  };
  auto reader = [&cm] {
    vector<string> result(50000);
    for (size_t i = 0; i < result.size(); ++i) {
      result[i] = cm[i].ref_to_value;
    }
    return result;
  };

  auto u1 = async(updater);
  auto r1 = async(reader);
  auto u2 = async(updater);
  auto r2 = async(reader);

  u1.get();
  u2.get();

  for (auto f : {&r1, &r2}) {
    auto result = f->get();
    ASSERT(all_of(result.begin(), result.end(), [](const string& s) {
      return s.empty() || s == "a" || s == "aa";
    }));
  }
}

void TestSpeedup() {
  {
    ConcurrentMap<int, int> single_lock(1);

    LOG_DURATION("Single lock");
    RunConcurrentUpdates(single_lock, 4, 50000);
  }
  {
    ConcurrentMap<int, int> many_locks(1000);

    LOG_DURATION("100 locks");
    RunConcurrentUpdates(many_locks, 4, 50000);
  }
}

void TestWrite(){
	{LOG_DURATION("TestWrite")
		ConcurrentMap<int, int> cm(3);
		auto cmfill = [&cm](){
			for (int i = 0; i != 100000; ++i){
					cm[i].ref_to_value = i;
			}
		};

		auto fthread = async(cmfill);
		auto sthread = async(cmfill);
		auto tthread = async(cmfill);
	
		fthread.get();
		sthread.get();
		tthread.get();

		ASSERT_EQUAL(cm[10].ref_to_value, 10);
	}
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestConcurrentUpdate);
  RUN_TEST(tr, TestReadAndWrite);
  RUN_TEST(tr, TestSpeedup);
	RUN_TEST(tr, TestWrite);
}
