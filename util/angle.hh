// Copyright (c) 2019 Ben Cox <cox@djehuti.com>. All Rights Reserved.

#pragma once

#include <cmath>

namespace djehuti {

class Angle final {
 public:
    static constexpr double DEFAULT_TOLERANCE = 1e-5;

    constexpr Angle() : radians_(0.0) {}
    ~Angle() = default;

    constexpr Angle(const Angle &) = default;
    constexpr Angle(Angle &&) = default;
    Angle &operator=(const Angle &) = default;
    Angle &operator=(Angle &&) = default;

    constexpr double radians() const { return radians_; }
    constexpr double degrees() const { return radians_ * HALF_CIRCLE_DEG / M_PI; }

    static constexpr Angle from_radians(double radians) { return Angle(radians); }
    static constexpr Angle from_degrees(double degrees) {
        return Angle(degrees * M_PI / HALF_CIRCLE_DEG);
    }

    bool almost_equal(const Angle &other, double tolerance = DEFAULT_TOLERANCE) const {
        return std::abs(radians_ - other.radians_) <= std::abs(tolerance);
    }

    bool operator==(const Angle &other) const { return almost_equal(other); }
    bool operator!=(const Angle &other) const { return !almost_equal(other); }
    bool operator<(const Angle &other) const { return radians_ < other.radians_; }
    bool operator>(const Angle &other) const { return radians_ > other.radians_; }

    double sin() const { return std::sin(radians_); }
    double cos() const { return std::cos(radians_); }
    double tan() const { return std::tan(radians_); }
    double sinh() const { return std::sinh(radians_); }
    double cosh() const { return std::cosh(radians_); }
    double tanh() const { return std::tanh(radians_); }

    static Angle asin(double d) { return Angle(std::asin(d)); }
    static Angle acos(double d) { return Angle(std::acos(d)); }
    static Angle atan(double d) { return Angle(std::atan(d)); }
    static Angle atan2(double y, double x) { return Angle(std::atan2(y, x)); }
    static Angle asinh(double d) { return Angle(std::asinh(d)); }
    static Angle acosh(double d) { return Angle(std::acosh(d)); }
    static Angle atanh(double d) { return Angle(std::atanh(d)); }

 private:
    friend constexpr Angle operator*(const Angle &, double);
    friend constexpr Angle operator/(const Angle &, double);
    friend constexpr Angle operator+(const Angle &, const Angle &);
    friend constexpr Angle operator-(const Angle &, const Angle &);

    static constexpr double HALF_CIRCLE_DEG = 180.0;
    static constexpr double TWO_PI = 2.0 * M_PI;

    explicit constexpr Angle(double radians) : radians_(normalize(radians)) {}

    static constexpr double normalize(double r) {
        return (r < 0) ? normalize(r + TWO_PI) : ((r > TWO_PI) ? normalize(r - TWO_PI) : r);
    }

    double radians_;
};

constexpr Angle operator*(const Angle &ang, double mult) {
    return Angle(ang.radians() * mult);
}

constexpr Angle operator/(const Angle &ang, double div) {
    return Angle(ang.radians() / div);
}

constexpr Angle operator+(const Angle &ang1, const Angle &ang2) {
    return Angle(ang1.radians() + ang2.radians());
}

constexpr Angle operator-(const Angle &ang1, const Angle &ang2) {
    return Angle(ang1.radians() - ang2.radians());
}

namespace literals {

constexpr Angle operator "" _rad(long double radians) {
    return Angle::from_radians(static_cast<double>(radians));
}

constexpr Angle operator "" _deg(long double degrees) {
    return Angle::from_degrees(static_cast<double>(degrees));
}

}  // namespace literals

}  // namespace djehuti
