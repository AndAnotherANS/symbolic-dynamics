# pragma once

#include "Utils.hpp"

#include <charconv>
#include <iomanip>
#include <iostream>
#include <vector>

void print_word_matrix(std::vector<std::vector<Word>> v)
{
    for (auto &row : v)
    {
        for (auto &col : row)
        {
            std::stringstream ss;
            for (auto &c: col)
                ss << c;
            std::cout << std::setw(5) << ss.str() <<  ' ';

        }
        std::cout << std::endl;
    }
}