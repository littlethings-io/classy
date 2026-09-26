#include "modules_main.hpp"

#include <gtest/gtest.h>

TEST(ModulesMainTest, RunReturnsSuccess)
{
    EXPECT_EQ(modules_main::Run(), 0);
}
