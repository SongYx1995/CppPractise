#include <iostream>
class Father {
public:
    void get() {
        std::cout << "father get" << std::endl;
    }
};

class Child : public Father {
public:
    void get() {
        std::cout << "son get" << std::endl;
    }
};

int main() {
    Father* obj = new Child();
    obj->get()
}