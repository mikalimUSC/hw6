#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Notes: 
        //convert to same case
        //Translate each letter into val between 0-35 --> use helper
        //follow formula

    std::string cleanedStr;
    for (char ch : k) {
        if (std::isalnum(ch)) {
            cleanedStr += std::tolower(ch); 
        }
    }
    const int maxChunks = 5;
    const int chunkSize = 6;
    unsigned long long w[maxChunks] = {0}; // 64-bit chunks

    int len = cleanedStr.length();
    int chunkIndex = maxChunks - 1;
    for (int i = len; i > 0 && chunkIndex >= 0; i -= chunkSize, --chunkIndex) {
        unsigned long long value = 0;
        unsigned long long power = 1;

        for (int j = std::max(0, i - chunkSize); j < i; ++j) {
            value = value * 36 + letterDigitToNumber(cleanedStr[j]);
        }

        w[chunkIndex] = value;
    }

    // hash time!
    unsigned long long hash = 0;
    for (int i = 0; i < maxChunks; ++i) {
        hash += rValues[i] * w[i];
    }

    return static_cast<HASH_INDEX_T>(hash);

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
    
    if (std::isalpha(letter)) {
        char convertedletter= std::tolower(letter) - 'a';
        return convertedletter ;
    } else if (std::isdigit(letter)) {
        char digitized = 26 + (letter - '0');
        return digitized;
    }
    return 0;
    
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
