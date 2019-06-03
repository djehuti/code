// Copyright (c) 2019 Ben Cox <cox@djehuti.com>. All Rights Reserved.

#include "audio/frequency.hh"

using namespace djehuti::literals;

namespace djehuti {
namespace audio {

constexpr double Frequency::DEFAULT_BEAT_TOLERANCE_HZ;
constexpr double Frequency::REFERENCE_NOTE;
constexpr double Frequency::REFERENCE_FREQ;
constexpr double Frequency::CROSSOVER_FREQ;

const Frequency &Frequency::audio_cd_sample_rate() {
    static const Frequency rate = 44100_hz;
    return rate;
}

const Frequency &Frequency::concert_pitch() {
    static const Frequency pitch = 440_hz;
    return pitch;
}

std::ostream &operator<<(std::ostream &os, const Frequency &freq) {
    switch (os.iword(Frequency::geti())) {
        case Frequency::HERTZ:
            os << freq.hertz();
            break;
        case Frequency::MIDI:
            os << freq.midi_note();
            break;
        case Frequency::PERIOD_SEC:
            os << freq.period_sec();
            break;
        default:  // AUTO and invalid values come here.
            os << freq.hertz() << "_hz";
            break;
    }
    return os;
}

}  // namespace audio
}  // namespace djehuti
