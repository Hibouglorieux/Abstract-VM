/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 00:03:05 by nathan            #+#    #+#             */
/*   Updated: 2021/01/21 10:04:23 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IOperand.hpp"
#include "Operand.hpp"
#include <iostream>
#include "readAVM.hpp"
#include "AVMcontainer.hpp"
#include "exceptions.hpp"
#include <functional>

int		main(int argc, char* argv[])
{
	AVMcontainer container;
	std::function<void()>	executeProgram;
	if (argc > 1)
		executeProgram = [&container, &argv]{readAVM::readFile(argv[1], container);};
	else
		executeProgram = [&container]{readAVM::readInput(container);};
	try
	{
		executeProgram();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	container.clear();
	return (0);
}
