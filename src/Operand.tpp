/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.tpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 01:50:49 by nathan            #+#    #+#             */
/*   Updated: 2021/02/02 15:07:59 by nathan           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include <sstream>
#include <cmath>// fmod && pow
#include <cstdlib> // strtod
#include <limits>
#include "exceptions.hpp"
#include <cxxabi.h>// good type for overflows
#include <fenv.h>// see values of pow

template <typename T>
Operand<T>::Operand(std::string const & value)
{
	double maxVal = HUGE_VAL;
	double minVal = -HUGE_VAL;
	double tmpNb = strtod(value.c_str(), nullptr);
	asString = value;


	if (tmpNb == HUGE_VAL)
		throw(overflowError(abi::__cxa_demangle(typeid(T).name(), 0, 0, nullptr), value));
	if (tmpNb == -HUGE_VAL)
		throw(underflowError(abi::__cxa_demangle(typeid(T).name(), 0, 0, nullptr), value));
	if (std::is_same<T, char>::value)
	{
		maxVal = std::numeric_limits<char>::max();
		minVal = std::numeric_limits<char>::min();
		type = int8;
		precision = charPrecision;
	}
	if (std::is_same<T, short>::value)
	{
		maxVal = std::numeric_limits<short>::max();
		minVal = std::numeric_limits<short>::min();
		type = int16;
		precision = shortPrecision;
	}
	if (std::is_same<T, int>::value)
	{
		maxVal = std::numeric_limits<int>::max();
		minVal = std::numeric_limits<int>::min();
		type = int32;
		precision = intPrecision;
	}
	if (std::is_same<T, float>::value)
	{
		maxVal = std::numeric_limits<float>::max();
		minVal = -std::numeric_limits<float>::max();
		type = float32;
		precision = floatPrecision;
	}
	if (std::is_same<T, double>::value)
	{
		type = double64;
		precision = doublePrecision;
	}
	if (tmpNb > maxVal)
		throw(overflowError(abi::__cxa_demangle(typeid(T).name(), 0, 0, nullptr), value));
	if (tmpNb < minVal)
		throw(underflowError(abi::__cxa_demangle(typeid(T).name(), 0, 0, nullptr), value));
	nb = tmpNb;
}

template <typename T>
Operand<T>::Operand(Operand<T> const & copy)
{
	this->nb = copy.nb;
	this->type = copy.type;
	this->asString = copy.string;
	this->precision = copy.precision;
}

template <typename T>
Operand<T> & Operand<T>::operator=(const Operand<T>& rhs)
{
	*this = Operand(rhs);
}

template <typename T>
Operand<T>::~Operand()
{
}

template <typename T>
int	Operand<T>::getPrecision() const
{
	return precision;
}

template <typename T>
eOperandType Operand<T>::getType() const
{
	return type;
}

template <typename T>
IOperand const* Operand<T>::operator+( IOperand const& rhs) const
{
	std::string newValue;
	double		newNb;
	std::stringstream ss;
	eOperandType newType = precision < rhs.getPrecision() ? rhs.getType() : type;

	ss << rhs.toString();
	ss >> newNb;

	ss.str(std::string());// clear
	ss.clear();

	newNb = this->nb + newNb;
	ss << newNb;
	newValue = ss.str();
	return createOperand(newType, newValue);
}

template <typename T>
IOperand const* Operand<T>::operator-( IOperand const& rhs) const
{
	std::string newValue;
	double		newNb;
	std::stringstream ss;
	eOperandType newType = precision < rhs.getPrecision() ? rhs.getType() : type;

	ss << rhs.toString();
	ss >> newNb;

	ss.str(std::string());// clear
	ss.clear();

	newNb = this->nb - newNb;
	ss << newNb;
	newValue = ss.str();
	return createOperand(newType, newValue);
}

template <typename T>
IOperand const* Operand<T>::operator*( IOperand const& rhs) const
{
	std::string newValue;
	double		newNb;
	std::stringstream ss;
	eOperandType newType = precision < rhs.getPrecision() ? rhs.getType() : type;

	ss << rhs.toString();
	ss >> newNb;

	ss.str(std::string());// clear
	ss.clear();

	newNb = this->nb * newNb;
	ss << newNb;
	newValue = ss.str();
	return createOperand(newType, newValue);
}

template <typename T>
IOperand const* Operand<T>::operator/( IOperand const& rhs) const
{
	std::string newValue;
	double		newNb;
	std::stringstream ss;
	eOperandType newType = precision < rhs.getPrecision() ? rhs.getType() : type;

	ss << rhs.toString();
	ss >> newNb;

	ss.str(std::string());// clear
	ss.clear();

	if (newNb == 0)
		throw(arythmeticError("Arythmetic error : division by 0"));
	if (type < float32 && (int)nb % (int)newNb)
		newType = float32;
	newNb = this->nb / newNb;
	ss << newNb;
	newValue = ss.str();
	return createOperand(newType, newValue);
}

template <typename T>
IOperand const* Operand<T>::operator%( IOperand const& rhs) const
{
	std::string newValue;
	double		newNb;
	std::stringstream ss;
	eOperandType newType = precision < rhs.getPrecision() ? rhs.getType() : type;

	ss << rhs.toString();
	ss >> newNb;

	ss.str(std::string());// clear
	ss.clear();

	if (newNb == 0)
		throw(arythmeticError("Arythmetic error : modulo by 0"));
	if (type > int32)
	{
		newNb = fmod((double)this->nb, (double)newNb);
	}
	else
	{
		newNb = (int)this->nb % (int)newNb;
	}
	ss << newNb;
	newValue = ss.str();
	return createOperand(newType, newValue); }

template <typename T>
IOperand const* Operand<T>::max( IOperand const& rhs ) const
{
	eOperandType newType = precision > rhs.getPrecision() ? rhs.getType() : this->type;
	IOperand const* target;
	std::stringstream ss;
	double rhsNb;

	ss << rhs.toString();
	ss >> rhsNb;
	target = rhsNb > (double)this->nb ? &rhs : this;
	return createOperand(newType, target->toString());
}

template <typename T>
IOperand const* Operand<T>::min( IOperand const& rhs ) const
{
	eOperandType newType = precision < rhs.getPrecision() ? rhs.getType() : this->type;
	IOperand const* target;
	std::stringstream ss;
	double rhsNb;

	ss << rhs.toString();
	ss >> rhsNb;
	target = rhsNb < (double)this->nb ? &rhs : this;
	return createOperand(newType, target->toString());
}

template <typename T>
IOperand const* Operand<T>::pow( IOperand const& rhs ) const
{
	double rhsNb;
	eOperandType newType = precision < rhs.getPrecision() ? rhs.getType() : this->type;
	std::stringstream ss;
	std::string newValue;
	double result;

	ss << rhs.toString();
	ss >> rhsNb;

	ss.str(std::string());// clear
	ss.clear();

	feclearexcept(FE_ALL_EXCEPT);
	result = std::pow((double)this->nb, rhsNb);
	
	ss << result;
	newValue = ss.str();

	if (fetestexcept(FE_INVALID))
		throw arythmeticError("Arythmetic error : base is negative and exponent not an integer");
	if (fetestexcept(FE_DIVBYZERO))
		throw arythmeticError("Arythmetic error : division by 0");
	if (fetestexcept(FE_OVERFLOW))
		throw overflowError(abi::__cxa_demangle(typeid(double).name(), 0, 0, nullptr), newValue);
	if (fetestexcept(FE_UNDERFLOW))
		throw overflowError(abi::__cxa_demangle(typeid(double).name(), 0, 0, nullptr), newValue);

	return createOperand(newType, newValue);
}

template <typename T>
std::string const & Operand<T>::toString() const
{
	return asString;
}
