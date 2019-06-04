# Copyright (c) 2019 Ben Cox <cox@djehuti.com>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

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
