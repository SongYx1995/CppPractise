#include "dag_engine.h"
#include <iostream>

void func_a() {
    std::cout << "func_a" << std::endl;
}

void func_b() {
    std::cout << "func_b" << std::endl;
}

void func_c() {
    std::cout << "func_c" << std::endl;
}

int main() {
    Dag dag;

    auto& node_a = dag.add_node(func_a);
    auto& node_b = dag.add_node(func_a);

    dag.add_edge(node_a, node_b);

    dag.run();
}