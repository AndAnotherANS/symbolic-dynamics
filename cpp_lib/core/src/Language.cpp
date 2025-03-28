#include "Language.hpp"


std::string hash_word(const Word& word)
{
    std::string hash;
    for (int i : word)
    {
        hash += std::to_string(i) + "$";
    }
    return hash;
}

std::set<std::string> hash_words(const std::vector<Word>& words)
{
    std::set<std::string> hashed_words;
    for (auto &&word : words)
    {
        hashed_words.insert(hash_word(word));
    }
    return hashed_words;
}