// Copyright (c) 2019 Ben Cox <cox@djehuti.com>. All Rights Reserved.

#include "util/angle.hh"

#include "gtest/gtest.h"

using namespace djehuti::literals;

namespace djehuti {

TEST(AngleTests, Basic) {
    EXPECT_EQ(Angle::from_radians(M_PI) / 2, 90.0_deg);
    EXPECT_EQ(90.0_deg, Angle::asin(1.0));
    EXPECT_EQ(90.0_deg + 90.0_deg, Angle::from_radians(M_PI));
    EXPECT_EQ(90.0_deg, Angle::atan2(1, 0));
    EXPECT_EQ(45.0_deg, Angle::atan2(1, 1));
    EXPECT_LT(Angle::asin(0.8), 90.0_deg);
    EXPECT_EQ(400.0_deg, 40.0_deg);
    EXPECT_EQ(20_deg, 10_deg - 350_deg);
    EXPECT_EQ(340_deg, 350_deg - 10_deg);
    EXPECT_LT((80_deg).cos(), 1.0);
    EXPECT_EQ(Angle::from_radians(-(1e-6)), Angle::from_radians(1e-6));
    EXPECT_NE(180_deg, 0_deg);
    EXPECT_EQ(360_deg, 0_deg);
    EXPECT_NE(90_deg, 270_deg);
    EXPECT_DOUBLE_EQ(0.8, Angle::atan2(4, 3).sin());
    EXPECT_DOUBLE_EQ(0.6, Angle::atan2(4, 3).cos());
}

}  // namespace djehuti
