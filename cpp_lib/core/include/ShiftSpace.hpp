#ifndef SHIFTSPACE_HPP
#define SHIFTSPACE_HPP

#include <vector>
#include <string>

class ShiftSpace {
protected:
    std::vector<int> alphabet;  

public:
    ShiftSpace();
    ~ShiftSpace();

    void initialize(const std::vector<std::string>& symbols);
    bool isValidSequence(const std::string& sequence) const;

};

#endif // SHIFTSPACE_HPP
