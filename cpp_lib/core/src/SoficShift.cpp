#include "BlockCode.hpp"
#include "SFT.hpp"
#include "SoficShift.hpp"

#include <utility>

SoficShift::SoficShift(std::vector<unsigned int> alphabet, UnweightedMatrixGraph edge_shift) : edge_shift(edge_shift)
{
    this->alphabet = std::move(alphabet);
};

UnweightedMatrixGraph SoficShift::get_edge_shift() const
{
    return this->edge_shift;
}

bool SoficShift::is_valid_sequence(const Word &sequence) const
{
    return false; // todo: implement
}



