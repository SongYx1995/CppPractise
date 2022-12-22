#include <iostream>
#include <unordered_map>
#include <typeinfo>
#include <cxxabi.h>


template <class B>
class DynamicFactory {
public:
    static void regist(const std::string& name, std::function<std::shared_ptr<B>()> func) {
        func_map.insert(std::make_pair(name, func));
    }
    static std::shared_ptr<B> get(const std::string& name) {
        auto iter = func_map.find(name);
        if (iter == func_map.end()) {
            std::cout << "class " << name << " not found" << std::endl;
            return nullptr;
        }
        return (iter->second)();
    }
    static std::unordered_map<std::string, std::function<std::shared_ptr<B>()>> func_map;
};

template <class B, class D>
class DyanmicCreator {
public:
    DyanmicCreator() {
        registor_;
    }
    struct Registor {
        Registor() {
            // std::cout << "Registor" << std::endl;
            char* demangle_name =
                    abi::__cxa_demangle(typeid(D).name(), nullptr, nullptr, nullptr);
            std::string s(demangle_name);
            auto f = []() {
                return std::make_shared<D>();
            };
            DynamicFactory<B>::regist(s, f);
        }
    };
    static Registor registor_;
};

template <class B>
std::unordered_map<std::string, std::function<std::shared_ptr<B>()>> DynamicFactory<B>::func_map;

template <class T1, class T2>
typename DyanmicCreator<T1, T2>::Registor DyanmicCreator<T1, T2>::registor_;

class Base {
public:
    virtual void func() {};
    virtual ~Base() = default;
};

class A : public Base, 
          public DyanmicCreator<Base, A> {
public:
    A() {};
    void func() {
        std::cout << "this is A" << std::endl;
    }
};

class B : public Base,
          public DyanmicCreator<Base, B> {
public:
    B(){};
    void func() {
        std::cout << "this is B" << std::endl;
    }
};

int main() {
    std::shared_ptr<Base> ptr_a = DynamicFactory<Base>::get("A");
    if (ptr_a != nullptr) {
        ptr_a->func();
    }

    std::shared_ptr<Base> ptr_b = DynamicFactory<Base>::get("B");
    if (ptr_b != nullptr) {
        ptr_b->func();
    }
}