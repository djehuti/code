# Copyright (c) 2019 Ben Cox <cox@djehuti.com>. All Rights Reserved.

package(default_visibility = ["//visibility:public"])

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
