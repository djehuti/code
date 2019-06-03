// Copyright (c) 2019 Ben Cox <cox@djehuti.com>. All Rights Reserved.

#include "util/angle.hh"

#include <sstream>

#include "gtest/gtest.h"

using namespace djehuti::literals;

namespace djehuti {

TEST(AngleTests, Basic) {
    EXPECT_TRUE((Angle::from_radians(M_PI) / 2).almost_equal(90.0_deg));
    EXPECT_TRUE(Angle::asin(1.0).almost_equal(90.0_deg));
    EXPECT_TRUE(Angle::from_radians(M_PI).almost_equal(90.0_deg + 90.0_deg));
    EXPECT_TRUE(Angle::atan2(1, 0).almost_equal(90.0_deg));
    EXPECT_TRUE(Angle::atan2(1, 1).almost_equal(45.0_deg));
    EXPECT_LT(Angle::asin(0.8), 90.0_deg);
    EXPECT_TRUE((400.0_deg).almost_equal(40.0_deg));
    EXPECT_TRUE((20_deg).almost_equal(10_deg - 350_deg));
    EXPECT_TRUE((340_deg).almost_equal(350_deg - 10_deg));
    EXPECT_LT((80_deg).cos(), 1.0);
    EXPECT_TRUE(Angle::from_radians(-(1e-6)).almost_equal(Angle::from_radians(1e-6)));
    EXPECT_NE(180_deg, 0_deg);
    EXPECT_TRUE((360_deg).almost_equal(0_deg));
    EXPECT_NE(90_deg, 270_deg);
    EXPECT_DOUBLE_EQ(0.8, Angle::atan2(4, 3).sin());
    EXPECT_DOUBLE_EQ(0.6, Angle::atan2(4, 3).cos());
}

TEST(AngleTests, Output) {
    {
        std::ostringstream oss;
        oss << 90_deg;
        EXPECT_EQ(oss.str(), "90_deg");
    }
    {
        std::ostringstream oss;
        oss << Angle::output_degrees << 45_deg;
        EXPECT_EQ(oss.str(), "45");
    }
    {
        std::ostringstream oss;
        oss << Angle::output_radians << 0_rad;
        EXPECT_EQ(oss.str(), "0");
    }
    {
        std::ostringstream oss;
        oss << Angle::output_degrees << 37_deg << "/" << Angle::output_auto << 110_deg;
        EXPECT_EQ(oss.str(), "37/110_deg");
    }
}

}  // namespace djehuti
