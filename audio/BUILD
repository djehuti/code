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
