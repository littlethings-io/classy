#include "modules_main.hpp"
#include "test_module.hpp"
#include <stdio.h>

#include <iostream>

namespace cc
{



int Run()
{
    matrix_1 mattrix(3, 3);
    mattrix.set(1, 1, 5);
    std::cout << mattrix.to_string() << std::endl;

    return 0;
}
}
