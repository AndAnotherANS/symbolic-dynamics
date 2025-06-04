#include "SFT.hpp"
#include "BlockCode.hpp"
#include "example_utils.cpp"

#include <bits/ostream.tcc>
#include <iostream>

template<bool irr>
void print_overview(SoficShift<true, irr> ss, std::string name)
{
    std::cout << name << ":\n";
    std::cout << "Entropy" << std::endl;
    std::cout << ss.entropy() << std::endl;
}

void sofic_example()
{
    // Sofic shifts are specified by their presentation, with there being two main traits that can be specified
    // during declaring a variable of type SoficShift - right-resolving and irreducible
    UnweightedMatrixGraph presentation(2);
    presentation.add_edge(0, 0, 1, {1});
    presentation.add_edge(0, 1, 1, {0});
    presentation.add_edge(1, 0, 1, {0});

    SoficShift<true, true> even_shift({0, 1}, presentation);
    // For now, it is caller's responsibility to check if the supplied presentation satisfies those traits

    // For right-resolving sofic shifts we can calculate entropy from perron-frobenius theorem
    print_overview(even_shift, "Even shift");

    // We can take unions and intersections of sofic shifts. These operations preserve right-resolving presentation,
    // but cannot guarantee irreducibility
    UnweightedMatrixGraph presentation_full(2);
    presentation_full.add_edge(0, 1, 1, {1});
    presentation_full.add_edge(1, 1, 1, {1});
    presentation_full.add_edge(0, 0, 1, {0});
    presentation_full.add_edge(1, 0, 1, {0});

    SoficShift<true, true> full_shift({0, 1}, presentation_full);

    std::cout << full_shift.get_edge_shift().get_adjacency_matrix() << std::endl;
    print_overview(full_shift, "Full shift");

    SoficShift<true, false> intersection = sofic_shift_intersection(full_shift, even_shift);
    SoficShift<true, false> sum = sofic_shift_union(full_shift, even_shift);

    print_overview(intersection, "Intersection");
    print_overview(sum, "Union");
}