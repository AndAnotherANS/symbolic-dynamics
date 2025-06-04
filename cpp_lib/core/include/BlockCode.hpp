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

    [[nodiscard]] SoficShift<false, false> map(const SFT &sft) const;

    template<bool RR, bool IRR>
    [[nodiscard]] SoficShift<false, false> map(const SoficShift<RR, IRR> &sofic_shift) const;

    [[nodiscard]] unsigned int get_memory() const;
    [[nodiscard]] unsigned int get_anticipation() const;
    [[nodiscard]] unsigned int get_window_size() const;

    [[nodiscard]] BlockCode compose(const BlockCode &other) const;

    virtual ~BlockCode() = default;
};


template<bool RR, bool IRR>
std::tuple<SFT, BlockCode> get_sft_factor_map(const SoficShift<RR, IRR>& shift)
{
    auto edges = shift.get_edge_shift().edges();
    unsigned int counter = 0;
    std::unordered_map<std::string, unsigned int> map;
    std::vector<unsigned int> alphabet;
    for (auto && edge : edges)
    {
        alphabet.push_back(counter);
        map[hash_word(edge.label)] = counter++;
    }

    auto complement = shift.get_edge_shift().complement();
    std::vector<Word> forbidden_words;
    for (auto &&edge: complement.edges())
    {
        forbidden_words.push_back({edge.source, edge.dest});
    }

    return std::make_tuple(SFT(alphabet, forbidden_words), BlockCode(map, 0, 0));


}


template<bool RR, bool IRR>
SoficShift<false, false> BlockCode::map(const SoficShift<RR, IRR> &sofic_shift) const
{
    auto [sft, factor_map] = get_sft_factor_map(sofic_shift);
    auto composed_map = factor_map.compose((*this));
    return composed_map.map(sft);
}