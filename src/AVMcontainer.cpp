/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVMcontainer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 05:27:23 by nathan            #+#    #+#             */
/*   Updated: 2021/01/16 07:08:30 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AVMcontainer.hpp"

AVMcontainer::AVMcontainer()
{
}

AVMcontainer::AVMcontainer(AVMcontainer const & copy)
{
	for (IOperand* it : operands)
		delete it;
	operands.clear();
	for (IOperand* it : copy.operands)
		operands.push_back(it);
}

AVMcontainer & AVMcontainer::operator=(AVMcontainer const & rhs)
{
	*this = AVMcontainer(rhs);
}

AVMcontainer::~AVMcontainer()
{
}

void AVMcontainer::clear()
{
	for (IOperand* it : operands)
		delete it;
	operands.clear();
}
