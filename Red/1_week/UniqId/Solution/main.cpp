#include <string>
#include <vector>
using namespace std;

#define LINE(a) b##a
#define LINE3(a) LINE(a)
#define UNIQ_ID LINE3(__LINE__) 

int main() {
  int UNIQ_ID = 0;
  string UNIQ_ID = "hello";
  vector<string> UNIQ_ID = {"hello", "world"};
  vector<int> UNIQ_ID = {1, 2, 3, 4};
}