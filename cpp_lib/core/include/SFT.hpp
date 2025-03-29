#pragma once
#include "Graph.hpp"
#include "SoficShift.hpp"
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

class SFT : public SoficShift
{
  protected:
    // Block code transforming original shift to internal representation
    BlockCode block_code;

    // Block code transforming internal shift to original shift
    OneBlockCode inverse_block_code = {};

    void build_edge_shift(const std::vector<Word> &forbidden_words);

  public:
    SFT() = default;

    SFT(unsigned int n_symbols, const UnweightedMatrixGraph &edge_shift);
    SFT(unsigned int n_symbols, const std::vector<Word> &forbidden_words);

    BlockCode get_block_code() const;

    OneBlockCode get_inverse_block_code() const;

    ~SFT() override = default;
};
