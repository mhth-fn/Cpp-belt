#include <sstream>
#include <iostream>
#include <exception>
using namespace std;

class Rational {
public:
    Rational() {
        // Реализуйте конструктор по умолчанию
		numerator = 0;
		denominator = 1;
    }

    Rational(int _numerator, int _denominator) {
        // Реализуйте конструктор
		if (_denominator == 0){
			throw invalid_argument("Invalid argument");
		}
		int gcd = GCD(abs(_numerator), abs(_denominator));
		numerator = _numerator / gcd;
		denominator = _denominator / gcd;
	
		if (denominator < 0){
			denominator = -denominator;
			numerator = -numerator;
		}	
    }

    int Numerator() const {
        // Реализуйте этот метод
		return numerator;
    }

    int Denominator() const {
        // Реализуйте этот метод
		return denominator;
    }

private:
    // Добавьте поля
	int numerator;
	int denominator;

	int GCD (int _numerator, int _denominator){
		while (_numerator > 0 && _denominator > 0) {
    
		if (_numerator > _denominator) {
					_numerator %= _denominator;
			} else {
					_denominator %= _numerator;
			}   
		} 
		return _numerator + _denominator;
	}
};

bool operator == (const Rational& a, const Rational& b){
	return a.Numerator() == b.Numerator() 
		&& a.Denominator() == b.Denominator();
}

Rational operator+(const Rational& a, const Rational& b){
	Rational res(a.Numerator() * b.Denominator() + b.Numerator() * a.Denominator(), a.Denominator() * b.Denominator());
	return res;
}


Rational operator-(const Rational& a, const Rational& b){
	Rational res(a.Numerator() * b.Denominator() - b.Numerator() * a.Denominator(), a.Denominator() * b.Denominator());
	return res;
}

Rational operator*(const Rational& a, const Rational& b){
	return {a.Numerator() * b.Numerator(),
			a.Denominator() * b.Denominator()};
}

Rational operator/(const Rational& a, const Rational& b){
	if (b.Numerator() == 0){
		throw domain_error("Division by zero");
	}
	return {a.Numerator() * b.Denominator(),
			a.Denominator() * b.Numerator()};
}

ostream& operator<<(ostream& stream, const Rational& a){
	stream << a.Numerator() << "/" << a.Denominator();
	return stream;
}

istream& operator>>(istream& stream, Rational& a){
	int n, d;
	char c;

	if (stream){
		stream >> n >> c >> d;
		if (!stream.fail() && c == '/'){
			a = Rational(n, d);
		} 
	}
	return stream;
}

bool operator<(const Rational& a, const Rational& b){
	return a.Numerator() * b.Denominator() < a.Denominator() * b.Numerator();
}

int main(){

	try{
		Rational a, b;
		char c;
		std::cin >> a >> c >> b;
		if (c == '+'){
			std::cout << a + b << '\n';
		} else if (c == '-'){
			std::cout << a - b << '\n';
		} else if (c == '*'){
			std::cout << a * b << '\n';
		} else {
			std::cout << a / b << '\n';
		}
	} catch(exception& exp){
		std::cout << exp.what() << '\n';
	}	
}
