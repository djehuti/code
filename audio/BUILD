# Copyright (c) 2019 Ben Cox <cox@djehuti.com>. All Rights Reserved.

cc_library(
    name = "audiobuffer",
    hdrs = ["audiobuffer.hh"],
)

cc_test(
    name = "audiobuffer_test",
    size = "small",
    srcs = ["audiobuffer_test.cc"],
    deps = [
        ":audiobuffer",
        "//util:angle",
        "@gtest//:main",
    ],
)

cc_library(
    name = "frequency",
    srcs = [
        "frequency.cc",
        "interval.cc",
    ],
    hdrs = [
        "frequency.hh",
        "interval.hh",
    ],
)

cc_test(
    name = "frequency_test",
    size = "small",
    srcs = ["frequency_test.cc"],
    deps = [
        ":frequency",
        "@gtest//:main",
    ],
)
