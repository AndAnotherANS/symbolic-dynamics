#pragma once

#include "SoficShift.hpp"
#include "Utils.hpp"
#include <limits>
#include <tuple>

const unsigned int WILDCARD = std::numeric_limits<unsigned int>::max();

class CylinderSet
{
protected:
	Word representation;
	int start=0;
	int end=-1;

	friend std::tuple<CylinderSet, CylinderSet>
	_synchronize_representation(const CylinderSet& cs1, const CylinderSet& cs2);

public:
	CylinderSet() = default;

	CylinderSet(Word representation, int start, int end);

	CylinderSet(std::vector<int> fixed_positions, std::vector<unsigned int> symbols);

    [[nodiscard]] unsigned int operator[](int index) const;

    [[nodiscard]] Word get_representation() const
    {
        return representation;
    }
    [[nodiscard]] int get_start() const
    {
        return start;
    }
    [[nodiscard]] int get_end() const
    {
        return end;
    }
    [[nodiscard]] std::tuple<int, int> get_range() const
    {
        return {start, end};
    }

    [[nodiscard]] CylinderSet intersection(const CylinderSet& other) const;

    [[nodiscard]] std::vector<CylinderSet> divide_into_disjoint() const;

    template<bool RR, bool IRR>
    [[nodiscard]] bool is_subset_of(const SoficShift<RR, IRR> &);
    //[[nodiscard]] bool is_subset_of(const CylinderSet &);

    virtual ~CylinderSet() = default;
};


// Currently we only calculate distances assuming cylinder sets come from a full shift
// (wildcard symbols can be any symbol from the alphabet, without constraints given by sofic shifts/sfts)
class Distance
{
protected:
	virtual std::tuple<double, double> _bound(CylinderSet &cs1, CylinderSet &cs2) const =0;
public:
	std::tuple<double, double> bound(CylinderSet &cs1, CylinderSet &cs2) const
	{
		auto [intermediate1, intermediate2] = _synchronize_representation(cs1, cs2);
		return _bound(intermediate1, intermediate2);
	}

	virtual ~Distance() = default;
};

class HammingDistance: public Distance
{
protected:
	std::tuple<double, double> _bound(CylinderSet &cs1, CylinderSet &cs2) const override;
};

class PadicDistance: public Distance
{
protected:
    std::tuple<double, double> _bound(CylinderSet &cs1, CylinderSet &cs2) const override;
};


// for right-resolving sofic shifts this only branches on every wildcard
// for non-right-resolving it might branch on every symbol, leading to bad performance
inline bool _check_paths_rec(const std::vector<unsigned> &alphabet, const UnweightedMatrixGraph &graph, const Word &word, unsigned int node, unsigned int position)
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

template<bool RR, bool IRR>
bool CylinderSet::is_subset_of(const SoficShift<RR, IRR> &ss)
{
    const UnweightedMatrixGraph graph = ss.get_edge_shift();
    for (unsigned node = 0; node < graph.size(); node++)
    {
        if (_check_paths_rec(ss.get_alphabet(), graph, representation, node, 0))
            return true;
    }
    return false;

}