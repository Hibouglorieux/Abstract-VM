/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVMcontainer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 05:27:23 by nathan            #+#    #+#             */
/*   Updated: 2021/01/20 09:44:48 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AVMcontainer.hpp"
#include <iostream>
#include "Operand.hpp"
#include "exceptions.hpp"

AVMcontainer::AVMcontainer()
{
	exited = false;
}

AVMcontainer::AVMcontainer(AVMcontainer const & copy)
{
	operands.clear();
	for (IOperand const * it : copy.operands)
		operands.push_back(it);
	exited = copy.exited;
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
	std::cout << typeAndValue << std::endl;
	if (typeAndValue.find("int8") != std::string::npos)
		*type = int8;
	if (typeAndValue.find("int16") != std::string::npos)
		*type = int16;
	if (typeAndValue.find("int32") != std::string::npos)
		*type = int32;
	if (typeAndValue.find("float") != std::string::npos)
		*type = float32;
	if (typeAndValue.find("double") != std::string::npos)
		*type = double64;
	*value = typeAndValue.erase(0, typeAndValue.find("(") + 1);
	*value = value->erase(value->find(")"));
}

void AVMcontainer::push(std::string typeAndValue)
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
		throw(notEnoughStackElem("Pop instruction error : the stack is empty"));
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
	double			assertNb, topNb;


	setTypeAndValue(typeAndValue, &type, &value);

	if (operands.size() == 0)
		throw(notEnoughStackElem("Assert instruction error : the stack is empty"));

	assertNb = strtod(value.c_str(), nullptr);
	topNb = strtod(operands.back()->toString().c_str(), nullptr);

	if (type != operands.back()->getType() && assertNb != topNb)
		throw(assertError("Assert instruction error : top value doesn't have the same type and value"));
	if (type != operands.back()->getType())
		throw(assertError("Assert instruction error : top value doesn't have the same type"));
	if (assertNb != topNb)
		throw(assertError("Assert instruction error : top value doesn't have the same value"));
}

void AVMcontainer::add()
{
	IOperand const * op1;
	IOperand const * op2;
	IOperand const * newelem;

	if (operands.size() == 0)
		throw(notEnoughStackElem("Add instruction error : the stack is empty"));
	if (operands.size() < 2)
		throw(notEnoughStackElem("Add instruction error : not enough elements"));
	op1 = operands.back();
	operands.pop_back();
	op2 = operands.back();
	operands.push_back(op1);
	newelem = *op1 + *op2;
	operands.pop_back();
	operands.pop_back();
	operands.push_back(newelem);
}

void AVMcontainer::sub()
{
	IOperand const * op1;
	IOperand const * op2;
	IOperand const * newelem;

	if (operands.size() == 0)
		throw(notEnoughStackElem("Sub instruction error : the stack is empty"));
	if (operands.size() < 2)
		throw(notEnoughStackElem("Sub instruction error : not enough elements"));
	op1 = operands.back();
	operands.pop_back();
	op2 = operands.back();
	operands.push_back(op1);
	newelem = *op1 - *op2;
	operands.pop_back();
	operands.pop_back();
	operands.push_back(newelem);
}

void AVMcontainer::mul()
{
	IOperand const * op1;
	IOperand const * op2;
	IOperand const * newelem;

	if (operands.size() == 0)
		throw(notEnoughStackElem("Mul instruction error : the stack is empty"));
	if (operands.size() < 2)
		throw(notEnoughStackElem("Mul instruction error : not enough elements"));
	op1 = operands.back();
	operands.pop_back();
	op2 = operands.back();
	operands.push_back(op1);
	newelem = *op1 * *op2;
	operands.pop_back();
	operands.pop_back();
	operands.push_back(newelem);
}

void AVMcontainer::div()
{
	IOperand const * op1;
	IOperand const * op2;
	IOperand const * newelem;

	if (operands.size() == 0)
		throw(notEnoughStackElem("Div instruction error : the stack is empty"));
	if (operands.size() < 2)
		throw(notEnoughStackElem("Div instruction error : not enough elements"));
	op1 = operands.back();
	operands.pop_back();
	op2 = operands.back();
	operands.push_back(op1);
	newelem = *op1 / *op2;
	operands.pop_back();
	operands.pop_back();
	operands.push_back(newelem);
}

void AVMcontainer::mod()
{
	IOperand const * op1;
	IOperand const * op2;
	IOperand const * newelem;

	if (operands.size() == 0)
		throw(notEnoughStackElem("Mod instruction error : the stack is empty"));
	if (operands.size() < 2)
		throw(notEnoughStackElem("Mod instruction error : not enough elements"));
	op1 = operands.back();
	operands.pop_back();
	op2 = operands.back();
	operands.push_back(op1);
	newelem = *op1 % *op2;
	operands.pop_back();
	operands.pop_back();
	operands.push_back(newelem);
}

void AVMcontainer::print()
{
	Operand<char>const * operand;

	if (operands.size() == 0)
		throw(notEnoughStackElem("Print instruction error : the stack is empty"));

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
	this->exited = true;
}

bool AVMcontainer::hasExited() const
{
	return exited;
}
