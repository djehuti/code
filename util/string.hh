// Copyright (c) 2019 Ben Cox <cox@djehuti.com>. All Rights Reserved.

#pragma once

#include <string>
#include <vector>

namespace djehuti {
namespace string {

/**
 * Split the given whole string into parts, separated by the given character.
 * Empty parts are discarded; split("::a:b:c::d::", ':') returns {"a","b","c","d"}.
 */
std::vector<std::string> split(const std::string &whole, char separator);

/// Join the given strings together, separated by the separator.
std::string join(const std::vector<std::string> &parts, const std::string &separator);

/// Join the given strings together, separated by the separator.
std::string join(const std::vector<std::string> &parts, char separator) {
    return join(parts, std::string(1u, separator));
}

}  // namespace string
}  // namespace djehuti
