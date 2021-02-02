/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVMcontainer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 05:27:23 by nathan            #+#    #+#             */
/*   Updated: 2021/02/02 15:38:10 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AVMcontainer.hpp"
#include <iostream>
#include "Operand.hpp"
#include "exceptions.hpp"

AVMcontainer::AVMcontainer()
{
	inDebug = false;
}

AVMcontainer::AVMcontainer(AVMcontainer const & copy)
{
	operands.clear();
	for (IOperand const * it : copy.operands)
		operands.push_back(it);
	inDebug = copy.inDebug;
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
	inDebug = false;
}

void AVMcontainer::setTypeAndValue(std::string& typeAndValue, eOperandType* type, std::string* value)
{
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
	IOperand const * toDel = operands.back();
	operands.pop_back();
	delete toDel;
}

void AVMcontainer::dump()
{
	for (auto it = operands.rbegin(); it != operands.rend(); it++)
	{
		std::cout << (*it)->toString() << std::endl;
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
	newelem = *op2 + *op1;
	operands.pop_back();
	operands.pop_back();
	delete op1;
	delete op2;
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
	newelem = *op2 - *op1;
	operands.pop_back();
	operands.pop_back();
	delete op1;
	delete op2;
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
	newelem = *op2 * *op1;
	operands.pop_back();
	operands.pop_back();
	delete op1;
	delete op2;
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
	newelem = *op2 / *op1;
	operands.pop_back();
	operands.pop_back();
	delete op1;
	delete op2;
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
	newelem = *op2 % *op1;
	operands.pop_back();
	operands.pop_back();
	delete op1;
	delete op2;
	operands.push_back(newelem);
}

void AVMcontainer::print()
{
	Operand<char> const * operand;
	if (operands.size() == 0)
		throw(notEnoughStackElem("Print instruction error : the stack is empty"));

	operand = dynamic_cast<Operand<char>const *>(operands.back());
	if (!operand)
		throw printError("Print instruction error : type isn't a 8-bit integer");
	if (operand->nb < 0)
		throw printError("Print instruction error : top element doesnt contain an ascii value");
	else
	{
		std::cout << operand->nb;
	}
}

void AVMcontainer::min()
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
	operands.pop_back();

	newelem = op2->min(*op1);
	delete op1;
	delete op2;
	operands.push_back(newelem);
}

void AVMcontainer::max()
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
	operands.pop_back();

	newelem = op2->max(*op1);
	delete op1;
	delete op2;
	operands.push_back(newelem);
}

void AVMcontainer::pow()
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

	newelem = op2->pow(*op1);

	operands.pop_back();
	operands.pop_back();
	delete op1;
	delete op2;
	operands.push_back(newelem);
}

void AVMcontainer::debug()
{
	inDebug = true;
}

bool AVMcontainer::isInDebug() const
{
	return inDebug;
}
