// Copyright (C) 2019 Ben Cox <cox@djehuti.com>. All Rights Reserved.

#pragma once

#include <cmath>
#include <iostream>

namespace djehuti {

/**
 * The Temperature class represents a temperature in a unit-safe way.
 * It is an immutable copyable and movable value type.
 */
class Temperature final {
 public:
    /// This is the default tolerance argument for almost_equal, and is used in operator==/!=.
    static constexpr double DEFAULT_TOLERANCE = 1e-5;

    /// The default constructor gives absolute zero.
    constexpr Temperature() : kelvin_(0) {}

    ~Temperature() = default;

    // Copyable and movable.
    constexpr Temperature(const Temperature &) = default;
    constexpr Temperature(Temperature &&) = default;
    Temperature &operator=(const Temperature &) = default;
    Temperature &operator=(Temperature &&) = default;

    /// Return the temperature expressed in Kelvin.
    constexpr double kelvin() const { return kelvin_; }

    /// Return the temperature expressed in degrees Celsius.
    constexpr double celsius() const { return Temperature::k_to_c(kelvin_); }

    /// Return the temperature expressed in degrees centigrade (synonym for Celsius).
    constexpr double centigrade() const { return Temperature::k_to_c(kelvin_); }

    /// Return the temperature expressed in degrees Fahrenheit.
    constexpr double fahrenheit() const { return Temperature::k_to_f(kelvin_); }

    /// Return a Temperature from a Kelvin measurement.
    static constexpr Temperature from_kelvin(double k) { return Temperature(k); }

    /// Return a Temperature from a Celsius measurement.
    static constexpr Temperature from_celsius(double c) {
        return Temperature(Temperature::c_to_k(c));
    }

    /// Return a Temperature from a centigrade measurement (synonym for Celsius).
    static constexpr Temperature from_centigrade(double c) { return from_celsius(c); }

    /// Return a Temperature from a Fahrenheit measurement.
    static constexpr Temperature from_fahrenheit(double f) {
        return Temperature(Temperature::f_to_k(f));
    }

    /// Returns the freezing point of water at standard sea level.
    static const Temperature &freezing();

    /// Returns the boiling point of water at standard sea level.
    static const Temperature &boiling();
 
    /// Returns absolute zero.
    static const Temperature &absolute_zero();

    /// Returns "normal human body temp".
    static const Temperature &body_temp();

    /// Returns a new Temperature, offset from this by the given Kelvin measure.
    constexpr Temperature plus_kelvin(double k) const {
        return Temperature(this->kelvin_ + k);
    }

    /// Returns a new Temperature, offset from this by the given Celsius measure (same as Kelvin).
    constexpr Temperature plus_celsius(double c) const { return plus_kelvin(c); }
    /// Returns a new Temperature, offset from this by the given centigrade measure (= Celsius).
    constexpr Temperature plus_centigrade(double c) const { return plus_kelvin(c); }
    /// Returns a new Temperature, offset from this by the given Fahrenheit measure.
    constexpr Temperature plus_fahrenheit(double f) const { return plus_kelvin(f * FK_FACTOR); }

    /// Returns a new Temperature, offset from this by the given Kelvin measure.
    constexpr Temperature minus_kelvin(double k) const { return plus_kelvin(-k); }
    /// Returns a new Temperature, offset from this by the given Celsius measure (same as Kelvin).
    constexpr Temperature minus_celsius(double c) const { return minus_kelvin(c); }
    /// Returns a new Temperature, offset from this by the given centigrade measure (= Celsius).
    constexpr Temperature minus_centigrade(double c) const { return minus_kelvin(c); }
    /// Returns a new Temperature, offset from this by the given Fahrenheit measure.
    constexpr Temperature minus_fahrenheit(double f) const { return plus_fahrenheit(-f); }

    /// Returns true if the two Temperatures are within `tolerance` Kelvin of one another.
    constexpr bool almost_equal(const Temperature &other,
                                double tolerance = DEFAULT_TOLERANCE) const {
        return std::abs(kelvin_ - other.kelvin_) <= std::abs(tolerance);
    }

    /// Returns true if the two Temperatures are exactly equal.
    constexpr bool operator==(const Temperature &other) const { return kelvin_ == other.kelvin_; }
    /// Returns false if the two Temperatures are exactly equal.
    constexpr bool operator!=(const Temperature &other) const { return !(*this == other); }
    /// Returns true if this Temperature is colder than the given Temperature.
    constexpr bool operator<(const Temperature &other) const { return kelvin_ < other.kelvin_; }
    /// Returns true if this Temperature is colder than or equal to the given Temperature.
    constexpr bool operator<=(const Temperature &other) const { return kelvin_ <= other.kelvin_; }
    /// Returns true if this Temperature is hotter than or equal to the given Temperature.
    constexpr bool operator>=(const Temperature &other) const { return kelvin_ >= other.kelvin_; }

    // I/O manipulators
    static std::ostream &output_auto(std::ostream &os) { return output_format(os, AUTO); }
    static std::ostream &output_kelvin(std::ostream &os) { return output_format(os, KELVIN); }
    static std::ostream &output_celsius(std::ostream &os) { return output_format(os, CELSIUS); }
    static std::ostream &output_centigrade(std::ostream &os) { return output_celsius(os); }
    static std::ostream &output_fahrenheit(std::ostream &os) {
        return output_format(os, FAHRENHEIT);
    }

 private:
    enum OutputFormat : long {
        AUTO = 0,
        KELVIN = 1,
        CELSIUS = 2,
        FAHRENHEIT = 3,
    };

    // This constructor is private; use one of the unit-safe factory methods instead.
    constexpr explicit Temperature(double k) : kelvin_(k) {}

    // Reference points.
    static constexpr double FREEZING_F = 32.0;
    static constexpr double BOILING_F = 212.0;
    static constexpr double FREEZING_C = 0.0;
    static constexpr double BOILING_C = 100.0;
    static constexpr double FREEZING_K = 273.15;
    static constexpr double BOILING_K = FREEZING_K + (BOILING_C - FREEZING_C);
    static constexpr double BODY_TEMP_C = 37.0;

    // Conversion factors.
    static constexpr double KF_FACTOR = ((BOILING_F - FREEZING_F) / (BOILING_K - FREEZING_K));
    static constexpr double FK_FACTOR = ((BOILING_K - FREEZING_K) / (BOILING_F - FREEZING_F));

    // Internal unit conversions.
    static inline constexpr double c_to_k(double c) { return c + (FREEZING_K - FREEZING_C); }
    static inline constexpr double k_to_c(double k) { return k + (FREEZING_C - FREEZING_K); }

    static inline constexpr double f_to_k(double f) {
        return (f - FREEZING_F) * FK_FACTOR + FREEZING_K;
    }

    static inline constexpr double k_to_f(double k) {
        return (k - FREEZING_K) * KF_FACTOR + FREEZING_F;
    }

    // Return the ios_base storage index for the format selector for Temperature.
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
    friend std::ostream &operator<<(std::ostream &, const Temperature &);

    /// The Temperature is internally stored in Kelvin.
    double kelvin_;
};

/// The stream inserter outputs the temp in Kelvin with "_kelvin" by default (if no stream
/// manipulator or Temperature::output_auto is used). If another output manipulator is used,
/// it outputs a raw number with no unit suffix.
std::ostream &operator<<(std::ostream &, const Temperature &);

namespace literals {

/// You can express a Temperature as a numeric literal (273.15_kelvin).
constexpr Temperature operator "" _kelvin(long double k) {
    return Temperature::from_kelvin(static_cast<double>(k));
}

/// You can express a Temperature as a numeric literal (0_kelvin).
constexpr Temperature operator "" _kelvin(unsigned long long k) {
    return Temperature::from_kelvin(static_cast<double>(k));
}

/// You can express a Temperature as a numeric literal (37.0_celsius).
constexpr Temperature operator "" _celsius(long double c) {
    return Temperature::from_celsius(static_cast<double>(c));
}

/// You can express a Temperature as a numeric literal (27_celsius).
constexpr Temperature operator "" _celsius(unsigned long long c) {
    return Temperature::from_celsius(static_cast<double>(c));
}

/// You can express a Temperature as a numeric literal (44.2_centigrade).
constexpr Temperature operator "" _centigrade(long double c) {
    return Temperature::from_centigrade(static_cast<double>(c));
}

/// You can express a Temperature as a numeric literal (100_centigrade).
constexpr Temperature operator "" _centigrade(unsigned long long c) {
    return Temperature::from_centigrade(static_cast<double>(c));
}

/// You can express a Temperature as a numeric literal (98.6_fahrenheit).
constexpr Temperature operator "" _fahrenheit(long double f) {
    return Temperature::from_fahrenheit(static_cast<double>(f));
}

/// You can express a Temperature as a numeric literal (32_fahrenheit).
constexpr Temperature operator "" _fahrenheit(unsigned long long f) {
    return Temperature::from_fahrenheit(static_cast<double>(f));
}

}  // namespace literals

}  // namespace djehuti
