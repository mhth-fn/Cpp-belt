#include <algorithm>
#include <iostream>
#include <vector>

class FunctionPart{
	public:
		FunctionPart(char new_operation, double new_value){
			operation = new_operation;
			value = new_value;
		}
		void Invert(){
			if (operation == '+'){
				operation = '-';
			} else if (operation == '-'){
				operation = '+';
			} else if (operation == '*'){
				operation = '/';
			} else if (operation == '/'){
				operation = '*';
			}
		}

		double Apply(const double number) const{
			if (operation == '+'){
				return number + value;
			} else if (operation == '-') {
				return number - value;
			} else if (operation == '*'){
				return number * value;
			} else if (operation == '/') {
				return number / value;
			}
			return -1;
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
				number = part.Apply(number);
			}
			return number;
		}

	private:
		std::vector<FunctionPart> parts;
};

