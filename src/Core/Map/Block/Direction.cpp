#include "Core/Map/Block/Direction.h"

Block::Direction::Direction(std::string s)
{
    if (s == "Right")
        dir = Right;
    else if (s == "Up")
        dir = Up;
    else if (s == "Left")
        dir = Left;
    else if (s == "Down")
        dir = Down;
    else
        dir = None;
}

Block::Direction::Direction(D d) : dir(d)
{
}

Block::Direction Block::Direction::rotate()
{
    Block::Direction tmp = *this;
    tmp.dir = (D)(((int)tmp.dir + 1) % 4);
    return tmp;
}

Block::Direction Block::Direction::reverse()
{
    return rotate().rotate();
}

std::string Block::Direction::getStr() const
{
    switch (dir)
    {
    case Right:
        return "Right";
    case Up:
        return "Up";
    case Left:
        return "Left";
    case Down:
        return "Down";
    default:
        return "None";
    }
}

Block::Direction::operator int() const
{
    return (int)dir;
}

// bool operator==(const Block::Direction &a, const Block::Direction::D &b) {
// return a.dir == b;
//}

Block::Direction::Direction(int i) {
    dir = (D)i;
}
