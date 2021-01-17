/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVMcontainer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 05:27:23 by nathan            #+#    #+#             */
/*   Updated: 2021/01/17 07:31:02 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AVMcontainer.hpp"
#include <iostream>
#include "Operand.hpp"

AVMcontainer::AVMcontainer()
{
}

AVMcontainer::AVMcontainer(AVMcontainer const & copy)
{
	this->clear();
	for (IOperand const * it : copy.operands)
		operands.push_back(it);
}

AVMcontainer & AVMcontainer::operator=(AVMcontainer const & rhs)
{
	*this = AVMcontainer(rhs);
	return *this;
}

AVMcontainer::~AVMcontainer()
{
}

void AVMcontainer::clear()
{
	for (IOperand const * it : operands)
		delete it;
	operands.clear();
}

void AVMcontainer::setTypeAndValue(std::string& typeAndValue, eOperandType* type, std::string* value)
{
	if (typeAndValue.find("int8"))
		*type = int8;
	if (typeAndValue.find("int16"))
		*type = int16;
	if (typeAndValue.find("int32"))
		*type = int32;
	if (typeAndValue.find("float"))
		*type = float32;
	if (typeAndValue.find("double"))
		*type = double64;
	*value = typeAndValue.erase(0, typeAndValue.find("(") + 1);
	*value = value->erase(value->find(")"));
}

void AVMcontainer::add(std::string typeAndValue)
{
	std::string		value;
	OperandCreator	whatIsAStaticMethod;
	eOperandType	type;

	setTypeAndValue(typeAndValue, &type, &value);
	operands.push_back(whatIsAStaticMethod.createOperand(type, value));
}

void AVMcontainer::pop()
{
	if (!(operands.size()))
	{
		;//TODO throw error
	}
	operands.pop_back();
}

void AVMcontainer::dump()
{
	for (IOperand const * it : operands)
	{
		std::cout << it->toString() << std::endl;
	}
}

void AVMcontainer::assert(std::string typeAndValue)
{
	std::string		value;
	OperandCreator	whatIsAStaticMethod;
	eOperandType	type;

	setTypeAndValue(typeAndValue, &type, &value);
	if (operands.size() == 0)
	{
		; //TODO throw error
	}
	if (type != operands.back()->getType())
	{
		; //TODO throw error
	}
	if (value.compare(operands.back()->toString()))
	{
		; //TODO throw error
	}
}

void AVMcontainer::add()
{
	IOperand const * op1;
	IOperand const * op2;
	if (operands.size() != 2)
	{
		//TODO throw error
	}
	op1 = operands.back();
	operands.pop_back();
	op2 = operands.back();
	operands.pop_back();
	operands.push_back(*op1 + *op2);
}

void AVMcontainer::sub()
{
	IOperand const * op1;
	IOperand const * op2;
	if (operands.size() != 2)
	{
		//TODO throw error
	}
	op1 = operands.back();
	operands.pop_back();
	op2 = operands.back();
	operands.pop_back();
	operands.push_back(*op1 - *op2);
}

void AVMcontainer::mul()
{
	IOperand const * op1;
	IOperand const * op2;
	if (operands.size() != 2)
	{
		//TODO throw error
	}
	op1 = operands.back();
	operands.pop_back();
	op2 = operands.back();
	operands.pop_back();
	operands.push_back(*op1 * *op2);
}

void AVMcontainer::div()
{
	IOperand const * op1;
	IOperand const * op2;
	if (operands.size() != 2)
	{
		//TODO throw error
	}
	op1 = operands.back();
	operands.pop_back();
	op2 = operands.back();
	operands.pop_back();
	operands.push_back(*op1 / *op2);
}

void AVMcontainer::mod()
{
	IOperand const * op1;
	IOperand const * op2;
	if (operands.size() != 2)
	{
		//TODO throw error
	}
	op1 = operands.back();
	operands.pop_back();
	op2 = operands.back();
	operands.pop_back();
	operands.push_back(*op1 % *op2);
}

void AVMcontainer::print()
{
	Operand<char>const * operand;

	if (operands.size() == 0)
	{
		;//TODO throw error
	}

	operand = dynamic_cast<Operand<char> const *>(operands.back());
	if (operand == nullptr)
	{
		;//TODO throw error
	}
	else
	{
		std::cout << (char)operand->nb;
	}
}

void AVMcontainer::exit()
{
}

