#pragma once

#include "Utils.hpp"
#include <limits>

class CylinderSet
{
protected:
	Word representation;
	int start;
	int end;

	friend std::tuple<CylinderSet, CylinderSet>
	_synchronize_representation(const CylinderSet& cs1, const CylinderSet& cs2);

public:
	CylinderSet() = default;

	CylinderSet(Word representation, int start, int end);

	CylinderSet(std::vector<int> fixed_positions, std::vector<unsigned int> symbols);

	Word& get_representation() const;
	int get_start() const;
	int get_end() const;

	virtual ~CylinderSet() = default;
};

std::tuple<CylinderSet, CylinderSet> _synchronize_representation(const CylinderSet& cs1, const CylinderSet& cs2)
{
	int common_start = std::min(cs1.start, cs2.start);

	int common_end = std::max(cs1.end, cs2.end);

	Word repr1(common_end - common_start, std::numeric_limits<unsigned>::max());
	std::copy(cs1.representation.begin(), cs1.representation.end(), repr1.begin());

	Word repr2(common_end - common_start, std::numeric_limits<unsigned>::max());
	std::copy(cs2.representation.begin(), cs2.representation.end(), repr2.begin());

	return { CylinderSet(repr1, common_start, common_end),
			CylinderSet(repr2, common_start, common_end)};
}

class Distance
{
protected:
	virtual double dist(CylinderSet &cs1, CylinderSet &cs2) const =0;
public:
	double operator()(CylinderSet &cs1, CylinderSet &cs2) const
	{
		auto [intermediate1, intermediate2] = _synchronize_representation(cs1, cs2);
		return dist(intermediate1, intermediate2);
	}

	virtual ~Distance() = default;
};

class HammingDistance: Distance
{
protected:
	double dist(CylinderSet &cs1, CylinderSet &cs2) const override;
};
