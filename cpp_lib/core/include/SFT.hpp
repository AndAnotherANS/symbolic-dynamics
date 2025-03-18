#ifndef SFT_HPP
#define SFT_HPP

#include <vector>
#include <unordered_map>
#include <string>
#include "Graph.hpp"
#include "Language.hpp"
#include <set>



class SFT
{
protected:
    std::vector<int> alphabet;
    UnweightedMatrixGraph vertex_shift;
    UnweightedMatrixGraph edge_shift;

    std::set<std::string> forbidden_words;

    int Mstep;

    std::vector<std::vector<int> > build_vertex_shift(int n) const;
    std::vector<std::vector<int> > build_edge_shift(int n) const;

public:
    SFT();

    SFT(UnweightedMatrixGraph vertex_or_edge_shift, bool is_vertex_shift);
    SFT(const std::vector<std::vector<int> >& forbidden_words);

    bool is_one_step();
    int get_Mstep();



    ~SFT();
};


#endif // SFT_HPP