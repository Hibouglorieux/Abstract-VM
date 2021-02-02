/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 06:08:38 by nathan            #+#    #+#             */
/*   Updated: 2021/02/02 14:29:57 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef IOPERAND_CLASS_H
# define IOPERAND_CLASS_H

#include <string>
enum eOperandType
{
	int8 = 0,
	int16 = 1,
	int32 = 2,
	float32 = 3,
	double64 = 4
};

class IOperand {
public:
	virtual int 			getPrecision(void) const = 0;// Precision of the type of the instance
	virtual eOperandType 	getType(void) const = 0;// Type of the instance

	virtual IOperand const* operator+( IOperand const& rhs ) const = 0;// Sum
	virtual IOperand const* operator-( IOperand const& rhs ) const = 0;// Difference
	virtual IOperand const* operator*( IOperand const& rhs ) const = 0;// Product
	virtual IOperand const* operator/( IOperand const& rhs ) const = 0;// Quotient
	virtual IOperand const* operator%( IOperand const& rhs ) const = 0;// Modulo

	virtual std::string const& toString( void )const= 0;// String representation of the instance

	virtual ~IOperand(void) {}

	//Bonus
	virtual IOperand const* max( IOperand const& rhs ) const = 0;
	virtual IOperand const* min( IOperand const& rhs ) const = 0;
	virtual IOperand const* pow( IOperand const& rhs ) const = 0;
};

#endif
