#ifndef DICT_H
#define DICT_H

#include <string>
#include <vector>

// Dict class
// An abstaction layer of list of words
class Dict {
public:
    void add(const std::string &word);
    bool contains(const std::string &word) const;

    std::string getWord(int index) const;
    int getIndex(const std::string &word) const; // if not found, return -1

    std::vector<std::string> getWords() const;

    int size() const;

    void load(const std::string &filename);
    void save(const std::string &filename) const;

    void clear();

private:
    std::vector<std::string> words;
};

#endif
