#include <iomanip>
#include <map>
#include <iostream>
#include <vector>
#include <utility>
#include <set>
using namespace std;

class ReadingManager {
public:
  ReadingManager()
      : user_page_counts_(MAX_USER_COUNT_ + 1, 0),
				user_count(0u) {}
	void NewRead(int user_id, int page_count){
		if (user_page_counts_[user_id] == 0){
			++user_count;
		} else {
			page_for_users[user_page_counts_[user_id]].erase(user_id);
		}
		NewAddUser(user_id, page_count);
		user_page_counts_[user_id] = page_count; 
	}
	double NewCheer(int user_id) const{
		if (user_page_counts_[user_id] == 0) {
      return 0; //1
    }
    if (user_count == 1) {
      return 1; //1
    }
		auto it = page_for_users.lower_bound(user_page_counts_[user_id]);
		int position = it->second.size() - 1;
		++it;
		for (; it != page_for_users.end(); ++it){ //1000 max
			auto test = it->first;
			position += it->second.size();
		}
		return (user_count - 1 - position) * 1.0 / (user_count - 1);


	}
private:
  // Статическое поле не принадлежит какому-то конкретному
  // объекту класса. По сути это глобальная переменная,
  // в данном случае константная.
  // Будь она публичной, к ней можно было бы обратиться снаружи
  // следующим образом: ReadingManager::MAX_USER_COUNT.
  static const int MAX_USER_COUNT_ = 100'000;
	map<int, set<int>> page_for_users;
	size_t user_count;

  vector<int> user_page_counts_;

	void NewAddUser(int user_id, int page_count){
		page_for_users[page_count].insert(user_id);
	}


};


int main() {
  // Для ускорения чтения данных отключается синхронизация
  // cin и cout с stdio,
  // а также выполняется отвязка cin от cout
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ReadingManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) { //Q
    string query_type;
    cin >> query_type;
    int user_id;
    cin >> user_id;

    if (query_type == "READ") {
      int page_count;
      cin >> page_count;
      manager.NewRead(user_id, page_count);
    } else if (query_type == "CHEER") {
      cout << setprecision(6) << manager.NewCheer(user_id) << "\n";
    }
  } //Q^2
  return 0;
}