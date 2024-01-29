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
#include <fstream>
#include <istream>
#include <map>
#include <string>
#include <variant>
#include <vector>
#include <sstream>

namespace Json {

  class Node : std::variant<std::vector<Node>,
                            std::map<std::string, Node>,
                            double,
                            int,
                            bool,
                            std::string> {
  public:
    using variant::variant;

    const auto& AsArray() const {
      return std::get<std::vector<Node>>(*this);
    }
    const auto& AsMap() const {
      return std::get<std::map<std::string, Node>>(*this);
    }
    double AsDouble() const {
      return std::get<double>(*this);
    }
    bool AsBool() const{
      return std::get<bool>(*this);
    }
    const auto& AsString() const {
      return std::get<std::string>(*this);
    }
  };

  class Document {
  public:
    explicit Document(Node root);

    const Node& GetRoot() const;

  private:
    Node root;
  };

  Document Load(std::istream& input);

}



double PI = 3.1415926535;
double R = 6371000.0;
      
using namespace std;

namespace Json {

  Document::Document(Node root) : root(move(root)) {
  }

  const Node& Document::GetRoot() const {
    return root;
  }

  Node LoadNode(istream& input);

  Node LoadArray(istream& input) {
    vector<Node> result;

    for (char c; input >> c && c != ']'; ) {
      if (c != ',') {
        input.putback(c);
      }
      result.push_back(LoadNode(input));
    }

    return Node(move(result));
  }

Node LoadInt(istream& input) {
    int result = 0;
    while (isdigit(input.peek())) {
      result *= 10;
      result += input.get() - '0';
    }
    return Node(result);
  }

  Node LoadDouble(istream& input) {
    double result = 0;

    int sign = 1;
    if (input.peek() == '-') {
      input.ignore();
      sign = -1;
    }

    while (isdigit(input.peek())) {
      result *= 10;
      result += input.get() - '0';
    }

    if (input.peek() != '.') {
      return Node(sign * result);
    }

    input.ignore();
    double double_res = result;
    double factor = 0.1;
    while (isdigit(input.peek())) {
      int digit = input.get() - '0';
      double_res += digit * factor;
      factor *= 0.1;
    }
    return Node(sign * double_res);
  }

  Node LoadString(istream& input) {
    string line;
    getline(input, line, '"');
    return Node(move(line));
  }

  Node LoadBool(istream& input) {
    string value(5, '\0');

    for (int i = 0; i < 4; ++i) {
      input >> value[i];
    }

    if (value.substr(0, 4) == "true") {
      return Node(true);
    }

    input >> value[4];
    return Node(false);
  }
  Node LoadDict(istream& input) {
    map<string, Node> result;

    for (char c; input >> c && c != '}'; ) {
      if (c == ',') {
        input >> c;
      }

      string key = LoadString(input).AsString();
      input >> c;
      result.emplace(move(key), LoadNode(input));
    }

    return Node(move(result));
  }

  Node LoadNode(istream& input) {
    char c;
    input >> c;

    if (c == '[') {
      return LoadArray(input);
    } else if (c == '{') {
      return LoadDict(input);
    } else if (c == '"') {
      return LoadString(input);
    } else {
      input.putback(c);
      if (input.peek() == 't' || input.peek() == 'f'){
        return LoadBool(input);
      } else {
      return LoadDouble(input);
      }
    }
  }

  Document Load(istream& input) {
    return Document{LoadNode(input)};
  }

}

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
    virtual stringstream ToJson() = 0;
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
    BusResponse(Struct& response, int id) :
    response_(move(response)), id_(id){}

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

    stringstream ToJson(){
        stringstream out;
        out << "\t{\n";
        if (response_.length !=0){
            out << "\t\t\"route_length\": " << response_.real_length << ",\n";
            out << "\t\t\"request_id\": " << id_ <<",\n";
            out << "\t\t\"curvature\": " << response_.real_length / response_.length << ",\n";
            out << "\t\t\"stop_count\": " << response_.stops << ",\n";
            out << "\t\t\"unique_stop_count\": " << response_.unique_stops << "\n";
        } else {
            out << "\t\t\"request_id\": " << id_ << ",\n";
            out << "\t\t\"error_message\": \"not found\"\n"; 
        }
        out << "\t}";
        return out;
    }
    int id_;
    Struct response_;
};

class StopResponse : public Response{
public:
    StopResponse(string_view stop, int id)
    : stop_(stop), id_(id), is_find(false) {}

    StopResponse(string_view stop, int id, set<string_view> buses)
    : stop_(stop), id_(id), buses_(buses), is_find(true) {}

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

    stringstream ToJson(){
        stringstream out;
        out << "\t{\n";

        if (is_find){
            out << "\t\t\"buses\" : [";
            if (buses_.size() != 0){
                out << "\n";
            }
            vector<string_view> buses{buses_.begin(), buses_.end()};
            for(size_t i = 0; i != buses.size(); ++i){
                out << "\t\t\t\"" << buses[i] << "\"";
                if (i != buses.size() - 1){
                    out << ",";
                }
                out << "\n";
            }
            if (buses_.size() != 0){
                out << "\t\t";
            }
            out << "],\n";
        }
        out << "\t\t\"request_id\": " << id_;
        if (!is_find){
            out << ",\n";
            out << "\t\t\"error_message\": \"not found\"";  
        }
        out << "\n";
        out << "\t}";
        return out;
    }
    int id_;
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
    virtual void ParseFrom(const map<string, Json::Node>& json_request) = 0;
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
    virtual void ParseFrom(const map<string, Json::Node>& json_request) = 0;
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
        return make_unique<BusResponse>(res, id_);
    }

    void ParseFrom(const map<string, Json::Node>& json_request) override{
        route = json_request.at("name").AsString();
        id_ =json_request.at("id").AsDouble();
    }
    int id_;
    string route;
};

class StopRequest : public Request{

    ResponseHolder Process(const RouteCatalog& rc) override{
        if (auto it = rc.GetStopToBuses().find(stop); it != end(rc.GetStopToBuses())){
            return make_unique<StopResponse>(stop, id_, it->second);
        } else{
            return make_unique<StopResponse>(stop, id_);
        }
    }
    void ParseFrom(const map<string, Json::Node>& json_request) override{
        stop = json_request.at("name").AsString();
        id_ =json_request.at("id").AsDouble();
    }

    int id_;
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
    void ParseFrom(const map<string, Json::Node>& json_request) override{
        string routename = json_request.at("name").AsString();
        Route res;
        res.is_circled = !json_request.at("is_roundtrip").AsBool();
        auto& stops_ = json_request.at("stops").AsArray();
        for (size_t i = 0; i != stops_.size(); ++i){
            res.stops_.push_back(stops_[i].AsString());
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
    void ParseFrom(const map<string, Json::Node>& json_request) override{
      string stopname = json_request.at("name").AsString();
      Coordinates cord = {json_request.at("latitude").AsDouble() * M_PI / 180.0, json_request.at("longitude").AsDouble() * M_PI / 180.0};
      stop = {move(stopname), cord};
      auto& road_distance = json_request.at("road_distances").AsMap();
      for (const auto& item : road_distance){
        distance_to_stops[item.first] = item.second.AsDouble();
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

// template <typename Request>
// unique_ptr<Request> ParseRequest(std::string_view request_str){ 
//     const auto request_type = ConvertEnumTypeFromString<typename Request::Type>(ReadToken(request_str), Request::STR_TO_ENUM_TYPE);
//     if (!request_type) {
//         return nullptr;
//     }
//     auto request = Request::Create(*request_type);
//     if (request) {
//         request->ParseFrom(request_str);
//     };
//     return request;
// }

// template <typename Request>
// std::vector<unique_ptr<Request>> ReadRequests(std::istream& in_stream = std::cin) {
//     const size_t request_count = ReadNumberOnLine<size_t>(in_stream);

//     std::vector<unique_ptr<Request>> requests;
//     requests.reserve(request_count);
//     for (size_t i = 0; i < request_count; ++i) {
//         std::string request_str;
//         getline(in_stream, request_str);
//         if (auto request = ParseRequest<Request>(request_str)) {
//             requests.push_back(move(request));
//         }
//     }
//     return requests;
// }


template <typename Request>
unique_ptr<Request> ParseRequest(const map<string, Json::Node>& json_request){ 
    const auto request_type = ConvertEnumTypeFromString<typename Request::Type>(json_request.at("type").AsString(), Request::STR_TO_ENUM_TYPE);
    if (!request_type) {
        return nullptr;
    }
    auto request = Request::Create(*request_type);
    if (request) {
        request->ParseFrom(json_request);
    };
    return request;
}
template <typename Request>
std::vector<unique_ptr<Request>> ReadRequests(const vector<Json::Node>& json_requests) {
    const size_t request_count = json_requests.size();

    std::vector<unique_ptr<Request>> requests;
    requests.reserve(request_count);
    for (size_t i = 0; i < request_count; ++i) {
        if (auto request = ParseRequest<Request>(json_requests[i].AsMap())) {
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


void PrintResponsesString(const vector<ResponseHolder>& responses, ostream& out_stream = cout) {
  for (const auto& response_holder : responses) {
    out_stream << response_holder->ToString();
  }
}

void PrintResponsesJson(const vector<ResponseHolder>& responses, ostream& out_stream = cout) {
    out_stream << "[\n";
    for (size_t i = 0; i != responses.size(); ++i) {
        out_stream << responses[i]->ToJson().str();
        if (i != responses.size() - 1){
            out_stream << ",";
        }
        out_stream << "\n";
    }
    out_stream << "]\n";
}

stringstream FromJsonToSS(Json::Document);

int main(){
    string str;
    getline(cin, str);
    stringstream ss(str);
    auto json = Json::Load(ss); 
    auto& base_request = json.GetRoot().AsMap().at("base_requests").AsArray();
    const auto route_catalog = RouteCatalogBuilder(ReadRequests<Init>(base_request)).Build();
    auto& stat_request = json.GetRoot().AsMap().at("stat_requests").AsArray();
    PrintResponsesJson(ProcessRequests(route_catalog, ReadRequests<Request>(stat_request)));
    return 0;
}

