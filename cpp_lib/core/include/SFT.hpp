#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "Graph.hpp"
#include "SoficShift.hpp"
#include <set>




class SFT: public SoficShift
{
protected:
    unsigned int n_symbols;
    UnweightedMatrixGraph vertex_shift;

    // Block code transforming original shift to internal representation
    std::unordered_map<int, Word> recoding_map; 

    UnweightedMatrixGraph build_vertex_shift();
    UnweightedMatrixGraph build_edge_shift(const std::vector<Word>& forbidden_words) const;
    UnweightedMatrixGraph build_block_code(const UnweightedMatrixGraph &edge_shift) const;

public:
    SFT() = default;

    SFT(unsigned int n_symbols, const UnweightedMatrixGraph& edge_shift);
    SFT(unsigned int n_symbols, const std::vector<std::vector<int> >& forbidden_words);



    ~SFT() override = default;
};

