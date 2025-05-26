#include "Utils.hpp"

namespace details
{
void generate_full_length_forbidden_words_rec(const Word &word, std::vector<Word> &full_forbidden_words,
                                              const std::vector<unsigned int> &alphabet, const unsigned int &length)
{
    if (word.size() == length)
    {
        full_forbidden_words.push_back(word);
        return;
    }
    for (auto &&symbol : alphabet)
    {
        Word new_word_back = word;
        new_word_back.push_back(symbol);
        generate_full_length_forbidden_words_rec(new_word_back, full_forbidden_words, alphabet, length);

        Word new_word_front = word;
        new_word_front.insert(new_word_front.begin(), symbol);
        generate_full_length_forbidden_words_rec(new_word_front, full_forbidden_words, alphabet, length);
    }
}

std::vector<Word> generate_full_length_forbidden_words(const std::vector<Word> &forbidden_words,
                                                           const std::vector<unsigned int>& alphabet, unsigned int length)
{
    auto full_forbidden_words = std::vector<Word>();
    for (auto &&word : forbidden_words)
    {
        generate_full_length_forbidden_words_rec(word, full_forbidden_words, alphabet, length);
    }

    return full_forbidden_words;
}

void generate_all_words_rec(const Word &word, std::vector<Word> &all_words, const std::vector<unsigned int> &alphabet,
                            const unsigned int &length)
{
    if (word.size() == length)
    {
        all_words.push_back(word);
        return;
    }
    for (auto &&symbol : alphabet)
    {
        Word new_word = word;
        new_word.push_back(symbol);
        generate_all_words_rec(new_word, all_words, alphabet, length);
    }
}

std::vector<Word> generate_all_words(const std::vector<unsigned int>& alphabet, unsigned int length)
{
    std::vector<Word> all_words;
    auto empty_word = Word();
    generate_all_words_rec(empty_word, all_words, alphabet, length);
    return all_words;
}

} // namespace details


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

