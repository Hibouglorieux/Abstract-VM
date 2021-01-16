/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readAVM.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 05:24:57 by nathan            #+#    #+#             */
/*   Updated: 2021/01/16 05:50:55 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef READAVM_CLASS_H
# define READAVM_CLASS_H
#include <stack>
#include <string>

class readAVM {
public:
	static void readFile(std::string fileName, std::stack<IOperator*>);
private:
	~readAVM(void);
};

#endif
