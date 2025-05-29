#include "CylinderSet.hpp"

#include <algorithm>
#include <limits>

CylinderSet::CylinderSet(Word representation, int start, int end)
{
    this->representation = std::move(representation);
}

CylinderSet::CylinderSet(std::vector<int> fixed_positions, std::vector<unsigned> symbols)
{
    start = *std::min_element(fixed_positions.begin(), fixed_positions.end());
    end = *std::max_element(fixed_positions.begin(), fixed_positions.end());

    Word repr(end - start, std::numeric_limits<unsigned int>::max());
    for (unsigned i = 0; i < fixed_positions.size(); i++)
    {
        unsigned index = fixed_positions[i] - start;
        repr[index] = symbols[i];
    }

    this->representation = repr;
}




