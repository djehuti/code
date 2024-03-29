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

#include "audio/frequency.hh"

#include <sstream>

#include "gtest/gtest.h"

using namespace djehuti::literals;
using namespace std::literals::chrono_literals;

namespace djehuti {
namespace audio {

#if HAVE_CONSTANT_CMATH
#define C4_FLAT 59.43_midi
#define C4 60_midi
#define Eb4 63_midi
#define A4 69_midi
#define C6 84_midi
#else
#define C4_FLAT Frequency::from_midi_note(59.43)
#define C4 Frequency::from_midi_note(60)
#define Eb4 Frequency::from_midi_note(63)
#define A4 Frequency::from_midi_note(69)
#define C6 Frequency::from_midi_note(84)
#endif

TEST(FrequencyTest, BasicTest) {
    EXPECT_DOUBLE_EQ((10_hz).period_sec(), 0.1);
    EXPECT_TRUE((0.25_hz).almost_equal(4_secper));
    EXPECT_TRUE((440_hz).minus_interval(1_octaves).almost_equal(220_hz));
    EXPECT_TRUE((C4).plus_interval(2_octaves).almost_equal(C6));
    EXPECT_TRUE((C4).interval(C4_FLAT).almost_equal(57_cents));
    EXPECT_TRUE((Pitch() - 12_semitones).interval(110_hz).almost_equal(1_octaves));
    EXPECT_TRUE((440_hz).beat_frequency(438_hz).almost_equal(2_hz));
    EXPECT_TRUE((440_hz + Interval::fifth() + 1.95_cents).almost_equal(660_hz));
    EXPECT_TRUE((C4 + Interval::minor_third()).almost_equal(Eb4));
    EXPECT_TRUE(Frequency::from_period(1000ns).almost_equal(1000000_hz));
    EXPECT_TRUE(Frequency::from_period(10s).almost_equal(0.1_hz));
    EXPECT_EQ((40_hz).period(), 25ms);
    EXPECT_TRUE((75_hz).almost_equal(Frequency::from_period(
        std::chrono::duration_cast<std::chrono::nanoseconds>(cd_frames(1)))));
}

TEST(FrequencyTest, IntervalOutput) {
    {
        std::ostringstream oss;
        oss << 7_semitones;
        EXPECT_EQ(oss.str(), "7_semitones");
    }
    {
        std::ostringstream oss;
        oss << Interval::output_auto << 7_semitones;
        EXPECT_EQ(oss.str(), "7_semitones");
    }
    {
        std::ostringstream oss;
        oss << Interval::output_semitones << 1_octaves;
        EXPECT_EQ(oss.str(), "12");
    }
    {
        std::ostringstream oss;
        oss << Interval::output_cents << 1.5_semitones;
        EXPECT_EQ(oss.str(), "150");
    }
    {
        std::ostringstream oss;
        oss << Interval::output_octaves << (Interval::tritone() * 5.0);
        EXPECT_EQ(oss.str(), "2.5");
    }
    {
        std::ostringstream oss;
        oss << Interval::output_semitones << 1_semitones << "/" << Interval::output_auto
            << 1_semitones;
        EXPECT_EQ(oss.str(), "1/1_semitones");
    }
}

TEST(FrequencyTest, FrequencyOutput) {
    {
        std::ostringstream oss;
        oss << 440_hz;
        EXPECT_EQ(oss.str(), "440_hz");
    }
    {
        std::ostringstream oss;
        oss << Frequency::output_auto << 1738_hz;
        EXPECT_EQ(oss.str(), "1738_hz");
    }
    {
        std::ostringstream oss;
        oss << Frequency::output_hertz << A4;
        EXPECT_EQ(oss.str(), "440");
    }
    {
        std::ostringstream oss;
        oss << Frequency::output_midi << A4 - 9_semitones;
        EXPECT_EQ(oss.str(), "60");
    }
    {
        std::ostringstream oss;
        oss << Frequency::output_period_sec << 0.25_hz;
        EXPECT_EQ(oss.str(), "4");
    }
    {
        std::ostringstream oss;
        oss << Frequency::output_hertz << 440_hz << "/" << Frequency::output_midi
            << (440_hz - Interval::fifth()) << "/" << Frequency::output_auto << 10_secper;
        EXPECT_EQ(oss.str(), "440/62/0.1_hz");
    }
}

}  // namespace audio
}  // namespace djehuti
