#pragma once
#include "Graph.hpp"
#include "GraphAlgorithms.hpp"
#include "ShiftSpace.hpp"

class BlockCode;



template<bool RightResolving, bool Irreducible>
class SoficShift : public ShiftSpace
{
  protected:
    UnweightedMatrixGraph edge_shift;

  public:
    SoficShift() = default;

    SoficShift(std::vector<unsigned int> alphabet, UnweightedMatrixGraph edge_shift);

    [[nodiscard]] UnweightedMatrixGraph get_edge_shift() const;

    [[nodiscard]] std::vector<unsigned int> get_alphabet() const
    {
        return alphabet;
    }

    ~SoficShift() override = default;
};

template<bool RR, bool IRR>
inline SoficShift<RR, IRR>::SoficShift(std::vector<unsigned int> alphabet, UnweightedMatrixGraph edge_shift) : edge_shift(edge_shift)
{
    this->alphabet = std::move(alphabet);
};

template <bool RR, bool IRR> inline UnweightedMatrixGraph SoficShift<RR, IRR>::get_edge_shift() const
{
    return this->edge_shift;
}

template <bool RR, bool IRR>
SoficShift<RR, false> inline sofic_shift_union(SoficShift<RR, IRR> ss1, SoficShift<RR, IRR> ss2)
{
    auto size1 = ss1.get_edge_shift().size();
    auto size2 = ss2.get_edge_shift().size();
    UnweightedMatrixGraph result_graph(size1 + size2);
    for (auto &&edge: ss1.get_edge_shift().edges())
        result_graph.add_edge(edge.source, edge.dest, 1, edge.label);

    for (auto &&edge: ss2.get_edge_shift().edges())
        result_graph.add_edge(edge.source + size1, edge.dest + size1, 1, edge.label);

    std::set<unsigned> alphabet;
    for (auto &&a: ss1.get_alphabet()) alphabet.insert(a);
    for (auto &&a: ss2.get_alphabet()) alphabet.insert(a);

    return {{alphabet.begin(), alphabet.end()}, result_graph};
}


template<bool RR, bool IRR>
SoficShift<RR, false> inline sofic_shift_intersection(SoficShift<RR, IRR> ss1, SoficShift<RR, IRR> ss2)
{
    auto size1 = ss1.get_edge_shift().size();
    auto size2 = ss2.get_edge_shift().size();
    UnweightedMatrixGraph label_product_graph(size1 * size2);
    for (auto &edge1 : ss1.get_edge_shift().edges())
    {
        for (auto &edge2 : ss2.get_edge_shift().edges())
        {
            if (edge1.label != edge2.label) continue;
            label_product_graph.add_edge(
                edge1.source * size1 + edge2.source,
                edge1.dest * size1 + edge2.dest,
                1,
                edge1.label
                );
        }
    }
    return {ss1.get_alphabet(), label_product_graph};

}



template<bool IRR> class SoficShift<true, IRR>
{
    UnweightedMatrixGraph edge_shift;
    double entropy();
};

template<bool IRR>
using RightResolvingSoficShift = SoficShift<true, IRR>;


template <> inline double SoficShift<true, false>::entropy()
{
    std::vector<Matrix<unsigned>> components = sccs_as_matrices<unsigned>(this->edge_shift);
    std::vector<double> perron_eigenvalues;
    for (Matrix<unsigned> &m: components)
    {
        auto [eigvect, eigval] = perron_frobenius_eigen(m.cast<double>());
        perron_eigenvalues.push_back(eigval);
    }
    return log(*std::max_element(perron_eigenvalues.begin(), perron_eigenvalues.end()));
}

template <> inline double SoficShift<true, true>::entropy()
{
    auto [eigvect, eigval] = perron_frobenius_eigen(edge_shift.get_adjacency_matrix().cast<double>());
    return log(eigval);
}
