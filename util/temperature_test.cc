// Copyright (c) 2019 Ben Cox <cox@djehuti.com>. All Rights Reserved.

#include "util/temperature.hh"

#include "gtest/gtest.h"

using namespace djehuti::literals;

namespace djehuti {

TEST(Temperature, Basic) {
    auto absolute_zero = Temperature();
    EXPECT_EQ(absolute_zero, Temperature::absolute_zero());
    auto freezing = Temperature::freezing();
    EXPECT_EQ(absolute_zero, freezing.minus_kelvin(freezing.kelvin()));
    EXPECT_LT(Temperature::freezing(), Temperature::boiling());
    EXPECT_EQ(Temperature::freezing().plus_centigrade(100.0), Temperature::boiling());
    EXPECT_EQ(Temperature::freezing().plus_fahrenheit(180.0), Temperature::boiling());
    EXPECT_EQ(Temperature::from_fahrenheit(-459.67), Temperature::absolute_zero());
    EXPECT_EQ(32.0_fahrenheit, Temperature::freezing());
    EXPECT_EQ(37_centigrade, 98.6_fahrenheit);
}

}  // namespace djehuti
