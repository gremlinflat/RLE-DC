#include "utils.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

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

// get current time in high resolution
long long getCurrentTime() {
    return std::chrono::high_resolution_clock::now().time_since_epoch().count();
}

// get delta time in nano seconds
long long getDeltaTime(long long start, long long end = getCurrentTime()) {
    return end - start;
}
