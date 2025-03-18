
#include "Language.hpp"
#include <vector>
#include <set>
#include <string>



std::string Language::hash_word(const std::vector<int>& word)
{
    std::string hash = "";
    for (std::size_t i = 0; i < word.size(); i++)
    {
        hash += std::to_string(word[i]);
    }
    return hash;
}

Language::Language(): n_symbols(0) {};

Language::Language(int n_symbols): n_symbols(n_symbols) {};



std::vector<std::vector<int> > extend_words(std::vector<std::vector<int> > words, int n_symbols)
{
    std::vector<std::vector<int> > extended_words;
    for (std::size_t i = 0; i < words.size(); i++)
    {
        for (std::size_t j = 0; j < n_symbols; j++)
        {
            std::vector<int> word = words[i];
            word.push_back(j);
            extended_words.push_back(word);
        }
    }
    return extended_words;
}

FullLanguage::FullLanguage(): Language() {};
FullLanguage::FullLanguage(int n_symbols): Language(n_symbols) {};

std::vector<std::vector<int> > FullLanguage::get_finite_words(int n) const
{
    std::vector<std::vector<int> > words;
    words.push_back(std::vector<int>());
    for (int i = 0; i < n; i++)
    {
        words = extend_words(words, n_symbols);
    }
    return words;
}