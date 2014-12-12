#include <ostream>
#include <iomanip>
#include <sstream>
#include "ConnectN.h"
#include "libs/randomgenerator.hpp"

ConnectN::ConnectN() :
    ConnectN(DEFAULT_POWER, DEFAULT_LINE, DEFAULT_COLUMN)
{ }

ConnectN::ConnectN(unsigned power, unsigned line, unsigned column) :
    _power(power),
    _line(line),
    _column(column),
    _started(false),
    _finished(false),
    _winner(nullptr),
    _activePlayer(nullptr),
    _players{{{ nullptr, Color::NONE }, { nullptr, Color::NONE }}},
    _board{line, std::vector<Color>{column, Color::NONE}}
{
    if (power < MIN_POWER || power > MAX_POWER) {
        throw std::out_of_range("Power must be comprised between 3 and 10");
    }
    if (column < MIN_POWER || column > DELTA_COLUMN
            || line < MIN_POWER || line > DELTA_LINE) {
        throw std::out_of_range("Line/column must be comprised between POWER and POWER + 10");
    }
}

void ConnectN::enroll(const Player *player)
{
    if (_players[0].first == nullptr) {
        _players[0].first = player;
    } else if (_players[1].first == nullptr) {
        if (player == _players[0].first) {
            throw std::invalid_argument("Player is already enrolled");
        } else {
            _players[1].first = player;
            if (nvs::random_integer(0, 1)) {
                _players[0].second = Color::WHITE;
                _players[1].second = Color::BLACK;
            } else {
                _players[0].second = Color::BLACK;
                _players[1].second = Color::WHITE;
            }
            _started = true;
            _activePlayer = _players[nvs::random_integer(0, 1)].first;
        }
    } else {
        throw std::logic_error("Too much players");
    }
}

void ConnectN::play(unsigned column)
{
    int line;
    if (!started()) {
        throw std::logic_error("Game not yet started");
    }
    if (finished()) {
        throw std::logic_error("Game already finished");
    }
    Color activeColor = color(activePlayer());
    if ((line = dropPiece(column, activeColor)) != -1) {
        if (horizontallyAligned(line, activeColor)
                || verticallyAligned(column, activeColor)
                || diagonallyAlignedBRUL(line, column, activeColor)
                || diagonallyAlignedBLUR(line, column, activeColor)) {
            _winner = _activePlayer;
            _finished = true;
        } else if (boardIsFull()) {
            _finished = true;
        }
        switchActivePlayer();
    } else {
        throw std::out_of_range("Can't play here");
    }
}

int ConnectN::dropPiece(unsigned column, Color color)
{
    int lineDropped = -1;
    bool added = false;
    if (column < _column) {
        unsigned line = _line;
        Color *cell;
        while (line > 0 && !added) {
            cell = &_board.at(line - 1).at(column);
            if (*cell == Color::NONE) {
                *cell = color;
                lineDropped = line - 1;
                added = true;
            }
            line--;
        }
    }

    return lineDropped;
}

void ConnectN::switchActivePlayer()
{
    if (_activePlayer == _players[0].first) {
        _activePlayer = _players[1].first;
    } else {
        _activePlayer = _players[0].first;
    }
}

bool ConnectN::horizontallyAligned(unsigned line, Color color)
{
    bool found = false;
    unsigned counter = 0;
    unsigned currentColumn = 0;

    while (!found && currentColumn < _column) {
        if (_board.at(line).at(currentColumn) == color) {
            counter++;
        } else {
            counter = 0;
        }
        if (counter == _power) {
            found = true;
        }
        currentColumn++;
    }

    return found;
}

bool ConnectN::verticallyAligned(unsigned column, Color color)
{
    bool found = false;
    unsigned counter = 0;
    int currentLine = _line - 1;

    while (!found && currentLine >= 0) {
        if (_board.at(currentLine).at(column) == color) {
            counter++;
        } else {
            counter = 0;
        }
        if (counter == _power) {
            found = true;
        }
        currentLine--;
    }

    return found;
}

bool ConnectN::diagonallyAlignedBRUL(unsigned line, unsigned column, Color color)
{
    bool found = false;
    unsigned counter = 0;
    int currentLine = line;
    int currentColumn = column;

    /* go to the bottom-right cell of the diagonal */
    while ((currentLine < _line - 1) && (currentColumn < _column - 1)) {
        currentLine++;
        currentColumn++;
    }

    /* go back up to the upper-left cell by checking if there are N aligned
     * pieces
     */
    while (!found && currentLine >= 0 && currentColumn >= 0) {
        if (_board.at(currentLine).at(currentColumn) == color) {
            counter++;
            if (counter == _power) {
                found = true;
            }
        } else {
            counter = 0;
        }
        currentLine--;
        currentColumn--;
    }

    return found;
}

bool ConnectN::diagonallyAlignedBLUR(unsigned line, unsigned column, Color color)
{
    bool found = false;
    unsigned counter = 0;
    int currentLine = line;
    int currentColumn = column;

    /* go to the bottom-left cell of the diagonal */
    while ((currentLine < _line - 1) && (currentColumn >= 0)) {
        currentLine++;
        currentColumn--;
    }

    /* go back up to the upper-right cell by checking if there are N aligned
     * pieces
     */
    while (!found && currentLine >= 0 && currentColumn < _column) {
        if (_board.at(currentLine).at(currentColumn) == color) {
            counter++;
            if (counter == _power) {
                found = true;
            }
        } else {
            counter = 0;
        }
        currentLine--;
        currentColumn++;
    }

    return found;
}

bool ConnectN::boardIsFull()
{
    bool isFull = true;
    unsigned line = 0;
    unsigned column = 0;

    while (isFull && line < _line) {
        while (isFull && column < _column) {
            if (_board.at(line).at(column) == Color::NONE) {
                isFull = false;
            }
            column++;
        }
        line++;
    }

    return isFull;
}

unsigned ConnectN::power() const
{
    return _power;
}

unsigned ConnectN::line() const
{
    return _line;
}

unsigned ConnectN::column() const
{
    return _column;
}

bool ConnectN::started() const
{
    return _started;
}

bool ConnectN::finished() const
{
    return _finished;
}

const Player * ConnectN::winner() const
{
    return _winner;
}

const Player * ConnectN::activePlayer() const
{
    return _activePlayer;
}

const std::array<std::pair<const Player *, Color>, 2> ConnectN::players() const
{
    return _players;
}

Color ConnectN::color(const Player *player) const
{
    if (player == _players[0].first) {
        return _players[0].second;
    } else if (player == _players[1].first) {
        return _players[1].second;
    } else {
        throw std::runtime_error("Unknown player");
    }
}

const std::vector<std::vector<Color>> &ConnectN::board() const
{
    return _board;
}

std::string to_string(const ConnectN &game)
{
    std::ostringstream oss;
    oss << game;
    return oss.str();
}

std::ostream &operator<<(std::ostream &out, ConnectN in) {
    /* Top indices */
    for (unsigned column = 0; column < in.column(); column++) {
        out << std::setw(3) << column << ' ';
    }
    out << std::endl;

    /* Board */
    for (unsigned i = 0; i < in.column() * 4 + 1; i++) {
        if (i % 4 == 0)
            out << '|';
        else
            out << '-';
    }
    out << std::endl;

    for (auto line : in.board()) {
        out << "| ";
        for (auto cell : line) {
            out << cell << " | ";
        }
        out << std::endl;
        for (unsigned i = 0; i < in.column() * 4 + 1; i++) {
            if (i % 4 == 0)
                out << '|';
            else
                out << '-';
        }
        out << std::endl;
    }

    /* Bottom indices */
    for (unsigned column = 0; column < in.column(); column++) {
        out << std::setw(3) << column << ' ';
    }
    out << std::endl;

    return out;
}
