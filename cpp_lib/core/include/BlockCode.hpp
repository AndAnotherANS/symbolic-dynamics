#pragma once

#include "SFT.hpp"
#include "SoficShift.hpp"

#include <Utils.hpp>
#include <string>
#include <unordered_map>

class BlockCode
{
protected:
    unsigned int memory=0;
    unsigned int anticipation=0;
public:
    virtual unsigned int map(Word &word) const = 0;

    SoficShift apply(SFT &sft) const;

    [[nodiscard]] unsigned int get_memory() const;
    [[nodiscard]] unsigned int get_anticipation() const;
    [[nodiscard]] unsigned int get_window_size() const;

    virtual ~BlockCode() = default;
};


class MapBlockCode: public BlockCode
{
protected:
    std::unordered_map<std::string, unsigned int> internal_map;
public:
    MapBlockCode() = default;
    explicit MapBlockCode(std::unordered_map<std::string, unsigned int> map);
    unsigned int map(Word &word) const override;
};
