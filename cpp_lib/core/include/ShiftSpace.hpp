#pragma once
#include <vector>
#include <string>

class ShiftSpace {
protected:
    std::vector<int> alphabet;  

public:
    ShiftSpace();

    void initialize(const std::vector<std::string>& symbols);
    bool isValidSequence(const std::string& sequence) const;

};

