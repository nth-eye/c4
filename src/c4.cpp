#include "c4.h"

namespace c4 {

namespace {

constexpr auto generate_bottom_top()
{
    std::array<uint64_t, 7> bottom = {};
    std::array<uint64_t, 7> top = {};

    for (int i = 0; i < 7; ++i) {
        bottom[i] = 1ULL << (7*i);
        top[i] = 1ULL << (5 + 7*i);
    }
    return std::make_pair(bottom, top);
}

// Could use structured bindings if they were constexpr >:|
constexpr auto pair = generate_bottom_top();
constexpr auto BOTTOM = pair.first;
constexpr auto TOP = pair.second;

// Idea taken from https://stackoverflow.com/questions/4261332/optimization-chance-for-following-bit-operations
// Thanks to Ben Jackson
bool haswon(uint64_t board)
{
    uint64_t y = board & (board >> 6);
    uint64_t z = board & (board >> 7);
    uint64_t w = board & (board >> 8);
    uint64_t x = board & (board >> 1);
    return  (y & (y >> 2 * 6)) | // check \ diagonal
            (z & (z >> 2 * 7)) | // check - horizontal
            (w & (w >> 2 * 8)) | // check / diagonal
            (x & (x >> 2));      // check | vertical
}

} // namespace

void Game::reset() 
{
    history.clear();
    all = TURN;
    current = 0;
    history.emplace_back(all, current);
}

void Game::test() 
{
    std::cout << str() << std::endl;

    while (result() == EMPTY) {
        std::cout << "\nMake move: " << std::flush;
        auto move = ask_input();
        act(move);
        std::cout << str() << std::endl;
    };
}

uint64_t Game::result() const
{
    // Define player who just made move.
    auto player = all ^ current;

    if (haswon(player))
        return player & TURN;

    if ((all & BOARD) == BOARD)
        return DRAW;

    return EMPTY;
}

bool Game::legal(Action col) const 
{
    if (col < 0 || col >= 7)
        return false;

    return (all & TOP[col]) == 0;
}

float Game::reward() const
{
    switch (result()) {
        case X:
        case O: return 1.0f;
        default: return 0.0f;
    }
}

float Game::act(Action col)
{
    current ^= all;
    all |= all + BOTTOM[col];

    history.emplace_back(all, current);

    return reward();
}

Action Game::ask_input() const
{
    Action move = NO_MOVE;
    while (true) {
        std::cin >> move;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\nIncorrect input\n" << std::endl;
        } else if (!legal(move)) {
            std::cout << "\nIllegal move\n" << std::endl;
        } else {
            break;
        }
    };
    return move;
}

ActionList Game::legal_actions() const
{
    ActionList moves;

    for (int i = 0; i < 7; ++i)
        if (!(all & TOP[i]))
            moves.push_back(i);

    return moves;
}

std::string Game::str() const
{
    std::stringstream ss;
    ss << '\n';

    char p1 = (current & TURN) == X ? 'X' : 'O';
    char p2 = p1 == 'X' ? 'O' : 'X';

    for (int row = 5; row >= 0; --row) {
        ss << '|';
        for (int col = 0; col < 7; ++col) {
            auto mask = (1ULL << (col*7 + row));
            if (current & mask)
                ss << p1;
            else if (all & mask)
                ss << p2;
            else 
                ss << '-';
            ss << '|';
        }
        ss << '\n';
    }
    ss << "\nturn:\t" << p1 << "\nwinner:\t";
    switch (result()) {
        case EMPTY:	ss << '-'; break;
        case X:		ss << 'X'; break;
        case O:		ss << 'O'; break;
        case DRAW:	ss << "draw"; break;
    }
    return ss.str();
}

}
