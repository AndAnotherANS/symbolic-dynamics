#ifndef SFT_HPP
#define SFT_HPP

#include <vector>
#include <unordered_map>
#include <string>
#include "Graph.hpp"
#include "Language.hpp"
#include "SoficShift.hpp"
#include <set>


class SFT: public SoficShift
{
protected:

    UnweightedMatrixGraph vertex_shift;

    std::set<std::string> forbidden_words;
    FullLanguage language;

    int Mstep;

    UnweightedMatrixGraph build_vertex_shift(int n) const;
    UnweightedMatrixGraph build_edge_shift(int n) const;

public:
    SFT();

    SFT(UnweightedMatrixGraph vertex_shift);
    SFT(const std::vector<std::vector<int> >& forbidden_words);

    bool is_one_step();
    int get_Mstep();



    ~SFT();
};


#endif // SFT_HPP