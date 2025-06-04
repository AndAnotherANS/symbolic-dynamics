#include "SFT.hpp"
#include "BlockCode.hpp"
#include "example_utils.cpp"

#include <bits/ostream.tcc>
#include <iostream>

void print_overview(SFT sft, std::string name)
{
    std::cout << name << ":\n";
    std::cout << "Entropy" << std::endl;
    std::cout << sft.entropy() << std::endl;
    std::cout << "Is transitive?" << std::endl;
    std::cout << (sft.is_transitive() ? "Yes" : "No") << std::endl;
    std::cout << "Is mixing?" << std::endl;
    std::cout << (sft.is_mixing() ? "Yes" : "No")<< std::endl;
}

void sft_example()
{
    // SFT is specified by an alphabet and a finite collection of forbidden words:
    SFT golden_mean_shift({0, 1}, {{1, 1}}); // this is golden mean shift

    // We can check some dynamical properties of this shift:
    // entropy, transitivity, mixing
    print_overview(golden_mean_shift, "Golden mean shift");


    // Each object inheriting from SoficShift is associated with particular representation, stored in edge_shift
    // attribute, accessible with get_edge_shift() method
    // (note: naming is a bit off, in literature edge shift has to have distinct labels on each edge)
    auto representation = golden_mean_shift.get_edge_shift();
    std::cout << std::endl << "Adjacency matrix:" << std::endl;
    std::cout << representation.get_adjacency_matrix() << std::endl;
    std::cout << "Label matrix" <<std::endl;
    print_word_matrix(representation.get_label_matrix());

    // We can construct another representation of the same SFT with get
    UnweightedMatrixGraph higher = std::get<1>(golden_mean_shift.get_nth_higher_block_shift(4));
    std::cout << std::endl << "Higher block shift matrix:" << std::endl;
    std::cout << higher.get_adjacency_matrix() << std::endl;
    // however, this representation is usually not generated in irreducible form (yet)

}