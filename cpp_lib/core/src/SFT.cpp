#include "SFT.hpp"
#include <vector>
#include <unordered_map>
#include <string>
#include "Language.hpp"

namespace details
{
    void generate_full_length_forbidden_words_rec(const Word& word, std::vector<Word>& full_forbidden_words, unsigned int n_symbols, unsigned int length)
    {
        if (word.size() == length)
        {
            full_forbidden_words.push_back(word);
            return;
        }
        for (int i = 0; i < n_symbols; i++)
        {
            Word new_word_back = word;
            new_word_back.push_back(i);
            generate_full_length_forbidden_words_rec(new_word_back, full_forbidden_words, n_symbols, length);
            
            Word new_word_front = word;
            new_word_front.insert(new_word_front.begin(), i);
            generate_full_length_forbidden_words_rec(new_word_front, full_forbidden_words, n_symbols, length);
        }
    }

    std::set<std::string> generate_full_length_forbidden_words(const std::vector<Word>& forbidden_words, unsigned int n_symbols, unsigned int length)
    {
        std::set<std::string> forbidden_words_set;
        for (auto &&word : forbidden_words)
        {
            std::vector<Word> full_forbidden_words = std::vector<Word>();
            generate_full_length_forbidden_words_rec(word, full_forbidden_words, n_symbols, length);
            for (auto &&word : full_forbidden_words)
            {
                forbidden_words_set.insert(hash_word(word));
            }
        }
        
        return forbidden_words_set;
    }

    void generate_all_words_rec(const Word& word, std::vector<Word>& all_words, unsigned int n_symbols, unsigned int max_length)
    {
        if (word.size() == max_length)
        {
            all_words.push_back(word);
            return;
        }
        for (int i = 0; i < n_symbols; i++)
        {
            Word new_word = word;
            new_word.push_back(i);
            generate_all_words_rec(new_word, all_words, n_symbols, max_length);
        
        }
    }

    std::vector<Word> generate_all_words(unsigned int n_symbols, unsigned int max_length)
    {
        std::vector<Word> all_words;
        Word empty_word = Word();
        generate_all_words_rec(empty_word, all_words, n_symbols, max_length);
        return all_words;
    }


} // namespace details

SFT::SFT(unsigned int n_symbols, const UnweightedMatrixGraph& edge_shift): SoficShift(n_symbols, edge_shift)
{
    this->edge_shift = edge_shift;
    for (auto &&vertex : this->vertex_shift.nodes())
    {
        this->recoding_map[vertex.index] = vertex.label;
    }
    
    
};

SFT::SFT(unsigned int n_symbols, const std::vector<Word>& forbidden_words): n_symbols(n_symbols)
{
    this->edge_shift = build_edge_shift(forbidden_words);
}


/*
 * Construction of edge shift from specified set of forbidden blocks
 * based on theorem 2.3.2 from
 * Lind D, Marcus B. An Introduction to Symbolic Dynamics and Coding. Cambridge University Press; 1995.
 *
 * We don't assume that the supplied list of blocks is of the same size, blocks shorter than the longest
 * one are padded with all combinations of symbols from the alphabet to construct all forbidden blocks
 */
UnweightedMatrixGraph SFT::build_edge_shift(const std::vector<Word>& forbidden_words) const
{
    unsigned int max_length = 0;
    for (auto &&word : forbidden_words)
    {
        if (word.size() > max_length)
        {
            max_length = word.size();
        }
    }

    std::set<std::string> forbidden_words_set = details::generate_full_length_forbidden_words(forbidden_words, this->n_symbols, max_length);
    std::vector<Word> allowed_words = details::generate_all_words(this->n_symbols, max_length -1);
    std::sort(allowed_words.begin(), allowed_words.end());

    UnweightedMatrixGraph edge_shift(allowed_words.size(), allowed_words);

    for (int i = 0; i < allowed_words.size(); i++)
    {
        for (int j = 0; j < allowed_words.size(); j++)
        {
            bool add_edge = true;
            Word common_word = Word();
            for (int k = 0; k < allowed_words[0].size()-1; k++)
            {
                if (allowed_words[i][k + 1] != allowed_words[j][k])
                {
                    add_edge = false;
                    break;
                }
                common_word.push_back(allowed_words[i][k + 1]);
            }
            if(add_edge)
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

                edge_shift.add_edge(i, j, 1, common_word);
                
            }
        }
    }
    return edge_shift;
}

// todo: replace MatrixGraph with some better optimized matrix implementation as we don't need the graph part
UnweightedMatrixGraph SFT::build_block_code(const UnweightedMatrixGraph &edge_shift) const
{
    for (auto&& edge: edge_shift.edges())
    {

    }
}
