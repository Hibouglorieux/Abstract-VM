/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readAVM.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 05:24:57 by nathan            #+#    #+#             */
/*   Updated: 2021/01/20 09:20:07 by nathan           ###   ########.fr       */
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
	static void readFile(std::string fileName, AVMcontainer& avmContainer);
	static void readLine(std::string line, AVMcontainer& avmContainer, int lineNumber = 0);
	static void executeLine(std::string line, AVMcontainer& avmContainer);
private:
	static void verifyGlobalSyntax(std::stringstream& wholeFile);
	static void verifyLine(std::string line, int lineNumber);
	readAVM(void) = delete;
	readAVM(readAVM const & copy) = delete;
	readAVM & operator=(readAVM const & rhs) = delete;
	~readAVM(void);
	static bool isReadingFile;
};

#endif
