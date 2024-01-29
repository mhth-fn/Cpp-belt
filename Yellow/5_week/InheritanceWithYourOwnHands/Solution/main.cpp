#include <iostream>
#include <string>

using namespace std;

class Animal {
public:
    // ваш код
	Animal(const string _name)
		: Name(_name){
		}

	const string Name;
};


class Dog : public Animal{
public:
    // ваш код
		Dog(const string _name) : Animal(_name){}

    void Bark() {
        cout << Name << " barks: woof!" << endl;
    }
};
