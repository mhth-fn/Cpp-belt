#include <iostream>
#include <optional>
#include <limits>

using T = int64_t;

static constexpr T max = std::numeric_limits<T>::max();
static constexpr T min = std::numeric_limits<T>::min();

std::optional<T> Sum(T a, T b){
    if ((a > 0 && b > 0 && ((max - a) < b))
     || (a < 0 && b < 0 && ((min - a) > b))){
        return std::nullopt;
    } 
    return a + b;
}

int main(){
    T a, b;
    std::cin >> a >> b;
    if (auto sum = Sum(a, b)){
        std::cout << *sum;
    } else{
        std::cout << "Overflow!";
    }
    std::cout << '\n';

    return 0;
}