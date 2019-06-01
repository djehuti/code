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

}  // namespace djehuti
