#include <iostream>

enum class MyEnum {
 aaa = -2,
 bbb= 1	
};

int main() {
  // MyEnum a = static_cast<MyEnum>(-2);
  MyEnum a;
  std::cout << static_cast<int>(a) << std::endl;
  if (a == MyEnum::aaa) {
	std::cout << "equal to aaa" << std::endl;
  } else if (a == MyEnum::bbb) {
	std::cout << "equal to bbb" << std::endl;
  }
}
