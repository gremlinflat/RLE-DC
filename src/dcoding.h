#ifndef DICT_CODING_H
#define DICT_CODING_H

#include <string>
#include <vector>

#include "utils/dict.h"

class DictCoding {
public:
    std::string encode(const std::string &sentence) const;
    std::string decode(const std::string &encodedSentence) const;

    void loadDictionary(const std::string &filename);
    void saveDictionary(const std::string &filename) const;

    void learnDictionary(const std::string &text, float threshold = 0.8); // append only, didnt flush the previous dictionary

    void clearDictionary();

private:
    Dict dict;
};

#endif
