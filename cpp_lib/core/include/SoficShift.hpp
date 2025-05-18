#pragma once
#include "Graph.hpp"
#include "ShiftSpace.hpp"

namespace details
{
struct Path
{
    Word word;
    unsigned int starting_vertex;
    unsigned int ending_vertex;
};
}


class SoficShift : public ShiftSpace
{
  protected:
    UnweightedMatrixGraph edge_shift;

  public:
    SoficShift() = default;

    SoficShift(unsigned int n_symbols, UnweightedMatrixGraph edge_shift);

    [[nodiscard]] UnweightedMatrixGraph get_edge_shift() const;

    [[nodiscard]] bool is_valid_sequence(const Word &sequence) const override;

    [[nodiscard]] std::vector<details::Path> paths_of_length(unsigned int length) const;

    ~SoficShift() override = default;
};
