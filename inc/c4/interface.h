#ifndef C4INTERFACE_H
#define C4_INTERFACE_H

#include "c4/engine.h"
#include <cstdio>

namespace c4 {

struct Interface : public Engine {

    void play()
    {
        print();
        while (result() == EMPTY) {
            act(input());
            print();
        };
    }

    void print() const
    {
        puts("\n");
        char p1 = turn() == X ? 'O' : 'X';
        char p2 = turn() == X ? 'X' : 'O';
        char c;
        for (int row = 5; row >= 0; --row) {
            printf("|");
            for (int col = 0; col < 7; ++col) {
                auto mask = bit(col * 7 + row);
                if (mask & opp)
                    c = p1;
                else if (mask & all)
                    c = p2;
                else 
                    c = ' ';
                printf("%c|", c);
            }
            printf("\n");
        }
        printf("\n");
        printf("turn:   %c \n", p2);
        printf("result: ");
        switch (result()) {
            case EMPTY:	c = '?'; break;
            case X:		c = 'X'; break;
            case O:		c = 'O'; break;
            case DRAW:	c = '='; break;
        }
        printf("%c \n\n", c);
    }

    Move input() const
    {
        long long move = -1;

        while (true) {
            printf("\nMake move: ");
            int result = scanf("%lld", &move);
            if (result == EOF || !result)
                puts("\nIncorrect input");
            else if (!legal(move))
                puts("\nIllegal move");
            else
                break;
            while (fgetc(stdin) != '\n');
        };
        return move;
    }
};

}

#endif