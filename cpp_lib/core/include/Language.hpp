#pragma once
#include <vector>
#include <set>
#include <string>

typedef std::vector<int> Word;

class Language
{
protected:
    int n_symbols = 0;
public:
    Language() = default;
    Language(int n_symbols);
    virtual std::string hash_word(const Word& word) const; 
    virtual std::vector<Word> get_finite_words(int n) const = 0;
};


std::vector<Word> extend_words(std::vector<Word> words, int n_symbols);


class FullLanguage : public Language
{
public:
    FullLanguage() = default;
    FullLanguage(int n_symbols);
    virtual std::vector<Word> get_finite_words(int n) const;
};

class FiniteLanguage : public Language
{
protected:
    std::vector<Word> words = {};
    std::set<std::string> hashes = {};
public:
    FiniteLanguage() = default;
    FiniteLanguage(int n_symbols);
    FiniteLanguage(int n_symbols, const std::vector<Word>& words);
    virtual std::vector<Word> get_finite_words(int n) const;
    void add_word(const Word& word);
    void add_words(const std::vector<Word>& words);
    bool contains(const Word& word) const;

};