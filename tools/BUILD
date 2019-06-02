# Copyright (c) 2019 Ben Cox <cox@djehuti.com>. All Rights Reserved.

cc_binary(
    name = "hworld",
    srcs = ["hworld.cc"],
)

cc_binary(
    name = "dumb_server",
    srcs = ["dumb_server.cc"],
    deps = [
        "@com_github_gflags_gflags//:gflags",
        "@glog//:glog",
        "@pistache//:pistache",
    ]
)

cc_test(
    name = "sample_test",
    srcs = ["sample_test.cc"],
    deps = [
        "@gtest//:main",
    ],
)
