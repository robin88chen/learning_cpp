#pragma once
#include <stdexcept>

template <typename T>
void fail_throw(bool is_fail, const std::string& msg) {
    throw T(msg);
}
