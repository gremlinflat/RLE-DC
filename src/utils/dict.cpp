#include "dict.h"
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

void Dict::add(const std::string &word) {
    words.push_back(word);
}

bool Dict::contains(const std::string &word) const {
    for (const std::string &w : words) {
        if (w == word) {
            return true;
        }
    }
    return false;
}

std::string Dict::getWord(int index) const {
    return words[index];
}

int Dict::getIndex(const std::string &word) const {
    for (size_t i = 0; i < words.size(); i++) {
        if (words[i] == word) {
            return i;
        }
    }
    return -1;
}

std::vector<std::string> Dict::getWords() const {
    return words;
}

int Dict::size() const {
    return words.size();
}

void Dict::load(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: could not open file " << filename << std::endl;
        return;
    }

    std::string word;
    while (file >> word) {
        add(word);
    }
}

void Dict::save(const std::string &filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: could not open file " << filename << std::endl;
        return;
    }

    for (const std::string &word : words) {
        file << word << std::endl;
    }
}

void Dict::clear() {
    words.clear();
}