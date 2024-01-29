#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <optional>
#include <cmath>
#include <memory>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
#include <set>
#include <iomanip>

double PI = 3.1415926535;
double R = 6371000.0;
      
using namespace std;


std::pair<std::string_view, std::optional<std::string_view>> 
                                SplitTwoStrict(std::string_view s, std::string_view delimiter = " ") {
  const size_t pos = s.find(delimiter);
  if (pos == s.npos) {
    return {s, std::nullopt};
  } else {
    return {s.substr(0, pos), s.substr(pos + delimiter.length())};
  }
}

std::pair<std::string_view, std::string_view> 
                                SplitTwo(std::string_view s, std::string_view delimiter = " ") {
  const auto [lhs, rhs_opt] = SplitTwoStrict(s, delimiter);
  return {lhs, rhs_opt.value_or("")};
}

std::string_view ReadToken(std::string_view& s, std::string_view delimiter = " ") {
  const auto [lhs, rhs] = SplitTwo(s, delimiter);
  s = rhs;
  return lhs;
}

template <typename Number>
Number ReadNumberOnLine(istream& stream) {
  Number number;
  stream >> number;
  string dummy;
  getline(stream, dummy);
  return number;
}

int ConvertToInt(std::string_view str) {
  size_t pos;
  const int result = std::stoi(std::string(str), &pos);
  if (pos != str.length()) {
    std::stringstream error;
    error << "string " << str << " contains " << (str.length() - pos) << " trailing chars";
    throw std::invalid_argument(error.str());
  }
  return result;
}

struct Coordinates{
    double latitude;
    double longitude;
};

struct Route{
    std::vector<std::string> stops_;
    bool is_circled = true;
};

double Spacing(const Coordinates& lhs, const Coordinates& rhs){
  double lon_diff = lhs.longitude > rhs.longitude ? lhs.longitude - rhs.longitude : rhs.longitude - lhs.longitude;
  return acos(sin(lhs.latitude) * sin(rhs.latitude) +
  cos(lhs.latitude) * cos(rhs.latitude) * cos(lon_diff)) * R;
}
class Response;
using ResponseHolder = unique_ptr<Response>;

class Response{
public:
    virtual string ToString() = 0;
};

class BusResponse : public Response{
public:
    struct Struct{
        string Bus = "";
        int stops = 0;
        int unique_stops = 0;
        double length = 0;
        double real_length = 0;
  };
    BusResponse(Struct& response) :
    response_(move(response)){}

    string ToString(){
        ostringstream out;
        if (response_.length != 0){
            out << "Bus " << response_.Bus << ": " << response_.stops << " stops on route, "
            << response_.unique_stops << " unique stops, " << fixed 
            << std::setprecision(6) << response_.real_length << " route length, "
            << response_.real_length / response_.length << " curvature";
        } else {
            out << "Bus " << response_.Bus << ": not found";
        }
        return out.str();
    }
    Struct response_;
};

class StopResponse : public Response{
public:
    StopResponse(string_view stop)
    : stop_(stop), is_find(false) {}

    StopResponse(string_view stop, set<string_view> buses)
    : stop_(stop), buses_(buses), is_find(true) {}

    string ToString(){
        ostringstream out;
        out << "Stop " << stop_ << ": ";
        if (is_find){
            if (buses_.size() != 0){
               out << "buses";
               for(const auto& bus : buses_){
                    out << " " << bus;
               }
            } else {
                out << "no buses";
            }
        } else {
            out << "not found";
        }
        return out.str();
    }

    string_view stop_;
    set<string_view> buses_;
    bool is_find; 
};

using RouteBase = std::unordered_map<std::string, Route>;
using StopBase = std::unordered_map<std::string, Coordinates>;
using StopToBuses = std::unordered_map<std::string_view, set<string_view>>;
class Init;
using InitHolder = unique_ptr<Init>;

class RouteCatalogBuilder;

class Init{
public:
    enum class Type{
        BUS,
        STOP
    };

    virtual void Process(RouteCatalogBuilder& builder) = 0;
    virtual void ParseFrom(std::string_view in) = 0;
    static InitHolder Create(Type type);

    const static unordered_map<string_view, Type> STR_TO_ENUM_TYPE; 
};

const unordered_map<string_view, Init::Type> Init::STR_TO_ENUM_TYPE = {
    {"Bus", Type::BUS},
    {"Stop", Type::STOP}
};

class RouteCatalog{
public:
    friend class RouteCatalogBuilder;
    friend class BusRequest;

    const RouteBase& GetRoutes() const{
        return routebase_;
    }

    const StopBase& GetStops() const{
        return stopbase_;
    }

    const StopToBuses& GetStopToBuses() const{
        return stop_to_buses_;
    }

    const auto& GetStopsDistance() const{
        return stops_distance_;
    }
private:
    RouteCatalog(RouteBase routebase, StopBase stopbase,  unordered_map<string, unordered_map<string, double>> stops_distance) :
    routebase_(move(routebase)), stopbase_(move(stopbase)), stops_distance_(move(stops_distance)){
        for (const auto& stop : stopbase_){
            stop_to_buses_[stop.first];
        }
        for (auto& item : routebase_){
            for (const auto& stop : item.second.stops_){
                stop_to_buses_[stop].insert(item.first);
            }
            if (item.second.is_circled){
                std::vector<string> tmp(item.second.stops_.rbegin() + 1, item.second.stops_.rend());
                for (auto& el : tmp){
                    item.second.stops_.push_back(el);
                }
            }
        }
    }

    RouteBase routebase_;
    StopBase stopbase_;
    StopToBuses stop_to_buses_;
    unordered_map<string, unordered_map<string, double>> stops_distance_;
};

class RouteCatalogBuilder{
private:
public:
    friend class RouteInit;
    friend class StopInit;

    RouteCatalogBuilder(const std::vector<std::unique_ptr<Init>> init_pull){
        size_t request_count = init_pull.size();
        for (size_t i = 0; i != request_count; ++i){
            init_pull[i]->Process(*this);
        }
    }
    RouteCatalog Build(){
        return RouteCatalog{move(routebase_temp), move(stopbase_temp), move(stops_distance)};
    }
private:
    RouteBase routebase_temp;
    StopBase stopbase_temp;
    unordered_map<string, unordered_map<string, double>> stops_distance;
};


class Request;
using RequestHolder = unique_ptr<Request>;

class Request{
public:
    enum class Type{
        BUS,
        STOP
    };
    
    virtual ResponseHolder Process(const RouteCatalog& rc) = 0;
    virtual void ParseFrom(std::string_view in) = 0;
    static RequestHolder Create(Type type);
    const static unordered_map<string_view, Type> STR_TO_ENUM_TYPE; 
};

const unordered_map<string_view, Request::Type> Request::STR_TO_ENUM_TYPE{
    {"Bus", Request::Type::BUS},
    {"Stop", Request::Type::STOP}
};

class BusRequest : public Request{

    ResponseHolder Process(const RouteCatalog& rc) override{
        auto it = rc.routebase_.find(route);
        BusResponse::Struct res;
        res.Bus = route;
        if (it != end(rc.routebase_)){
            const auto& rb = it->second.stops_;
            res.stops = rb.size();
            res.unique_stops = set(rb.begin(), rb.end()).size();
            string_view lhs, rhs;
            for (const auto& item : rb){
                if (lhs.empty()){
                    lhs = item;
                } else {
                    rhs = item;
                    res.real_length += rc.GetStopsDistance().at(string(lhs)).at(string(rhs));
                    res.length += Spacing(rc.stopbase_.at(string(lhs)), rc.stopbase_.at(string(rhs)));
                    lhs = item;
                }
            }
            // if (it->second.is_circled){
            //     res.real_length += res.real_length;
            //     res.length += res.length;
            //     res.stops = res.stops * 2 - 1;
            // }
        }
        return make_unique<BusResponse>(res);
    }

    void ParseFrom(std::string_view in) override{
        route = string(in);
    }
    
    string route;
};

class StopRequest : public Request{

    ResponseHolder Process(const RouteCatalog& rc) override{
        if (auto it = rc.GetStopToBuses().find(stop); it != end(rc.GetStopToBuses())){
            return make_unique<StopResponse>(stop, it->second);
        } else{
            return make_unique<StopResponse>(stop);
        }
    }
    void ParseFrom(std::string_view in) override{
        stop = string(in);
    }

    string stop; 
};

RequestHolder Request::Create(Request::Type type) {
  switch (type) {
    case Request::Type::BUS:
        return make_unique<BusRequest>();
    case Request::Type::STOP:
        return make_unique<StopRequest>();
    default:
      return nullptr;
  }
}

class RouteInit : public Init{
public:
    RouteInit(){};
    void Process(RouteCatalogBuilder& builder) override{
        builder.routebase_temp.insert(move(route));
    }
    void ParseFrom(std::string_view in) override{
      string routename = string(ReadToken(in, ": "));
      Route res;
      string delimiter = " - ";
      if (in.find(">") != string_view::npos){
        delimiter[1] = '>';
        res.is_circled = false;
      }
      while (!in.empty()){
        res.stops_.push_back(string(ReadToken(in, delimiter)));
      }
      route = {routename, move(res)};
    }

    std::pair<string, Route> route;
};

class StopInit : public Init{
public:
    StopInit(){};
    void Process(RouteCatalogBuilder& builder) override{
        for (const auto& item : distance_to_stops){
            builder.stops_distance[stop.first][item.first] = item.second;
        }
        for (const auto& item : distance_to_stops){
            if(auto it = builder.stops_distance.find(item.first); it == end(builder.stops_distance)
                        || (it->second.find(stop.first)) == (it->second.end())){
                            builder.stops_distance[item.first][stop.first] = item.second;
            }
        }
        builder.stopbase_temp.insert(move(stop));
    }
    void ParseFrom(std::string_view in) override{
      string stopname = string(ReadToken(in, ": "));
      Coordinates cord = {stod(string(ReadToken(in))) * M_PI / 180.0, stod(string(ReadToken(in))) * M_PI / 180.0};
      stop = {move(stopname), cord};
      while (!in.empty()){
        double distance = stod(string(ReadToken(in, "m to ")));
        distance_to_stops[string(ReadToken(in, ", "))] = distance;
      }
    }
    unordered_map<string, double> distance_to_stops;
    pair <string, Coordinates> stop;
};

InitHolder Init::Create(Init::Type type){
    switch (type)
    {
        case Init::Type::BUS: 
            return make_unique<RouteInit>();
        case Init::Type::STOP:
            return make_unique<StopInit>(); 
        default:
            break;
    }
    return {};
}

template <typename EnumType>
std::optional<EnumType> ConvertEnumTypeFromString(std::string_view type_str,
                                                                const unordered_map<string_view, EnumType> str_to_enum_type) {
    if (const auto it = str_to_enum_type.find(type_str);
      it != str_to_enum_type.end()) {
        return it->second;
    } 
    return nullopt;
}

template <typename Request>
unique_ptr<Request> ParseRequest(std::string_view request_str){ 
    const auto request_type = ConvertEnumTypeFromString<typename Request::Type>(ReadToken(request_str), Request::STR_TO_ENUM_TYPE);
    if (!request_type) {
        return nullptr;
    }
    auto request = Request::Create(*request_type);
    if (request) {
        request->ParseFrom(request_str);
    };
    return request;
}

template <typename Request>
std::vector<unique_ptr<Request>> ReadRequests(std::istream& in_stream = std::cin) {
    const size_t request_count = ReadNumberOnLine<size_t>(in_stream);

    std::vector<unique_ptr<Request>> requests;
    requests.reserve(request_count);
    for (size_t i = 0; i < request_count; ++i) {
        std::string request_str;
        getline(in_stream, request_str);
        if (auto request = ParseRequest<Request>(request_str)) {
            requests.push_back(move(request));
        }
    }
    return requests;
}


vector<ResponseHolder> ProcessRequests(const RouteCatalog& rc, const vector<RequestHolder>& requests){
 vector<ResponseHolder> res;
 for (const auto& request : requests){
   res.push_back(request->Process(rc));
 }
 return res;
}


void PrintResponses(const vector<ResponseHolder>& responses, ostream& out_stream = cout) {
  for (const auto& response_holder : responses) {
    out_stream << response_holder->ToString() << endl;
  }
}

void Test();
int main(){
    //Test();
    const auto route_catalog = RouteCatalogBuilder(ReadRequests<Init>()).Build();
    PrintResponses(ProcessRequests(route_catalog, ReadRequests<Request>()));

    return 0;
}

void Test(){
    stringstream out, in;
    in << 10
    << "Stop Tolstopaltsevo: 55.611087, 37.20829\n"
    << "Stop Marushkino: 55.595884, 37.209755\n"
    << "Bus Test Name: Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye\n"
    << "Bus 750: Tolstopaltsevo - Marushkino - Rasskazovka\n"
    << "Stop Rasskazovka: 55.632761, 37.333324\n"
    << "Stop Biryulyovo Zapadnoye: 55.574371, 37.6517\n"
    << "Stop Biryusinka: 55.581065, 37.64839\n"
    << "Stop Universam: 55.587655, 37.645687\n"
    << "Stop Biryulyovo Tovarnaya: 55.592028, 37.653656\n"
    << "Stop Biryulyovo Passazhirskaya: 55.580999, 37.659164\n";

    const auto route_catalog = RouteCatalogBuilder(ReadRequests<Init>(in)).Build();
    RouteBase expected_routes = {{"750", {{"Tolstopaltsevo", "Marushkino", "Rasskazovka"}, true}},
    {"Test Route", {{"Biryulyovo Zapadnoye", "Biryusinka", "Universam", "Biryulyovo Tovarnaya", "Biryulyovo Passazhirskaya"}, false}}};
    //ASSERT_EQUAL(route_catalog.GetRoutes(), expected_routes);A
}