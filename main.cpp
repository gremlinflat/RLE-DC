#include <iostream>
#include <string>

#include "src/utils/logger.h"

#include "src/rlev1.h"
#include "src/rlev2.h"

int main() {
    std::string text;
    std::cout << "Enter text to encode: ";
    std::getline(std::cin, text);

    std::string method;
    std::cout << "1. RLE_V1 (basic original RLE)" << std::endl;
    std::cout << "2. RLE_V2 (improved RLE)" << std::endl;

    std::cout << "Enter method to use [1-2]: ";
    std::getline(std::cin, method);

    std::cout << std::endl;

    if (method == "1") {
        RLE_V1 rle;
        std::string encoded = rle.encode(text);
        std::string decoded = rle.decode(encoded);

        std::cout << "--- RLE_V1 ---" << std::endl;
        std::cout << "Original: " << text << std::endl;
        std::cout << "Encoded: " << encoded << std::endl;
        std::cout << "Decoded: " << decoded << std::endl;
    } else if (method == "2") {
        RLE_V2 rle;
        std::string encoded = rle.encode(text);
        std::string decoded = rle.decode(encoded);

        std::cout << "--- RLE_V2 ---" << std::endl;
        std::cout << "Original: " << text << std::endl;
        std::cout << "Encoded: " << encoded << std::endl;
        std::cout << "Decoded: " << decoded << std::endl;
    } else {
        std::cout << "Invalid method" << std::endl;
    }

    return 0;
}
