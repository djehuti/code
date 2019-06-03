// Copyright (c) 2019 Ben Cox <cox@djehuti.com>. All Rights Reserved.

#include "util/temperature.hh"

#include <sstream>

#include "gtest/gtest.h"

using namespace djehuti::literals;

namespace djehuti {

TEST(Temperature, Basic) {
    auto absolute_zero = Temperature();
    EXPECT_EQ(absolute_zero, Temperature::absolute_zero());
    auto freezing = Temperature::freezing();
    EXPECT_TRUE(absolute_zero.almost_equal(freezing.minus_kelvin(freezing.kelvin())));
    EXPECT_LT(Temperature::freezing(), Temperature::boiling());
    EXPECT_TRUE(
        Temperature::freezing().plus_centigrade(100.0).almost_equal(Temperature::boiling()));
    EXPECT_TRUE(
        Temperature::freezing().plus_fahrenheit(180.0).almost_equal(Temperature::boiling()));
    EXPECT_TRUE(Temperature::from_fahrenheit(-459.67).almost_equal(Temperature::absolute_zero()));
    EXPECT_TRUE(Temperature::freezing().almost_equal(32.0_fahrenheit));
    EXPECT_TRUE((37_centigrade).almost_equal(98.6_fahrenheit));
}

TEST(Temperature, Output) {
    {
        std::ostringstream oss;
        oss << Temperature::freezing();
        EXPECT_EQ(oss.str(), "273.15_kelvin");
    }
    {
        std::ostringstream oss;
        oss << Temperature::output_auto << Temperature::absolute_zero();
        EXPECT_EQ(oss.str(), "0_kelvin");
    }
    {
        std::ostringstream oss;
        oss << Temperature::output_kelvin << Temperature::boiling();
        EXPECT_EQ(oss.str(), "373.15");
    }
    {
        std::ostringstream oss;
        oss << Temperature::output_celsius << Temperature::body_temp();
        EXPECT_EQ(oss.str(), "37");
    }
    {
        std::ostringstream oss;
        oss << Temperature::output_centigrade << Temperature::freezing();
        EXPECT_EQ(oss.str(), "0");
    }
    {
        std::ostringstream oss;
        oss << Temperature::output_fahrenheit << Temperature::body_temp();
        EXPECT_EQ(oss.str(), "98.6");
    }
    {
        std::ostringstream oss;
        oss << Temperature::output_kelvin << 40_kelvin << "/" << Temperature::output_celsius
            << 20_centigrade << "/" << Temperature::output_fahrenheit << 0_celsius << "/"
            << Temperature::output_auto << 100_kelvin;
        EXPECT_EQ(oss.str(), "40/20/32/100_kelvin");
    }
}

}  // namespace djehuti
