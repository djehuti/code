// Copyright (c) 2019 Ben Cox <cox@djehuti.com>. All Rights Reserved.

#pragma once

#include <cstdlib>
#include <type_traits>
#include <vector>

namespace djehuti {
namespace audio {

/**
 * An AudioBuffer holds a snippet of some number of channels of audio.
 * This object just holds the samples; it doesn't keep any indication of
 * channel ordering or sample rate; that is up to a higher-level abstraction.
 */
template <typename SampleType,
          typename = std::enable_if_t<std::is_default_constructible<SampleType>::value>>
class AudioBuffer {
 public:
    /// The default constructor creates an empty buffer (0 samples, 0 channels).
    AudioBuffer() = default;
    virtual ~AudioBuffer() = default;

    // Copyable and movable.
    AudioBuffer(const AudioBuffer &) = default;
    AudioBuffer(AudioBuffer &) = default;
    AudioBuffer &operator=(const AudioBuffer &) = default;
    AudioBuffer &operator=(AudioBuffer &) = default;

    /// Create an AudioBuffer with the given number of samples and channels.
    explicit AudioBuffer(size_t length, size_t num_channels = 1u)
        : length_(length),
          num_channels_(num_channels),
          samples_(length * num_channels) {}

    /// Resize the AudioBuffer.
    void reallocate(size_t length, size_t num_channels = 1u) {
        length_ = length;
        num_channels_ = num_channels;
        samples_.resize(length * num_channels);
    }

    /// Direct access to the raw samples. Is not bounds-checked.
    SampleType &at(size_t offset, size_t channel_num = 0u) {
        return samples_[index(offset, channel_num)];
    }

    /// Direct const access to the raw samples. Is not bounds-checked.
    const SampleType &at(size_t offset, size_t channel_num = 0u) const {
        return samples_[index(offset, channel_num)];
    }

    /// The length of the AudioBuffer, in samples.
    size_t length() const { return length_; }

    /// The number of audio channels.
    size_t num_channels() const { return num_channels_; }

 private:
    // Compute the index at which the given sample is stored.
    size_t index(size_t offset, size_t channel_num) {
        return offset * num_channels_ + channel_num;
    }

    size_t length_;
    size_t num_channels_;
    std::vector<SampleType> samples_;
};

}  // namespace audio
}  // namespace djehuti
