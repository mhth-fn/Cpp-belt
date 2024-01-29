/*

Stop Tolstopaltsevo: 55.611087, 37.20829 -> unique_ptr<StopsInit>
Bus 256: Biryulyovo Zapadnoye > Biryusinka -> unique_ptr<RoutesInit>

class Init{
    virtual void Process() = 0;
}
class StopsInit : protected Init;
class RoutesInit : protected Init;




*/

#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

struct Coordinates{
    double latitude;
    double longitude;
};

struct Route{
    std::vector<std::string> stops_;
    bool is_circled = false;
};

using RouteBase = std::unordered_map<std::string, Route>;
using StopBase = std::unordered_map<std::string, Coordinates>;

class RouteCatalog{
public:
    friend class RouteCatalogBuilder;

private:
    RouteCatalog(RouteBase routebase, StopBase stopbase) :
    routebase_(move(routebase)), stopbase_(move(stopbase)) {}

    RouteBase routebase_;
    StopBase stopbase_;
};

class Init;
// InitPull must have a method ->dbpull for bd
class RouteCatalogBuilder{
private:
public:
    RouteCatalogBuilder();
    RouteCatalogBuilder(const std::vector<std::unique_ptr<Init>> init_pull);
    RouteCatalog Build(){
        return RouteCatalog{move(routebase_temp), move(stopbase_temp)};
    }
private:
    RouteBase routebase_temp;
    StopBase stopbase_temp;

};

class Init{
public:
    virtual void Process(RouteCatalogBuilder& builder) = 0;
    virtual void ParseFrom(std::istream& in = std::cin) = 0;

    enum class Type{
        Bus,
        Stop
    };
};

class RouteInit : public Init{
public:
    void Process(RouteCatalogBuilder& builder) override;
    void ParseFrom(std::istream& in = std::cin) override{
        auto t = Init::Type::Bus;
    }
};

class StopInit : public Init{
    void Process(RouteCatalogBuilder& builder) override;
    void ParseFrom(std::istream& in = std::cin) override;
};


