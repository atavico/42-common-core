/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:49:35 by atarsi            #+#    #+#             */
/*   Updated: 2023/01/20 18:37:11 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

# include <string>
# include <iostream>

class Fixed
{
    private:
            int                 _fixed;
            static const int    _fbits = 8;
    public:
            Fixed (void);
            Fixed (const Fixed &src);
            ~Fixed (void);
            Fixed   &operator=(const Fixed &other);
            int     getRawBits (void) const;
            void    setRawBits (int const raw);
};

#endif