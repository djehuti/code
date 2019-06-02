cc_library(
    name = "main",
    srcs = glob(
        ["googletest/src/*.cc", "googletest/src/*.h"],
        exclude = ["googletest/src/gtest-all.cc"],
    ),
    hdrs = glob([
        "googletest/**/*.h",
    ]),
    copts = ["-Iexternal/gtest/googletest"],
    includes = ["googletest/include"],
    linkopts = ["-lpthread"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "gmock",
    srcs = glob(
        ["googlemock/src/*.cc", "googlemock/src/*.h"],
        exclude = ["googlemock/src/gmock-all.cc"],
    ),
    hdrs = glob([
        "googlemock/**/*.h",
    ]),
    copts = ["-Iexternal/gtest/googlemock"],
    includes = ["googlemock/include"],
    linkopts = ["-lpthread"],
    visibility = ["//visibility:public"],
    deps = [
        ":main",
    ],
)
