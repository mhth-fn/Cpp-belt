#include <iostream>
#include <algorithm>
#include <deque>
#include <set>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <cstdint>
using namespace std;

//< (Q^2)
struct Event{
	int64_t time;
	string hotel_name;
	uint64_t client_id;
	int room_count;
};

class Booking{
public:

	void Book(int64_t	time, string hotel_name, uint64_t clien_id, int room_count){
		Event event{time, hotel_name, clien_id, room_count};
		Update(event);
		rooms_in_hotels[hotel_name] += room_count;
		booker[hotel_name][clien_id] += room_count;

	}

	int Clients(string hotel_name){ //1
		return booker[hotel_name].size();
	}

	int Rooms(string hotel_name){ //1
		return rooms_in_hotels[hotel_name];
	}

private:
	map<uint64_t, int> id_count;
	map<string, map<uint64_t, int>> booker;
	map<string, uint64_t> rooms_in_hotels;
	deque<Event> events_;

	void Update(const Event& event){
		events_.push_back(event);
		while (abs(events_.back().time - events_.front().time) >= 86400){
			const Event& old_event = events_.front();
			rooms_in_hotels[old_event.hotel_name] -= old_event.room_count;
			booker[old_event.hotel_name][old_event.client_id] -= old_event.room_count;
			if (booker[old_event.hotel_name][old_event.client_id] == 0){
				booker[old_event.hotel_name].erase(old_event.client_id);
			}
			events_.pop_front();

		}
	}
};

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	Booking hotels;
	int query_count;
	std::cin >> query_count;
	
	
	for (int query_id = 0; query_id != query_count; ++query_id){
		string query_type;
		cin >> query_type;
		
		int64_t time;
		int client_id, room_count;
		string hotel_name;
		if (query_type == "BOOK"){
			cin >> time >> hotel_name >> client_id >> room_count;	
			hotels.Book(time, hotel_name, client_id, room_count);
		} else if (query_type == "CLIENTS"){
			cin >> hotel_name;
			std::cout << hotels.Clients(hotel_name) << '\n';
		} else if (query_type == "ROOMS"){
			cin >> hotel_name;
			std::cout << hotels.Rooms(hotel_name) << '\n';
		}
	}

	return 0;
}
