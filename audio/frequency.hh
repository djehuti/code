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

#pragma once

#include <chrono>
#include <cmath>
#include <iostream>

#include "audio/interval.hh"
#include "util/math.hh"

namespace djehuti {
namespace audio {

using cd_frames = std::chrono::duration<int64_t, std::ratio<1, 75>>;

/**
 * Represents a frequency/pitch/period.
 * Is an immutable, copyable and movable value type.
 */
class Frequency final {
 public:
    /// The default constructor returns A440.
    constexpr Frequency() : hertz_(REFERENCE_FREQ) {}
    ~Frequency() = default;

    // Copyable and movable.
    constexpr Frequency(const Frequency &) = default;
    constexpr Frequency(Frequency &&) = default;
    Frequency &operator=(const Frequency &) = default;
    Frequency &operator=(Frequency &&) = default;

    /// Return the Frequency expressed in Hz.
    constexpr double hertz() const { return hertz_; }
    /// Return the Frequency expressed as a cycle length in seconds (1/Hz).
    constexpr double period_sec() const { return 1.0 / hertz_; }
    /// Return the Frequency expressed as a cycle length (1/Hz).
    MAYBE_CONSTEXPR std::chrono::nanoseconds period() const {
        return std::chrono::nanoseconds(std::lround(period_sec() * BILLION));
    }
    /// Returns the Frequency expressed as a MIDI note number.
    MAYBE_CONSTEXPR double midi_note() const {
        return REFERENCE_NOTE + Interval::from_ratio(hertz_ / REFERENCE_FREQ).semitones();
    }

    /// Create a Frequency from Hz.
    static constexpr Frequency from_hertz(double hz) { return Frequency(hz); }
    /// Create a Frequency from a cycle length in seconds (1/Hz).
    static constexpr Frequency from_period_sec(double period) { return Frequency(1.0 / period); }
    /// Create a Frequency from a cycle length (1/Hz).
    static constexpr Frequency from_period(const std::chrono::nanoseconds &period) {
        return Frequency::from_period_sec(static_cast<double>(period.count()) / BILLION);
    }
    /// Create a Frequency from a MIDI note number.
    static MAYBE_CONSTEXPR Frequency from_midi_note(double p) {
        return Frequency(REFERENCE_FREQ * Interval::from_semitones(p - REFERENCE_NOTE).ratio());
    }

    /// Return a Frequency representing the audio CD sample rate.
    static const Frequency &audio_cd_sample_rate();
    /// Return a Frequency representing modern concert pitch (A440).
    static const Frequency &concert_pitch();

    /// Return the Interval between this Frequency and the other.
    MAYBE_CONSTEXPR Interval interval(const Frequency &other) const {
        return Interval::from_ratio(hertz_ / other.hertz_);
    }
    /// Return the ratio between this Frequency and the other.
    constexpr double ratio(const Frequency &other) const { return hertz_ / other.hertz_; }
    /// Return the ratio between the period of this Frequency and the period of the other.
    constexpr double period_ratio(const Frequency &other) const { return other.hertz_ / hertz_; }
    /// Return the beat frequency between this Frequency and the other.
    constexpr Frequency beat_frequency(const Frequency &other) const {
        return Frequency(hertz_ - other.hertz_);
    }

    /// Return a new Frequency related to this one by the given interval in semitones.
    Frequency plus_interval(const Interval &i) const { return Frequency(hertz_ * i.ratio()); }
    /// Return a new Frequency related to this one by the given interval in semitones.
    Frequency minus_interval(const Interval &i) const { return Frequency(hertz_ / i.ratio()); }

    /// The default tolerance for the zerobeat function.
    static constexpr double DEFAULT_BEAT_TOLERANCE_HZ = 1e-3;
    // TODO(bcox): Why can't this be static constexpr Frequency DEFAULT_BEAT_TOLERANCE?
    // Compiler says "incomplete type" but the non-static ones are OK.

    /// Return true if the beat Frequency between this Frequency and the other is slower than
    /// the tolerance (tolerance given in Hertz).
    bool zerobeat(const Frequency &other, double tolerance_hz = DEFAULT_BEAT_TOLERANCE_HZ) const {
        return beat_frequency(other) <= Frequency::from_hertz(tolerance_hz);
    }

    /// Return true if the other Frequency is within the given interval of this one.
    bool in_unison(const Frequency &other, double tolerance = Interval::DEFAULT_TOLERANCE) const {
        return interval(other).almost_equal(Interval::from_cents(0.0), tolerance);
    }

    /// Returns true if this Frequency is "the same as" the other. (If below the crossover
    /// frequency, checks the beat frequency; if higher, checks the pitch unison).
    bool almost_equal(const Frequency &other) const {
        return (hertz_ < CROSSOVER_FREQ) ? zerobeat(other) : in_unison(other);
    }

    bool operator==(const Frequency &other) const { return hertz_ == other.hertz_; }
    bool operator!=(const Frequency &other) const { return !(*this == other); }
    bool operator<(const Frequency &other) const { return hertz_ < other.hertz_; }
    bool operator<=(const Frequency &other) const { return hertz_ <= other.hertz_; }
    bool operator>(const Frequency &other) const { return hertz_ > other.hertz_; }
    bool operator>=(const Frequency &other) const { return hertz_ >= other.hertz_; }

    // I/O manipulators.
    static std::ostream &output_auto(std::ostream &os) { return output_format(os, AUTO); }
    static std::ostream &output_hertz(std::ostream &os) { return output_format(os, HERTZ); }
    static std::ostream &output_midi(std::ostream &os) { return output_format(os, MIDI); }
    static std::ostream &output_period_sec(std::ostream &os) {
        return output_format(os, PERIOD_SEC);
    }
    // static std::ostream &output_notename(std::ostream &os) {
    //    return output_format(os, NOTENAME);
    // }

 private:
    // Output formats.
    enum OutputFormat : long {
        AUTO = 0,
        HERTZ = 1,
        MIDI = 2,
        PERIOD_SEC = 3,
        // NOTENAME = 4
    };

    // Reference points.
    static constexpr double REFERENCE_FREQ = 440.0;
    static constexpr double REFERENCE_NOTE = 69.0;
    static constexpr double CROSSOVER_FREQ = 88.0;
    static constexpr double BILLION = 1000000000.0;

    // This constructor is private; use one of the unit-safe factory methods.
    constexpr explicit Frequency(double hz) : hertz_(djehuti::abs(hz)) {}

    // Return the ios_base storage index for the format selector for Frequency.
    static int geti() {
        static int i = std::ios_base::xalloc();
        return i;
    }

    // Set the output format to the given value.
    static std::ostream &output_format(std::ostream &os, OutputFormat fmt) {
        os.iword(geti()) = fmt;
        return os;
    }

    // The stream inserter needs to access geti() and OutputFormat.
    friend std::ostream &operator<<(std::ostream &, const Frequency &);

    /// The Frequency is internally stored in Hz.
    double hertz_;
};

// Synonyms.
using Period = Frequency;
using Pitch = Frequency;

/// In AUTO mode (the default, or if Frequency::output_auto manipulator is used), the stream
/// inserter represents the Frequency as a _hz literal. In the other modes, a raw number in
/// the appropriate unit is output, with no suffix.
std::ostream &operator<<(std::ostream &, const Frequency &);

template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
Frequency operator*(const Frequency &freq, const T &f) {
    return Frequency::from_hertz(freq.hertz() * f);
}

template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
Frequency operator*(const T &f, const Frequency &freq) {
    return Frequency::from_hertz(f * freq.hertz());
}

template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
Frequency operator/(const Frequency &freq, const T &d) {
    return Frequency::from_hertz(freq.hertz() / d);
}

Frequency operator+(const Frequency &freq, const Interval &intv) {
    return Frequency::from_hertz(freq.hertz() * intv.ratio());
}

Frequency operator-(const Frequency &freq, const Interval &intv) {
    return Frequency::from_hertz(freq.hertz() / intv.ratio());
}

}  // namespace audio

namespace literals {

/// You can express a Frequency as a numeric constant (53.5_hz).
inline constexpr audio::Frequency operator"" _hz(long double hz) {
    return audio::Frequency::from_hertz(static_cast<double>(hz));
}

/// You can express a Frequency as a numeric constant (440_hz).
inline constexpr audio::Frequency operator"" _hz(unsigned long long hz) {
    return audio::Frequency::from_hertz(static_cast<long double>(hz));
}

#if HAVE_CONSTEXPR_CMATH

/// You can express a Frequency as a numeric MIDI note number constant (60.2_midi).
inline constexpr audio::Frequency operator"" _midi(long double midi) {
    return audio::Frequency::from_midi_note(static_cast<double>(midi));
}

/// You can express a Frequency as a numeric MIDI note number constant (72_midi).
inline constexpr audio::Frequency operator"" _midi(unsigned long long hz) {
    return audio::Frequency::from_midi_note(static_cast<long double>(hz));
}

#endif  // HAVE_CONSTEXPR_CMATH

/// You can express a Frequency by its period with _secper (0.25_secper = 4_hz).
inline constexpr audio::Frequency operator"" _secper(long double secper) {
    return audio::Frequency::from_period_sec(static_cast<double>(secper));
}

/// You can express a Frequency by its period with _secper (10_secper = 0.1_hz).
inline constexpr audio::Frequency operator"" _secper(unsigned long long secper) {
    return audio::Frequency::from_period_sec(static_cast<double>(secper));
}

}  // namespace literals

}  // namespace djehuti
