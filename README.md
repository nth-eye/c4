# c4

Minimalistic Connect4 C++20 game environment which uses as little resources as possible with the help of bitboards. By rewriting `input()` and `print()` functions in `Interface`, the engine can be integrated in any specific environment and device.

## Board representation

```
        +-------------------+
        | 0 0 0 0 0 0 0 0 1 | <-- 63 bit
row 5	| 1 1 1 1 1 1 1 0 0 |
row 4	| 1 1 1 1 1 1 1 0 0 |
row 3	| 1 1 1 1 1 1 1 0 0 |
row 2	| 1 1 1 1 1 1 1 0 0 |
row 1	| 1 1 1 1 1 1 1 0 0 |
row 0	| 1 1 1 1 1 1 1 0 0 | <-- 56 bit
        +-------------------+
          |           |
          0 bit       42 bit
```

Last bit represents current player. 0x0 is X and 0x8000000000000000 is O.

## How to use

```cpp
#include "c4/interface.h"
...
c4::Interface{}.play();
```
