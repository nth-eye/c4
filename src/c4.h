#include <cstdint>
#include <cassert>
#include <sstream>
#include <iostream>
#include <array>
#include <vector>
#include <limits>
#include <tuple>

#pragma once

namespace c4 {

// BOARD REPRESENTATION:	  	

//      +-------------------+
//      | 0 0 0 0 0 0 0 0 1 | <-- 63 bit
// row 5| 1 1 1 1 1 1 1 0 0 |
// row 4| 1 1 1 1 1 1 1 0 0 |
// row 3| 1 1 1 1 1 1 1 0 0 |
// row 2| 1 1 1 1 1 1 1 0 0 |
// row 1| 1 1 1 1 1 1 1 0 0 |
// row 0| 1 1 1 1 1 1 1 0 0 | <-- 56 bit
//      +-------------------+
//        |               |
//      0 bit           42 bit

// Last bit represents current player. 0x0 is X and 0x8000000000000000 is O.


inline constexpr uint64_t BOARD = 0xFDFBF7EFDFBF;
inline constexpr uint64_t TURN = 0x8000000000000000;

using Action = int;
using ActionList = std::vector<Action>;
using State = std::pair<uint64_t, uint64_t>;

enum : uint64_t {	
    X = 0x0, 
    O = 0x8000000000000000, 
    EMPTY = 0x2, 
    DRAW = 0x3	
};

class Game {
    uint64_t all = TURN;
    uint64_t current = 0;
    std::vector<State> history;
public:
    static constexpr Action NO_MOVE = 7;

    Game() { history.emplace_back(all, current); }
    Game(uint64_t all_, uint64_t current_) : all(all_), current(current_) { history.emplace_back(all, current); }

    void reset();
    void test();

    uint64_t result() const;
    uint64_t to_play() const    { return current & TURN; }
    bool terminal() const       { return result() != EMPTY; }
    bool legal(Action move) const;
    float reward() const;
    float act(Action move);

    Action ask_input() const;
    ActionList legal_actions() const;

    std::string str() const;
};

}
