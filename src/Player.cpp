#include "Player.h"

Player::Player(const std::string &name) :
    _name(name)
{ }

const std::string &Player::name() const
{
    return _name;
}
