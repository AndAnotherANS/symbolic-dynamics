#include "SFT.hpp"
#include "BlockCode.hpp"
#include "Utils.hpp"
#include <string>
#include <unordered_map>
#include <algorithm>
#include <utility>
#include <vector>

SFT::SFT(std::vector<unsigned int> alphabet, const std::vector<Word> &forbidden_words)
{
    this->alphabet = std::move(alphabet);
    this->forbidden_words = forbidden_words;
    build_edge_shift(forbidden_words);
}


void SFT::build_edge_shift(const std::vector<Word> &forbidden_words)
{
    unsigned int max_length = 2;
    for (auto &&word : forbidden_words)
    {
        if (word.size() > max_length)
        {
            max_length = word.size();
        }
    }

    this->M_step = max_length-1;
    this->edge_shift = std::get<0>(get_nth_higher_block_shift(max_length-1));
}


/*
 * Construction of edge shift from specified set of forbidden blocks
 * based on theorem 2.3.2 from
 * Lind D, Marcus B. An Introduction to Symbolic Dynamics and Coding. Cambridge University Press; 1995.
 *
 * We don't assume that the supplied list of blocks is of the same size, blocks shorter than the longest
 * one are padded with all combinations of symbols from the alphabet to construct all forbidden blocks
 */
std::tuple<UnweightedMatrixGraph, UnweightedMatrixGraph, BlockCode, BlockCode> SFT::get_nth_higher_block_shift(
    unsigned int n) const
{
    if (n < this->M_step)
    {
        throw std::invalid_argument("SFT::get_nth_higher_block_shift invalid parameter");
    }
    std::vector<Word> forbidden_words_vect =
        details::generate_full_length_forbidden_words(this->forbidden_words, this->alphabet, n + 1);

    std::set<std::string> forbidden_words_set;
    std::ranges::transform(forbidden_words_vect, std::inserter(forbidden_words_set, forbidden_words_set.begin()),
                           hash_word);

    std::vector<Word> allowed_words = details::generate_all_words(this->alphabet, n);
    std::sort(allowed_words.begin(), allowed_words.end());

    UnweightedMatrixGraph higher_block_edge_shift(allowed_words.size(), allowed_words);
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

                edge_shift.add_edge(i, j, 1, {allowed_words[i][0]});
                higher_block_edge_shift.add_edge(i, j, 1, common_word);
            }
        }
    }

    return {edge_shift, higher_block_edge_shift, BlockCode(block_code, 0, allowed_word_size + 1),
            BlockCode(inverse_block_code, 0, 0)};
}
double SFT::entropy()
{
    auto [eigvect, eigval] = perron_frobenius_eigen(edge_shift.get_adjacency_matrix().cast<double>());
    return log(eigval);
}

bool SFT::is_transitive() const
{
    auto [_, n_sccs] = strongly_connected_components(edge_shift);
    return n_sccs == 1;
}
bool SFT::is_mixing() const
{
    return is_primitive(edge_shift);
}

unsigned int SFT::get_M_step() const
{
    return M_step;
}


