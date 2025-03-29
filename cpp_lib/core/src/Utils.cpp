#include "Utils.hpp"

std::string hash_word(const Word &word)
{
    std::string hash;
    for (unsigned const int i : word)
    {
        hash += std::to_string(i) + "$";
    }
    return hash;
}

std::set<std::string> hash_words(const std::vector<Word> &words)
{
    std::set<std::string> hashed_words;
    for (auto &&word : words)
    {
        hashed_words.insert(hash_word(word));
    }
    return hashed_words;
}
BlockCode::BlockCode(std::unordered_map<std::string, unsigned int> map, unsigned int length)
    : map(std::move(map)), length(length)
{
}
unsigned int BlockCode::at(const Word &word) const
{
    return map.at(hash_word(word));
}

unsigned int BlockCode::at(const std::string &word_hash) const
{
    return map.at(word_hash);
}
unsigned int BlockCode::block_length() const
{
    return length;
}

 OneBlockCode::OneBlockCode(std::unordered_map<unsigned int, unsigned int> map): int_map(std::move(map))
{
    for (auto &&i : int_map) this->map[hash_word(Word({i.first}))] = i.second;
    this->length = 1;
}


unsigned int OneBlockCode::at(unsigned int symbol) const
{
    return int_map.at(symbol);
}

Word translate_word(const Word &word, const BlockCode &block_code)
{
    Word translated_word;
    unsigned int block_length = block_code.block_length();
    for (int i = 0; i < word.size() - block_length; i++)
    {
        translated_word.push_back(block_code.at(std::vector(word.begin() + i, word.begin() + i + block_length)));
    }
    return translated_word;
}

Word translate_word(const Word &word, const OneBlockCode &block_code)
{
    Word translated_word;
    for (auto &&symbol : word)
    {
        translated_word.push_back(block_code.at(symbol));
    }
    return translated_word;
}
