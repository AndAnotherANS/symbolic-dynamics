#include <gtest/gtest.h>
#include "Language.hpp"

TEST(FullLanguage, FiniteWordGeneration) {
    FullLanguage language(3);
    std::vector<std::vector<int>> words = language.get_finite_words(3);
    std::vector<std::vector<int>> expected_words = {
        {0, 0, 0},
        {0, 0, 1},
        {0, 0, 2},
        {0, 1, 0},
        {0, 1, 1},
        {0, 1, 2},
        {0, 2, 0},
        {0, 2, 1},
        {0, 2, 2},
        {1, 0, 0},
        {1, 0, 1},
        {1, 0, 2},
        {1, 1, 0},
        {1, 1, 1},
        {1, 1, 2},
        {1, 2, 0},
        {1, 2, 1},
        {1, 2, 2},
        {2, 0, 0},
        {2, 0, 1},
        {2, 0, 2},
        {2, 1, 0},
        {2, 1, 1},
        {2, 1, 2},
        {2, 2, 0},
        {2, 2, 1},
        {2, 2, 2}
    };
    ASSERT_EQ(words, expected_words);
}

TEST(FiniteLanguage, AddAndContainsWord) {
    FiniteLanguage language(3);
    Word word = {0, 1, 2};
    language.add_word(word);
    ASSERT_TRUE(language.contains(word));
    ASSERT_FALSE(language.contains({1, 2, 3}));
}

TEST(FiniteLanguage, GetFiniteWords) {
    FiniteLanguage language(3, {{0, 1}, {1, 2, 3}, {2}});
    std::vector<Word> words = language.get_finite_words(2);
    std::vector<Word> expected_words = {
        {0, 1},
        {2}
    };
    ASSERT_EQ(words, expected_words);
}

TEST(Language, HashWord) {
    Language* language = new FullLanguage(3);
    Word word = {0, 1, 2};
    std::string hash = language->hash_word(word);
    ASSERT_EQ(hash, "0$1$2$");
    delete language;
}