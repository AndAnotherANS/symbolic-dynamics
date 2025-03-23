#ifndef SOPHICSHIFT_HPP
#define SOPHICSHIFT_HPP

#include "ShiftSpace.hpp"
#include "Graph.hpp"



class SoficShift : public ShiftSpace 
{
protected:
    UnweightedMatrixGraph edge_shift;

public:
    SoficShift();

    SoficShift(UnweightedMatrixGraph edge_shift);

    ~SoficShift();

};

#endif // SOPHICSHIFT_HPP
