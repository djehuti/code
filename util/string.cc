// Copyright (c) 2019 Ben Cox <cox@djehuti.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "util/string.hh"

#include <sstream>

namespace djehuti {
namespace string {

std::vector<std::string> split(const std::string &whole, char separator) {
    std::istringstream iss(whole);
    std::string part;
    std::vector<std::string> parts;
    while (!iss.eof()) {
        int c = iss.get();
        if (c == std::istringstream::traits_type::eof()) {
            break;
        }
        if (c == static_cast<int>(separator)) {
            if (!part.empty()) {
                parts.emplace_back(std::move(part));
                part = "";
            }
        } else {
            part.push_back(static_cast<char>(c));
        }
    }
    if (!part.empty()) {
        parts.emplace_back(std::move(part));
    }
    return parts;
}

std::string join(const std::vector<std::string> &parts, const std::string &separator) {
    std::ostringstream oss;
    bool first = true;
    for (const auto &part : parts) {
        if (!first) {
            oss << separator;
        }
        first = false;
        oss << part;
    }
    return oss.str();
}

}  // namespace string
}  // namespace djehuti
