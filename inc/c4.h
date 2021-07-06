#ifndef C4_H
#define C4_H

#include <cstdint>
#include <cstddef>

using Bitboard  = uint_fast64_t;
using Move      = uint_fast8_t;

struct MoveList {
    const Move* begin() const { return &list[0]; }
    const Move* end() const   { return &list[len]; }
    size_t size() const       { return len; }
    void erase(size_t idx)    { list[idx] = list[--len]; }
    void save(Move m)         { list[len++] = m; }
private:
    Move list[7];
    size_t len = 0;
};

constexpr Bitboard BOARD    = 0xfdfbf7efdfbf;
constexpr Bitboard TURN     = 0x8000000000000000;

enum : Bitboard { X, EMPTY, DRAW, O = TURN };

struct C4 {

    void print() const;
    void play();
    void reset();
    void make_move(Move move);
    bool legal(Move move) const;

    Bitboard turn() const    { return current & TURN; }
    Bitboard result() const;

    Move ask_input() const;
    MoveList moves() const;
private:
    Bitboard all        = TURN;
    Bitboard current    = 0;
};

#endif // C4_H
