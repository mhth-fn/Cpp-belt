#pragma once

#include "http_request.h"

#include <string_view>
#include <string>
#include <map>
#include <set>
using namespace std;

class Stats {
public:
	Stats();

  void AddMethod(string_view method);

  void AddUri(string_view uri);

  const map<string_view, int>& GetMethodStats() const;
  const map<string_view, int>& GetUriStats() const;
private:
	const set<string> methods {"GET", "POST", "PUT", "DELETE", "UNKNOWN"};
	set<string>::iterator it;
	set<string>::iterator it_uri;
	const set<string> uris {"/", "/order", "/product", "/basket", "/help", "unknown"};
	map<string_view, int> methodstats_;
	map<string_view, int> uristats_;
};

HttpRequest ParseRequest(string_view line);

