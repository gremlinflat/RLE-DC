#ifndef RLEV2_H
#define RLEV2_H

#include <string>

class RLE_V2 {
public:
    std::string encode(const std::string &text);
    std::string decode(const std::string &encoded);

private:
    std::string encodeSingle(const std::string &text);
    std::string decodeSingle(const std::string &encoded);
};

#endif