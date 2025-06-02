
#include "Measure.hpp"
double MarkovMeasure::cylinder_set_measure(const CylinderSet &cs) const
{
    auto stationary_dist = stationary_distribution();
    std::vector<CylinderSet> disjoint_cylinders = cs.divide_into_disjoint();
    double measure = 0;
    for (CylinderSet &c: disjoint_cylinders)
    {
        Word repr = c.get_representation();
        double cylinder_measure = stationary_dist(repr[0]);
        for (int i = 0; i < repr.size() - 1; i++)
        {
            cylinder_measure *= transition_matrix(repr[i], repr[i+1]);
        }
        measure += cylinder_measure;
    }
    return measure;
}
bool MarkovMeasure::compatible_with(const SFT& sft) const
{
    Matrix<unsigned int> complement_matrix = sft.get_edge_shift().complement().get_adjacency_matrix();
    Array<double> complement_array = complement_matrix.array().cast<double>();
    Array<double> multiplied = complement_array * (transition_matrix.array());
    return multiplied.abs().sum() == 0;
}
ColumnVector<double> MarkovMeasure::stationary_distribution() const
{
    auto [vect, val] = perron_frobenius_eigen(transition_matrix);
    return vect;
}
