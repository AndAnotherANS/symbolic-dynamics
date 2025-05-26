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
    [[nodiscard]] virtual bool is_valid_sequence(const Word &sequence) const = 0;

    virtual ~ShiftSpace() = default;
};
