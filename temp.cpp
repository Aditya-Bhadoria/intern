#include <iostream>
#include <array>
class SuperMemoryLeaker{
   std::array<std::string, 100000> arr;
};
int main(){
    // super memory leak
    SuperMemoryLeaker* x {new (std::nothrow) SuperMemoryLeaker{}};
    while(true){
        x = new (std::nothrow) SuperMemoryLeaker {};
        if(!x){
            std::cout << "no memory remaining :(\n";
            break;
        }
    }
}