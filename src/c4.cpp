#include <cstdio>
#include <array>
#include "c4.h"

constexpr Bitboard bit(int i) { return 1ul << i; }

constexpr bool haswon(Bitboard board)
{
    Bitboard y = board & (board >> 6);
    Bitboard z = board & (board >> 7);
    Bitboard w = board & (board >> 8);
    Bitboard x = board & (board >> 1);
    return  (y & (y >> 2 * 6)) | // check \ diagonal
            (z & (z >> 2 * 7)) | // check - horizontal
            (w & (w >> 2 * 8)) | // check / diagonal
            (x & (x >> 2));      // check | vertical
}

template<bool Top>
constexpr auto generate()
{
    std::array<Bitboard, 7> arr = {};

    for (int i = 0; i < 7; ++i)
        arr[i] = bit(5 * Top + 7 * i);

    return arr;
}

constexpr auto BOTTOM   = generate<false>();
constexpr auto TOP      = generate<true>();

void C4::print() const
{
    puts("\n");

    char p1 = (current & TURN) == X ? 'X' : 'O';
    char p2 = (current & TURN) == X ? 'O' : 'X';
    char c;

    for (int row = 5; row >= 0; --row) {

        printf("|");

        for (int col = 0; col < 7; ++col) {

            Bitboard mask = bit(col * 7 + row);

            if (current & mask)
                c = p1;
            else if (all & mask)
                c = p2;
            else 
                c = '-';

            printf("%c|", c);
        }
        printf("\n");
    }
    printf("\n");
    printf("turn:   %c \n", p1);
    printf("result: ");

    switch (result()) {
        case EMPTY:	c = '?';    break;
        case X:		c = 'X';    break;
        case O:		c = 'O';    break;
        case DRAW:	c = '-';    break;
    }
    printf("%c \n\n", c);
}

void C4::play() 
{
    print();

    while (result() == EMPTY) {
        Move move = ask_input();
        make_move(move);
        print();
    };
}

void C4::reset() 
{
    all     = TURN;
    current = 0;
}

void C4::make_move(Move col)
{
    current ^= all;
    all     |= all + BOTTOM[col];
}

bool C4::legal(Move col) const 
{
    if (col > 6)
        return false;

    return !(all & TOP[col]);
}

Bitboard C4::result() const
{
    auto player = all ^ current;

    if (haswon(player))
        return player & TURN;

    if ((all & BOARD) == BOARD)
        return DRAW;

    return EMPTY;
}

Move C4::ask_input() const
{
    long long move = -1;

    while (true) {

        printf("\nMake move: ");

        int result = scanf("%lld", &move);

        if (result == EOF || !result) {
            puts("\nIncorrect input");
        } else if (!legal(move)) {
            puts("\nIllegal move");
        } else {
            break;
        }
        while (fgetc(stdin) != '\n');
    };
    return move;
}

MoveList C4::moves() const
{
    MoveList moves;

    for (int i = 0; i < 7; ++i)
        if (!(all & TOP[i]))
            moves.save(i);

    return moves;
}
