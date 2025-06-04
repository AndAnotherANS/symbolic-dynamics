#pragma once
#include "Utils.hpp"
#include <string>
#include <vector>

class ShiftSpace
{
  protected:
    std::vector<unsigned int> alphabet;

  public:
    ShiftSpace();
    explicit ShiftSpace(const std::vector<unsigned int>& alphabet): alphabet(alphabet) {};

    virtual ~ShiftSpace() = default;
};
