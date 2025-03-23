#pragma once
#include "ShiftSpace.hpp"
#include "Graph.hpp"



class SoficShift : public ShiftSpace 
{
protected:
    UnweightedMatrixGraph edge_shift;

public:
    SoficShift();

    SoficShift(UnweightedMatrixGraph edge_shift);

};

