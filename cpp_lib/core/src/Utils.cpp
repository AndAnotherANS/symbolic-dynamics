#include "Utils.hpp"

namespace details
{
void generate_full_length_forbidden_words_rec(const Word &word, std::vector<Word> &full_forbidden_words,
                                              unsigned int n_symbols, unsigned int length)
{
    if (word.size() == length)
    {
        full_forbidden_words.push_back(word);
        return;
    }
    for (int i = 0; i < n_symbols; i++)
    {
        Word new_word_back = word;
        new_word_back.push_back(i);
        generate_full_length_forbidden_words_rec(new_word_back, full_forbidden_words, n_symbols, length);

        Word new_word_front = word;
        new_word_front.insert(new_word_front.begin(), i);
        generate_full_length_forbidden_words_rec(new_word_front, full_forbidden_words, n_symbols, length);
    }
}

std::set<std::string> generate_full_length_forbidden_words(const std::vector<Word> &forbidden_words,
                                                           unsigned int n_symbols, unsigned int length)
{
    std::set<std::string> forbidden_words_set;
    for (auto &&word : forbidden_words)
    {
        auto full_forbidden_words = std::vector<Word>();
        generate_full_length_forbidden_words_rec(word, full_forbidden_words, n_symbols, length);
        for (auto &&word2 : full_forbidden_words)
        {
            forbidden_words_set.insert(hash_word(word2));
        }
    }

    return forbidden_words_set;
}

void generate_all_words_rec(const Word &word, std::vector<Word> &all_words, unsigned int n_symbols,
                            unsigned int max_length)
{
    if (word.size() == max_length)
    {
        all_words.push_back(word);
        return;
    }
    for (int i = 0; i < n_symbols; i++)
    {
        Word new_word = word;
        new_word.push_back(i);
        generate_all_words_rec(new_word, all_words, n_symbols, max_length);
    }
}

std::vector<Word> generate_all_words(unsigned int n_symbols, unsigned int max_length)
{
    std::vector<Word> all_words;
    auto empty_word = Word();
    generate_all_words_rec(empty_word, all_words, n_symbols, max_length);
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

