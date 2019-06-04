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

#include "audio/audiobuffer.hh"

#include "gtest/gtest.h"

#include "util/angle.hh"

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
