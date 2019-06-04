// Copyright (c) 2019 Ben Cox <cox@djehuti.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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
