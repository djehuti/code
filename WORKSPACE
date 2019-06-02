# Copyright (c) 2019 Ben Cox <cox@djehuti.com>. All Rights Reserved.

workspace(name = "code")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "com_github_gflags_gflags",
    url = "https://github.com/gflags/gflags/archive/v2.2.2.zip",
    sha256 = "19713a36c9f32b33df59d1c79b4958434cb005b5b47dc5400a7a4b078111d9b5",
    strip_prefix = "gflags-2.2.2",
)

http_archive(
    name = "glog",
    url = "https://github.com/google/glog/archive/v0.4.0.zip",
    sha256 = "9e1b54eb2782f53cd8af107ecf08d2ab64b8d0dc2b7f5594472f3bd63ca85cdc",
    strip_prefix = "glog-0.4.0",
)

http_archive(
    name = "gtest",
    url = "https://github.com/google/googletest/archive/release-1.8.1.zip",
    sha256 = "927827c183d01734cc5cfef85e0ff3f5a92ffe6188e0d18e909c5efebf28a0c7",
    build_file = "@//build:gtest.BUILD",
    strip_prefix = "googletest-release-1.8.1",
)

http_archive(
    name = "pistache",
    url = "https://github.com/oktal/pistache/archive/117db02eda9d63935193ad98be813987f6c32b33.zip",
    sha256 = "3b3e57b2eb15cd5b295d2948bfd7fea37b1aabd73fc13197933f50919eafcfdf",
    build_file = "@//build:pistache.BUILD",
    strip_prefix = "pistache-117db02eda9d63935193ad98be813987f6c32b33",
)

# TODO(bcox): Stuff to add:
# https://en.cppreference.com/w/cpp/links/libs
#   * Flatbuffers               https://github.com/google/flatbuffers
#      + GRPC? Protobuf?
#   * Eigen                     https://bitbucket.org/eigen/eigen/src/default/
#   * curlpp                    https://github.com/jpbarrette/curlpp
#   * RapidJSON                 https://github.com/Tencent/rapidjson
#   * Zlib                      https://github.com/madler/zlib
#   * BoringSSL                 https://github.com/google/boringssl
#   * Synthesis Toolkit         https://ccrma.stanford.edu/software/stk/
#   * SOCI                      https://github.com/SOCI/soci
#      + SQLite3?
#   * Abseil?
#   + ZeroMQ?
#   * BDE (Blomberg)?
#   * OpenCV?
#   * JUCE?
#   * Qt?
#   * Dlib?
#   * Tensorflow?
#   * Libevent?
#   * FMOD?                     https://www.fmod.com/
