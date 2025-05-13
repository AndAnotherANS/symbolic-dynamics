#pragma once
#include "Graph.hpp"
#include "SoficShift.hpp"
#include "BlockCode.hpp"
#include <vector>

class SFT : public SoficShift
{
  protected:

    UnweightedMatrixGraph one_step_edge_shift;

    // Block code transforming original shift to internal representation
    MapBlockCode original_to_one_step_code;

    // Block code transforming internal shift to original shift
    MapBlockCode one_step_to_original_code;

    void build_edge_shift(const std::vector<Word> &forbidden_words);

  public:
    SFT() = default;

    SFT(unsigned int n_symbols, const UnweightedMatrixGraph &edge_shift);
    SFT(unsigned int n_symbols, const std::vector<Word> &forbidden_words);

    MapBlockCode get_original_to_one_step_code() const;

    MapBlockCode get_one_step_to_original_code() const;

    ~SFT() override = default;
};
