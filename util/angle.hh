// Copyright (c) 2019 Ben Cox <cox@djehuti.com>. All Rights Reserved.

#pragma once

#include <cmath>
#include <iostream>

namespace djehuti {

/**
 * The Angle class represents an angle in a unit-safe way.
 * It is an immutable copyable and movable value type.
 */
class Angle final {
 public:
    /// This is the default tolerance argument for almost_equal, and is used in operator==/!=.
    static constexpr double DEFAULT_TOLERANCE = 1e-5;

    /// The default constructor returns a zero angle.
    constexpr Angle() : radians_(0.0) {}
    ~Angle() = default;

    // Copyable and movable.
    constexpr Angle(const Angle &) = default;
    constexpr Angle(Angle &&) = default;
    Angle &operator=(const Angle &) = default;
    Angle &operator=(Angle &&) = default;

    /// Return the Angle measurement in radians. Always in the range [0, 2*Pi).
    constexpr double radians() const { return radians_; }
    /// Return the Angle measurement in degrees. Always in the range [0, 360).
    constexpr double degrees() const { return radians_ * HALF_CIRCLE_DEG / M_PI; }

    /// Create an Angle from a measurement in radians.
    static constexpr Angle from_radians(double radians) { return Angle(radians); }

    /// Create an Angle from a measurement in degrees.
    static constexpr Angle from_degrees(double degrees) {
        return Angle(degrees * M_PI / HALF_CIRCLE_DEG);
    }

    /// Returns true if the two Angles are within `tolerance` radians of one other.
    bool almost_equal(const Angle &other, double tolerance = DEFAULT_TOLERANCE) const {
        double diff = radians_ - other.radians_;
        while (diff < -M_PI) {
            diff += TWO_PI;
        }
        while (diff >= M_PI) {
            diff -= TWO_PI;
        }
        return std::abs(diff) <= std::abs(tolerance);
    }

    /// Returns true if the two Angles are within 1e-5 radians of one another.
    bool operator==(const Angle &other) const { return almost_equal(other); }
    /// Returns false if the two Angles are within 1e-5 radians of one another.
    bool operator!=(const Angle &other) const { return !almost_equal(other); }
    /// Returns true if the Angle is smaller than the other.
    bool operator<(const Angle &other) const { return radians_ < other.radians_; }
    /// Returns true if the Angle is larger than the other.
    bool operator>(const Angle &other) const { return radians_ > other.radians_; }

    /// Returns the sine of the Angle.
    double sin() const { return std::sin(radians_); }
    /// Returns the cosine of the Angle.
    double cos() const { return std::cos(radians_); }
    /// Returns the tangent of the Angle.
    double tan() const { return std::tan(radians_); }
    /// Returns the hyperbolic sine of the Angle.
    double sinh() const { return std::sinh(radians_); }
    /// Returns the hyperbolic cosine of the Angle.
    double cosh() const { return std::cosh(radians_); }
    /// Returns the hyperbolic tangent of the Angle.
    double tanh() const { return std::tanh(radians_); }

    /// Returns the Angle whose sine is d.
    static Angle asin(double d) { return Angle(std::asin(d)); }
    /// Returns the Angle whose cosine is d.
    static Angle acos(double d) { return Angle(std::acos(d)); }
    /// Returns the Angle whose tangent is d.
    static Angle atan(double d) { return Angle(std::atan(d)); }
    /// Returns the Angle whose tangent is y/x.
    static Angle atan2(double y, double x) { return Angle(std::atan2(y, x)); }
    /// Returns the Angle whose hyperbolic sine is d.
    static Angle asinh(double d) { return Angle(std::asinh(d)); }
    /// Returns the Angle whose hyperbolic cosine is d.
    static Angle acosh(double d) { return Angle(std::acosh(d)); }
    /// Returns the Angle whose hyperbolic tangent is d.
    static Angle atanh(double d) { return Angle(std::atanh(d)); }

 private:
    friend constexpr Angle operator*(const Angle &, double);
    friend constexpr Angle operator/(const Angle &, double);
    friend constexpr Angle operator+(const Angle &, const Angle &);
    friend constexpr Angle operator-(const Angle &, const Angle &);

    static constexpr double HALF_CIRCLE_DEG = 180.0;
    static constexpr double TWO_PI = 2.0 * M_PI;

    // This constructor is private; use one of the static methods that specifies units instead.
    explicit constexpr Angle(double radians) : radians_(normalize(radians)) {}

    // Converts a radians measure to be in the range [0, 2*Pi).
    static constexpr double normalize(double r) {
        return (r < 0) ? normalize(r + TWO_PI) : ((r >= TWO_PI) ? normalize(r - TWO_PI) : r);
    }

    /// The Angle is internally stored in radians.
    double radians_;
};

/// Returns the (normalized) Angle multiplied by mult.
constexpr Angle operator*(const Angle &ang, double mult) {
    return Angle(ang.radians() * mult);
}

/// Returns the Angle divided by div.
constexpr Angle operator/(const Angle &ang, double div) {
    return Angle(ang.radians() / div);
}

/// Returns the (normalized) sum of the two Angles.
constexpr Angle operator+(const Angle &ang1, const Angle &ang2) {
    return Angle(ang1.radians() + ang2.radians());
}

/// Returns the (normalized) difference between the two Angles.
/// Note that if ang2 is larger than ang1, the result will be 360 degrees minus the difference,
/// and not a negative angle.
constexpr Angle operator-(const Angle &ang1, const Angle &ang2) {
    return Angle(ang1.radians() - ang2.radians());
}

namespace literals {

/// You can express an Angle as a radian literal ("1.0_rad").
constexpr Angle operator "" _rad(long double radians) {
    return Angle::from_radians(static_cast<double>(radians));
}

/// You can express an Angle as a degrees literal ("90.0_deg").
constexpr Angle operator "" _deg(long double degrees) {
    return Angle::from_degrees(static_cast<double>(degrees));
}

/// You can express an Angle as a degrees literal ("90_deg").
constexpr Angle operator "" _deg(unsigned long long degrees) {
    return Angle::from_degrees(static_cast<double>(degrees));
}

/// Output the Angle on the given stream (as a degrees literal).
std::ostream &operator<<(std::ostream &os, const Angle &angle) {
    return os << angle.degrees() << "_deg";
}

}  // namespace literals

}  // namespace djehuti
