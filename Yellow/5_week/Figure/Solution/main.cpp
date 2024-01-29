#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <iomanip>
#include <cmath>

using namespace std;

class Figure{
public:
	Figure(const string& name, double perimeter, double area)
		: name_(name),
		perimeter_(perimeter),
		area_(area){}

	virtual string Name() const = 0;
	virtual double Perimeter() const = 0;
	virtual double Area() const = 0;

protected:
	string name_;
	double perimeter_;
	double area_;
};

class Rect : public Figure{
public:
	Rect(int a, int b) : Figure("RECT", 2 * (a + b), a * b){};

	string Name() const{
		return name_;
	}

	double Perimeter() const{
		return perimeter_;
	}

	double Area() const{
		return area_;
	}

}; 


class Triangle : public Figure{
public:
	Triangle(int a, int b, int c) : Figure("TRIANGLE", a + b + c,
			S(a, b, c)){}

	double S(int a, int b, int c){
		double p = 0.5 * (a + b + c);
		return sqrt(p * (p - a) * (p - b) * (p - c));
	}

	string Name() const{
		return name_;
	}

double Perimeter() const{
	return perimeter_;
}

double Area() const{
	return area_;
}


};

class Circle : public Figure{
public:
	Circle(int R) : Figure("CIRCLE", 2 * R * 3.14, R * R * 3.14){}

	string Name() const{
		return name_;
	}

	double Perimeter() const{
		return perimeter_;
	}

	double Area() const{
		return area_;
	}


};

shared_ptr<Figure> CreateFigure(istringstream& is){
	string fig;
	is >> fig;

	if (fig == "RECT"){
		int a, b;
		is >> a >> b;
		return make_shared<Rect>(a, b);
	} else if (fig == "TRIANGLE"){
		int a, b, c;
		is >> a >> b >> c;
		return make_shared<Triangle>(a, b, c);
	} else {
		int R;
		is >> R;
		return make_shared<Circle>(R);
	}
}

int main() {
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "ADD") {
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << endl;
      }
    }
  }
  return 0;
}
