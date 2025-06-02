#pragma once
#include "CylinderSet.hpp"
#include "Matrix.hpp"
#include "SFT.hpp"

class Measure
{
public:
    [[nodiscard]] virtual double cylinder_set_measure(const CylinderSet &cs) const = 0;

    virtual ~Measure() = default;
};


class MarkovMeasure: public Measure
{
  public:
    [[nodiscard]] double cylinder_set_measure(const CylinderSet &cs) const override;

  protected:
    Matrix<double> transition_matrix;
public:
    explicit MarkovMeasure(Matrix<double> const &transition_matrix) :transition_matrix(transition_matrix) {};

    [[nodiscard]] bool compatible_with(const SFT& sft) const;
    [[nodiscard]] ColumnVector<double> stationary_distribution() const;
};
