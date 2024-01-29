#include <iostream>
#include <vector>
#include <utility>
#include <map>

using namespace std;

template <typename T>
vector<T> Sqr(vector<T> vi);

template <typename first, typename second>
map<first, second> Sqr(map<first, second> m);

template <typename first, typename second>
pair<first, second> Sqr(pair<first, second> p);

template <typename T>
T Sqr(T n);

template <typename T>
vector<T> Sqr(vector<T> vi){
	vector<T> res;
	for (auto& x : vi){
		res.push_back(Sqr(x));
	}
	return res;
}

template <typename first, typename second>
map<first, second> Sqr(map<first, second> m){
	map<first, second> res;
	for (auto& item : m){
		res[item.first] = Sqr(item.second);
	}
	return res;
}

template <typename first, typename second>
pair<first, second> Sqr(pair<first, second> p){
	return {Sqr(p.first), Sqr(p.second)};
}

template <typename T>
T Sqr(T n){
	return n * n;
}

int main(){
	     

	vector<int> v = {1, 2, 3};
	cout << "vector:";
	for (int x : Sqr(v)) {
 		 cout << ' ' << x;
	}
	cout << endl;

	map<int, pair<int, int>> map_of_pairs = {
  	{4, {2, 2}},
  	{7, {4, 3}}
	};
	cout << "map of pairs:" << endl;
	for (const auto& x : Sqr(map_of_pairs)) {
  		cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
	}
}
