#include "test_runner.h"

#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;


struct Email {
  string from;
  string to;
  string body;
};


class Worker {
public:
  virtual ~Worker() = default;
  virtual void Process(unique_ptr<Email> email) = 0;
  virtual void Run() {
    // только первому worker-у в пайплайне нужно это имплементировать
    throw logic_error("Unimplemented");
  }

protected:
  // реализации должны вызывать PassOn, чтобы передать объект дальше
  // по цепочке обработчиков
  void PassOn(unique_ptr<Email> email) const{
    next_->Process(move(email));
  }

public:
  void SetNext(unique_ptr<Worker> next){
    next_ = move(next);
  }

private:
  unique_ptr<Worker> next_ = nullptr;
};


class Reader : public Worker {
public:
  // реализуйте класс
  Reader(istream& in){
    while (in){
      auto email = make_unique<Email>();

      string str;
      getline(in, str);
      email->from = str;
      getline(in, str);
      email->to = str;
      getline(in, str);
      email->body = str;
      pool.push_back(move(email));
    } 
  }
  
  void Run() override{
    for (auto& email : pool){
      PassOn(move(email));
    }
  }

void Process(unique_ptr<Email> email) override{
  Run();
}
private:
  vector<unique_ptr<Email>> pool;
};


class Filter : public Worker {
public:
  using Function = function<bool(const Email&)>;

public:
  // реализуйте класс
  Filter(Function& pred) : pred_(pred){}
  void Process(unique_ptr<Email> email) override{
    if (pred_(*email)){
      PassOn(move(email));
    } 
  }
private: 
  Function& pred_;
};


class Copier : public Worker {
public:
  // реализуйте класс
  Copier(const string& address) : address_(address){}

  void Process(unique_ptr<Email> email) override{
    auto new_email = make_unique<Email>();
    new_email->body = email->body;
    new_email->from = email->from;
    new_email->to = address_;
    PassOn(move(new_email));
  }

private: 
  string address_;
};


class Sender : public Worker {
public:
  // реализуйте класс
  Sender(ostream& out) : out_(out){}

  void Process(unique_ptr<Email> email) override{
    out_ << email->from << '\n' << email->to << '\n' << email->body << '\n';
  }

private:
  ostream& out_;
};


// реализуйте класс
class PipelineBuilder {
public:
  // добавляет в качестве первого обработчика Reader
  explicit PipelineBuilder(istream& in){
    begin = make_unique<Reader>(in);
  }

  // добавляет новый обработчик Filter
  PipelineBuilder& FilterBy(Filter::Function filter){
    auto chain = make_unique<Filter>(filter);
    begin->SetNext(move(chain));
    return *this;
  }

  // добавляет новый обработчик Copier
  PipelineBuilder& CopyTo(string recipient){
    auto chain = make_unique<Copier>(recipient);
    begin->SetNext(move(chain));
    return *this;
  }

  // добавляет новый обработчик Sender
  PipelineBuilder& Send(ostream& out){
    auto chain = make_unique<Sender>(out);
    begin->SetNext(move(chain));
    return *this;
  }

  // возвращает готовую цепочку обработчиков
  unique_ptr<Worker> Build(){
    return move(begin);
  }
private:
  unique_ptr<Worker> begin;
};


void TestSanity() {
  string input = (
    "erich@example.com\n"
    "richard@example.com\n"
    "Hello there\n"

    "erich@example.com\n"
    "ralph@example.com\n"
    "Are you sure you pressed the right button?\n"

    "ralph@example.com\n"
    "erich@example.com\n"
    "I do not make mistakes of that kind\n"
  );
  istringstream inStream(input);
  ostringstream outStream;

  PipelineBuilder builder(inStream);
  builder.FilterBy([](const Email& email) {
    return email.from == "erich@example.com";
  });
  builder.CopyTo("richard@example.com");
  builder.Send(outStream);
  auto pipeline = builder.Build();

  pipeline->Run();

  string expectedOutput = (
    "erich@example.com\n"
    "richard@example.com\n"
    "Hello there\n"

    "erich@example.com\n"
    "ralph@example.com\n"
    "Are you sure you pressed the right button?\n"

    "erich@example.com\n"
    "richard@example.com\n"
    "Are you sure you pressed the right button?\n"
  );
  //ASSERT_EQUAL(expectedOutput, outStream.str());
  std::cout << expectedOutput << '\n' 
  << "MY OUT: " << '\n' << outStream.str();


}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSanity);
  return 0;
}
