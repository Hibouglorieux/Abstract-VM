/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptions.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 09:31:16 by nathan            #+#    #+#             */
/*   Updated: 2021/01/20 09:24:57 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exceptions.hpp"
#include <sstream>
#define OVERFLOW_MSG "Overflow error : "
#define UNDERFLOW_MSG "Underflow error: "

std::string formatError(std::string msg, std::string typeOfNumber, std::string number)
{
	return msg + std::string("Trying to assign ") + number + " as " + typeOfNumber;
}

overflowError::overflowError(std::string typeOfNumber, std::string number) : std::overflow_error(formatError(OVERFLOW_MSG, typeOfNumber, number))
{ }

overflowError::~overflowError()
{ }

underflowError::underflowError(std::string typeOfNumber, std::string number) : std::underflow_error(formatError(UNDERFLOW_MSG, typeOfNumber, number))
{ }

underflowError::~underflowError()
{ }

notEnoughStackElem::notEnoughStackElem(std::string msg) : std::runtime_error(msg) 
{ }

notEnoughStackElem::~notEnoughStackElem()
{ }

assertError::assertError(std::string msg) : std::runtime_error(msg) 
{ }

assertError::~assertError()
{ }

arythmeticError::arythmeticError(std::string msg) : std::runtime_error(msg) 
{ }

arythmeticError::~arythmeticError()
{ }

parsingError::parsingError(std::string msg) : std::runtime_error(msg) 
{ }

parsingError::~parsingError()
{ }

exitError::exitError(std::string msg) : std::runtime_error(msg) 
{ }

exitError::~exitError()
{ }
