cc_library(
    name = "main",
    srcs = glob(
        ["googletest/src/*.cc", "googletest/src/*.h"],
        exclude = ["googletest/src/gtest-all.cc"]
    ),
    hdrs = glob([
        "googletest/**/*.h",
    ]),
    copts = ["-Iexternal/gtest/googletest"],
    includes = ["googletest/include"],
    linkopts = ["-pthread"],
    visibility = ["//visibility:public"],
)
