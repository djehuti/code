// Copyright (C) 2019 Ben Cox <cox@djehuti.com>. All Rights Reserved.

#pragma once

#include <cmath>

namespace djehuti {

class Temperature final {
 public:
    static constexpr double DEFAULT_TOLERANCE = 1e-4;

    Temperature() : kelvin_(0) {}
    
    Temperature(const Temperature &other) = default;
    Temperature(Temperature &&other) = default;
    Temperature &operator=(const Temperature &other) = default;
    Temperature &operator=(Temperature &&other) = default;

    double kelvin() const { return kelvin_; }
    double celsius() const { return Temperature::k_to_c(kelvin_); }
    double centigrade() const { return Temperature::k_to_c(kelvin_); }
    double fahrenheit() const { return Temperature::k_to_f(kelvin_); }

    static Temperature from_kelvin(double k) { return Temperature(k); }
    static Temperature from_celsius(double c) { return Temperature(Temperature::c_to_k(c)); }
    static Temperature from_centigrade(double c) { return from_celsius(c); }
    static Temperature from_fahrenheit(double f) { return Temperature(Temperature::f_to_k(f)); }

    static const Temperature &freezing();
    static const Temperature &boiling();
    static const Temperature &absolute_zero();

    Temperature plus_kelvin(double k) const {
        Temperature result(*this);
        result.kelvin_ += k;
        return result;
    }

    Temperature plus_celsius(double c) const { return plus_kelvin(c); }
    Temperature plus_centigrade(double c) const { return plus_kelvin(c); }
    Temperature plus_fahrenheit(double f) const { return plus_kelvin(f * FK_FACTOR); }

    Temperature minus_kelvin(double k) const { return plus_kelvin(-k); }
    Temperature minus_celsius(double c) const { return minus_kelvin(c); }
    Temperature minus_centigrade(double c) const { return minus_kelvin(c); }
    Temperature minus_fahrenheit(double f) const { return plus_fahrenheit(-f); }

    bool almost_equal(const Temperature &other, double tolerance = DEFAULT_TOLERANCE) const {
        return std::abs(kelvin_ - other.kelvin_) <= DEFAULT_TOLERANCE;
    }

    bool operator==(const Temperature &other) const { return almost_equal(other); }
    bool operator!=(const Temperature &other) const { return !almost_equal(other); }
    bool operator<(const Temperature &other) const { return kelvin_ < other.kelvin_; }
    bool operator>(const Temperature &other) const { return kelvin_ > other.kelvin_; }

 private:
    explicit Temperature(double k) : kelvin_(k) {}

    static constexpr double FREEZING_F = 32.0;
    static constexpr double BOILING_F = 212.0;
    static constexpr double FREEZING_C = 0.0;
    static constexpr double BOILING_C = 100.0;
    static constexpr double FREEZING_K = 273.15;
    static constexpr double BOILING_K = FREEZING_K + (BOILING_C - FREEZING_C);

    static constexpr double KF_FACTOR = ((BOILING_F - FREEZING_F) / (BOILING_K - FREEZING_K));
    static constexpr double FK_FACTOR = ((BOILING_K - FREEZING_K) / (BOILING_F - FREEZING_F));

    static inline double c_to_k(double c) { return c + (FREEZING_K - FREEZING_C); }
    static inline double k_to_c(double k) { return k + (FREEZING_C - FREEZING_K); }

    static inline double f_to_k(double f) {
        return (f - FREEZING_F) * FK_FACTOR + FREEZING_K;
    }

    static inline double k_to_f(double k) {
        return (k - FREEZING_K) * KF_FACTOR + FREEZING_F;
    }

    double kelvin_;
};

}  // namespace djehuti
