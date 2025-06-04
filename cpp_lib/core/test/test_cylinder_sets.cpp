#include "CylinderSet.hpp"
#include "Measure.hpp"

#include <gtest/gtest.h>


TEST(CylinderSet, ConstructingObject)
{
    CylinderSet cylinder_set({0, 1, WILDCARD, 0, 1}, -1, 3);
    ASSERT_EQ(cylinder_set[-1], 0);
    ASSERT_EQ(cylinder_set[0], 1);
    ASSERT_EQ(cylinder_set[1], WILDCARD);
    ASSERT_EQ(cylinder_set[-10], WILDCARD);


    CylinderSet cylinder_set2({-10, 0, 10}, {0, 1, 2});
    ASSERT_EQ(cylinder_set2[-10], 0);
    ASSERT_EQ(cylinder_set2[10], 2);
    ASSERT_EQ(cylinder_set2[3], WILDCARD);
    ASSERT_EQ(cylinder_set2[-100], WILDCARD);
    auto [start, end] = cylinder_set2.get_range();
    ASSERT_EQ(start, -10);
    ASSERT_EQ(end, 10);

}

TEST(CylinderSet, Distances)
{
    HammingDistance hamming_distance;
    PadicDistance padic_distance;
    CylinderSet cylinder_set({0, 1, WILDCARD, 0, 1}, -1, 3);
    CylinderSet cylinder_set2({0, 0, WILDCARD, 0, 1}, -2, 2);
    auto [h_lower, h_upper] = hamming_distance.bound(cylinder_set, cylinder_set2);
    auto [p_lower, p_higher] = padic_distance.bound(cylinder_set, cylinder_set2);

    ASSERT_DOUBLE_EQ(h_lower, 1);
    ASSERT_DOUBLE_EQ(h_upper, std::numeric_limits<double>::infinity());
    ASSERT_DOUBLE_EQ(p_lower, 0.25);
    ASSERT_DOUBLE_EQ(p_higher, 2.5);
}

TEST(CylinderSet, Intersection)
{
    CylinderSet cylinder_set({0, 1, WILDCARD, 1, 1}, -1, 3);
    CylinderSet cylinder_set2({0, 0, WILDCARD, 1, 1}, -2, 2);
    CylinderSet intersection = cylinder_set.intersection(cylinder_set2);
    ASSERT_EQ(intersection[-1], 0);
    ASSERT_EQ(intersection[0], WILDCARD);
    ASSERT_EQ(intersection[1], WILDCARD);
    ASSERT_EQ(intersection[2], 1);
    auto [start, end] = intersection.get_range();
    ASSERT_EQ(start, -1);
    ASSERT_EQ(end, 2);
}

TEST(CylinderSet, SubsetOfShift)
{
    CylinderSet cylinder_set({0, 1, 0, 1, 1, 0, 1}, -1, 5);
    CylinderSet cylinder_set2({0, 0, 0, 1, 0, 1, 0, 0}, -2, 5);
    CylinderSet cylinder_set3({0, WILDCARD, 0, 1, 0, 1, 0, WILDCARD}, -2, 5);
    CylinderSet cylinder_set4({0, 0, 0, 1, WILDCARD, 1, 0, WILDCARD}, -2, 5);

    UnweightedMatrixGraph g(2);
    g.add_edge(0, 0, 1, {0});
    g.add_edge(1, 0, 1, {0});
    g.add_edge(0, 1, 1, {1});

    SoficShift<false, true> ss({0, 1}, g);

    ASSERT_FALSE(cylinder_set.is_subset_of(ss));
    ASSERT_TRUE(cylinder_set2.is_subset_of(ss));
    ASSERT_TRUE(cylinder_set3.is_subset_of(ss));
    ASSERT_FALSE(cylinder_set4.is_subset_of(ss));
}

TEST(Measure, CylinderMeasure)
{
    Eigen::Matrix<double, 2, 2> m;
    m << 0.25, 0.75, 0.25, 0.75;
    MarkovMeasure measure(m);
    ColumnVector<double> stationary = measure.stationary_distribution();
    ASSERT_TRUE(stationary.isApprox(m * stationary));

    CylinderSet zero({0}, {0});
    CylinderSet one({0}, {1});
    ASSERT_NEAR(measure.cylinder_set_measure(zero) + measure.cylinder_set_measure(one), -1.414, 0.01);
}