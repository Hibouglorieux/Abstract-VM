/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AOperand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 03:47:55 by nathan            #+#    #+#             */
/*   Updated: 2021/01/16 04:13:06 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AOPERAND_CLASS_H
# define AOPERAND_CLASS_H
#include "IOperand.hpp"

class OperandCreator {
public:
	AOperand();
	IOperand const * createOperand( eOperandType type, std::string const & value ) const;
	~AOperand(void){};
private:
	void initialize();
	IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createDouble( std::string const & value ) const;
	std::array<std::function<IOperand const * (std::string const &), 5>> iniFuncArray;
};


#endif
