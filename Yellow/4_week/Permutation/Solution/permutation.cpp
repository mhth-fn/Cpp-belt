#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

int Factorial(size_t n){
    if (n < 2){
        return 1;
    }
    return n * Factorial(n - 1);
}

void Permutation(size_t N){
    vector<size_t> numbers(N);
    for (size_t i = N; i != 0; --i){
        numbers[i - 1] = i;
    }
    for (size_t i = 0; i != Factorial(N); ++i){
        prev_permutation(numbers.begin(), numbers.end());
        for (size_t j = 0; j != N; ++j){
            cout << numbers[j] << " ";
        }
        cout << endl;
    }

}

int main(){
    size_t N;
    cin >> N;
    Permutation(N);

    return 0;
}