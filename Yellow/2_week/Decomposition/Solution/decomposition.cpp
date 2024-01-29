#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

using schedule_t = map<string, vector<string>>;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
  // Реализуйте эту функцию
	string buf;
	is >> buf;
	if (buf == "NEW_BUS"){
		q.type = QueryType::NewBus;
		is >> q.bus;
		size_t stop_count;
		is >> stop_count;
		q.stops.resize(stop_count);
		for (auto& stop : q.stops){
			cin >> stop;
		}
	} else if (buf == "BUSES_FOR_STOP"){
		cin >> q.stop;
		q.type = QueryType::BusesForStop;
	} else if (buf == "STOPS_FOR_BUS"){
		q.type = QueryType::StopsForBus;
		cin >> q.bus;
	}	else if (buf == "ALL_BUSES"){
		q.type = QueryType::AllBuses;
	}
	return is;
}

struct BusesForStopResponse {
  // Наполните полями эту структуру
	vector<string> BusesForStop;

};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
  // Реализуйте эту функцию
	 if (r.BusesForStop.size() == 0) {
        os << "No stop";
      } else {
        for (const string& bus : r.BusesForStop) {
          os << bus << " ";
        }
      }
  return os;
}


struct StopsForBusResponse {
  string bus;
  vector<pair<string, vector<string>>> stops_for_buses;
};



ostream& operator << (ostream& os, const StopsForBusResponse& r) {
  if (r.stops_for_buses.empty()) {
    os << "No bus";
  } else {
    bool first = true;
    for (const auto& stop_and_buses : r.stops_for_buses) {
      if (!first) {
        os << endl;
      }
      first = false;
      os << "Stop " << stop_and_buses.first << ":";
      if (stop_and_buses.second.size() == 1) {
        os << " no interchange";
      } else {
        for (const auto& bus : stop_and_buses.second) {
          if (bus != r.bus) {
            os << " " << bus;
          }
        }
      }
    }
  }
  return os;
}

struct AllBusesResponse {
  // Наполните полями эту структуру
	schedule_t AllBuses;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
  // Реализуйте эту функцию
	if (r.AllBuses.empty()){
		return os << "No buses";
	}
	bool is_first = true;
	for (const auto& bus_item : r.AllBuses) {
		  if (!is_first){
			  os << endl;
		  }
		  is_first = false;
          os << "Bus " << bus_item.first << ": ";
          for (const string& stop : bus_item.second) {
            os << stop << " ";
          }
        }
	
  return os;
}

class BusManager {
	schedule_t buses_to_stops;
	schedule_t stops_to_buses;
public:
  void AddBus(const string& bus, const vector<string>& stops) {
    // Реализуйте этот метод
	 buses_to_stops[bus] = stops;
	 for (auto& stop : stops){
		 stops_to_buses[stop].push_back(bus);
	 }
  }

  BusesForStopResponse GetBusesForStop(const string& stop) const {
    // Реализуйте этот метод
	  if (stops_to_buses.count(stop) == 0){
		  return {};
	  }
	  return {stops_to_buses.at(stop)};
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const {
    // Реализуйте этот метод
    vector<pair<string, vector<string>>> result;

    if (buses_to_stops.count(bus) > 0) {
      for (const auto& stop : buses_to_stops.at(bus)) {
        result.push_back(make_pair(stop, stops_to_buses.at(stop)));
      }
    }
    return StopsForBusResponse{bus, result};

  }

  AllBusesResponse GetAllBuses() const {
    // Реализуйте этот метод
	return {buses_to_stops};
  }
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }

  return 0;
}
