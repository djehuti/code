// Copyright (c) 2019 Ben Cox <cox@djehuti.com>. All Rights Reserved.

#include "audio/audiobuffer.hh"

#include "util/angle.hh"

#include "gtest/gtest.h"

namespace djehuti {
namespace audio {

TEST(AudioBufferTest, Basic) {
    AudioBuffer<double> buf(361u, 2u);
    EXPECT_EQ(buf.length(), 361u);
    EXPECT_EQ(buf.num_channels(), 2u);

    size_t i;
    for (i = 0u; i <= 360u; ++i) {
        buf.at(i, 0u) = Angle::from_degrees(static_cast<double>(i)).sin();
        buf.at(i, 1u) = Angle::from_degrees(static_cast<double>(i)).cos();
    }

    auto buf2 = buf;
    EXPECT_EQ(buf2.length(), 361u);
    EXPECT_EQ(buf2.num_channels(), 2u);

    // Check that the buffer contents are the same.
    for (i = 0u; i <= 360u; ++i) {
        EXPECT_DOUBLE_EQ(buf.at(i, 0u), buf2.at(i, 0u));
        EXPECT_DOUBLE_EQ(buf.at(i, 1u), buf2.at(i, 1u));
    }

    // Now rewrite buf2.
    for (i = 0u; i <= 360u; ++i) {
        buf2.at(i, 0u) = Angle::from_degrees(static_cast<double>(i)).cos();
        buf2.at(i, 1u) = Angle::from_degrees(static_cast<double>(i)).sin();
    }

    // Check that the buffer contents are now channel-swapped.
    for (i = 0u; i <= 360u; ++i) {
        EXPECT_DOUBLE_EQ(buf.at(i, 0u), buf2.at(i, 1u));
        EXPECT_DOUBLE_EQ(buf.at(i, 1u), buf2.at(i, 0u));
    }

    // Check the assignment operator.
    buf2 = buf;

    // Check that the buffer contents are the same again.
    for (i = 0u; i <= 360u; ++i) {
        EXPECT_DOUBLE_EQ(buf.at(i, 0u), buf2.at(i, 0u));
        EXPECT_DOUBLE_EQ(buf.at(i, 1u), buf2.at(i, 1u));
    }

    buf2.reallocate(721u, 2u);
    EXPECT_EQ(buf2.length(), 721u);
    EXPECT_EQ(buf.length(), 361u);
}

}  // namespace audio
}  // namespace djehuti
