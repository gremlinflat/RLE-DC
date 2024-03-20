#include "dcoding.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

std::string DictCoding::encode(const std::string &sentence) const {
    std::stringstream encoded;
    std::string word;
    std::istringstream iss(sentence);
    while (iss >> word) {
        int index = dict.getIndex(word);
        if (index != -1) {
            encoded << index << " ";
        } else {
            // Word not found in dictionary
            encoded << word << " "; // Use the word itself as code
        }
    }
    return encoded.str();
}

std::string DictCoding::decode(const std::string &encodedSentence) const {
    std::stringstream decoded;
    std::istringstream iss(encodedSentence);
    std::string code;
    while (iss >> code) {
        try {
            int index = std::stoi(code);
            if (index >= 0 && index < dict.size()) {
                decoded << dict.getWord(index) << " ";
            } else {
                // Code out of bounds, treat as unknown word
                decoded << code << " ";
            }
        } catch (const std::invalid_argument &) {
            // Not a valid integer code, treat as word
            decoded << code << " ";
        }
    }
    return decoded.str();
}

void DictCoding::loadDictionary(const std::string &filename) {
    dict.load(filename);
}

void DictCoding::saveDictionary(const std::string &filename) const {
    dict.save(filename);
}

void DictCoding::learnDictionary(const std::string &text, float threshold) {
    // Split text into words
    std::istringstream iss(text);
    std::string word;
    std::unordered_map<std::string, int> wordFreq;

    // Count the frequency of each word
    while (iss >> word) {
        wordFreq[word]++;
    }

    // Sort words by frequency in descending order
    std::vector<std::pair<std::string, int>> sortedWords(wordFreq.begin(), wordFreq.end());
    std::sort(sortedWords.begin(), sortedWords.end(),
              [](const auto &a, const auto &b) { return a.second > b.second; });

    // Pick threshold% of the most frequent words
    int numWordsToAdd = static_cast<int>(threshold * sortedWords.size());
    numWordsToAdd = std::max(numWordsToAdd, 1); // Ensure at least 1 word is added
    for (int i = 0; i < numWordsToAdd; ++i) {
        dict.add(sortedWords[i].first);
    }
}

void DictCoding::clearDictionary() {
    dict.clear();
}