/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 00:03:05 by nathan            #+#    #+#             */
/*   Updated: 2021/02/02 15:56:30 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "readAVM.hpp"
#include "AVMcontainer.hpp"
#include "exceptions.hpp"
#include <functional>
#include <sstream>

int		main(int argc, char* argv[])
{
	AVMcontainer container;
	std::function<void()>	executeProgram;

	if (argc > 1)
	{
		executeProgram = [&container, &argv]{
			std::stringstream program = readAVM::openFile(argv[1]);
			readAVM::readProgram(program, container);};
	}
	else
	{
		executeProgram = [&container]{
			std::stringstream program = readAVM::readInput();
			readAVM::readProgram(program, container);};
	}
	try {
		executeProgram();
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	container.clear();
	return (0);
}
