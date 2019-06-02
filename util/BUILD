# Copyright (c) 2019 Ben Cox <cox@djehuti.com>. All Rights Reserved.

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "angle",
    srcs = ["angle.cc"],
    hdrs = ["angle.hh"],
)

cc_test(
    name = "angle_test",
    size = "small",
    srcs = ["angle_test.cc"],
    deps = [
        ":angle",
        "@gtest//:main",
    ],
)

cc_library(
    name = "temperature",
    srcs = ["temperature.cc"],
    hdrs = ["temperature.hh"],
)

cc_test(
    name = "temperature_test",
    size = "small",
    srcs = ["temperature_test.cc"],
    deps = [
        ":temperature",
        "@gtest//:main",
    ],
)

cc_library(
    name = "string",
    srcs = ["string.cc"],
    hdrs = ["string.hh"],
)

cc_test (
    name = "string_test",
    size = "small",
    srcs = ["string_test.cc"],
    deps = [
        ":string",
        "@gtest//:main",
        "@gtest//:gmock",
    ],
)
