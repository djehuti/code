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
