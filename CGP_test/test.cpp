//
// Created by hungr on 2020/08/12.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace {
    TEST(ENVIRONMENT_TEST, SAMPLE) {
        std::cout << "sample" << std::endl;
        EXPECT_TRUE(true);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

