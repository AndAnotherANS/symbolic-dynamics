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

    void initialize(const std::vector<std::string> &word);

    virtual ~ShiftSpace() = default;
};
