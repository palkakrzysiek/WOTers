#ifndef STRUCTURAL_ELEMENTS_H
#define STRUCTURAL_ELEMENTS_H
// vim: set ts=2 sw=2:
enum Element {EMPTY = 0, ACTIVE = 1, INACTIVE = 2};
enum {BLACK = 0, WHITE = 255};
enum {FG = WHITE, BG = BLACK};
const int NUM_OF_STRUCTURAL_ELEMENTS = 9;
const uint8_t STRUCTURAL_ELEMENT[NUM_OF_STRUCTURAL_ELEMENTS][3][3] = {
  { // 0
    {0, 0, 0},
    {2, 1, 2},
    {1, 1, 1}
  },
  { // 1
    {2, 0, 0},
    {1, 1, 0},
    {1, 1, 2}
  },
  { // 2
    {1, 2, 0},
    {1, 1, 0},
    {1, 2, 0}
  },
  { // 3
    {1, 1, 2},
    {1, 1, 0},
    {2, 0, 0}
  },
  { // 4
    {1, 1, 1},
    {2, 1, 2},
    {0, 0, 0}
  },
  { // 5
    {2, 1, 1},
    {0, 1, 1},
    {0, 0, 2}
  },
  { // 6
    {0, 2, 1},
    {0, 1, 1},
    {0, 2, 1}
  },
  { // 7
    {0, 0, 2},
    {0, 1, 1},
    {2, 1, 1}
  },
  { // 8
    {2, 1, 2},
    {1, 1, 1},
    {2, 1, 2}
  }
};

#endif
