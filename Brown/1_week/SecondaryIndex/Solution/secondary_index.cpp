#include "test_runner.h"
#include "profile.h"

#include <iostream>
#include <unordered_map>
#include <list>
#include <map>
#include <string_view>
#include <string>
#include <tuple>
#include <utility>
using namespace std;

struct Record {
  string id;
  string title;
  string user;
  int timestamp;
  int karma;
};

// Реализуйте этот класс
class Database {
public:
  bool Put(Record record){
		if (by_id.find(record.id) == end(by_id)){ //1
			auto el = base.insert(end(base), std::move(record)); //1
			const Record& tmp = *el; //1
			auto time_it = by_time.insert({tmp.timestamp, &tmp}); //logN
			auto user_it = by_user.insert({string_view(tmp.user), &tmp}); //logN
			auto karma_it = by_karma.insert({tmp.karma, &tmp}); //logN
			Bonds bond{time_it, karma_it, user_it, el}; //1
			by_id.insert({el->id, std::move(bond)}); //LogN
			
			return true;
		}
		return false;
	} //4*LogN
  const Record* GetById(const string& id) const{
		auto el = by_id.find(id);
		if (el != end(by_id)){
			return &*el->second.base;	
		}
		return nullptr;
	}//1
  bool Erase(const string& id){
		auto el = by_id.find(id);
		if (el != end(by_id)){
			by_user.erase(el->second.user);
			by_karma.erase(el->second.karma);
			by_time.erase(el->second.time);
			base.erase(el->second.base);
			by_id.erase(el);

			return true;
		}//1
		return false;
	}

  template <typename Callback>
  void RangeByTimestamp(int low, int high, Callback callback) const{
		for (auto it = by_time.lower_bound(low); it != by_time.upper_bound(high); ++it){
				if(!callback(*it->second)) break;
		}
	}

  template <typename Callback>
  void RangeByKarma(int low, int high, Callback callback) const{
		for (auto it = by_karma.lower_bound(low); it != by_karma.upper_bound(high); ++it){
				if(!callback(*it->second)) break;
		}
	}

  template <typename Callback>
  void AllByUser(const string& user, Callback callback) const{
		for (auto it = by_user.lower_bound(user); it != by_user.upper_bound(user)
				&& it != end(by_user); ++it){
				if(!callback(*it->second)) break;
		}
	}

private:
	struct Bonds{
		multimap<int, const Record*>::iterator time;
		multimap<int, const Record*>::iterator karma;
		multimap<string_view, const Record*>::iterator user;
		list<Record>::iterator base;	
	};

	list<Record> base;	
	unordered_map<string, Bonds> by_id;
	multimap<int, const Record*> by_time;
	multimap<int, const Record*> by_karma;
	multimap<string_view, const Record*> by_user;

};

void TestRangeBoundaries() {
  const int good_karma = 1000;
  const int bad_karma = -10;

  Database db;
  db.Put({"id1", "Hello there", "master", 1536107260, good_karma});
  db.Put({"id2", "O>>-<", "general2", 1536107260, bad_karma});

  int count = 0;
  db.RangeByKarma(bad_karma, good_karma, [&count](const Record&) {
    ++count;
    return true;
  });

  ASSERT_EQUAL(2, count);
}

void TestSameUser() {
  Database db;
  db.Put({"id1", "Don't sell", "master", 1536107260, 1000});
  db.Put({"id2", "Rethink life", "master", 1536107260, 2000});

  int count = 0;
  db.AllByUser("master", [&count](const Record&) {
    ++count;
    return true;
  });

  ASSERT_EQUAL(2, count);
}

void TestReplacement() {
  const string final_body = "Feeling sad";

  Database db;
  db.Put({"id", "Have a hand", "not-master", 1536107260, 10});
  db.Erase("id");
  db.Put({"id", final_body, "not-master", 1536107260, -10});

  auto record = db.GetById("id");
  ASSERT(record != nullptr);
  ASSERT_EQUAL(final_body, record->title);
}

void MyTest(){
	Database db;
	{LOG_DURATION("PUT")
	for (size_t i = 0; i != 100000; ++i){
		const int j = i;
		db.Put({to_string(i % 10000), to_string(i % 10000), to_string(i), j, j});
	}
	}

	{LOG_DURATION("GET")
	for (size_t i = 0; i != 100000; ++i){
		db.GetById(to_string(i));
	}
	}
	{LOG_DURATION("ERASE")
	for (size_t i = 0; i != 100000; ++i){
		db.Erase(to_string(i));
	}
	}

}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestRangeBoundaries);
  RUN_TEST(tr, TestSameUser);
  RUN_TEST(tr, TestReplacement);
	RUN_TEST(tr, MyTest);
  return 0;
}
