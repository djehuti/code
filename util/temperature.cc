// Copyright (c) 2019 Ben Cox <cox@djehuti.com>. All Rights Reserved.

#include "util/temperature.hh"

namespace djehuti {

constexpr double Temperature::DEFAULT_TOLERANCE;
constexpr double Temperature::FREEZING_F;
constexpr double Temperature::BOILING_F;
constexpr double Temperature::FREEZING_C;
constexpr double Temperature::BOILING_C;
constexpr double Temperature::FREEZING_K;
constexpr double Temperature::BOILING_K;
constexpr double Temperature::BODY_TEMP_C;
constexpr double Temperature::KF_FACTOR;
constexpr double Temperature::FK_FACTOR;

const Temperature &Temperature::freezing() {
    static const Temperature freeze(FREEZING_K);
    return freeze;
}

const Temperature &Temperature::boiling() {
    static const Temperature boil(BOILING_K);
    return boil;
}

const Temperature &Temperature::absolute_zero() {
    static const Temperature zero;
    return zero;
}

const Temperature &Temperature::body_temp() {
    static const auto body_temp = Temperature::from_celsius(BODY_TEMP_C);
    return body_temp;
}

std::ostream &operator<<(std::ostream &os, const Temperature &temp) {
    switch (os.iword(Temperature::geti())) {
    case Temperature::KELVIN:
        os << temp.kelvin();
        break;
    case Temperature::CELSIUS:
        os << temp.celsius();
        break;
    case Temperature::FAHRENHEIT:
        os << temp.fahrenheit();
        break;
    default:  // AUTO and invalid values come here.
        os << temp.kelvin() << "_kelvin";
        break;
    }
    return os;
}

}  // namespace djehuti
