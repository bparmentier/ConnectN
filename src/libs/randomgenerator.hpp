/*!
 * \file randomgenerator.hpp
 * \brief Définitions de fonctions conviviales pour générer des séquences
 *        pseudo-aléatoires.
 */

#ifndef RANDOMGENERATOR_HPP
#define RANDOMGENERATOR_HPP

#include <random>
#include <limits>
#include <stdexcept>
#include <ctime>

/*!
 * \brief Espace de nom de Nicolas Vansteenkiste.
 *
 */
namespace nvs
{

// fonctions template

/*!
 * \brief Générateur d'entiers aléatoires.
 *
 * Il s'agit d'une distribution entière uniforme.
 *
 * The effect is undefined if T is not one of : short, int, long,
 * long long, unsigned short, unsigned int, unsigned long, or
 * unsigned long long.
 *
 * \param min la valeur minimale pouvant être retournée.
 * \param max la valeur maximale pouvant être retournée.
 *
 * \return un entier entre <tt>min</tt> et <tt>max</tt>.
 *
 * \exception std::invalid_argument si <tt>min</tt> > <tt>max</tt>.
 *
 * \author nvs
 * \version 0.3
 * \date 2014
 */
template<typename T>
T random_integer(T min = std::numeric_limits<T>::min(),
                 T max = std::numeric_limits<T>::max())
{
    if (min > max)
    {
        throw std::invalid_argument {__func__};
    }

    static std::uniform_int_distribution<T> distribution;

    if (distribution.min() != min || distribution.max() != max)
    {
        distribution.param(
            typename decltype(distribution)::param_type {min, max});
    }

    //    static std::mt19937 engine
    //    {
    //        static_cast<typename decltype(engine)::result_type>(
    //            std::time(nullptr))
    //    };

    static std::mt19937 engine(std::time(nullptr));

    return distribution(engine);
}

} // namespace nvs

#endif // RANDOMGENERATOR_HPP
