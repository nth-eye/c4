## Connect4-cpp
Minimalistic Connect4 game environment which uses bitboards.

### Board representation

'''
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
'''

Last bit represents current player. 0x0 is X and 0x8000000000000000 is O.
