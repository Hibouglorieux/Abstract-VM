/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVMcontainer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 05:27:23 by nathan            #+#    #+#             */
/*   Updated: 2021/01/16 05:49:49 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AVMcontainer.hpp"

AVMcontainer::AVMcontainer()
{
}

AVMcontainer::~AVMcontainer()
{
	for (IOperator* it : operators)
		delete it;
	opeartors.clear();
}

AVMcontainer::AVMcontainer(AVMcontainer const & copy)
{
	for (IOperator* it : operators)
		delete it;
	opeartors.clear();
	for (IOperator* it : copy.operators)
		operators.push_back(new IOperator(*it));
}

AVMcontainer & operator=(AVMcontainer const & rhs)
{
	*this = AVMcontainer(rhs);
}
