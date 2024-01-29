#include <memory>
#include <iostream>

void Test(std::unique_ptr<int>& ptr){
    std::cout << "Good\n";
}
int main(){
    std::unique_ptr<int> r = std::make_unique<int>();
    Test(r);
    return 0;
}