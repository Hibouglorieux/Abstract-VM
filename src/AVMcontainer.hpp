/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AVMcontainer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 05:27:25 by nathan            #+#    #+#             */
/*   Updated: 2021/02/02 15:38:13 by nathan           ###   ########.fr       */
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
	void setTypeAndValue(std::string& typeAndValue, eOperandType* type, std::string* value);
	void push(std::string typeAndValue);
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
	void clear(void);// to be called once done with the object to free mem
	bool isInDebug() const;

	//bonus
	void min();
	void max();
	void pow();
	void debug();
private:
	bool inDebug;
	std::vector<IOperand const *> operands;
};

#endif
