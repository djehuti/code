// Copyright (c) 2019 Ben Cox <cox@djehuti.com>. All Rights Reserved.

#include "util/string.hh"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace djehuti {
namespace string {

TEST(StringTests, Join) {
    const std::vector<std::string> just_one{"hello"};
    EXPECT_EQ(join(just_one, ":"), "hello");

    const std::vector<std::string> two{"hello", "world"};
    EXPECT_EQ(join(two, ' '), "hello world");

    const std::vector<std::string> four{"a", "b", "c", "d"};
    EXPECT_EQ(join(four, ':'), "a:b:c:d");
}

TEST(StringTests, Split) {
    const auto one = split("one", ';');
    const std::vector<std::string> expected_one{"one"};
    EXPECT_THAT(one, ::testing::ContainerEq(expected_one));

    const auto two = split("one\ntwo", '\n');
    const std::vector<std::string> expected_two{"one", "two"};
    EXPECT_THAT(two, ::testing::ContainerEq(expected_two));

    // This one has consecutive separators.
    const auto four = split("::a:b:c::d::", ':');
    const std::vector<std::string> expected_four{"a", "b", "c", "d"};
    EXPECT_THAT(four, ::testing::ContainerEq(expected_four));
}

}  // namespace string
}  // namespace djehuti
