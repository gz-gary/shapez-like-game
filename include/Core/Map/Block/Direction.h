#ifndef __DIRECTION_H__
#define __DIRECTION_H__

#include <string>

namespace Block
{
class Direction
{

  public:
    typedef enum
    {
        Right = 0,
        Up = 1,
        Left = 2,
        Down = 3,
        None
    } D;

    D dir;

    Direction(std::string);
    Direction(D d);
    Direction(int i);
    Direction rotate();
    Direction reverse();
    std::string getStr() const;
    operator int() const;

    // friend bool operator==(const Direction &a, const Direction::D &b);
};

} // namespace Block

struct PipeLisObj {
    int x, y;
    Block::Direction dir_frm, dir_to;
};

// bool operator==(const Block::Direction &a, const Block::Direction::D &b);

#endif
