# Copyright (C) 2019 Ben Cox <cox@djehuti.com>. All Rights Reserved.

cc_library(
    name = "pistache",
    srcs = glob(["src/common/*.cc", "src/client/*.cc", "src/server/*.cc"]),
    hdrs = glob(["**/*.h"]),
    copts = ["-Iexternal/pistache/include"],
    includes = ["include"],
    deps = [
        "@gtest//:main",
    ],
    visibility = ["//visibility:public"],
)
