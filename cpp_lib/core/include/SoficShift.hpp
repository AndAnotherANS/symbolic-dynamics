#pragma once
#include "Graph.hpp"
#include "ShiftSpace.hpp"

class BlockCode;


class SoficShift : public ShiftSpace
{
  protected:
    UnweightedMatrixGraph edge_shift;

  public:
    SoficShift() = default;

    SoficShift(std::vector<unsigned int> alphabet, UnweightedMatrixGraph edge_shift);

    [[nodiscard]] UnweightedMatrixGraph get_edge_shift() const;

    [[nodiscard]] std::vector<unsigned int> get_alphabet() const
    {
        return alphabet;
    }

    [[nodiscard]] bool is_valid_sequence(const Word &sequence) const override;

    ~SoficShift() override = default;
};
