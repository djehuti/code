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

#include <cmath>
#include <iostream>

#include "util/math.hh"

namespace djehuti {
namespace audio {

/**
 * Represents a pitch interval, as a ratio or in semitones or octaves.
 * Is an immutable value type that is copyable and mutable.
 */
class Interval final {
 public:
    static constexpr double DEFAULT_TOLERANCE = 1e-4;

    /// The default constructor returns a unison interval (0 semitones).
    constexpr Interval() : semitones_(0.0) {}
    ~Interval() = default;

    // Copyable and movable.
    constexpr Interval(const Interval &) = default;
    constexpr Interval(Interval &&) = default;
    Interval &operator=(const Interval &) = default;
    Interval &operator=(Interval &&) = default;

    /// Return the Interval expressed in semitones.
    constexpr double semitones() const { return semitones_; }
    /// Return the Interval expressed in cents.
    constexpr double cents() const { return semitones_ * CENTS_PER_SEMITONE; }
    /// Return the Interval expressed in octaves.
    constexpr double octaves() const { return semitones_ / SEMITONES_PER_OCTAVE; }
    /// Return the Interval expressed as a ratio.
    MAYBE_CONSTEXPR double ratio() const { return std::exp2(octaves()); }

    /// Create an Interval from a number of semitones.
    static constexpr Interval from_semitones(double semitones) { return Interval(semitones); }
    /// Create an Interval from a number of cents.
    static constexpr Interval from_cents(double cents) {
        return Interval(cents / CENTS_PER_SEMITONE);
    }
    /// Create an Interval from a number of octaves.
    static constexpr Interval from_octaves(double octaves) {
        return Interval(octaves * SEMITONES_PER_OCTAVE);
    }
    /// Create an Interval from a ratio.
    static MAYBE_CONSTEXPR Interval from_ratio(double ratio) {
        return Interval(SEMITONES_PER_OCTAVE * std::log2(ratio));
    }

    /// Returns true if the intervals are almost equivalent, with the given tolerance.
    constexpr bool almost_equal(const Interval &other, double tolerance = DEFAULT_TOLERANCE) const {
        return djehuti::abs(semitones_ - other.semitones_) <= tolerance;
    }

    /// Returns true if the intervals are exactly equal.
    constexpr bool operator==(const Interval &other) const {
        return semitones_ == other.semitones_;
    }
    /// Returns false if the intervals are exactly equal.
    constexpr bool operator!=(const Interval &other) const { return !(*this == other); }
    /// Returns true if this interval is smaller than the other.
    /// Downward intervals are smaller than upward intervals.
    constexpr bool operator<(const Interval &other) const { return semitones_ < other.semitones_; }
    /// Returns true if this interval is smaller than or equal to the other.
    /// Downward intervals are smaller than upward intervals.
    constexpr bool operator<=(const Interval &other) const {
        return semitones_ <= other.semitones_;
    }
    /// Returns true if this interval is larger than the other.
    /// Upward intervals are larger than downward intervals.
    constexpr bool operator>(const Interval &other) const { return semitones_ > other.semitones_; }
    /// Returns true if this interval is larger than or equal to the other.
    /// Upward intervals are larger than downward intervals.
    constexpr bool operator>=(const Interval &other) const {
        return semitones_ >= other.semitones_;
    }

    // Musically-useful intervals.
    static const Interval &unison();
    static const Interval &half_step();
    static const Interval &whole_step();
    static const Interval &major_second() { return whole_step(); }
    static const Interval &minor_third();
    static const Interval &major_third();
    static const Interval &fourth();
    static const Interval &perfect_fourth() { return fourth(); }
    static const Interval &tritone();
    static const Interval &augmented_fourth() { return tritone(); }
    static const Interval &diminshed_fifth() { return tritone(); }
    static const Interval &fifth();
    static const Interval &perfect_fifth() { return fifth(); }
    static const Interval &minor_sixth();
    static const Interval &major_sixth();
    static const Interval &minor_seventh();
    static const Interval &major_seventh();
    static const Interval &minor_ninth();
    static const Interval &major_ninth();
    static const Interval &minor_tenth();
    static const Interval &major_tenth();

    // I/O manipulators.
    static std::ostream &output_auto(std::ostream &os) { return output_format(os, AUTO); }
    static std::ostream &output_semitones(std::ostream &os) { return output_format(os, SEMITONES); }
    static std::ostream &output_cents(std::ostream &os) { return output_format(os, CENTS); }
    static std::ostream &output_octaves(std::ostream &os) { return output_format(os, OCTAVES); }
    // static std::ostream &output_musical(std::ostream &os) { return output_format(os, MUSICAL); }

 private:
    // Output format selectors.
    enum OutputFormat : long {
        AUTO = 0,
        SEMITONES = 1,
        CENTS = 2,
        OCTAVES = 3,
        // MUSICAL = 4
    };

    // Reference points.
    static constexpr double SEMITONES_PER_OCTAVE = 12.0;
    static constexpr double CENTS_PER_SEMITONE = 100.0;

    // This constructor is private; use a unit-safe factory instead.
    constexpr explicit Interval(double semitones) : semitones_(semitones) {}

    // Return the ios_base storage index for the format selector for Intervals.
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
    friend std::ostream &operator<<(std::ostream &, const Interval &);

    /// The interval is represented internally as a number of semitones.
    double semitones_;
};

/// When the stream output format is AUTO (the defalt), the stream inserter represents an Interval
/// in octaves if it if 1 octave or larger, in semitones if it is 1 semitone or larger but smaller
/// than an octave, and in cents if it is smaller than a semitone, and outputs a suffix indicating
/// which unit has been used (the same format accepted as literals in the C++ code).
/// For example, `os << Interval::output_auto << Interval::from_semitones(7)` will output
/// "7_semitones".
/// If the format is not AUTO (one of the output format manipulators has been used), it is output
/// as a plain number with the given units.
/// That is, `os << Interval::output_semitones << Interval::from_cents(50.0)` will output "0.5".
std::ostream &operator<<(std::ostream &os, const Interval &intv);

/// Returns the sum of the two intervals.
constexpr Interval operator+(const Interval &one, const Interval &other) {
    return Interval::from_semitones(one.semitones() + other.semitones());
}

/// Returns the difference between the intervals.
constexpr Interval operator-(const Interval &one, const Interval &other) {
    return Interval::from_semitones(one.semitones() - other.semitones());
}

/// Returns an Interval multiplied by the given factor.
template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
constexpr Interval operator*(const Interval &intv, const T &f) {
    return Interval::from_semitones(intv.semitones() * f);
}

/// Returns an Interval multiplied by the given factor.
template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
constexpr Interval operator*(const T &f, const Interval &intv) {
    return Interval::from_semitones(f * intv.semitones());
}

/// Returns an Interval that is this one divided by the given divisor.
template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
constexpr Interval operator/(const Interval &intv, const T &d) {
    return Interval::from_semitones(intv.semitones() / d);
}

}  // namespace audio

namespace literals {

/// You can express an interval in semitones (3.5_semitones).
inline constexpr audio::Interval operator"" _semitones(long double semis) {
    return audio::Interval::from_semitones(static_cast<double>(semis));
}

/// You can express an interval in semitones (7_semitones).
inline constexpr audio::Interval operator"" _semitones(unsigned long long semis) {
    return audio::Interval::from_semitones(static_cast<double>(semis));
}

/// You can express an interval in cents (50.0_cents).
inline constexpr audio::Interval operator"" _cents(long double cents) {
    return audio::Interval::from_cents(static_cast<double>(cents));
}

/// You can express an interval in cents (50_cents).
inline constexpr audio::Interval operator"" _cents(unsigned long long cents) {
    return audio::Interval::from_cents(static_cast<double>(cents));
}

/// You can express an interval in octaves (2.0_octaves).
inline constexpr audio::Interval operator"" _octaves(long double octaves) {
    return audio::Interval::from_octaves(static_cast<double>(octaves));
}

/// You can express an interval in octaves (1_octaves).
inline constexpr audio::Interval operator"" _octaves(unsigned long long octaves) {
    return audio::Interval::from_octaves(static_cast<double>(octaves));
}

}  // namespace literals

}  // namespace djehuti
