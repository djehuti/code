// Copyright (c) 2019 Ben Cox <cox@djehuti.com>. All Rights Reserved.

#include "audio/interval.hh"

using namespace djehuti::literals;

namespace djehuti {
namespace audio {

constexpr double Interval::DEFAULT_TOLERANCE;
constexpr double Interval::SEMITONES_PER_OCTAVE;
constexpr double Interval::CENTS_PER_SEMITONE;

const Interval &Interval::unison() {
    static const Interval i = 0_semitones;
    return i;
}

const Interval &Interval::half_step() {
    static const Interval i = 1_semitones;
    return i;
}

const Interval &Interval::whole_step() {
    static const Interval i = 2_semitones;
    return i;
}

const Interval &Interval::minor_third() {
    static const Interval i = 3_semitones;
    return i;
}

const Interval &Interval::major_third() {
    static const Interval i = 4_semitones;
    return i;
}

const Interval &Interval::fourth() {
    static const Interval i = 5_semitones;
    return i;
}

const Interval &Interval::tritone() {
    static const Interval i = 6_semitones;
    return i;
}

const Interval &Interval::fifth() {
    static const Interval i = 7_semitones;
    return i;
}

const Interval &Interval::minor_sixth() {
    static const Interval i = 8_semitones;
    return i;
}

const Interval &Interval::major_sixth() {
    static const Interval i = 9_semitones;
    return i;
}

const Interval &Interval::minor_seventh() {
    static const Interval i = 10_semitones;
    return i;
}

const Interval &Interval::major_seventh() {
    static const Interval i = 11_semitones;
    return i;
}

const Interval &Interval::minor_ninth() {
    static const Interval i = 13_semitones;
    return i;
}

const Interval &Interval::major_ninth() {
    static const Interval i = 14_semitones;
    return i;
}

const Interval &Interval::minor_tenth() {
    static const Interval i = 15_semitones;
    return i;
}

const Interval &Interval::major_tenth() {
    static const Interval i = 16_semitones;
    return i;
}

std::ostream &operator<<(std::ostream &os, const Interval &intv) {
    switch (os.iword(Interval::geti())) {
        case Interval::SEMITONES:
            os << intv.semitones();
            break;
        case Interval::CENTS:
            os << intv.cents();
            break;
        case Interval::OCTAVES:
            os << intv.octaves();
            break;
        default:  // AUTO and invalid values will come here.
            if (std::abs(intv.semitones()) >= 12.0) {
                os << intv.octaves() << "_octaves";
            } else if (std::abs(intv.semitones()) >= 1.0) {
                os << intv.semitones() << "_semitones";
            } else {
                os << intv.cents() << "_cents";
            }
            break;
    }
    return os;
}

}  // namespace audio
}  // namespace djehuti
