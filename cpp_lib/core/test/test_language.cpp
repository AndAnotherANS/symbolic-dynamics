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