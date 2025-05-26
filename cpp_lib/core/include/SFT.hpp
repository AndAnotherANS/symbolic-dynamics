#pragma once
#include "Graph.hpp"
#include "SoficShift.hpp"
#include <memory>
#include <vector>

class BlockCode;

class SFT : public SoficShift
{
  protected:
    unsigned int M_step = 0;

    std::vector<Word> forbidden_words;

    void build_edge_shift(const std::vector<Word> &forbidden_words);

  public:
    SFT() = default;

    SFT(std::vector<unsigned int> alphabet, const std::vector<Word> &forbidden_words);

    // edge shift, higher-block edge shift, block code, inverse block code
    [[nodiscard]] std::tuple<UnweightedMatrixGraph, UnweightedMatrixGraph, BlockCode, BlockCode>
    get_nth_higher_block_shift(unsigned int n) const;

    [[nodiscard]] unsigned int get_M_step() const;

    ~SFT() override = default;
};

std::tuple<SFT, BlockCode> get_sft_factor_map(const SoficShift &shift);