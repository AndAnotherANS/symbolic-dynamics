#pragma once
#include <set>
#include <string>
#include <vector>

typedef std::vector<unsigned int> Word;

std::string hash_word(const Word &word);
std::set<std::string> hash_words(const std::vector<Word> &words);

namespace details
{

void generate_full_length_forbidden_words_rec(const Word &word, std::vector<Word> &full_forbidden_words,
                                              const std::vector<unsigned int> &alphabet, const unsigned int &length);

std::set<std::string> generate_full_length_forbidden_words(const std::vector<Word> &forbidden_words,
                                                           const std::vector<unsigned int>& alphabet, unsigned int length);

void generate_all_words_rec(const Word &word, std::vector<Word> &all_words, const std::vector<unsigned int> &alphabet,
                            const unsigned int &length);


std::vector<Word> generate_all_words(const std::vector<unsigned int>& alphabet, unsigned int length);

}

