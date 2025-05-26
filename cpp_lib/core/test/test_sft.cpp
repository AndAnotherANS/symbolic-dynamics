#include "SFT.hpp"

#include <algorithm>
#include "BlockCode.hpp"
#include <gtest/gtest.h>

template<typename T>
std::set<std::string> vec2set(std::vector<T> vec)
{
    std::set<std::string> set;
    std::transform(vec.begin(), vec.end(), std::inserter(set, set.begin()), hash_word);
    return set;
}

TEST(SFTTest, ForbiddenWordsCompletion)
{
    std::vector<unsigned int> alphabet = {0, 1};
    std::vector<Word> forbidden_words = {{1, 1}, {1, 0, 1}};

    std::vector<Word> expected_full_length_forbidden_words = {{1, 1, 0}, {1, 1, 1}, {0, 1, 1}, {1, 0, 1}};
    ASSERT_EQ(
        vec2set<Word>(details::generate_full_length_forbidden_words(forbidden_words, alphabet, 3)),
        vec2set<Word>(expected_full_length_forbidden_words)
        );


}

TEST(SFTTest, SFTOperations)
{
    std::vector<unsigned int> alphabet = {0, 1};
    std::vector<Word> forbidden_words = {{1, 1}, {0, 1, 1}};

    SFT sft(alphabet, forbidden_words);
    ASSERT_EQ(sft.get_M_step(), 3);
}

TEST(SFTTest, BlockCodes)
{
    std::function<unsigned int(const Word&)> fun = [](const Word& w) {
        return 1 - w[0];
    };

    BlockCode swap_symbols_automorphism(fun, 0, 0);

    // full binary shift
    SFT sft({0, 1}, {});

    SoficShift sft2 = swap_symbols_automorphism.map(sft);

    ASSERT_EQ(sft.get_edge_shift().get_adjacency_matrix(), sft2.get_edge_shift().get_adjacency_matrix());
}