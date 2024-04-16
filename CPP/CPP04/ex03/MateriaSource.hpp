/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:51:53 by atarsi            #+#    #+#             */
/*   Updated: 2023/03/19 12:21:39 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIASOURCE_HPP
# define MATERIASOURCE_HPP

# include <iostream>
# include "IMateriaSource.hpp"
# include "AMateria.hpp"

class MateriaSource: public IMateriaSource
{
public:
	MateriaSource(void);
	MateriaSource(const MateriaSource &src);
	~MateriaSource(void);

	MateriaSource	&operator=(const MateriaSource &other);
	
	virtual void		learnMateria(AMateria *materia_to_learn);
	virtual AMateria	*createMateria(std::string const & type);
	//void				printMaterias(void) const;
private:
	AMateria		*(_inventory[4]);
};

 #endif