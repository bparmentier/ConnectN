/*! \file ConnectN.h
 * ConnectN class definition
 */

#ifndef CONNECTN_H
#define CONNECTN_H

#include <vector>
#include <array>
#include <string>
#include <sstream>

#include "Player.h"
#include "Color.h"

/*!
 * \brief The ConnectN game
 */
class ConnectN
{
private:
    unsigned _power;
    unsigned _line;
    unsigned _column;
    bool _started;
    bool _finished;
    const Player *_winner;
    const Player *_activePlayer;
    std::array<std::pair<const Player *, Color>, 2> _players;
    std::vector<std::vector<Color>> _board;

    /* Drop piece in the given column */
    int dropPiece(unsigned column, Color color);

    /* Switch active player */
    void switchActivePlayer();

    /* Check if horizontally aligned */
    bool horizontallyAligned(unsigned line, Color color);

    /* Check if vertically aligned */
    bool verticallyAligned(unsigned column, Color color);

    /* Check if aligned in bottom-right to upper-left diagonal: \ */
    bool diagonallyAlignedBRUL(unsigned line, unsigned column, Color color);

    /* Check if aligned in bottom-left to upper-right diagonal: / */
    bool diagonallyAlignedBLUR(unsigned line, unsigned column, Color color);

    /* Check if board is full */
    bool boardIsFull();

public:
    enum {
        DEFAULT_POWER = 4, /*!< Default power */
        DEFAULT_LINE = 6, /*!< Default line */
        DEFAULT_COLUMN = 7 /*!< Default column */
    };

    /*!
     * \brief Minimum allowed power
     */
    static const unsigned MIN_POWER = 3;

    /*!
     * \brief Maximum allowed power
     */
    static const unsigned MAX_POWER = 10;

    /*!
     * \brief Maximum line number depending on the maximum allowed power
     */
    static const unsigned DELTA_LINE = MAX_POWER + 10;

    /*!
     * \brief Maximum column number depending on the maximum allowed power
     */
    static const unsigned DELTA_COLUMN = MAX_POWER + 10;

    /*!
     * \brief Default ConnectN constructor.
     * DEFAULT_POWER, DEFAULT_LINE and DEFAULT_COLUMN are used as default
     * values.
     */
    ConnectN();

    /*!
     * \brief Custom ConnectN constructor
     * \param power number of pieces to align
     * \param line number of lines of the board
     * \param column number of columns of the board
     */
    ConnectN (unsigned power, unsigned line, unsigned column);

    /*!
     * \brief Enroll a player
     * \param player the player to enroll
     * \throw std::invalid_argument if the given player is already enrolled
     * \throw std::logic_error if two players are already enrolled
     */
    void enroll(const Player *player);

    /*!
     * \brief Play at the given column.
     * This method tries to drop a piece in the column given as parameter. If it
     * works, the board is checked to see if N pieces are aligned. If true, the
     * winner is the current player; if not, the other player becomes the
     * current player, and the game continues.
     * \param column the column where to play
     * \throw std::logic_error if
     *   * the game is not started
     *   * the game is finished
     * \throw std::out_of_range if
     *   * the column is full
     *   * the column given as parameter is out of the board
     */
    void play(unsigned column);

    /*!
     * \brief Return the number of pieces to align
     * \return the number of pieces to align
     */
    unsigned power() const;

    /*!
     * \brief Return the number of lines
     * \return the number of lines
     */
    unsigned line() const;

    /*!
     * \brief Return the number of columns
     * \return the number of columns
     */
    unsigned column() const;

    /*!
     * \brief Check if the game is started
     * \return `true` if the game is started, `false`
     * otherwise
     */
    bool started() const;

    /*!
     * \brief Check if the game is finished
     * \return `true` if the game is finished, `false`
     * otherwise
     */
    bool finished() const;

    /*!
     * \brief Return the winner
     * \return the winner if any, `nullptr` otherwise
     */
    const Player * winner() const;

    /*!
     * \brief Return the active player
     * \return the active player if any, `nullptr` otherwise
     */
    const Player * activePlayer() const;

    /*!
     * \brief Return an array of players, associated with their color
     * \return an array of players, associated with their color
     */
    const std::array<std::pair<const Player *, Color>, 2> players() const;

    /*!
     * \brief Return the color of the given player
     * \return the color of the given player
     */
    Color color(const Player *) const;

    /*!
     * \brief Return the game board
     * \return the game board
     */
    const std::vector<std::vector<Color>> &board() const;
};

/*!
 * \brief to_string
 * \param game the game
 * \return the string representation of the ConnectN game
 */
std::string to_string(const ConnectN &game);

/*!
 * \brief ConnectN output stream operator
 * \param out the output stream
 * \param in the ConnectN game
 * \return the string representation of the ConnectN game
 */
std::ostream &operator<<(std::ostream &out, ConnectN in);

#endif // CONNECTN_H
