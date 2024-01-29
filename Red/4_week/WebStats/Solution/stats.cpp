#include "stats.h"

  const map<string_view, int>& Stats::GetMethodStats() const{
		return methodstats_;
	}
  const map<string_view, int>& Stats::GetUriStats() const{
		return uristats_;
	}
Stats::Stats(){
		for (const auto& item : methods){
			methodstats_[item] = 0;
			it = methods.find("UNKNOWN");
		}
		for (const auto& item : uris){
			uristats_[item] = 0;
			it_uri = uris.find("unknown");
		}
	}
  void Stats::AddMethod(string_view method){
		auto itt = methods.find(string(method));
		if (itt == end(methods)){
			++methodstats_[*it];
		} else {
			++methodstats_[*itt];
		}
	}

  void Stats::AddUri(string_view uri){
		auto itt = uris.find(string(uri));
		if (itt == end(uris)){
			++uristats_[*it_uri];
		} else {
			++uristats_[*itt];
		}
	}

HttpRequest ParseRequest(string_view line){
	HttpRequest res;
	line.remove_prefix(line.find_first_not_of(" "));
	size_t space = line.find(' ');
	res.method = line.substr(0, space);	
	line.remove_prefix(space + 1);
	space = line.find(' ');
	res.uri = line.substr(0, space);	
	line.remove_prefix(space + 1);
	res.protocol = line.substr(0);	

	return res;
}




