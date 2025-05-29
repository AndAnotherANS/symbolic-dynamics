#pragma once
#include "Utils.hpp"




class CylinderSet
{
  protected:
    Word representation;
    int start;
    int end;
    friend CylinderSet _synchronize_representation(const CylinderSet& cs1, const CylinderSet& cs2);

  public:
    CylinderSet() = default;
    CylinderSet(Word representation, int start, int end);
    CylinderSet(std::vector<int> fixed_positions, std::vector<unsigned int> symbols);
    virtual ~CylinderSet() = default;
};

CylinderSet _synchronize_representation(const CylinderSet& cs1, const CylinderSet& cs2)
{

}