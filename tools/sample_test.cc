// Copyright (c) 2019 Ben Cox <cox@djehuti.com>. All Rights Reserved.

#include "gtest/gtest.h"

TEST(SampleTest, Basic) {
    int two = 2;
    int maybe_four = two + two;
    EXPECT_EQ(maybe_four, 4);
}
