
#include "Language.hpp"
#include <vector>
#include <set>
#include <string>



// Language implementation
std::string Language::hash_word(const std::vector<int>& word) const
{
    std::string hash = "";
    for (std::size_t i = 0; i < word.size(); i++)
    {
        hash += std::to_string(word[i]) + "$";
    }
    return hash;
}

Language::Language(int n_symbols): n_symbols(n_symbols) {};



std::vector<Word> extend_words(std::vector<Word> words, int n_symbols)
{
    std::vector<Word> extended_words;
    for (std::size_t i = 0; i < words.size(); i++)
    {
        for (std::size_t j = 0; j < n_symbols; j++)
        {
            Word word = words[i];
            word.push_back(j);
            extended_words.push_back(word);
        }
    }
    return extended_words;
}


// FullLanguage implementation
FullLanguage::FullLanguage(int n_symbols): Language(n_symbols) {};

std::vector<std::vector<int> > FullLanguage::get_finite_words(int n) const
{
    std::vector<Word> words;
    words.push_back(Word());
    for (std::size_t i = 0; i < n; i++)
    {
        words = extend_words(words, n_symbols);
    }
    return words;
}

// FiniteLanguage implementation

FiniteLanguage::FiniteLanguage(int n_symbols): Language(n_symbols) {};

FiniteLanguage::FiniteLanguage(int n_symbols, const std::vector<Word>& words): Language(n_symbols)
{
    this->add_words(words);
}

std::vector<Word> FiniteLanguage::get_finite_words(int n) const
{
    std::vector<Word> result_words;
    for (const Word& word : words)
    {
        if(word.size() <= n)
            result_words.push_back(word);
    }
    return result_words;
}

void FiniteLanguage::add_word(const Word& word)
{
    std::string hash = this->hash_word(word);
    if (!hashes.contains(hash))
    {
        words.push_back(word);
        hashes.insert(hash);
    }
}

void FiniteLanguage::add_words(const std::vector<Word>& new_words)
{
    for (const Word& word : new_words)
    {
        this->add_word(word);
    }
}

bool FiniteLanguage::contains(const Word& word) const
{
    std::string hash = this->hash_word(word);
    return hashes.contains(hash);
}