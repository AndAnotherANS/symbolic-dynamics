#include "SFT.hpp"
#include "Utils.hpp"
#include <string>
#include <unordered_map>
#include <vector>


SFT::SFT(unsigned int n_symbols, const UnweightedMatrixGraph &edge_shift) : SoficShift(n_symbols, edge_shift) {};

SFT::SFT(unsigned int n_symbols, const std::vector<Word> &forbidden_words)
{
    this->n_symbols = n_symbols;
    build_edge_shift(forbidden_words);
}

MapBlockCode SFT::get_original_to_one_step_code() const
{
    return original_to_one_step_code;
}
MapBlockCode SFT::get_one_step_to_original_code() const
{
    return one_step_to_original_code;
}

/*
 * Construction of edge shift from specified set of forbidden blocks
 * based on theorem 2.3.2 from
 * Lind D, Marcus B. An Introduction to Symbolic Dynamics and Coding. Cambridge University Press; 1995.
 *
 * We don't assume that the supplied list of blocks is of the same size, blocks shorter than the longest
 * one are padded with all combinations of symbols from the alphabet to construct all forbidden blocks
 */
void SFT::build_edge_shift(const std::vector<Word> &forbidden_words)
{
    unsigned int max_length = 0;
    for (auto &&word : forbidden_words)
    {
        if (word.size() > max_length)
        {
            max_length = word.size();
        }
    }

    std::set<std::string> forbidden_words_set =
        details::generate_full_length_forbidden_words(forbidden_words, this->n_symbols, max_length);
    std::vector<Word> allowed_words = details::generate_all_words(this->n_symbols, max_length - 1);
    std::sort(allowed_words.begin(), allowed_words.end());

    UnweightedMatrixGraph one_step_edge_shift(allowed_words.size(), allowed_words);
    UnweightedMatrixGraph edge_shift(allowed_words.size(), allowed_words);

    std::unordered_map<std::string, unsigned int> block_code;
    std::unordered_map<std::string, unsigned int> inverse_block_code;

    std::size_t edge_index = 0;
    const auto allowed_word_size = allowed_words[0].size();

    for (unsigned int i = 0; i < allowed_words.size(); i++)
    {
        for (unsigned int j = 0; j < allowed_words.size(); j++)
        {
            bool add_edge = true;
            auto common_word = Word();
            for (int k = 0; k < allowed_word_size - 1; k++)
            {
                if (allowed_words[i][k + 1] != allowed_words[j][k])
                {
                    add_edge = false;
                    break;
                }
                common_word.push_back(allowed_words[i][k + 1]);
            }
            if (add_edge)
            {
                common_word.insert(common_word.begin(), allowed_words[i][0]);
                common_word.push_back(allowed_words[j][allowed_words[0].size() - 1]);
                if (forbidden_words_set.contains(hash_word(common_word)))
                {
                    add_edge = false;
                }
            }
            if (add_edge)
            {
                block_code[hash_word(common_word)] = i;
                inverse_block_code[hash_word(Word({i}))] = common_word[0];

                edge_shift.add_edge(i, j, 1, allowed_words[i][0]);
                one_step_edge_shift.add_edge(i, j, 1, edge_index++);
            }
        }
    }
    this->one_step_edge_shift = one_step_edge_shift;
    this->edge_shift = edge_shift;
}
