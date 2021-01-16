/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 00:03:05 by nathan            #+#    #+#             */
/*   Updated: 2021/01/16 05:19:02 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IOperand.hpp"
#include "Operand.hpp"
#include <iostream>

int		main(int argc, char* argv[])
{
	Operand<int> i("43.5");
	Operand<float> a("19");
	IOperand const* pouet = i + a;

	std::cout << a.toString() << std::endl;
	std::cout << i.toString() << std::endl;
	std::cout << pouet->toString() << std::endl;
	return (0);
}
