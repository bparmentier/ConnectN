/*! \file Color.h
 * Color enum class definition
 */

#ifndef COLOR_H
#define COLOR_H

#include <ostream>
#include <string>

/*!
 * \brief The Color enum class
 * \enum Color
 */
enum class Color {
    NONE, /*!< an empty color */
    BLACK, /*!< a black piece */
    WHITE /*!< a white piece */
};

/*!
 * \brief to_string
 * \param color the color
 * \return the string representation of the color
 */
std::string to_string(Color color);

/*!
 * \brief Color output stream operator
 * \param out the output stream
 * \param in the color
 * \return the string representation of the color
 */
std::ostream &operator<<(std::ostream &out, Color in);

#endif // COLOR_H
