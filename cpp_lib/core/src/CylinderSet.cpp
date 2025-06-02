#include "CylinderSet.hpp"

#include <algorithm>
#include <complex>
#include <limits>

CylinderSet::CylinderSet(Word representation, int start, int end) : start(start), end(end)
{
    if (representation.size() != end - start + 1)
        throw std::runtime_error("Cylinder set representation size mismatch");
    this->representation = std::move(representation);
}

CylinderSet::CylinderSet(std::vector<int> fixed_positions, std::vector<unsigned> symbols)
{
    start = *std::min_element(fixed_positions.begin(), fixed_positions.end());
    end = *std::max_element(fixed_positions.begin(), fixed_positions.end());

    Word repr(end - start + 1, WILDCARD);
    for (unsigned i = 0; i < fixed_positions.size(); i++)
    {
        unsigned index = fixed_positions[i] - start;
        repr[index] = symbols[i];
    }

    this->representation = repr;
}
unsigned int CylinderSet::operator[](int index) const
{
    if (index < start || index > end)
        return WILDCARD;
    return representation[index - start];
}
CylinderSet CylinderSet::intersection(const CylinderSet &other) const
{
    auto [synch_cs1, synch_cs2] = _synchronize_representation((*this), other);
    auto [start, end] = synch_cs1.get_range();
    Word result_repr = Word(end - start + 1, WILDCARD);
    int result_start = std::numeric_limits<int>::max();
    int result_end = std::numeric_limits<int>::max();
    for (int i = start; i < end + 1; i++)
    {
        if (synch_cs1[i] == synch_cs2[i])
        {
            result_end = i;
            if (result_start == std::numeric_limits<int>::max())
                result_start = i;
            result_repr[i - start] = synch_cs1[i];
        }
    }
    if (result_end == std::numeric_limits<int>::max())
        return {};
    result_repr = Word(result_repr.begin() + result_start - start, result_repr.begin() + result_end - start + 1);
    return {result_repr, result_start, result_end};
}
std::vector<CylinderSet> CylinderSet::divide_into_disjoint() const
{
    const int MAX_INT = std::numeric_limits<int>::max();
    std::vector<CylinderSet> result;
    Word current_repr;
    int current_start = MAX_INT, current_end = MAX_INT;
    for (int i = start; i <= end + 1; i++)
    {
        unsigned int current_symbol = (*this)[i];
        if (current_symbol != WILDCARD)
        {
            if (current_start == MAX_INT)
                current_start = i;
            current_repr.push_back(current_symbol);
        }
        else
        {
            if (current_end == MAX_INT)
                current_end = i - 1;
            result.emplace_back(std::vector(current_repr), current_start, current_end);
            current_repr.clear();
            current_start = current_end = MAX_INT;
        }
    }
    return result;
}

// for right-resolving sofic shifts this only branches on every wildcard
// for non-right-resolving it might branch on every symbol, leading to bad performance
bool _check_paths_rec(const std::vector<unsigned> &alphabet, const UnweightedMatrixGraph &graph, const Word &word, unsigned int node, unsigned int position)
{
    if (position >= word.size()) return true;

    unsigned int current_symbol = word[position];
    if (current_symbol == WILDCARD)
    {
        for (unsigned int symbol: alphabet)
        {
            bool symbol_ok = false;
            for (auto &&edge : graph.edges_from(node))
            {
                if (edge.label[0] == symbol)
                {
                    symbol_ok = _check_paths_rec(alphabet, graph, word, edge.dest, position+1);
                    if (symbol_ok) break;
                }
            }
            if (!symbol_ok) return false;
        }

    }
    else
    {
        bool symbol_ok = false;
        for (auto &&edge : graph.edges_from(node))
        {
            if (edge.label[0] == current_symbol)
            {
                symbol_ok = _check_paths_rec(alphabet, graph, word, edge.dest, position+1);
                if (symbol_ok) break;
            }
        }
        if (!symbol_ok) return false;
    }
    return true;


}


bool CylinderSet::is_subset_of(const SoficShift &ss)
{
    const UnweightedMatrixGraph graph = ss.get_edge_shift();
    for (unsigned node = 0; node < graph.size(); node++)
    {
        if (_check_paths_rec(ss.get_alphabet(), graph, representation, node, 0))
            return true;
    }
    return false;

}
bool CylinderSet::is_subset_of(const CylinderSet &)
{
    return false;
}

std::tuple<double, double> HammingDistance::_bound(CylinderSet &cs1, CylinderSet &cs2) const
{
    double dist_lower = 0;
    double dist_upper = std::numeric_limits<double>::infinity();
    auto [start, end] = cs1.get_range();
    for (int i = start; i < end + 1; i++)
    {
        if (cs1[i] != WILDCARD and cs2[i] != WILDCARD and cs1[i] != cs2[i])
            dist_lower += 1;
    }
    return {dist_lower, dist_upper};
}
std::tuple<double, double> PadicDistance::_bound(CylinderSet &cs1, CylinderSet &cs2) const
{
    double dist_lower = 0;
    double dist_upper = 0;
    auto [start, end] = cs1.get_range();
    for (int i = start; i < end + 1; i++)
    {
        if (cs1[i] == WILDCARD or cs2[i] == WILDCARD)
        {
            dist_upper += std::pow(2., -abs(i));
        }
        else if (cs1[i] != cs2[i])
        {
            dist_upper += std::pow(2., -abs(i));
            dist_lower += std::pow(2., -abs(i));
        }
    }
    dist_upper += std::pow(2., -abs(start));
    dist_upper += std::pow(2., -abs(end));
    return {dist_lower, dist_upper};
}

std::tuple<CylinderSet, CylinderSet> _synchronize_representation(const CylinderSet &cs1, const CylinderSet &cs2)
{
    int common_start = std::min(cs1.start, cs2.start);

    int common_end = std::max(cs1.end, cs2.end);

    Word repr1(common_end - common_start + 1, std::numeric_limits<unsigned>::max());
    std::copy(cs1.representation.begin(), cs1.representation.end(), repr1.begin() + (cs1.start - common_start));

    Word repr2(common_end - common_start + 1, std::numeric_limits<unsigned>::max());
    std::copy(cs2.representation.begin(), cs2.representation.end(), repr2.begin() + (cs2.start - common_start));

    return {CylinderSet(repr1, common_start, common_end), CylinderSet(repr2, common_start, common_end)};
}
