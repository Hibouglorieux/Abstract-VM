/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.tpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 01:50:49 by nathan            #+#    #+#             */
/*   Updated: 2021/01/17 07:32:34 by nathan           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include <sstream>
#include <cmath>// fmod
#include <cstdlib> // strtod
#include <limits>

/*
template <typename T>
Operand<T>::Operand()
{
	nb = 0;
	type = int8;
	asString = "0";
	precision = charPrecision;
}
*/

template <typename T>
Operand<T>::Operand(std::string const & value)
{
	double maxVal = HUGE_VAL;
	double minVal = -HUGE_VAL;
	nb = strtod(value.c_str(), nullptr);
	asString = value;

	if (nb == HUGE_VAL)
	{
		;//throw error
	}
	if (nb == -HUGE_VAL)
	{
		;//throw error
	}
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
		minVal = std::numeric_limits<float>::min();
		type = float32;
		precision = floatPrecision;
	}
	if (std::is_same<T, double>::value)
	{
		type = double64;
		precision = doublePrecision;
	}
	if (nb > maxVal)
	{
		;//TODO throw error
	}
	if (nb < minVal)
	{
		;//TODO throw error
	}
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

#include <iostream>

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

	//TODO check if 0
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

	//TODO check if 0
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
	return createOperand(newType, newValue);
}

template <typename T>
std::string const & Operand<T>::toString() const
{
	return asString;
}
