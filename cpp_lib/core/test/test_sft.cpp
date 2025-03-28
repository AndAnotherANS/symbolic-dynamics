#include "SFT.hpp"
#include <gtest/gtest.h>

TEST(SFTTest, BinaryShiftWithForbiddenWord) {
    int n_symbols = 2;
    std::vector<Word> forbidden_words = {{1, 1}}; // golden mean shift 
    SFT sft(n_symbols, forbidden_words);

    auto edge_shift = sft.get_edge_shift();
    const UnweightedMatrixGraph::Matrix& edge_shift_matrix = edge_shift.get_adjacency_matrix();

    EXPECT_EQ(edge_shift_matrix, UnweightedMatrixGraph::Matrix(
        {{1, 1}, 
        {1, 0}}
    )
    );

    EXPECT_EQ(edge_shift.get_node_label(0), Word({0}));
    EXPECT_EQ(edge_shift.get_node_label(1), Word({1}));

    EXPECT_EQ(edge_shift.get_label_matrix(), 
    UnweightedMatrixGraph::LabelMatrix(
        {{Word({0, 0}), Word({0, 1})}, 
        {Word({1, 0}), Word()}}
    )
    );

}

TEST(SFTTest, TernaryShiftWithForbiddenWords) {
    int n_symbols = 3;
    std::vector<Word> forbidden_words = {{1, 1}, {2, 2}};
    SFT sft(n_symbols, forbidden_words);

    auto edge_shift = sft.get_edge_shift();
    const UnweightedMatrixGraph::Matrix& edge_shift_matrix = edge_shift.get_adjacency_matrix();

    EXPECT_EQ(edge_shift_matrix, UnweightedMatrixGraph::Matrix(
            {{1, 1, 1},
             {1, 0, 1},
             {1, 1, 0}}
    )
    );

    EXPECT_EQ(edge_shift.get_node_label(0), Word({0}));
    EXPECT_EQ(edge_shift.get_node_label(1), Word({1}));
    EXPECT_EQ(edge_shift.get_node_label(2), Word({2}));

    EXPECT_EQ(edge_shift.get_label_matrix(),
              UnweightedMatrixGraph::LabelMatrix(
                        {{Word({0, 0}), Word({0, 1}), Word({0, 2})},
                        {Word({1, 0}), Word(), Word({1, 2})},
                        {Word({2, 0}), Word({2, 1}), Word()}}
              )
    );

}

TEST(SFTTest, BinaryShiftWithThreeLetterForbiddenWord) {
    int n_symbols = 2;
    std::vector<Word> forbidden_words = {{1, 1, 0}};
    SFT sft(n_symbols, forbidden_words);

    auto edge_shift = sft.get_edge_shift();
    const UnweightedMatrixGraph::Matrix& edge_shift_matrix = edge_shift.get_adjacency_matrix();

    EXPECT_EQ(edge_shift_matrix, UnweightedMatrixGraph::Matrix(
            {{1, 1, 0, 0},
             {0, 0, 1, 1},
             {1, 1, 0, 0},
             {0, 0, 0, 1}}
    )
    );

    EXPECT_EQ(edge_shift.get_node_label(0), Word({0, 0}));
    EXPECT_EQ(edge_shift.get_node_label(1), Word({0, 1}));
    EXPECT_EQ(edge_shift.get_node_label(2), Word({1, 0}));
    EXPECT_EQ(edge_shift.get_node_label(3), Word({1, 1}));

    EXPECT_EQ(edge_shift.get_label_matrix(),
              UnweightedMatrixGraph::LabelMatrix(
                      {{Word({0, 0, 0}), Word({0, 0, 1}), Word(), Word()},
                       {Word(), Word(), Word({0, 1, 0}), Word({0, 1, 1})},
                       {Word({1, 0, 0}), Word({1, 0, 1}), Word(), Word()},
                       {Word(), Word(), Word(), Word({1, 1, 1})}}
              )
    );

}

TEST(SFTTest, BinaryShiftWithThreeAndTwoLetterForbiddenWord) {
    int n_symbols = 2;
    std::vector<Word> forbidden_words = {{1, 0}, {1, 1, 0}};
    SFT sft(n_symbols, forbidden_words);

    auto edge_shift = sft.get_edge_shift();
    const UnweightedMatrixGraph::Matrix& edge_shift_matrix = edge_shift.get_adjacency_matrix();

    EXPECT_EQ(edge_shift_matrix, UnweightedMatrixGraph::Matrix(
            {{1, 1, 0, 0},
             {0, 0, 0, 1},
             {0, 0, 0, 0},
             {0, 0, 0, 1}}
    )
    );

    EXPECT_EQ(edge_shift.get_node_label(0), Word({0, 0}));
    EXPECT_EQ(edge_shift.get_node_label(1), Word({0, 1}));
    EXPECT_EQ(edge_shift.get_node_label(2), Word({1, 0}));
    EXPECT_EQ(edge_shift.get_node_label(3), Word({1, 1}));

    EXPECT_EQ(edge_shift.get_label_matrix(),
              UnweightedMatrixGraph::LabelMatrix(
                      {{Word({0, 0, 0}), Word({0, 0, 1}), Word(), Word()},
                       {Word(), Word(), Word(), Word({0, 1, 1})},
                       {Word(), Word(), Word(), Word()},
                       {Word(), Word(), Word(), Word({1, 1, 1})}}
              )
    );

}