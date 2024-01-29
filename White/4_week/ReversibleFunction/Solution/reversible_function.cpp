#include <algorithm>
#include <vector>
using namespace std;


class FunctionPart{
	public:
		FunctionPart(char new_operation, double new_value){
			operation = new_operation;
			value = new_value;
		}
		void Invert(){
			if (operation == '+'){
				operation = '-';
			} else {
				operation = '+';
			}
		}

		double Apply() const{
			if (operation == '+'){
				return value;
			} else {
				return -value;
			}
		}
	private:
		char operation;
		double value;
};

class Function{ 
	public:
		void AddPart(char operation, double number){
			parts.push_back({operation, number});
		}
		void Invert(){
			for (auto& part : parts){
				part.Invert();
			}
			reverse(parts.begin(), parts.end());
		}
		double Apply (double number) const{
			for (const auto& part : parts){
				number += part.Apply();
			}
			return number;
		}

	private:
		std::vector<FunctionPart> parts;
};


