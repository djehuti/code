# Copyright (c) 2019 Ben Cox <cox@djehuti.com>. All Rights Reserved.

workspace(name = "code")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

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
