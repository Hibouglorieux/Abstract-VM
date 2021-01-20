/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 00:03:05 by nathan            #+#    #+#             */
/*   Updated: 2021/01/20 09:42:52 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IOperand.hpp"
#include "Operand.hpp"
#include <iostream>
#include "readAVM.hpp"
#include "AVMcontainer.hpp"
#include "exceptions.hpp"

int		main(int argc, char* argv[])
{
	AVMcontainer container;
	readAVM::readFile("example.avm", container);
	if (!container.hasExited())
		throw exitError("Error: the program doesn't have an exit instruction");
	container.clear();
	return (0);
}
