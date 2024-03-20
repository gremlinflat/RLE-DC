#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "src/utils/logger.h"

#include "src/dcoding.h"
#include "src/rlev1.h"
#include "src/rlev2.h"

int main1() {
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

int compressionRatio(std::string original, std::string compressed) {
    return (compressed.size() * 100) / original.size();
}

void saveStringToFile(const std::string &filename, const std::string &text) {
    std::ofstream
        file(filename);
    file << text;
    file.close();
}

// read text file as a string
std::string readTextFileIntoSingleString(const std::string &filename) {
    std::ifstream file(filename);
    std::string text;
    std::string line;
    while (std::getline(file, line)) {
        text += line + "\n";
    }
    return text;
}

// read text file as an array of string
std::vector<std::string> readTextFile(const std::string &filename) {
    std::ifstream file(filename);
    std::vector<std::string> text;
    std::string line;
    while (std::getline(file, line)) {
        text.push_back(line);
    }
    return text;
}

int main() {
    DictCoding dc;
    dc.loadDictionary("english_dictionary_alpha.txt");

    // std::string text = "hello world henlo world workld world helli hello";
    // std::string text = readTextFileIntoSingleString("test/input_wiki.txt");
    // dc.learnDictionary(text);

    // dc.saveDictionary("learned_sequence.txt");

    std::string rawText = readTextFileIntoSingleString("test/input_wiki2.txt");

    std::string encoded = dc.encode(rawText);
    std::string decoded = dc.decode(encoded);

    std::cout << "Original: " << rawText << std::endl;

    saveStringToFile("test/encoded.txt", encoded);
    saveStringToFile("test/decoded.txt", decoded);

    std::cout << "Original size: " << rawText.size() << std::endl;
    std::cout << "Encoded size: " << encoded.size() << std::endl;
    std::cout << "Compression ratio: " << compressionRatio(rawText, encoded) << "%" << std::endl;

    return 0;
}
