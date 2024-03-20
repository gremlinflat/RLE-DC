#include "rlev2.h"
#include <cctype>

std::string RLE_V2::encode(const std::string &text) {
    std::string encoded;
    std::string encodedSingle = encodeSingle(text);
    encoded += encodedSingle;
    return encoded;
}

std::string RLE_V2::decode(const std::string &encoded) {
    std::string decoded;
    std::string decodedSingle = decodeSingle(encoded);
    decoded += decodedSingle;
    return decoded;
}

std::string RLE_V2::encodeSingle(const std::string &text) {
    std::string encodedSingle;
    char prevChar = text[0];
    int count = 1;
    for (size_t i = 1; i < text.size(); ++i) {
        if (text[i] != prevChar) {
            if (count > 1) {
                encodedSingle += std::to_string(count);
            }
            encodedSingle += prevChar;
            prevChar = text[i];
            count = 1;
        } else {
            ++count;
        }
    }
    if (count > 1) {
        encodedSingle += std::to_string(count);
    }
    encodedSingle += prevChar; // Last character count
    return encodedSingle;
}

std::string RLE_V2::decodeSingle(const std::string &encoded) {
    std::string decodedSingle;
    int count = 0;
    for (size_t i = 0; i < encoded.size(); ++i) {
        if (isdigit(encoded[i])) {
            count = count * 10 + (encoded[i] - '0');
        } else {
            decodedSingle += std::string(count == 0 ? 1 : count, encoded[i]);
            count = 0;
        }
    }
    return decodedSingle;
}
