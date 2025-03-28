#pragma once
#include <vector>
#include <set>
#include <string>

typedef std::vector<int> Word;


std::string hash_word(const Word& word);
std::set<std::string> hash_words(const std::vector<Word>& words);
