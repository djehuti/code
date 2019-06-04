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
