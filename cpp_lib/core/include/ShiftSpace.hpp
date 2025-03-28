#pragma once
#include <vector>
#include <string>
#include "Language.hpp"

class ShiftSpace {
protected:
    std::vector<int> alphabet;  

public:
    ShiftSpace();

    void initialize(const std::vector<std::string>& symbols);
    [[nodiscard]] virtual bool isValidSequence(const Word& sequence) const = 0;

    virtual ~ShiftSpace() = default;
};

