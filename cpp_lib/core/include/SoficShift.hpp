#pragma once
#include "Graph.hpp"
#include "ShiftSpace.hpp"

class SoficShift : public ShiftSpace
{
  protected:
    UnweightedMatrixGraph edge_shift;

  public:
    SoficShift() = default;

    SoficShift(unsigned int n_symbols, UnweightedMatrixGraph edge_shift);

    [[nodiscard]] UnweightedMatrixGraph get_edge_shift() const;

    [[nodiscard]] bool isValidSequence(const Word &sequence) const override;

    ~SoficShift() override = default;
};
