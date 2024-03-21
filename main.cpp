#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "src/utils/logger.h"
#include "src/utils/utils.h"

#include "src/dcoding.h"
#include "src/rlev1.h"
#include "src/rlev2.h"

void rlev1() {
    RLE_V1 rle;
    Logger logger;
    std::string input;
    logger.log("RLE_V1 - Basic original RLE");

    std::string choice;
    std::cout << "---------------------------------"
              << std::endl;
    std::cout << "1. Raw text (interactive)" << std::endl;
    std::cout << "2. Text from file" << std::endl;
    std::cout << "Enter choice [1-2]: ";
    std::getline(std::cin, choice);

    if (choice == "1") {
        std::cout << "Enter text to encode: ";
        std::getline(std::cin, input);
    } else if (choice == "2") {
        std::cout << "Enter file name: ";
        std::string filename;
        std::getline(std::cin, filename);
        input = readTextFileIntoSingleString(filename);
    } else {
        std::cout << "Invalid choice" << std::endl;
        return;
    }

    // get current time for benchmarking
    auto start = std::chrono::high_resolution_clock::now();
    std::string encoded = rle.encode(input);
    auto end = std::chrono::high_resolution_clock::now();

    // count time in nano seconds
    auto encodingTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    logger.log("Raw text: " + input);
    logger.log("Encoded text: " + encoded);
    logger.log("Encoding time: " + std::to_string(encodingTime) + " ns");
    logger.log("Compression ratio: " + std::to_string(compressionRatio(input, encoded)) + "%");

    // get current time for benchmarking
    start = std::chrono::high_resolution_clock::now();
    std::string decoded = rle.decode(encoded);
    end = std::chrono::high_resolution_clock::now();

    // count time in nano seconds
    auto decodingTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    // logger utils call log
    logger.log("Decoded text: " + decoded);
    logger.log("Decoding time: " + std::to_string(decodingTime) + " ns");
}

void rlev2() {
    RLE_V2 rle;
    Logger logger;
    std::string input;
    logger.log("RLE_V2 - Improved RLE");

    std::string choice;
    std::cout << "---------------------------------"
              << std::endl;
    std::cout << "1. Raw text (interactive)" << std::endl;
    std::cout << "2. Text from file" << std::endl;
    std::cout << "Enter choice [1-2]: ";
    std::getline(std::cin, choice);

    if (choice == "1") {
        std::cout << "Enter text to encode: ";
        std::getline(std::cin, input);
    } else if (choice == "2") {
        std::cout << "Enter file name: ";
        std::string filename;
        std::getline(std::cin, filename);
        input = readTextFileIntoSingleString(filename);
    } else {
        std::cout << "Invalid choice" << std::endl;
        return;
    }

    // get current time for benchmarking
    auto start = std::chrono::high_resolution_clock::now();
    std::string encoded = rle.encode(input);
    auto end = std::chrono::high_resolution_clock::now();

    // count time in nano seconds
    auto encodingTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    logger.log("Raw text: " + input);
    logger.log("Encoded text: " + encoded);
    logger.log("Encoding time: " + std::to_string(encodingTime) + " ns");
    logger.log("Compression ratio: " + std::to_string(compressionRatio(input, encoded)) + "%");

    // get current time for benchmarking
    start = std::chrono::high_resolution_clock::now();
    std::string decoded = rle.decode(encoded);
    end = std::chrono::high_resolution_clock::now();

    // count time in nano seconds
    auto decodingTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    // logger utils call log
    logger.log("Decoded text: " + decoded);
    logger.log("Decoding time: " + std::to_string(decodingTime) + " ns");
}

void dcodingStatic() {
    DictCoding dc;
    Logger logger;
    std::string input;
    logger.log("Dictionary Coding - Static Dictionary (English Dictionary)");

    std::string choice;
    std::cout << "1. DNA Dictionary" << std::endl;
    std::cout << "2. English Dictionary" << std::endl;
    std::cout << "Enter choice [1-2]: ";
    std::getline(std::cin, choice);

    if (choice == "1") {
        dc.loadDictionary("test/dna_dictionary.txt");
    } else if (choice == "2") {
        dc.loadDictionary("test/english_dictionary_alpha.txt");
    } else {
        std::cout << "Invalid choice" << std::endl;
        return;
    }

    std::cout << "---------------------------------"
              << std::endl;
    std::cout << "1. Raw text (interactive)" << std::endl;
    std::cout << "2. Text from file" << std::endl;
    std::cout << "Enter choice [1-2]: ";
    std::getline(std::cin, choice);

    if (choice == "1") {
        std::cout << "Enter text to encode: ";
        std::getline(std::cin, input);
    } else if (choice == "2") {
        std::cout << "Enter file name: ";
        std::string filename;
        std::getline(std::cin, filename);
        input = readTextFileIntoSingleString(filename);
    } else {
        std::cout << "Invalid choice" << std::endl;
        return;
    }

    // get current time for benchmarking
    auto start = std::chrono::high_resolution_clock::now();
    std::string encoded = dc.encode(input);
    auto end = std::chrono::high_resolution_clock::now();

    // count time in nano seconds
    auto encodingTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    logger.log("Raw text: " + input);
    logger.log("Encoded text: " + encoded);
    logger.log("Encoding time: " + std::to_string(encodingTime) + " ns");
    logger.log("Compression ratio: " + std::to_string(compressionRatio(input, encoded)) + "%");

    // get current time for benchmarking
    start = std::chrono::high_resolution_clock::now();
    std::string decoded = dc.decode(encoded);
    end = std::chrono::high_resolution_clock::now();

    // count time in nano seconds
    auto decodingTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    // logger utils call log
    logger.log("Decoded text: " + decoded);
    logger.log("Decoding time: " + std::to_string(decodingTime) + " ns");
}

void dcodingLearnable() {
    DictCoding dc;
    Logger logger;
    std::string input;
    logger.log("Dictionary Coding - Learnable Dictionary");

    std::string rawDictionaryFilename;
    std::cout << "Enter the text file to learn the pattern from: ";
    std::getline(std::cin, rawDictionaryFilename);

    float threshold;
    std::cout << "Enter the threshold for learning [0.0 - 1.0]: ";
    std::cin >> threshold;
    std::cin.ignore();

    std::string choice;
    std::cout << "---------------------------------"
              << std::endl;
    std::cout << "1. Raw text (interactive)" << std::endl;
    std::cout << "2. Text from file" << std::endl;
    std::cout << "Enter choice [1-2]: ";
    std::getline(std::cin, choice);

    if (choice == "1") {
        std::cout << "Enter text to encode: ";
        std::getline(std::cin, input);
    } else if (choice == "2") {
        std::cout << "Enter file name: ";
        std::string filename;
        std::getline(std::cin, filename);
        input = readTextFileIntoSingleString(filename);
    } else {
        std::cout << "Invalid choice" << std::endl;
        return;
    }

    // get current time for benchmarking
    auto start = std::chrono::high_resolution_clock::now();
    dc.learnDictionary(readTextFileIntoSingleString(rawDictionaryFilename), threshold);
    auto end = std::chrono::high_resolution_clock::now();

    // count time in nano seconds
    auto learningTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    // logger utils call log
    logger.log("Learning time: " + std::to_string(learningTime) + " ns");

    // get current time for benchmarking
    start = std::chrono::high_resolution_clock::now();
    std::string encoded = dc.encode(input);
    end = std::chrono::high_resolution_clock::now();

    // count time in nano seconds
    auto encodingTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    logger.log("Raw text: " + input);
    logger.log("Encoded text: " + encoded);
    logger.log("Encoding time: " + std::to_string(encodingTime) + " ns");
    logger.log("Compression ratio: " + std::to_string(compressionRatio(input, encoded)) + "%");

    // get current time for benchmarking
    start = std::chrono::high_resolution_clock::now();
    std::string decoded = dc.decode(encoded);
    end = std::chrono::high_resolution_clock::now();

    // count time in nano seconds
    auto decodingTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    // logger utils call log
    logger.log("Decoded text: " + decoded);
    logger.log("Decoding time: " + std::to_string(decodingTime) + " ns");

    std::cout << "---------------------------------"
              << std::endl;
    std::cout << "Do you want to save the learned dictionary to a file? [y/n]: ";
    std::string saveChoice;
    std::getline(std::cin, saveChoice);
    if (saveChoice == "y") {
        std::cout << "Enter file name: ";
        std::string filename;
        std::getline(std::cin, filename);
        dc.saveDictionary(filename);
    }
}

int main() {
    std::cout << "Interactive mode" << std::endl;
    std::cout << "1. RLE V1" << std::endl;
    std::cout << "2. RLE V2" << std::endl;
    std::cout << "3. Dictionary Coding (static dictionary)" << std::endl;
    std::cout << "4. Dictionary Coding (learnable)" << std::endl;

    std::string choice;
    std::cout << "Enter choice [1-4]: ";
    std::getline(std::cin, choice);

    std::cout << "---------------------------------"
              << std::endl;

    switch (std::stoi(choice)) {
    case 1:
        rlev1();
        break;
    case 2:
        rlev2();
        break;
    case 3:
        dcodingStatic();
        break;
    case 4:
        dcodingLearnable();
        break;
    default:
        std::cout << "Invalid choice" << std::endl;
        break;
    }

    return 0;
}