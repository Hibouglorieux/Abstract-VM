/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVMcontainer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 05:27:25 by nathan            #+#    #+#             */
/*   Updated: 2021/01/16 07:07:54 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef AVMCONTAINER_CLASS_H
# define AVMCONTAINER_CLASS_H
#include <vector>
#include "IOperand.hpp"
#include "OperandCreator.hpp"

class AVMcontainer {
public:
	AVMcontainer(void);
	AVMcontainer(AVMcontainer const & copy);
	AVMcontainer & operator=(AVMcontainer const & rhs);
	~AVMcontainer(void);
	void clear(void);
private:
	std::vector<IOperand*> operands;
};

#endif
