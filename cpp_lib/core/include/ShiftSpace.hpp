#pragma once
#include "Utils.hpp"
#include <string>
#include <vector>

class ShiftSpace
{
  protected:
    unsigned int n_symbols = 0;

  public:
    ShiftSpace();

    void initialize(const std::vector<std::string> &symbols);
    [[nodiscard]] virtual bool is_valid_sequence(const Word &sequence) const = 0;

    virtual ~ShiftSpace() = default;
};
