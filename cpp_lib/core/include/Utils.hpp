#pragma once
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

typedef std::vector<unsigned int> Word;

std::string hash_word(const Word &word);
std::set<std::string> hash_words(const std::vector<Word> &words);

class BlockCode
{
protected:
    std::unordered_map<std::string, unsigned int> map;
    unsigned int length = 0;
public:

    BlockCode() = default;
    BlockCode(std::unordered_map<std::string, unsigned int> map, unsigned int length);

    unsigned int at(const Word &word) const;
    unsigned int at(const std::string &word_hash) const;

    unsigned int block_length() const;

};

class OneBlockCode: public BlockCode
{
protected:
    std::unordered_map<unsigned int, unsigned int> int_map;

public:
    OneBlockCode() = default;
    OneBlockCode(std::unordered_map<unsigned int, unsigned int> map);
    unsigned int at(unsigned int symbol) const;
};

Word translate_word(const Word &word, const BlockCode &block_code);

Word translate_word(const Word &word, const OneBlockCode &block_code);
