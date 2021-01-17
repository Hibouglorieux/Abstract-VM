/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 00:03:05 by nathan            #+#    #+#             */
/*   Updated: 2021/01/17 07:35:29 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IOperand.hpp"
#include "Operand.hpp"
#include <iostream>
#include "readAVM.hpp"
#include "AVMcontainer.hpp"

int		main(int argc, char* argv[])
{
	Operand<int> i("43.5");
	Operand<float> a("19");
	IOperand const* pouet = i + a;

	AVMcontainer container;
	readAVM::readFile("example.avm", container);
	return (0);
}
