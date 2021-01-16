/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avm.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 06:01:23 by nathan            #+#    #+#             */
/*   Updated: 2021/01/16 04:06:12 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef AVM_CLASS_H
# define AVM_CLASS_H

#include <stack>
#include "IOperand.hpp"

class avm {
public:
	avm(void);
	~avm(void);
private:
	std::stack<IOperand*> operands;
};

#endif
