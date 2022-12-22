#include <string>
#include <memory>
#include <iostream>
#include <vector>

int main() {
    std::vector<std::shared_ptr<std::string>> keys;
    for (int i = 0; i < 10; ++i) {
        // std::string tmp = std::to_string(i);
        std::string tmp(i);
        std::cout << (void*)(tmp.data()) << std::endl;
    }
    // for (int i = 0; i < 10; ++i) {
    //     std::cout << "key: " << (*keys[i]) << std::endl;
    // }
}

// class MyClass {
// public:
//     int* data;
//     MyClass(int a) {
//         data = new int(a);
//     }
//     ~MyClass() {
//         delete data;
//     }
//     MyClass(MyClass&& other) {
//         this.data = other.data;
//     }
// };

// int main() {
//     std::vector<MyClass> keys;
//     for (int i = 0; i < 10; ++i) {
//         MyClass k(i);
//         std::cout << k.data << "\t" << (void*)(&(k.data)) << std::endl;
//         keys.emplace_back(std::move(k));
//         // std::cout << (void*)(keys[i].data()) << std::endl;
//     }
//     for (int i = 0; i < 10; ++i) {
//         std::cout << "key: " << keys[i].data << std::endl;
//     }
// }



    // std::vector<std::shared_ptr<std::string>> list;
    // for (int i = 0; i < 10; i++) {
    //     auto str = std::make_shared<std::string>(std::to_string(i));
    //     list.emplace_back(str);
    // }
    // for (int i = 0; i < 10; i++) {
    //     std::cout << *(list[i]) << std::endl;
    // }