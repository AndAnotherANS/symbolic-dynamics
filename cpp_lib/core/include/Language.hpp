#pragma once
#include <vector>
#include <set>
#include <string>

class Language
{
protected:
    int n_symbols;
public:
    Language();
    Language(int n_symbols);
    virtual std::string hash_word(const std::vector<int>& word);
    virtual std::vector<std::vector<int> > get_finite_words(int n) const = 0;
};


std::vector<std::vector<int> > extend_words(std::vector<std::vector<int> > words, int n_symbols);


class FullLanguage : public Language
{
public:
    FullLanguage();
    FullLanguage(int n_symbols);
    virtual std::vector<std::vector<int> > get_finite_words(int n) const;
};