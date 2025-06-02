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

    [[nodiscard]] bool is_subset_of(const SoficShift &);
    [[nodiscard]] bool is_subset_of(const CylinderSet &);

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