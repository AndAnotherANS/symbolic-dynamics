#include "BlockCode.hpp"


SoficShift BlockCode::apply(SFT &sft) const
{
    UnweightedMatrixGraph higher_block_shift = sft.get_nth_higher_block_shift();
}

unsigned int BlockCode::get_memory() const
{
    return memory;
}
unsigned int BlockCode::get_anticipation() const
{
    return anticipation;
}

unsigned int BlockCode::get_window_size() const
{
    return anticipation + memory + 1;
}

MapBlockCode::MapBlockCode(std::unordered_map<std::string, unsigned int> map): internal_map(std::move(map)) {}

unsigned int MapBlockCode::map(Word &word) const
{
    return internal_map.at(hash_word(word));
}


