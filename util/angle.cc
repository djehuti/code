// Copyright (c) 2019 Ben Cox <cox@djehuti.com>. All Rights Reserved.

#include "util/angle.hh"

namespace djehuti {

constexpr double Angle::DEFAULT_TOLERANCE;
constexpr double Angle::HALF_CIRCLE_DEG;
constexpr double Angle::TWO_PI;

std::ostream &operator<<(std::ostream &os, const Angle &angle) {
    switch (os.iword(Angle::geti())) {
        case Angle::RADIANS:
            os << angle.radians();
            break;
        case Angle::DEGREES:
            os << angle.degrees();
            break;
        default:  // AUTO and invalid values come here.
            os << angle.degrees() << "_deg";
            break;
    }
    return os;
}

}  // namespace djehuti
