#include "rlev1.h"
#include <cctype>

std::string RLE_V1::encode(const std::string &text) {
    std::string encoded;
    int count = 1;
    for (size_t i = 1; i <= text.size(); ++i) {
        if (i == text.size() || text[i] != text[i - 1]) {
            encoded += std::to_string(count) + text[i - 1];
            count = 1;
        } else {
            ++count;
        }
    }
    return encoded;
}

std::string RLE_V1::decode(const std::string &encoded) {
    std::string decoded;
    int count = 0;
    for (char c : encoded) {
        if (isdigit(c)) {
            count = count * 10 + (c - '0');
        } else {
            decoded += std::string(count == 0 ? 1 : count, c);
            count = 0;
        }
    }
    return decoded;
}
