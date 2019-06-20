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
    deps = [
        "//util:math",
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
