/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVMcontainer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 05:27:25 by nathan            #+#    #+#             */
/*   Updated: 2021/01/17 07:21:40 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef AVMCONTAINER_CLASS_H
# define AVMCONTAINER_CLASS_H
#include <vector>
#include "IOperand.hpp"
#include "OperandCreator.hpp"

#define INSTR "push (VALUE)|pop|dump|assert (VALUE)|add|sub|mul|div|mod|print|exit"
class AVMcontainer {
public:
	AVMcontainer(void);
	AVMcontainer(AVMcontainer const & copy);
	AVMcontainer & operator=(AVMcontainer const & rhs);
	~AVMcontainer(void);
	void setTypeAndValue(std::string& typeAndValue, eOperandType* type, std::string* value);
	void add(std::string typeAndValue);
	void pop();
	void dump();
	void assert(std::string typeAndValue);
	void add();
	void sub();
	void mul();
	void div();
	void mod();
	void print();
	void exit();
	void clear(void);
private:
	std::vector<IOperand const *> operands;
};

#endif
