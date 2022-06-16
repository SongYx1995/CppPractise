#include <functional>
#include <iostream>
#include <vector>

class MyClass {
public:
    int data = 0;
    MyClass() = default;
    ~MyClass() {
        data = -1;
    }
};
int main() {

    std::vector<std::reference_wrapper<MyClass>> vec;
    {
        MyClass a;
        vec.push_back(a);
    }
    std::cout << vec[0].get().data;
}