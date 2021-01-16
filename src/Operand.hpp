/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 01:55:05 by nathan            #+#    #+#             */
/*   Updated: 2021/01/16 05:41:55 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_CLASS_H
# define OPERAND_CLASS_H
#include "IOperand.hpp"
#include "OperandCreator.hpp"

enum eOperandPrecision
{
	charPrecision = 3,
	shortPrecision = 5,
	intPrecision = 10,
	floatPrecision = 39,
	doublePrecision = 309
};

template <typename T>
class Operand : public IOperand, private OperandCreator{
public:
	Operand(std::string const & value);
	Operand(Operand<T> const & copy);
	Operand<T>& operator=(Operand<T> const & rhs);
	virtual int 			getPrecision(void) const;
	virtual eOperandType 	getType(void) const;

	virtual IOperand const* operator+( IOperand const& rhs ) const;
	virtual IOperand const* operator-( IOperand const& rhs ) const;
	virtual IOperand const* operator*( IOperand const& rhs ) const;
	virtual IOperand const* operator/( IOperand const& rhs ) const;
	virtual IOperand const* operator%( IOperand const& rhs ) const;

	virtual std::string const& toString( void ) const;

	virtual ~Operand(void);
	T nb;
private:
	eOperandPrecision precision;
	std::string asString;
	eOperandType type;
	Operand(void) = delete;

};
#include "Operand.tpp"

#endif
