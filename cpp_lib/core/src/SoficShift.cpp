
#include "SoficShift.hpp"

SoficShift::SoficShift(unsigned int n_symbols, UnweightedMatrixGraph edge_shift) : edge_shift(edge_shift)
{
    this->n_symbols = n_symbols;
};

UnweightedMatrixGraph SoficShift::get_edge_shift() const
{
    return this->edge_shift;
}

bool SoficShift::isValidSequence(const Word &sequence) const
{
    return false; // todo: implement
}
