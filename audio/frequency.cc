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
