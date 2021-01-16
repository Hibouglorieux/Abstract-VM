/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AOperand.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 03:47:52 by nathan            #+#    #+#             */
/*   Updated: 2021/01/16 04:11:35 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AOperand.hpp"

AOperand::AOperand()
{
	iniFuncArray[int8] = createInt8;
	iniFuncArray[int16] = createInt16;
	iniFuncArray[int32] = createInt32;
	iniFuncArray[float32] = createFloat;
	iniFuncArray[double64] = createDouble;
}

IOperand const * AOperand::createOperand( eOperandType type, std::string const & value ) const
{
	if (type == int8)
		return createInt8(value);
	else if (type == int16)
		return createInt16(value);
	else if (type == int32)
		return createInt32(value);
	else if (type == float32)
		return createFloat(value);
	else if (type == double64)
		return createDouble(value);
	//TODO throw error here
}
