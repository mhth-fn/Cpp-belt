#include "game_object.h"
#include "geo2d.h"

#include "test_runner.h"

#include <memory>
#include <vector>

using namespace std;
// Определите классы Unit, Building, Tower и Fence так, чтобы они наследовались
// от GameObject и реализовывали его интерфейс.
geo2d::Rectangle Evaluat(const Building &that);
geo2d::Circle Evaluat(const Tower &that);
geo2d::Segment Evaluat(const Fence &that);
class Unit : public GameObject {
public:
  explicit Unit(geo2d::Point position) : position_(position) {}

  geo2d::Point GetPosition() const { return position_; }

  bool Collide(const GameObject &that) const override{
    return that.CollideWith(*this);
  }
  bool CollideWith(const Unit &that) const override{
    return geo2d::Collide(this->GetPosition(), that.GetPosition());
  }
  bool CollideWith(const Building &that) const override{
    return geo2d::Collide(this->GetPosition(), Evaluat(that));
  }
  bool CollideWith(const Tower &that) const override{
    return geo2d::Collide(this->GetPosition(), Evaluat(that));
  }
  bool CollideWith(const Fence &that) const override{
    return geo2d::Collide(this->GetPosition(), Evaluat(that));
  }

private:
  geo2d::Point position_;
};

class Building : public GameObject {
public:
  explicit Building(geo2d::Rectangle geometry) : position_(geometry) {}

  auto GetPosition() const { return position_; }

  bool Collide(const GameObject &that) const override{
    return that.CollideWith(*this);
  }
  bool CollideWith(const Unit &that) const override{
    return geo2d::Collide(this->GetPosition(), that.GetPosition());
  }
  bool CollideWith(const Building &that) const override{
    return geo2d::Collide(this->GetPosition(), that.GetPosition());
  }
  bool CollideWith(const Tower &that) const override{
    return geo2d::Collide(this->GetPosition(), Evaluat(that));
  }
  bool CollideWith(const Fence &that) const override{
    return geo2d::Collide(this->GetPosition(), Evaluat(that));
  }

private:
  geo2d::Rectangle position_;
};

class Tower : public GameObject {
public:
  explicit Tower(geo2d::Circle geometry) : position_(geometry) {}

  geo2d::Circle GetPosition() const { return position_; }

  bool Collide(const GameObject &that) const override{
    return that.CollideWith(*this);
  }
  bool CollideWith(const Unit &that) const override{
    return geo2d::Collide(this->GetPosition(), that.GetPosition());
  }
  bool CollideWith(const Building &that) const override{
    return geo2d::Collide(this->GetPosition(), Evaluat(that));
  }
  bool CollideWith(const Tower &that) const override{
    return geo2d::Collide(this->GetPosition(), that.GetPosition());
  }
  bool CollideWith(const Fence &that) const override{
    return geo2d::Collide(this->GetPosition(), Evaluat(that));
  }

private:
  geo2d::Circle position_;
};

class Fence : public GameObject {
public:
  explicit Fence(geo2d::Segment geometry) : position_(geometry) {}

  geo2d::Segment GetPosition() const { return position_; }

  bool Collide(const GameObject &that) const override{
    return that.CollideWith(*this);
  }
  bool CollideWith(const Unit &that) const override{
    return geo2d::Collide(this->GetPosition(), that.GetPosition());
  }
  bool CollideWith(const Building &that) const override{
    return geo2d::Collide(this->GetPosition(), that.GetPosition());
  }
  bool CollideWith(const Tower &that) const override{
    return geo2d::Collide(this->GetPosition(), that.GetPosition());
  }
  bool CollideWith(const Fence &that) const override{
    return geo2d::Collide(this->GetPosition(), that.GetPosition());
  }

private:
  geo2d::Segment position_;
};

geo2d::Rectangle Evaluat(const Building &that){
  return that.GetPosition();
}

geo2d::Circle Evaluat(const Tower &that){
  return that.GetPosition();
}

geo2d::Segment Evaluat(const Fence &that){
  return that.GetPosition();
}
// Реализуйте функцию Collide из файла GameObject.h
bool Collide(const GameObject &first, const GameObject &second) {
  return first.Collide(second);
}

void TestAddingNewObjectOnMap() {
  // Юнит-тест моделирует ситуацию, когда на игровой карте уже есть какие-то
  // объекты, и мы хотим добавить на неё новый, например, построить новое здание
  // или башню. Мы можем его добавить, только если он не пересекается ни с одним
  // из существующих.
  using namespace geo2d;

  const vector<shared_ptr<GameObject>> game_map = {
      make_shared<Unit>(Point{3, 3}),
      make_shared<Unit>(Point{5, 5}),
      make_shared<Unit>(Point{3, 7}),
      make_shared<Fence>(Segment{{7, 3}, {9, 8}}),
      make_shared<Tower>(Circle{Point{9, 4}, 1}),
      make_shared<Tower>(Circle{Point{10, 7}, 1}),
      make_shared<Building>(Rectangle{{11, 4}, {14, 6}})};

  for (size_t i = 0; i < game_map.size(); ++i) {
    Assert(Collide(*game_map[i], *game_map[i]),
           "An object doesn't collide with itself: " + to_string(i));

    for (size_t j = 0; j < i; ++j) {
      Assert(!Collide(*game_map[i], *game_map[j]),
             "Unexpected collision found " + to_string(i) + ' ' + to_string(j));
    }
  }

  auto new_warehouse = make_shared<Building>(Rectangle{{4, 3}, {9, 6}});
  ASSERT(!Collide(*new_warehouse, *game_map[0]));
  ASSERT(Collide(*new_warehouse, *game_map[1]));
  ASSERT(!Collide(*new_warehouse, *game_map[2]));
  ASSERT(Collide(*new_warehouse, *game_map[3]));
  ASSERT(Collide(*new_warehouse, *game_map[4]));
  ASSERT(!Collide(*new_warehouse, *game_map[5]));
  ASSERT(!Collide(*new_warehouse, *game_map[6]));

  auto new_defense_tower = make_shared<Tower>(Circle{{8, 2}, 2});
  ASSERT(!Collide(*new_defense_tower, *game_map[0]));
  ASSERT(!Collide(*new_defense_tower, *game_map[1]));
  ASSERT(!Collide(*new_defense_tower, *game_map[2]));
  ASSERT(Collide(*new_defense_tower, *game_map[3]));
  ASSERT(Collide(*new_defense_tower, *game_map[4]));
  ASSERT(!Collide(*new_defense_tower, *game_map[5]));
  ASSERT(!Collide(*new_defense_tower, *game_map[6]));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestAddingNewObjectOnMap);
  return 0;
}
