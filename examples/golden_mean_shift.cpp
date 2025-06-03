#include <iostream>

#include <SFT.hpp>
#include <GraphAlgorithms.hpp>
#include <Utils.hpp>
#include <ios>

int main() {
    // std::vector<unsigned int> alphabet{0, 1};
    // std::vector<Word> forbidden_words{{0, 0}, {0, 1}};
    // SFT golden_shift_mean(alphabet, forbidden_words);
    // auto edge_shift = golden_shift_mean.get_edge_shift();
    // auto scc_rv = strongly_connected_components(edge_shift);
    // std::cout << std::boolalpha;
    // std::cout << "Is golden mean shift transitive? "
    //     << (scc_rv.number_of_strongly_connected_components == 1) << "\n";
    // std::cout << "Is golden mean shift weakly mixing? " << is_primitive(edge_shift) << "\n";
    // std::cout << edge_shift.get_adjacency_matrix() << "\n";

    SFT graph1({0, 1}, {{1, 1}});
    SFT graph2({0, 1}, {{0, 1}, {1, 0}});
    std::cout << graph1.get_edge_shift().get_adjacency_matrix() << "\n";
    std::cout << "==============================\n";
    std::cout << graph2.get_edge_shift().get_adjacency_matrix() << "\n";
}
