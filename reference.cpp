#include <iostream>

void f(int&& b) {
    std::cout << "r value" << std::endl;
}

void f(int& b) {
    std::cout << "l value" << std::endl;
}

template<typename T>
void func(T&& b) {
    f(std::forward<T>(b));
}

int main() {
    int b = 1;
    func(b);
    func(1);
}