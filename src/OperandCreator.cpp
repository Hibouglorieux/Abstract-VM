/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandCreator.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 03:47:52 by nathan            #+#    #+#             */
/*   Updated: 2021/02/02 19:54:39 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OperandCreator.hpp"
#include "Operand.hpp"// almost cyclic, static not allowed because reasons

OperandCreator::OperandCreator()
{
	iniFuncArray[int8] = [=](std::string const & value){
		return (createInt8(value));
	};
	iniFuncArray[int16] = [=](std::string const & value){
		return (createInt16(value));
	};
	iniFuncArray[int32] = [=](std::string const & value){
		return (createInt32(value));
	};
	iniFuncArray[float32] = [=](std::string const & value){
		return (createFloat(value));
	};
	iniFuncArray[double64] = [=](std::string const & value){
		return (createDouble(value));
	};
}

OperandCreator::OperandCreator(OperandCreator const & copy) : OperandCreator()
{
	(void)copy;
}

OperandCreator& OperandCreator::operator=(const OperandCreator & rhs)
{
	*this = OperandCreator(rhs);
	return *this;
}

OperandCreator::~OperandCreator()
{
}

IOperand const * OperandCreator::createOperand( eOperandType type, std::string const & value ) const
{
	if (type == int8)
		return createInt8(value);
	else if (type == int16)
		return createInt16(value);
	else if (type == int32)
		return createInt32(value);
	else if (type == float32)
		return createFloat(value);
	else
		return createDouble(value);
}

IOperand const * OperandCreator::createInt8( std::string const & value) const
{
	return new Operand<char>(value);
}

IOperand const * OperandCreator::createInt16( std::string const & value) const
{
	return new Operand<short>(value);
}

IOperand const * OperandCreator::createInt32( std::string const & value) const
{
	return new Operand<int>(value);
}

IOperand const * OperandCreator::createFloat( std::string const & value) const
{
	return new Operand<float>(value);
}

IOperand const * OperandCreator::createDouble( std::string const & value) const
{
	return new Operand<double>(value);
}
