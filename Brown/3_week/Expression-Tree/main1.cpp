#include "Common.h"
#include "test_runner.h"

#include <sstream>

class Digit : public Expression{
public:
  Digit(int digit) : digit_(digit){}

  int Evaluate() const override{
    return digit_;
  }

  std::string ToString() const override{
    return  std::to_string(digit_);
  }
private:
  int digit_;
};

class Operation : public Expression{
public:
  Operation(char op, ExpressionPtr lhs, ExpressionPtr rhs) : op_(op),
  lhs_(move(lhs)), rhs_(move(rhs)) {}

  int Evaluate() const override{
    if (op_ == '+'){
      return lhs_->Evaluate() + rhs_->Evaluate();
    } else if (op_ == '-'){
      return lhs_->Evaluate() - rhs_->Evaluate();
    } else if (op_ == '*'){
      return lhs_->Evaluate() * rhs_->Evaluate();
    }
  }

  std::string ToString() const override{
    return '(' + lhs_->ToString() + ')' + op_ + '(' + rhs_->ToString() + ')';
  }
private:
  char op_;
  ExpressionPtr lhs_, rhs_;
};


// Функции для формирования выражения
ExpressionPtr Value(int value){
  return std::make_unique<Digit>(value);
}
ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right){
  return std::make_unique<Operation>('+', move(left), move(right));
}
ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right){
  return std::make_unique<Operation>('*', move(left), move(right));
}


using namespace std;

string Print(const Expression* e) {
  if (!e) {
    return "Null expression provided";
  }
  stringstream output;
  output << e->ToString() << " = " << e->Evaluate();
  return output.str();
}

void Test() {
  ExpressionPtr e1 = Product(Value(2), Sum(Value(3), Value(4))); 
  ASSERT_EQUAL(Print(e1.get()), "(2)*((3)+(4)) = 14");

  ExpressionPtr e2 = Sum(move(e1), Value(5));
  ASSERT_EQUAL(Print(e2.get()), "((2)*((3)+(4)))+(5) = 19");

  ASSERT_EQUAL(Print(e1.get()), "Null expression provided");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, Test);
  return 0;
}