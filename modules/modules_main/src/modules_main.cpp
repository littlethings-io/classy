#include "modules_main.hpp"
#include "test_module.hpp"

#include <iostream>

namespace cc
{


void test_matrix() {
}


int Run()
{
    std::cout << "Begin test_matrix" << "\n";
    test_matrix();
    std::cout << "**************************" << "\n\n";
    return 0;
}
}
