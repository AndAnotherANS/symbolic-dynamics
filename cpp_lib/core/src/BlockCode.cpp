#include "BlockCode.hpp"


SoficShift<false, false> BlockCode::map(const SFT &sft) const
{
    auto window_size = get_window_size();
    auto n = std::max(get_window_size(), sft.get_M_step());
    auto higher_block_shift = std::get<1>(sft.get_nth_higher_block_shift(n));
    std::set<unsigned int> images;
    for (auto &&edge: higher_block_shift.edges())
    {
        Word label = Word(edge.label.begin(), edge.label.begin() + window_size);
        auto image = this->map(label);
        images.insert(image);
        higher_block_shift.set_edge_label(edge.source, edge.dest, {image});

    }
    SoficShift<false, false> result(std::vector(images.begin(), images.end()), higher_block_shift);
    return result;
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
BlockCode BlockCode::compose(const BlockCode &other) const
{

    auto fun = [this, other](const Word& w)
    {
        Word intermediate;
        for (unsigned i = memory; i < w.size() - anticipation - 1; i++)
            intermediate.push_back(this->map(Word(w.begin() + i, w.begin() + i + get_window_size())));
        return other.map(intermediate);
    };

    return BlockCode(fun, memory + other.memory, anticipation + other.anticipation);
}

BlockCode::BlockCode(const std::unordered_map<std::string, unsigned int> &map, unsigned int memory, unsigned int anticipation): memory(memory), anticipation(anticipation)
{
    this->internal_fun = [map](const Word& w) {return map.at(hash_word(w));};
}

 BlockCode::BlockCode(const std::function<unsigned int(const Word&)>& fun, unsigned int memory, unsigned int anticipation): memory(memory), anticipation(anticipation)
{
    this->internal_fun = fun;
}


unsigned int BlockCode::map(const Word &word) const
{
    if (word.size() != get_window_size())
        throw std::runtime_error("BlockCode::map: wrong size");
    return internal_fun(word);
}
