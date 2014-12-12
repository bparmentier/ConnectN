#include <sstream>
#include <string>

#include "Color.h"

std::string to_string(Color color)
{
    std::ostringstream oss;
    oss << color;
    return oss.str();
}

std::ostream &operator<<(std::ostream &out, Color in)
{
    switch (in) {
    case Color::BLACK:
        out << "X";
        break;
    case Color::WHITE:
        out << "O";
        break;
    case Color::NONE:
        out << ' ';
        break;
    default:
        break;
    }

    return out;
}
