
#include "SoficShift.hpp"

SoficShift::SoficShift(unsigned int n_symbols, UnweightedMatrixGraph edge_shift) : edge_shift(edge_shift)
{
    this->n_symbols = n_symbols;
};

UnweightedMatrixGraph SoficShift::get_edge_shift() const
{
    return this->edge_shift;
}

bool SoficShift::is_valid_sequence(const Word &sequence) const
{
    return false; // todo: implement
}


std::vector<details::Path> SoficShift::paths_of_length(unsigned int length) const
{
    using details::Path;
    std::vector<Path> queue;
    for (unsigned int i = 0; i < edge_shift.size(); i++)
    {
        queue.push_back(Path({}, i, i));
    }
    std::vector<Path> paths;
    while (!queue.empty())
    {
        Path p = queue.back();
        queue.pop_back();
        if (paths.size() == length)
        {
            paths.push_back(p);
        }
        else
        {
            for (auto &&neighbor : edge_shift.neighbors(p.ending_vertex()))
            {
                Path p2(p);
                p2.ending_vertex = neighbor;
                p2.word.push_back(edge_shift.get_edge_label(p.ending_vertex, neighbor));
                queue.push_back(p2);
            }
        }
    }
    return paths;
}


