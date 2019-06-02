// Copyright (c) 2019 Ben Cox <cox@djehuti.com>. All Rights Reserved.

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
