#include "modules_main.hpp"
#include "test_module.hpp"

#include <iostream>

namespace cc
{

void test_send_email();

void test_send_sms();

void test_dispatcher();

int Run()
{
    std::cout << "Begin test_send_email" << "\n";
    test_send_email();
    std::cout << "\n**************************" << "\n\n";

    std::cout << "Begin test_send_sms" << "\n";
    test_send_sms();
    std::cout << "\n**************************" << "\n\n";

    std::cout << "Begin test_dispatcher" << "\n";
    test_dispatcher();
    std::cout << "**************************" << "\n\n";

    return 0;
}

void test_send_email() {}

void test_send_sms() {}

void test_dispatcher() {}

} // namespace cc
