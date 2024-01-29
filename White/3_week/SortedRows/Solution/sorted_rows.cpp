#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class SortedStrings {
public:
  void AddString(const std::string& s) {
    // добавить строку s в набор
	  sorted_str.push_back(s);
	  sort(sorted_str.begin(), sorted_str.end());

  }
  std::vector<std::string> GetSortedStrings() {
    // получить набор из всех добавленных строк в отсортированном порядке
		return sorted_str;
  }
private:
  // приватные поля
  std::vector<std::string> sorted_str;
};

void PrintSortedStrings(SortedStrings& strings) {
  for (const std::string& s : strings.GetSortedStrings()) {
	  std::cout << s << " ";
  }
  std::cout << std::endl;
}


int main() {
  SortedStrings strings;
  
  strings.AddString("first");
  strings.AddString("third");
  strings.AddString("second");
  PrintSortedStrings(strings);
  
  strings.AddString("second");
  PrintSortedStrings(strings);
  
  return 0;
}

