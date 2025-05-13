#include "BlockCode.hpp"

unsigned int BlockCode::get_memory() const
{
    return memory;
}
unsigned int BlockCode::get_anticipation() const
{
    return anticipation;
}


MapBlockCode::MapBlockCode(std::unordered_map<std::string, unsigned int> map): map(std::move(map)) {}

unsigned int MapBlockCode::apply(Word &word) const
{
    return map.at(hash_word(word));
}


