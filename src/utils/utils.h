#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

int compressionRatio(std::string original, std::string compressed);

void saveStringToFile(const std::string &filename, const std::string &text);

std::string readTextFileIntoSingleString(const std::string &filename);

std::vector<std::string> readTextFile(const std::string &filename);

// get current time in high resolution
long long getCurrentTime();

// get delta time in nano seconds
long long getDeltaTime(long long start, long long end);

#endif