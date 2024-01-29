#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <sstream>

using namespace std;

bool IsSubdomain(string_view subdomain, string_view domain) {
  int i = 0;
  int j = 0;
  while (i < subdomain.size() && j < domain.size()) {
    char test1 = subdomain[i];
    char test2 = domain[j];
    if (subdomain[i++] != domain[j++]) {
      return false;
    }
  }
  return (i == subdomain.size() && (domain[j] == '.' || j == domain.size()))
      || (j == domain.size() && (subdomain[i] == '.' || i == subdomain.size()));
}


vector<string> ReadDomains(istream& in = cin) {
  size_t count;
  in >> count;

  vector<string> domains;
  for (size_t i = 0; i < count; ++i) {
    string domain;
    in >> domain;
    domains.push_back(domain);
  }
  return domains;
}


int main() {
  vector<string> banned_domains = [&]{
    vector<string> res = ReadDomains();
    for (string& domain : res) {
      reverse(begin(domain), end(domain));
    }
    sort(begin(res), end(res));

    return res;
  }();
  vector<string> domains_to_check = ReadDomains();

  size_t insert_pos = 0;
  for (string& domain :banned_domains) {
    if (insert_pos == 0 || !IsSubdomain(domain, banned_domains[insert_pos - 1])) {
      swap(banned_domains[insert_pos++], domain);
    }
  }
  banned_domains.resize(insert_pos);


  for (string& domain : domains_to_check) {
      reverse(begin(domain), end(domain));
  }
  for (const string_view domain : domains_to_check) {
    const auto it = upper_bound(begin(banned_domains), end(banned_domains), domain);
    if ((it == begin(banned_domains) || !IsSubdomain(domain, *(prev(it))))) {
      cout << "Good" << endl;
    } else {
      cout << "Bad" << endl;
    }
  }
  return 0;
 }
