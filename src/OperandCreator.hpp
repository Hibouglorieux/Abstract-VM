/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandCreator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 03:47:55 by nathan            #+#    #+#             */
/*   Updated: 2021/01/16 05:51:02 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef OPERANDCREATOR_CLASS_H
# define OPERANDCREATOR_CLASS_H
#include "IOperand.hpp"
#include <array>
#include <functional>

class OperandCreator {
public:
	OperandCreator(void);
	OperandCreator( OperandCreator const & copy );
	OperandCreator & operator=( const OperandCreator& rhs );
	virtual ~OperandCreator(void);
	IOperand const * createOperand( eOperandType type, std::string const & value ) const;
private:
	IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createDouble( std::string const & value ) const;
	std::array<std::function<IOperand const * (std::string const &)>, 5> iniFuncArray;
};


#endif
