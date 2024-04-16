/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:03:35 by atarsi            #+#    #+#             */
/*   Updated: 2023/03/24 15:29:48 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"
#include "Character.hpp"
#include "Ice.hpp"
#include "Cure.hpp"

int main(void) {
	IMateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());
	ICharacter* me = new Character("me");
	AMateria* tmp;

	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);

	ICharacter* bob = new Character("bob");

	me->use(0, *bob);
	me->use(1, *bob);

	delete bob;
	delete me;
	delete src;

	std::cout << "PERSONAL TESTS (DROPPING)" << std::endl;

	ICharacter *jason = new Character("jason");
	ICharacter *target = new Character("target");
	IMateriaSource *ms = new MateriaSource();
	ms->learnMateria(new Ice());
	ms->learnMateria(new Cure());

	AMateria *AM;

	AM = ms->createMateria("ice");
	jason->equip(AM);
	AM = ms->createMateria("cure");
	jason->equip(AM);
	AM = ms->createMateria("ice");
	jason->equip(AM);

	jason->use(0, *target);
	jason->use(1, *target);
	jason->use(2, *target);

	jason->unequip(0);
	jason->unequip(1);
	jason->unequip(2);

	delete jason;
	delete target;
	delete ms;

	return (0);
}