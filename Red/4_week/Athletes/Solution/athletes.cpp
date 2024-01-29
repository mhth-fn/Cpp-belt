#include <list>
#include <iostream>
#include <set>
#include <map>


struct Athletes{
	int number;
	std::list<int>::iterator order;

	bool operator<(const Athletes& other) const{
		return number < other.number;
	}
};

int main(){
	size_t N;
	std::cin >> N;
	
	std::list<int> order;
	std::map<int, std::list<int>::iterator> athletes;	
	int fnum, snum;
	for (size_t i = 0; i != N; ++i){
		std::cin >> fnum >> snum;
		if (athletes.find(snum) == end(athletes)){
			order.push_back(fnum);
			athletes[fnum] = --end(order);
		} else {
			athletes[fnum] = order.insert(athletes[snum], fnum);
		}
	}

	for (const auto& x : order){
		std::cout << x << " ";
	}
	std::cout << std::endl;

	return 0;
}
