#ifndef C4_ENGINE_H
#define C4_ENGINE_H

#include <cstdint>
#include <cstddef>
#include <array>
#include <bit>

namespace c4 {

using Board = uint_fast64_t;
using Move  = uint_fast8_t;

inline constexpr Board BOARD = 0xfdfbf7efdfbf;
inline constexpr Board TURN  = 0x8000000000000000;

enum : Board { X, EMPTY, DRAW, O = TURN };

struct MoveList {
    constexpr MoveList(Move bb) : bb{bb} {}
    constexpr MoveList begin()          { return bb; }
    constexpr MoveList end()            { return 0; }
    constexpr auto operator*() const    { return std::countr_zero(bb); }
    constexpr auto operator++()         { bb &= bb - 1; }
    constexpr bool operator!=(const MoveList&) const = default;
    constexpr bool operator==(const MoveList&) const = default;
private:
    Move bb = 0;
};

constexpr auto bit(int i) 
{ 
    return 1ul << i; 
}

constexpr auto generate(bool top)
{
    std::array<Board, 7> arr = {};
    for (int i = 0; i < 7; ++i)
        arr[i] = bit(5 * top + 7 * i);
    return arr;
}

struct Engine {

    constexpr void reset()
    {
        all = TURN;
        opp = 0;
    }

    constexpr void act(Move col)
    {
        constexpr auto bottom = generate(false);
        all |= all + bottom[col];
        opp ^= all;
    }

    constexpr bool legal(Move col) const
    {
        constexpr auto top = generate(true);
        return col < 7 && !(all & top[col]);
    }

    constexpr MoveList moves() const
    {
        return (~all & BOARD) >> 40;
    }

    constexpr Board turn() const
    { 
        return opp & TURN; 
    }

    constexpr Board result() const
    {
        if (won(opp))
            return ~opp & TURN;
        return (all & BOARD) == BOARD ? DRAW : EMPTY;
    }
private:
    static constexpr bool won(Board board)
    {
        Board y = board & (board >> 6);
        Board z = board & (board >> 7);
        Board w = board & (board >> 8);
        Board x = board & (board >> 1);
        return  (y & (y >> 2 * 6)) | // check \ diagonal
                (z & (z >> 2 * 7)) | // check - horizontal
                (w & (w >> 2 * 8)) | // check / diagonal
                (x & (x >> 2));      // check | vertical
    }
protected:
    Board all = TURN;
    Board opp = 0;
};

}

#endif