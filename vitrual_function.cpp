#include <iostream>
class BaseClass {
public:
    BaseClass() {
        std::cout << "BaseClass Contruct\n";
    };

    virtual ~BaseClass() {
        std::cout << "BaseClass Destoried\n";
    };
    void reload() {
        func();
    }
    virtual void func() {
        std::cout << "BaseClass Do\n";
    }
};

class ChildClass : public BaseClass {
public:
    ChildClass() {
        std::cout << "ChildClass Contruct\n";
    };
    ~ChildClass() {
        std::cout << "ChildClass Destoried\n";
    };

    void func() {
        std::cout << "ChildClass Do\n";
    }
};

int main() {
    BaseClass* ptr = new ChildClass(); // 指针
    ptr->func();
    BaseClass& base_class = *ptr; // 引用
    base_class.func();
    delete ptr;
}