#include "SFT.hpp"
#include <gtest/gtest.h>

TEST(SFTTest, BinaryShiftWithForbiddenWords)
{
    int n_symbols = 2;
    std::vector<Word> forbidden_words = {{1, 1}, {1, 0, 1}};
    SFT sft(n_symbols, forbidden_words);

    auto edge_shift = sft.get_edge_shift();
    auto block_code = sft.get_block_code();
}