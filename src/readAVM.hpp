/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readAVM.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 05:24:57 by nathan            #+#    #+#             */
/*   Updated: 2021/01/21 10:13:40 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef READAVM_CLASS_H
# define READAVM_CLASS_H
#include <stack>
#include <string>
#include "IOperand.hpp"
#include "AVMcontainer.hpp"

class readAVM {
public:
	static void readFile(std::string fileName, AVMcontainer& container);
	static void readLine(std::string line, AVMcontainer& container);
	static void readInput(AVMcontainer& container);
private:
	static void executeLine(std::string line, AVMcontainer& container);
	static void verifyGlobalSyntax(std::stringstream& wholeFile);
	static void verifyLine(std::string line);
	readAVM(void) = delete;
	readAVM(readAVM const & copy) = delete;
	readAVM & operator=(readAVM const & rhs) = delete;
	~readAVM(void);
	static bool isReadingFile;
};

#endif
