#include "SFT.hpp"
#include <vector>
#include <unordered_map>
#include <string>



SFT::SFT() : Mstep(0) {};

SFT::SFT(UnweightedMatrixGraph vertex_shift)
{
    this->vertex_shift = vertex_shift;
    this->edge_shift = build_edge_shift(Mstep); // TODO: Calculate Edge Shift
    Mstep = 0; // TODO: Calculate Mstep
};

SFT::SFT(const std::vector<std::vector<int> >& forbidden_words) : Mstep(0)
{

    this->language = FullLanguage();
    for (const std::vector<int>& word : forbidden_words)
    {
        this->forbidden_words.insert(language.hash_word(word));
    }
}