#include <sstream>
#include <iostream>
#include <string>
int main () {
    std::stringstream ss;
    ss << "test" << std::to_string(123);
    std::string s = ss.str();
    std::cout << s;
}
