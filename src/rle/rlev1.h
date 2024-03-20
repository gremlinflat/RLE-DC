#ifndef RLEV1_H
#define RLEV1_H

#include <string>

class RLE_V1 {
public:
    std::string encode(const std::string &text);
    std::string decode(const std::string &encoded);
};

#endif
