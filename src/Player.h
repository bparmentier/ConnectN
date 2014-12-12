/*! \file Player.h
 * Player class definition
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "Color.h"

class ConnectN;

/*!
 * \brief A ConnectN player
 */
class Player
{
private:
    const std::string _name;

public:
    /*!
     * \brief Player constructor
     * \param name the name of the player
     */
    Player(const std::string &name);

    /*!
     * \brief Return the name of the player
     * \return the name of the player
     */
    const std::string &name() const;
};

#endif // PLAYER_H
