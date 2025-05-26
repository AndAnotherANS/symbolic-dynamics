#pragma once


#include "SoficShift.hpp"
#include "SFT.hpp"

#include <Utils.hpp>
#include <string>
#include <unordered_map>

class BlockCode
{
protected:
    std::function<unsigned int(const Word&)> internal_fun;
    unsigned int memory=0;
    unsigned int anticipation=0;
public:
    explicit BlockCode(const std::function<unsigned int(const Word&)>& fun, unsigned int memory, unsigned int anticipation);
    explicit BlockCode(const std::unordered_map<std::string, unsigned int> &map, unsigned int memory, unsigned int anticipation);


    [[nodiscard]] unsigned int map(const Word &word) const;

    [[nodiscard]] SoficShift map(const SFT &sft) const;
    [[nodiscard]] SoficShift map(const SoficShift &sofic_shift) const;

    [[nodiscard]] unsigned int get_memory() const;
    [[nodiscard]] unsigned int get_anticipation() const;
    [[nodiscard]] unsigned int get_window_size() const;

    [[nodiscard]] BlockCode compose(const BlockCode &other) const;

    virtual ~BlockCode() = default;
};

